"""Фреймворк модульного тестирования для Scheme-интерпретатора.

Использование: python3 scheme_test.py <файл>

Выполняет <файл> как будто содержимое файла водится в интерпретатор Scheme,
сравнивает каждую выводимую интерпретатором строку с ожидаемой (описанной в
комментарии).

Например,

(display (+ 2 3))
; expect 5

При нахождении расхождений выводит номера строк.
"""

import io
import sys
from buffer import Buffer
from scheme import read_eval_print_loop, create_global_frame
from scheme_tokens import tokenize_lines

def summarize(output, expected_output):
    """Суммирует результаты запущенных тестов."""
    num_failed, num_expected = 0, len(expected_output)

    def failed(expected, actual, line):
        nonlocal num_failed
        num_failed += 1
        print('тест провален в строке', line)
        print('   ожидал', expected)
        print('  получил', actual)

    for (actual, (expected, line_number)) in zip(output, expected_output):
        if expected.startswith("Error"):
            if not actual.startswith("Ошибка"):
                failed('an error indication', actual, line_number)
        elif actual != expected:
            failed(expected, actual, line_number)
    print('{0} тестов; {1} провалено.'.format(num_expected, num_failed))

EXPECT_STRING = '; expect'

class TestReader:
    """TestReader итеративно собирает ожидаемые результаты тестов."""
    def __init__(self, lines, stdout):
        self.lines = lines
        self.stdout = stdout
        self.last_out_len = 0
        self.output = []
        self.expected_output = []
        self.line_number = 0

    def __iter__(self):
        for line in self.lines:
            line = line.rstrip('\n')
            self.line_number += 1
            if line.lstrip().startswith(EXPECT_STRING):
                expected = line.split(EXPECT_STRING, 1)[1][1:].split(' ; ')
                for exp in expected:
                    self.expected_output.append((exp, self.line_number))
                out_lines = self.stdout.getvalue().split('\n')
                if len(out_lines) > self.last_out_len:
                    self.output.extend(out_lines[-1-len(expected):-1])
                else:
                    self.output.extend([''] * len(expected))
                self.last_out_len = len(out_lines)
            yield line
        raise EOFError

def run_tests(src_file='tests.scm'):
    """Запускает цикл прочитать-выполнить, который считывает строки
    из src_file и получает результаты."""
    sys.stderr = sys.stdout = io.StringIO() # перехватывает вывод в stdout и stderr
    reader = None
    try:
        reader = TestReader(open(src_file).readlines(), sys.stdout)
        src = Buffer(tokenize_lines(reader))
        def next_line():
            src.current()
            return src
        read_eval_print_loop(next_line, create_global_frame())
    except BaseException as exc:
        sys.stderr = sys.__stderr__
        if reader:
            print("Тестирование остановлено из-за неизвестного исключения"
                  "после строки {0}:\n>>>".format(reader.line_number),
                  file=sys.stderr)
        raise
    finally:
        sys.stdout = sys.__stdout__  # восстанавливает stdout
        sys.stderr = sys.__stderr__  # восстанавливает stderr
    summarize(reader.output, reader.expected_output)

if __name__ == '__main__':
    args = sys.argv[1:]
    run_tests(*args)
