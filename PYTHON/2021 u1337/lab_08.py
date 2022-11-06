### Лабораторная работа № 8: Подготовка к контрольной"""

###############################
# Определение связных списков #
###############################

class Link:
    """Связный список.

    >>> s = Link(1)
    >>> s.first
    1
    >>> s.rest is Link.empty
    True
    >>> s = Link(2, Link(3, Link(4)))
    >>> s.second
    3
    >>> s.first = 5
    >>> s.second = 6
    >>> s.rest.rest = Link.empty
    >>> s                                    # Отображает результат repr(s)
    Link(5, Link(6))
    >>> s.rest = Link(7, Link(Link(8, Link(9))))
    >>> s
    Link(5, Link(7, Link(Link(8, Link(9)))))
    >>> print(s)                             # Выводит результат str(s)
    <5 7 <8 9>>
    """
    empty = ()

    def __init__(self, first, rest=empty):
        assert rest is Link.empty or isinstance(rest, Link)
        self.first = first
        self.rest = rest

    @property
    def second(self):
        return self.rest.first

    @second.setter
    def second(self, value):
        self.rest.first = value

    def __repr__(self):
        if self.rest is not Link.empty:
            rest_repr = ', ' + repr(self.rest)
        else:
            rest_repr = ''
        return 'Link(' + repr(self.first) + rest_repr + ')'

    def __str__(self):
        string = '<'
        while self.rest is not Link.empty:
            string += str(self.first) + ' '
            self = self.rest
        return string + str(self.first) + '>'

# Вопрос 1.
def deep_len(lnk, o = 0):
    """Возвращает «глубокий» размер связного списка с возможными вложениями.

    >>> deep_len(Link(1, Link(2, Link(3))))
    3
    >>> deep_len(Link(Link(1, Link(2)), Link(3, Link(4))))
    4
    >>> levels = Link(Link(Link(1, Link(2)), \
            Link(3)), Link(Link(4), Link(5)))
    >>> print(levels)
    <<<1 2> 3> <4> 5>
    >>> deep_len(levels)
    5
    """
    if lnk is Link.empty :
        return 0
    elif lnk is not Link.empty and not isinstance(lnk.first, Link) :
        return 1 + deep_len(lnk.rest)
    elif lnk is not Link.empty and isinstance(lnk.first, Link) :
        op = deep_len(lnk.first)
        return op + deep_len(lnk.rest)
    else :
        pass

# Рекурсия/Древовидная рекурсия
# Вопрос 3.

def insert_into_all(item, nested_list):
    """В предположении, что nested_list — это список списков, возвращает новый
    список, включающий всё, что было в nested_list, но к каждому вложенному
    списку в начало добавляется элемент item.

    >>> nl = [[], [1, 2], [3]]
    >>> insert_into_all(0, nl)
    [[0], [0, 1, 2], [0, 3]]
    """
    int_j = 0
    new_list = []
    while int_j < len(nested_list) :
        new_list.append([item] + nested_list[int_j])
        int_j += 1
    return new_list


def subseqs(s):
    """В предположении, что S является списком, возвращает вложенный список
    всевозможных подпоследовательностей элементов исходного списка.
    Подпоследовательности могут быть добавлены в любом порядке.

    >>> seqs = subseqs([1, 2, 3])
    >>> sorted(seqs)
    [[], [1], [1, 2], [1, 2, 3], [1, 3], [2], [2, 3], [3]]
    >>> subseqs([])
    [[]]
    """
    if len(s) == 0 :
        return [[]]
    else :
        a = insert_into_all(s[0], subseqs(s[1:])) + subseqs(s[1:])
        return a

# Вопрос 4.
def inc_subseqs(s):
    """В предположении, что S является списком, возвращает вложенный список
    всевозможных подпоследовательностей элементов исходного списка, за
    исключением подпоследовательностей с убывающим порядком хотя бы двух
    соседних элементов. Подпоследовательности могут быть добавлены в любом порядке.

    >>> seqs = inc_subseqs([1, 3, 2])
    >>> sorted(seqs)
    [[], [1], [1, 2], [1, 3], [2], [3]]
    >>> inc_subseqs([])
    [[]]
    >>> seqs2 = inc_subseqs([1, 1, 2])
    >>> sorted(seqs2)
    [[], [1], [1], [1, 1], [1, 1, 2], [1, 2], [1, 2], [2]]

    """
    def subseq_helper(s, prev):
        if not s:
            return ____________________
        elif s[0] < prev:
            return ____________________
        else:
            a = ______________________
            b = ______________________
            return insert_into_all(________, ______________) + ________________
    return subseq_helper(____, ____)

# ООП
# Вопрос 5.

class Keyboard:
    """Класс Keyboard принимает некоторое количество кнопок Button, и имеет
    словарь для сопоставления положения кнопок (ключи) и кнопок Button (значения).

    >>> b1 = Button(0, "H")
    >>> b2 = Button(1, "I")
    >>> k = Keyboard(b1, b2)
    >>> k.buttons[0].key
    'H'
    >>> k.press(1)
    'I'
    >>> k.press(2) #Тут нет кнопки
    ''
    >>> k.typing([0, 1])
    'HI'
    >>> k.typing([1, 0])
    'IH'
    >>> b1.times_pressed
    2
    >>> b2.times_pressed
    3

    """

    def __init__(self, *args):
        self.buttons = {}
        for button in args : self.buttons[button.pos] = button

    def press(self, info):
        """Принимает положение нажатой кнопки и возвращает результат"""
        if info in self.buttons :
            self.buttons[info].times_pressed += 1
            return self.buttons[info].key
        else : return ''

    def typing(self, typing_input):
        """Принимает список положений нажатых кнопок и возвращает
        результирующую последовательность результатов нажатий"""
        result = ''
        for item in typing_input :
            result += self.press(item)
        return result

class Button:
    def __init__(self, pos, key):
        self.pos = pos
        self.key = key
        self.times_pressed = 0

# Nonlocal
# Вопрос 6.
def make_advanced_counter_maker():
    """Создаёт функцию, которая создает счётчики, понимающие сообщения
    "count", "global-count", "reset", и "global-reset".

    Смотри на примеры:

    >>> make_counter = make_advanced_counter_maker()
    >>> tom_counter = make_counter()
    >>> tom_counter('count')
    1
    >>> tom_counter('count')
    2
    >>> tom_counter('global-count')
    1
    >>> jon_counter = make_counter()
    >>> jon_counter('global-count')
    2
    >>> jon_counter('count')
    1
    >>> jon_counter('reset')
    >>> jon_counter('count')
    1
    >>> tom_counter('count')
    3
    >>> jon_counter('global-count')
    3
    >>> jon_counter('global-reset')
    >>> tom_counter('global-count')
    1
    """
    global_count = 0
    def foo() :
        count = 0
        nonlocal global_count
        def fu(_str) :
            nonlocal global_count
            nonlocal count
            if _str == 'count' :
                count += 1
                return count
            elif _str == 'global-count' :
                global_count += 1
                return global_count
            elif _str == 'reset' :
                count = 0
            elif _str == 'global-reset' :
                global_count = 0
        return fu
    return foo

# Вопрос 8.
# Списки
def trade(first, second):
    """Производит обмен наименьшими префиксами (подпоследовательностями) списков
    first и second, которые одинаковы по сумме элементов.

    >>> a = [1, 1, 3, 2, 1, 1, 4]
    >>> b = [4, 3, 2, 7]
    >>> trade(a, b) # Меняет 1+1+3+2=7 на 4+3=7
    'По рукам!'
    >>> a
    [4, 3, 1, 1, 4]
    >>> b
    [1, 1, 3, 2, 2, 7]
    >>> c = [3, 3, 2, 4, 1]
    >>> trade(b, c)
    'Нет!'
    >>> b
    [1, 1, 3, 2, 2, 7]
    >>> c
    [3, 3, 2, 4, 1]
    >>> trade(a, c)
    'По рукам!'
    >>> a
    [3, 3, 2, 1, 4]
    >>> b
    [1, 1, 3, 2, 2, 7]
    >>> c
    [4, 3, 1, 4, 1]
    """
    it_m, it_n, it_len = 0, 0, 0
    m, n = first[it_m], second[it_n]
    while m != n:
        if m < n and it_len < len(first):
            it_m += 1
            m = m + first[it_m]
        elif n < m and it_len < len(second):
            it_n += 1
            n = n + second[it_n]
        else :
            break
        it_len += 1
    
    if m == n:
        first[:it_m + 1], second[:it_n + 1] = second[:it_n + 1], first[:it_m + 1]
        return 'По рукам!'
    else:
        return 'Нет!'

# Вопрос 9.
# Генераторы
def permutations(seq):
    """Генерирует все перестановки заданной последовательности. Каждая
    перестановка — это список элементов исходной последовательности в другом
    порядке. Перестановки могут выдаваться в любом порядке.

    >>> perms = permutations([100])
    >>> type(perms)
    <class 'generator'>
    >>> next(perms)
    [100]
    >>> try:
    ...     next(perms)
    ... except StopIteration:
    ...     print('Больше вариантов нет!')
    Больше вариантов нет!
    >>> sorted(permutations([1, 2, 3])) # Возвращает отсортированный список результатов
    [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
    >>> sorted(permutations((10, 20, 30)))
    [[10, 20, 30], [10, 30, 20], [20, 10, 30], [20, 30, 10], [30, 10, 20], [30, 20, 10]]
    >>> sorted(permutations("ab"))
    [['a', 'b'], ['b', 'a']]

    """
    if ____________________:
        yield ____________________
    else:
        for perm in _____________________:
            for _____ in ________________:
                _________________________

# Вопрос 10.
# Рекурсивные объекты
def make_to_string(front, mid, back, empty_repr):
    """ Возвращает функцию, которая преобразует связные списки в строки.

    >>> umputun_to_string = make_to_string("[", "|-]-->", "", "[]")
    >>> bobuk_to_string = make_to_string("(", " . ", ")", "()")
    >>> lst = Link(1, Link(2, Link(3, Link(4))))
    >>> umputun_to_string(lst)
    '[1|-]-->[2|-]-->[3|-]-->[4|-]-->[]'
    >>> umputun_to_string(Link.empty)
    '[]'
    >>> bobuk_to_string(lst)
    '(1 . (2 . (3 . (4 . ()))))'
    >>> bobuk_to_string(Link.empty)
    '()'
    """


    def foo(lnk) :
        if lnk is not Link.empty:
            return front + str(lnk.first) + mid + foo(lnk.rest) + back
        else :
            return empty_repr
    return foo



# Вопрос 10.
def tree_map(fn, t):
    """Применяет функцию fn ко всем элементам дерева t и возвращает новое дерево
    с результатами.

    >>> numbers = Tree(1,
    ...                [Tree(2,
    ...                      [Tree(3),
    ...                       Tree(4)]),
    ...                 Tree(5,
    ...                      [Tree(6,
    ...                            [Tree(7)]),
    ...                       Tree(8)])])
    >>> print(tree_map(lambda x: 2**x, numbers))
    2
      4
        8
        16
      32
        64
          128
        256
    >>> print(numbers)
    1
      2
        3
        4
      5
        6
          7
        8
    """
    def get_tree(t) :
        if t.is_leaf() :
            return Tree(fn(t.label))
        else :
            return Tree(fn(t.label), [get_tree(b) for b in t.branches])
    return get_tree(t)
    
# Вопрос 12.
def long_paths(tree, n):
    """Возвращает список всех путей в дереве, которые не короче n.

    >>> t = Tree(3, [Tree(4), Tree(4), Tree(5)])
    >>> left = Tree(1, [Tree(2), t])
    >>> mid = Tree(6, [Tree(7, [Tree(8)]), Tree(9)])
    >>> right = Tree(11, [Tree(12, [Tree(13, [Tree(14)])])])
    >>> whole = Tree(0, [left, Tree(13), mid, right])
    >>> for path in long_paths(whole, 2):
    ...     print(path)
    ...
    <0 1 2>
    <0 1 3 4>
    <0 1 3 4>
    <0 1 3 5>
    <0 6 7 8>
    <0 6 9>
    <0 11 12 13 14>
    >>> for path in long_paths(whole, 3):
    ...     print(path)
    ...
    <0 1 3 4>
    <0 1 3 4>
    <0 1 3 5>
    <0 6 7 8>
    <0 11 12 13 14>
    >>> long_paths(whole, 4)
    [Link(0, Link(11, Link(12, Link(13, Link(14)))))]
    """
    "*** ТВОЙ КОД ЗДЕСЬ ***"

##############
# Класс Tree #
##############

class Tree:
    """
    >>> t = Tree(3, [Tree(2, [Tree(5)]), Tree(4)])
    >>> t.label
    3
    >>> t.branches[0].label
    2
    >>> t.branches[1].is_leaf()
    True
    """
    def __init__(self, label, branches=[]):
        for b in branches:
            assert isinstance(b, Tree)
        self.label = label
        self.branches = list(branches)

    def is_leaf(self):
        return not self.branches

    def __repr__(self):
        if self.branches:
            branch_str = ', ' + repr(self.branches)
        else:
            branch_str = ''
        return 'Tree({0}{1})'.format(self.label, branch_str)

    def __str__(self):
        def print_tree(t, indent=0):
            tree_str = '  ' * indent + str(t.label) + "\n"
            for b in t.branches:
                tree_str += print_tree(b, indent + 1)
            return tree_str
        return print_tree(self).rstrip()

# def rec(s, ss, it= 0) :
#     if s == ss and it == 0 : lst, int_j, X, Y = [[s[it]]], it + 1, s, [s[it]]
#     else : lst, int_j, X, Y = [s], it + 1, ss, s
#     while int_j < len(X) :
#         lst.append(Y + [None] * (int_j - it - 1) + [X[int_j]])
#         if it == 0: lst.append([None] + [None] * (int_j - it - 1) + [X[int_j]])
#         int_j += 1
#     int_j = 1
#     while int_j < len(lst) :
#         lst[int_j] = rec(s= lst[int_j], ss= ss, it=len(lst[int_j])-1)
#         int_j += 1
#     if it == 0 : return lst
#     else : return sum(lst, ['!'])

# def correct(s) :
#     nlst = [[]]
#     for item in s :
#         if '!' in item:
#             int_j, int_k = 1, 0
#             while int_j < len(item):
#                 if item[int_j] == '!':
#                     nlst.append(item[int_k + 1:int_j])
#                     int_k = int_j
#                 if int_j == len(item) - 1 :
#                     nlst.append(item[int_k + 1:])
#                 int_j += 1
#         else :
#             nlst.append(item)
#     int_j = 0
#     while int_j < len(nlst) :
#         if None in nlst[int_j] :
#             nlst[int_j] = [a for a in nlst[int_j] if a != None]
#         int_j += 1
#     return nlst  
# if s != [] : nlst = rec(s, s, 0); nlst = correct(nlst); return nlst
# else : return [[]]