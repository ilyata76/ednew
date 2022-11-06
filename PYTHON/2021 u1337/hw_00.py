def my_email():
    """Возвращает строку с твоим e-mail адресом.

    >>> my_email() != 'someone@example.com'
    True
    """
    return 'ilyata76@yandex.ru'

from operator import add, mul

def thirteen_thirty_seven():
    """Нужно придумать самое захватывающее выражение, которое приводит к результату 1337.
    Можно использовать только числа и функции add(. . .) и mul(. . .). Чем длиннее, тем лучше.

    >>> thirteen_thirty_seven()
    1337
    """
    "*** ТВОЙ КОД ЗДЕСЬ ***"
    return add(add(mul(add(add(mul(3, 4) + 1337 + mul(3, 9), mul(3, 9) - 1337 + mul(3, 4)), -1), 13), mul(100, 3)), mul(6, 6))
