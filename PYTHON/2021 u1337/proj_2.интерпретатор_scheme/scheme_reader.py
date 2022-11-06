"""В этом модуле реализованы встроенные типы данных языка Scheme и
парсер Scheme-выражений.

В дополнение к типам, определенным в этом файле, некоторые типы данных в Scheme
представлены соответствующими типами Python:
    number:       int или float
    symbol:       string
    boolean:      bool
    unspecified:  None

Метод __repr__ Scheme-значения будет возвращать
Python-выражение (когда возможно), которое при
вычислении (на Python) даст это значение.

Метод __str__ Scheme-значения будет возвращать
Scheme-выражение (когда возможно),
которое при вычислении (на Scheme) даст это значение.
"""

from __future__ import print_function  # Совместимость с Python 2

import numbers

from scheme_tokens import tokenize_lines, DELIMITERS
from buffer import Buffer, InputReader, LineReader

# Пары и Scheme-списки

class Pair(object):
    """A pair has two instance attributes: first and second.  For a Pair to be
    a well-formed list, second is either a well-formed list or nil.  Some
    methods only apply to well-formed lists.

    Пара имеет два атрибута: first (первый) и second (второй). Чтобы пара была
    форматным списком требуется, чтобы second был либо форматным списком,
    либо nil. Некоторые методы работают только с форматными списками.

    >>> s = Pair(1, Pair(2, nil))
    >>> s
    Pair(1, Pair(2, nil))
    >>> print(s)
    (1 2)
    >>> print(s.map(lambda x: x+4))
    (5 6)
    """
    def __init__(self, first, second):
        self.first = first
        self.second = second

    def __repr__(self):
        return 'Pair({0}, {1})'.format(repr(self.first), repr(self.second))

    def __str__(self):
        s = '(' + repl_str(self.first)
        second = self.second
        while isinstance(second, Pair):
            s += ' ' + repl_str(second.first)
            second = second.second
        if second is not nil:
            s += ' . ' + repl_str(second)
        return s + ')'

    def __len__(self):
        n, second = 1, self.second
        while isinstance(second, Pair):
            n += 1
            second = second.second
        if second is not nil:
            raise TypeError('вызов len для неформатного списка')
        return n

    def __eq__(self, p):
        if not isinstance(p, Pair):
            return False
        return self.first == p.first and self.second == p.second

    def map(self, fn):
        """Возвращает Scheme-список, содержащий результат применения FN
        к каждому элементу SELF."""
        mapped = fn(self.first)
        if self.second is nil or isinstance(self.second, Pair):
            return Pair(mapped, self.second.map(fn))
        else:
            raise TypeError('неформатный список')

class nil(object):
    """Пустой список"""

    def __repr__(self):
        return 'nil'

    def __str__(self):
        return '()'

    def __len__(self):
        return 0

    def map(self, fn):
        return self

nil = nil() # присвоение скрывает класс nil; доступен только экземпляр

# Парсер Scheme-списков

# Знаки цитирования
quotes = {"'":  'quote',
          '`':  'quasiquote',
          ',':  'unquote'}

def scheme_read(src):
    """Считывает следующее выражение из SRC (буфера токенов).

    >>> scheme_read(Buffer(tokenize_lines(['nil'])))
    nil
    >>> scheme_read(Buffer(tokenize_lines(['1'])))
    1
    >>> scheme_read(Buffer(tokenize_lines(['true'])))
    True
    >>> scheme_read(Buffer(tokenize_lines(['(+ 1 2)'])))
    Pair('+', Pair(1, Pair(2, nil)))
    """
    if src.current() is None:
        raise EOFError

    val = src.remove_front() # Получение первого токена
    if val == 'nil':
        # НАЧАЛО ЗАДАЧИ 1
        return nil
        # КОНЕЦ ЗАДАЧИ 1
    elif val == '(':
        # НАЧАЛО ЗАДАЧИ 1
        return read_tail(src)
        # КОНЕЦ ЗАДАЧИ 1
    elif val in quotes:
        # НАЧАЛО ЗАДАЧИ 7
        src = scheme_read(src)
        return Pair(quotes[val], Pair(src, nil))
        
        
        # КОНЕЦ ЗАДАЧИ 7
    elif val not in DELIMITERS:
        return val
    else:
        raise SyntaxError('неожиданный токен: {0}'.format(val))

def read_tail(src):
    """Возвращает остаток списка в SRC.

    >>> read_tail(Buffer(tokenize_lines([')'])))
    nil
    >>> read_tail(Buffer(tokenize_lines(['2 3)'])))
    Pair(2, Pair(3, nil))
    >>> read_line('(1 . 2)')
    Pair(1, 2)
    """
    try:
        if src.current() is None:
            raise SyntaxError('неожиданный конец файла')
        elif src.current() == ')':
            # НАЧАЛО ЗАДАЧИ 1
            src.remove_front()
            return nil
            # КОНЕЦ ЗАДАЧИ 1
        elif src.current() == '.':
            # НАЧАЛО ЗАДАЧИ 2
            src.remove_front()
            if src.current() == '(' :
                val = scheme_read(src)
            else :
                val = src.remove_front()

            if src.current() == ')' :
                src.remove_front()
            else :
                raise SyntaxError

            return val
            # КОНЕЦ ЗАДАЧИ 2
        else:
            # НАЧАЛО ЗАДАЧИ 1
            first = scheme_read(src)
            second = read_tail(src)
            return Pair(first, second)
            # КОНЕЦ ЗАДАЧИ 1
    except EOFError:
        raise SyntaxError('неожиданный конец файла')

# Вспомогательные методы

def buffer_input(prompt='scm> '):
    """Возвращает экземпляр Buffer содержащий интерактивный ввод."""
    return Buffer(tokenize_lines(InputReader(prompt)))

def buffer_lines(lines, prompt='scm> ', show_prompt=False):
    """Возвращает экземпляр Buffer, получающий данные из строк (LINES)."""
    if show_prompt:
        input_lines = lines
    else:
        input_lines = LineReader(lines, prompt)
    return Buffer(tokenize_lines(input_lines))

def read_line(line):
    """Считывает строку LINE, предполагая, что это Scheme-выражение."""
    return scheme_read(Buffer(tokenize_lines([line])))

def repl_str(val):
    """В основном совпадает со str(val), за исключением булевых значений
    и undefined."""
    if val is True:
        return "#t"
    if val is False:
        return "#f"
    if val is None:
        return "undefined"
    if isinstance(val, numbers.Number) and not isinstance(val, numbers.Integral):
        return repr(val)  # поддержка Python 2
    return str(val)

# Интерактивный цикл
def read_print_loop():
    """Запускает интерактивный цикл считать-напечатать для Scheme-выражений."""
    while True:
        try:
            src = buffer_input('read> ')
            while src.more_on_line:
                expression = scheme_read(src)
                print('str :', expression)
                print('repr:', repr(expression))
        except (SyntaxError, ValueError) as err:
            print(type(err).__name__ + ':', err)
        except (KeyboardInterrupt, EOFError):  # <Control>-D и т.д.
            print()
            return

if __name__ == '__main__':
    import sys
    args = sys.argv[1:]
    if len(args) and '--repl' in args:
        read_print_loop()