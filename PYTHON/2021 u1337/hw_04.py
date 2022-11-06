### HW_04: Абстрактные типы данных

# Вопрос 1.
def interval(a, b):
    """Создает интервал от a до b."""
    return [a, b]

def lower_bound(x):
    """Возвращает нижнюю границу интервала x."""
    return x[0]

def upper_bound(x):
    """Возвращает верхнюю границу интервала x."""
    return x[1]

def str_interval(x):
    """Возвращает строковое представление интервала x.

    >>> str_interval(interval(-1, 2))
    'от -1 до 2'
    """
    return f'от {lower_bound(x)} до {upper_bound(x)}'

def add_interval(x, y):
    """Возвращает интервал всевозможных сумм значений из x и y.

    >>> str_interval(add_interval(interval(-1, 2), interval(4, 8)))
    'от 3 до 10'
    """
    lower = lower_bound(x) + lower_bound(y)
    upper = upper_bound(x) + upper_bound(y)
    return interval(lower, upper)

def mul_interval(x, y):
    """Возвращает интервал всевозможных произведений значений из x и y.

    >>> str_interval(mul_interval(interval(-1, 2), interval(4, 8)))
    'от -8 до 16'
    """
    p1 = lower_bound(x) * lower_bound(y)
    p2 = lower_bound(x) * upper_bound(y)
    p3 = upper_bound(x) * lower_bound(y)
    p4 = upper_bound(x) * upper_bound(y)
    return interval(min(p1, p2, p3, p4), max(p1, p2, p3, p4))

# Вопрос 2.
def div_interval(x, y):
    """Возвращает интервал, содержащий частные любых значений из x на 
    любые значения из y.

    Деление реализовано как умножение x на величину, обратную к y.

    >>> str_interval(div_interval(interval(-1, 2), interval(4, 8)))
    'от -0.25 до 0.5'
    """
    assert abs(lower_bound(y) - upper_bound(y)) < lower_bound(y) or abs(lower_bound(y) - upper_bound(y)) < upper_bound(y), 'Делимый интервал не должен пересекать ноль'
    reciprocal_y = interval(1/upper_bound(y), 1/lower_bound(y))
    return mul_interval(x, reciprocal_y)

# Вопрос 3.
def sub_interval(x, y):
    """Возвращает интервал, содержащий разности любых значений из x с 
    любыми значениями из y.

    >>> str_interval(sub_interval(interval(-1, 2), interval(4, 8)))
    'от -9 до -2'
    """
    reciprocal_y = interval(-upper_bound(y),-lower_bound(y))
    return add_interval(x, reciprocal_y)

# Вопрос 4.
def par1(r1, r2):
    return div_interval(mul_interval(r1, r2), add_interval(r1, r2))

def par2(r1, r2):
    one = interval(1, 1)
    rep_r1 = div_interval(one, r1)
    rep_r2 = div_interval(one, r2)
    return div_interval(one, add_interval(rep_r1, rep_r2))

# Вот эти два интервала дают разные результаты при вычислении сопротивления параллельных резисторов:
r1 = interval(1, 1)
r2 = interval(1, 2)

# Вопрос 5.
def multiple_references_explanation():
    return """Проблема множественных ссылок..."""

# Вопрос 6.
def quadratic(x, a, b, c):
    """Возвращает интервал, описывающий область значения квадратичной функции с
    коэффициентами a, b и c для интервала области определения x.

    >>> str_interval(quadratic(interval(0, 2), -2, 3, -1))
    'от -3 до 0.125'
    >>> str_interval(quadratic(interval(1, 3), 2, -3, 1))
    'от 0 до 10'
    """
    x1 = lower_bound(x)
    x2 = upper_bound(x)
    
    def get_fun_value(x) :
        return a * x**2 + b * x + c

    if a > 0 :
        ext = -b / (2 * a)
        f_ext = get_fun_value(ext)

        if ext >= x1 :
            f_d = f_ext
            f_u = get_fun_value(x1) if get_fun_value(x1) > get_fun_value(x2) else get_fun_value(x2)
        else :
            f_d = get_fun_value(x1)
            f_u = get_fun_value(x2)       
        return interval(f_d, f_u)

    elif a < 0 :
        ext = -b / (2 * a)
        f_ext = get_fun_value(ext)

        if ext >= x1 :
            f_u = f_ext
            f_d = get_fun_value(x1) if get_fun_value(x1) < get_fun_value(x2) else get_fun_value(x2)
        else :
            f_u = get_fun_value(x1)
            f_d = get_fun_value(x2)

        return interval(f_d, f_u)
    else :
        f_d = get_fun_value(x1) if b > 0 else get_fun_value(x2)
        f_u = get_fun_value(x2) if b > 0 else get_fun_value(x1)
        return interval(f_d, f_u)

# Вопрос 7.
def polynomial(x, c):
    """Возвращает интервал, описывающий область значения полиномиальной функции с
    коэффициентами c для интервала области определения x.

    >>> str_interval(polynomial(interval(0, 2), [-1, 3, -2]))
    'от -3 до 0.125'
    >>> str_interval(polynomial(interval(1, 3), [1, -3, 2]))
    'от 0 до 10'
    >>> str_interval(polynomial(interval(0.5, 2.25), [10, 24, -6, -8, 3]))
    'от 18.0 до 23.0'
    """

    def get_polynominal_fun_value(c) :
        def fun_x(x) :
            int_j, result = 0, 0
            while int_j < len(c) :
                result += c[int_j] * pow(x, int_j)
                int_j += 1
            return result
        return fun_x

    def create_poly_list_for_d(c) :
        int_j, lst = 0, []
        while int_j < len(c) :
            if int_j > 0 :
                lst.append(c[int_j] * int_j)
            int_j += 1
        return lst

    upper, lower, int_j, offset1, offset2, extremums = 0, 0, 0, 1, 1, []

    while int_j < len(create_poly_list_for_d(c)) :

        extremums += [
            find_zero(
                f = get_polynominal_fun_value(create_poly_list_for_d(c)),
                df = get_polynominal_fun_value(create_poly_list_for_d(create_poly_list_for_d(c))),
                guess= offset1 + 0.1
        ),
            find_zero(
                f = get_polynominal_fun_value(create_poly_list_for_d(c)),
                df = get_polynominal_fun_value(create_poly_list_for_d(create_poly_list_for_d(c))),
                guess= offset2 - 0.1
            )
        ]
        
        offset1, offset2 = extremums[0 + int_j], extremums[1 + int_j]
        print(offset1, offset2)
        print(extremums)
        int_j += 1


    get_fun_falue = get_polynominal_fun_value(c)
    extremums = [i for i in extremums if (i >= lower_bound(x) and i <= lower_bound(x))]

    int_i = 0
    while int_i < len(extremums) :
        if int_i == 0 :
            upper, lower = get_fun_falue(extremums[int_i]), get_fun_falue(extremums[int_i])
        else :
            if upper < get_fun_falue(extremums[int_i]) :
                upper = get_fun_falue(extremums[int_i])
            if lower > get_fun_falue(extremums[int_i]) :
                lower = get_fun_falue(extremums[int_i])
        int_i += 1

    return interval(
        min(lower, get_fun_falue(lower_bound(x)), get_fun_falue(upper_bound(x))),
        max(upper, get_fun_falue(lower_bound(x)), get_fun_falue(upper_bound(x)))
        )







# Метод Ньютона (вдруг пригодится)

def improve(update, close, guess=1, max_updates=100):
    """Итеративно улучшает guess с помощью update, пока close(guess) является ложью или
    количество итераций меньше max_updates."""
    k = 0
    while not close(guess) and k < max_updates:
        guess = update(guess)
        k = k + 1
    return guess

def approx_eq(x, y, tolerance=1e-15):
    return abs(x - y) < tolerance

def find_zero(f, df, guess=1):
    """Возвращает нули функции f, имеющую производную df."""
    def near_zero(x):
        return approx_eq(f(x), 0)
    return improve(newton_update(f, df), near_zero, guess)

def newton_update(f, df):
    """Возвращает функцию update для функции f, имеющей производную df, используя
    метод Ньютона."""
    def update(x):
        return x - f(x) / df(x)
    return update
