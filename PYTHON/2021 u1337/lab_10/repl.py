try:
    import readline  # история ввода и поддержка стрелочек для CLI
except ImportError:
    pass  # есть не у всех
import sys

from reader import read
from expr import global_env

# начало программы
if __name__ == '__main__':
    """Запускает REPL.
    `python3 repl.py` полноценный запуск REPL.
    `python3 repl.py --read` только считывание и парсинг без выполнения.
    """
    read_only = len(sys.argv) == 2 and sys.argv[1] == '--read'

    while True:
        try:
            # `input` печатает > , ожидает ввода и возвращает ввод пользователя.
            user_input = input('> ')
            expr = read(user_input)
            if expr is not None:
                if read_only:
                    print(repr(expr))
                else:
                    print(expr.eval(global_env))
        except (SyntaxError, NameError, TypeError, ZeroDivisionError, KeyError, OverflowError, RuntimeError) as err:
            print(type(err).__name__ + ':', err)
        except (KeyboardInterrupt, EOFError):  # Ctrl-C, Ctrl-D
            print()  # пустая строка
            break  # выход из цикла while (и из программы)