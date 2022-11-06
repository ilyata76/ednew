"""Модуль buffer помогает при итерировании по строкам и токенам."""

from __future__ import print_function  # Совместимость с Python 2

import math
import sys

if sys.version_info[0] < 3:  # Совместимость с Python 2
    def input(prompt):
        sys.stderr.write(prompt)
        sys.stderr.flush()
        line = sys.stdin.readline()
        if not line: raise EOFError()
        return line.rstrip('\r\n')

class Buffer(object):
    """Класс Buffer предоставляет способ доступа к токенам в строках.

    Его конструктор принимает итератор SOURCE, который по запросу
    выдаёт следующую строку токенов в виде списка или None
    (если данных больше нет).

    Класс Buffer соединяет последовательности, полученные из source
    и выдает элементы из них (по очереди, один за раз) с помощью метода
    remove_front(), загружая данные из source по мере необходимости.

    В дополнение Buffer предоставляет метод для анализа значения
    следующего элемента без удаления последнего.

    Метод __str__ выводит все токены считанные до текущей позиции
    (до конца текущей) строки, помечая текущий токен с помощью >>.

    >>> buf = Buffer(iter([['(', '+'], [15], [12, ')']]))
    >>> buf.remove_front()
    '('
    >>> buf.remove_front()
    '+'
    >>> buf.current()
    15
    >>> print(buf)
    1: ( +
    2:  >> 15
    >>> buf.remove_front()
    15
    >>> buf.current()
    12
    >>> buf.remove_front()
    12
    >>> print(buf)
    1: ( +
    2: 15
    3: 12 >> )
    >>> buf.remove_front()
    ')'
    >>> print(buf)
    1: ( +
    2: 15
    3: 12 ) >>
    >>> buf.remove_front()  # вернёт None
    """
    def __init__(self, source):
        self.index = 0
        self.lines = []
        self.source = source
        self.current_line = ()
        self.current()

    def remove_front(self):
        """Удаляет следующий элемент из self и возвращает его.
        Если достигнут конец данных, возвращает None."""
        current = self.current()
        self.index += 1
        return current

    def current(self):
        """Возвращает текущий элемент или None (если конец)."""
        while not self.more_on_line:
            self.index = 0
            try:
                self.current_line = next(self.source)
                self.lines.append(self.current_line)
            except StopIteration:
                self.current_line = ()
                return None
        return self.current_line[self.index]

    @property
    def more_on_line(self):
        return self.index < len(self.current_line)

    def __str__(self):
        """Возвращает считанное; текущий элемент помечается с помощью >>."""
        # Форматирование строки для выравнивания номеров строк
        n = len(self.lines)
        msg = '{0:>' + str(math.floor(math.log10(n))+1) + "}: "

        # В вывод включается до трёх предыдущих строк и текущая строка
        s = ''
        for i in range(max(0, n-4), n-1):
            s += msg.format(i+1) + ' '.join(map(str, self.lines[i])) + '\n'
        s += msg.format(n)
        s += ' '.join(map(str, self.current_line[:self.index]))
        s += ' >> '
        s += ' '.join(map(str, self.current_line[self.index:]))
        return s.strip()

# Попытка импорта readline для истории интерактивного ввода
try:
    import readline
except:
    pass

class InputReader(object):
    """InputReader — итерируемый тип, запрашивающий ввод от пользователя.
    """
    def __init__(self, prompt):
        self.prompt = prompt

    def __iter__(self):
        while True:
            yield input(self.prompt)
            self.prompt = ' ' * len(self.prompt)

class LineReader(object):
    """LineReader — итерируемый тип, печатающий строки после промта."""
    def __init__(self, lines, prompt, comment=";"):
        self.lines = lines
        self.prompt = prompt
        self.comment = comment

    def __iter__(self):
        while self.lines:
            line = self.lines.pop(0).strip('\n')
            if (self.prompt is not None and line != "" and
                not line.lstrip().startswith(self.comment)):
                print(self.prompt + line)
                self.prompt = ' ' * len(self.prompt)
            yield line
        raise EOFError