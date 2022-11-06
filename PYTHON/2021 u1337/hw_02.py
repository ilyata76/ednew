""" Домашнее задание № 2 """

# Необходимые определения
from operator import add, mul, sub

square = lambda x: x * x
identity = lambda x: x
triple = lambda x: 3 * x
increment = lambda x: x + 1

# Вопрос 1.

def product(n, term):
    """
    Возвращает произведение первых n членов (terms) последовательности.
    
    Аргументы:
        n (int): количество перемножаемых элементов последовательности.
        term (func): функция одного аргумента.

    >>> product(3, identity)  # 1 * 2 * 3
    6
    >>> product(5, identity)  # 1 * 2 * 3 * 4 * 5
    120
    >>> product(3, square)    # 1^2 * 2^2 * 3^2
    36
    >>> product(5, square)    # 1^2 * 2^2 * 3^2 * 4^2 * 5^2
    14400
    >>> product(3, increment) # (1+1) * (2+1) * (3+1)
    24
    >>> product(3, triple)    # 1*3 * 2*3 * 3*3
    162
    """

    int_mul = 1

    if n == 0:
        return 0

    while n != 0 :
        int_mul *= term(n)
        n -= 1

    return int_mul

def factorial(n):
    """
    Возвращает факториал n при n >= 0, используя функцию product.

    >>> factorial(4)  # 4 * 3 * 2 * 1
    24
    >>> factorial(6)  # 6 * 5 * 4 * 3 * 2 * 1
    720
    """
    return product(n, identity)

# Вопрос 2.

def accumulate(combiner, base, n, term):
    """
    Возвращает результат объединения (combining) первых n членов последовательности.

    >>> accumulate(add, 0, 5, identity)  # 0 + 1 + 2 + 3 + 4 + 5
    15
    >>> accumulate(add, 11, 5, identity) # 11 + 1 + 2 + 3 + 4 + 5
    26
    >>> accumulate(add, 11, 0, identity) # 11
    11
    >>> accumulate(add, 11, 3, square)   # 11 + 1^2 + 2^2 + 3^2
    25
    >>> accumulate(mul, 2, 3, square)    # 2 * 1^2 * 2^2 * 3^2
    72
    >>> accumulate(lambda x, y: x + y + 1, 2, 3, square)
    19
    """
    
    int_result = base

    while n != 0:
        int_result = combiner(int_result, term(n))
        n -= 1

    return int_result



def summation_using_accumulate(n, term):
    """
    Возвращает сумму term(1) + ... + term(n). Реализация с использованием accumulate.

    >>> summation_using_accumulate(5, square)
    55
    >>> summation_using_accumulate(5, triple)
    45
    """
    return accumulate(add, 0, n, term)

def product_using_accumulate(n, term):
    """
    Возвращает произведение term(1) * ... * term(n). Реализация с использованием accumulate.

    >>> product_using_accumulate(3, lambda x: (x+1)*(x+5)*x)
    48384
    >>> product_using_accumulate(4, square)
    576
    >>> product_using_accumulate(6, triple)
    524880
    """
    return accumulate(mul, 1, n, term)

# Вопрос 3.

def double(f):
    """
    Возвращает функцию, применяющую f дважды.

    Аргументы:
        f (func): функция одного аргумента.

    >>> double(square)(2)
    16
    """

    def h(x) :
        return f(f(x))

    return h

# Вопрос 4.

def make_repeater(f, n):
    """Возвращает функцию, применяющую f n раз.

    Аргументы:
        f (func): функция одного аргумента.
        n (int): количество применений функции f.
        
    >>> add_three = make_repeater(increment, 3)
    >>> add_three(5)
    8
    >>> make_repeater(triple, 5)(1) # 3 * 3 * 3 * 3 * 3 * 1
    243
    >>> make_repeater(square, 2)(5) # square(square(5))
    625
    >>> make_repeater(square, 4)(5) # square(square(square(square(5))))
    152587890625
    >>> make_repeater(square, 0)(5) # Да, применение функции ноль раз тоже имеет смысл! 
    5
    """

    def h (x) :

        if n == 0:
            return x

        o = f(x)
        
        int_j = n

        while int_j != 1 and int_j != 0:
            o = f(o)
            int_j -= 1

        return o

    return h


def compose1(f, g):
    """Возвращает функцию h такую, что h(x) = f(g(x))."""
    def h(x):
        return f(g(x))
    return h

# Вопрос 5.

def zero(f):
    return lambda x: x

def successor(n):
    return lambda f: lambda x: f(n(f)(x))

def one(f):
    """Число Чёрча 1."""
    return lambda x: f(x)

def two(f):
    """Число Чёрча 2."""
    return lambda x: f(f(x))

three = successor(two)

def church_to_int(n):
    """Преобразует число Чёрча n в целое число Python.

    >>> church_to_int(zero)
    0
    >>> church_to_int(one)
    1
    >>> church_to_int(two)
    2
    >>> church_to_int(three)
    3
    """
    def h(x) :
        return x + 1

    def o(x) :
        return n(h)(x)

    return o(0)

def add_church(m, n):
    """Возвращает число Чёрча m + n для чисел Чёрча m и n.

    >>> church_to_int(add_church(two, three))
    5
    """

    int_j = church_to_int(n)
    while int_j != 0 :
        m = successor(m)
        int_j -= 1

    return m

    # и как это сделать по-человечески? : как-то повзаимодействовать одной функцией на другую?

def mul_church(m, n):
    """Возвращает число Чёрча m * n для чисел Чёрча m и n.

    >>> four = successor(three)
    >>> church_to_int(mul_church(two, three))
    6
    >>> church_to_int(mul_church(three, four))
    12
    """
    return lambda x : n(m(x))

def pow_church(m, n):
    """Возвращает число Чёрча m ** n для чисел Чёрча m и n.

    >>> church_to_int(pow_church(two, three))
    8
    >>> church_to_int(pow_church(three, two))
    9
    """
    int_j = church_to_int(n)
    fun_res = m

    while int_j != 1 :
        fun_res = mul_church(fun_res, m)
        int_j -= 1 

    return fun_res