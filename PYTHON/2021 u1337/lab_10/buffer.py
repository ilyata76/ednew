class Buffer(object):
    """Buffer предоставляет возможность доступа к элементам последовательности по одному.
    Конструктор принимает последовательность "source".
    Buffer поставляет элементы из источника по одному за раз, через метод remove_front().
    В дополнение Buffer предоставляет метод current() чтобы узнать, какой элемент будет
    следующим.
    >>> buf = Buffer(['(', '+', 15, 12, ')'])
    >>> buf.remove_front()
    '('
    >>> buf.remove_front()
    '+'
    >>> buf.current()
    15
    >>> buf.remove_front()
    15
    >>> buf.current()
    12
    >>> buf.remove_front()
    12
    >>> buf.remove_front()
    ')'
    >>> buf.remove_front()  # возвращает None
    """
    def __init__(self, source):
        self.index = 0
        self.source = source

    def remove_front(self):
        """Удаляет следующий элемент из self и возвращает его. Если больше
        элементов нет — возвращает None."""
        current = self.current()
        self.index += 1
        return current

    def current(self):
        """Возвращает текущий элемент или None, если больше элементов не осталось."""
        if self.index >= len(self.source):
            return None
        else:
            return self.source[self.index]

    def expect(self, expected):
        actual = self.remove_front()
        if expected != actual:
            raise SyntaxError("ожидалось '{}', а получено '{}'".format(expected, actual))
        else:
            return actual

    def __str__(self):
        return str(self.source[self.index:])