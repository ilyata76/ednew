import operator

from utils import comma_separated

class Expr:
    """
    При вводе строки в интерпретатор она распарсивается (преобразуется) в выражение.
    Это выражение представляется в коде экземпляром класса `Expr`.

    Этот интерпретатор поддерживает четыре типа выражений:
        - литералы, здесь просто числа (например, 42 или 4.2)
        - имена (например, my_awesome_variable_name)
        - вызывающие выражения (то есть add(3, 4))
        - лямбда-выражение (то есть lambda x: x)

    Вызывающие выражения и лямбда-выражения построены из более простых выражений.
    И тело лямбда-выражения, и оператор, и операнды вызывающего выражения являются
    подвыражениями. Это означает, что `Expr` — рекурсивная структура данных, похожая
    на дерево. Этот тип дерева называют «абстрактное синтаксическое дерево».

    У класса `Expr` существует четыре подкласса в соответствии с поддерживаемыми
    типами выражений: `Literal`, `Name`, `CallExpr`, и `LambdaExpr`.
    """

    def __init__(self, *args):
        # Звёздочка (*) означает, что `args` будет таплом аргументов, переданных
        # в эту функцию.
        self.args = args

    def eval(self, env):
        """
        Каждый подкласс Expr реализует собственный метод eval.

        `env` — это связывающий строки с экземплярами класса `Value` словарь,
        представляющий окружение, в котором вычисляется выражение.

        Метод должен возвращать экземпляр `Value` — результат вычисления выражения.
        """
        raise NotImplementedError

    def __str__(self):
        """
        Возвращает человекочитаемую строку, описывающую выражение (то есть то,
        что вводится в интерпретатор).

        >>> expr = CallExpr(LambdaExpr(['x'], Name('x')), [Literal(5)])
        >>> str(expr)
        '(lambda x: x)(5)'
        """
        raise NotImplementedError

    def __repr__(self):
        """
        Возвращает техническое представление выражения.

        >>> expr1 = LambdaExpr(['f'], CallExpr(Name('f'), [Literal(0)]))
        >>> expr1
        LambdaExpr(['f'], CallExpr(Name('f'), [Literal(0)]))

        >>> expr2 = CallExpr(LambdaExpr([], Literal(5)), [])
        >>> expr2
        CallExpr(LambdaExpr([], Literal(5)), [])
        """
        args = '(' + comma_separated([repr(arg) for arg in self.args]) + ')'
        return type(self).__name__ + args

class Literal(Expr):
    """Литерал — это способ представления в коде фиксированного значения. В
    PyCombinator единственные литералы — числа. Класс `Literal` должен всегда
    «вычисляться» в значение класса `Number`.

    Атрибут `value` содержит значение экземпляра `Literal`.
    """
    def __init__(self, value):
        Expr.__init__(self, value)
        self.value = value

    def eval(self, env):
        return Number(self.value)

    def __str__(self):
        return str(self.value)

class Name(Expr):
    """Класс `Name` - это переменная. При вычислении значения производится поиск
    переменной в текущем окружении.

    Атрибут `string` содержит имя переменной (в виде Python-строки).
    """
    def __init__(self, string):
        Expr.__init__(self, string)
        self.string = string

    def eval(self, env):
        """
        >>> env = {
        ...     'a': Number(1),
        ...     'b': LambdaFunction([], Literal(0), {})
        ... }
        >>> Name('a').eval(env)
        Number(1)
        >>> Name('b').eval(env)
        LambdaFunction([], Literal(0), {})
        >>> try:
        ...     print(Name('c').eval(env))
        ... except NameError:
        ...     print('Exception raised!')
        Exception raised!
        """
        try :
            result = env[self.string]
            return result
        except KeyError:
            raise NameError('такого имени в текущем окружении нет')
        

    def __str__(self):
        return self.string

class LambdaExpr(Expr):
    """Лямбда-выражение, вычисляющееся в экземпляр `LambdaFunction`.

    Атрибут `parameters` — список имён переменных (список строк).
    Атрибут `body` — экземпляр класса `Expr`.

    Например, лямбда-выражение `lambda x, y: add(x, y)` распарсится в

    LambdaExpr(['x', 'y'], CallExpr(Name('add'), [Name('x'), Name('y')])),

    где `parameters` — это список ['x', 'y'], `body` — это выражение
    CallExpr('add', [Name('x'), Name('y')]).
    """
    def __init__(self, parameters, body):
        Expr.__init__(self, parameters, body)
        self.parameters = parameters
        self.body = body

    def eval(self, env):
        return LambdaFunction(self.parameters, self.body, env)

    def __str__(self):
        body = str(self.body)
        if not self.parameters:
            return 'lambda: ' + body
        else:
            return 'lambda ' + comma_separated(self.parameters) + ': ' + body

class CallExpr(Expr):
    """Вызывающее выражение представляет вызов функции.

    Атрибут `operator` — экземпляр `Expr`.
    Атрибут `operands` — список экземпляров `Expr`.

    Например, `add(3, 4)` будет

    CallExpr(Name('add'), [Literal(3), Literal(4)])

    где `operator` — это Name('add'), а `operands` — это [Literal(3), Literal(4)].
    """
    def __init__(self, operator, operands):
        Expr.__init__(self, operator, operands)
        self.operator = operator
        self.operands = operands

    def eval(self, env):
        """
        >>> from reader import read
        >>> new_env = global_env.copy()
        >>> new_env.update({'a': Number(1), 'b': Number(2)})
        >>> add = CallExpr(Name('add'), [Literal(3), Name('a')])
        >>> add.eval(new_env)
        Number(4)
        >>> new_env['a'] = Number(5)
        >>> add.eval(new_env)
        Number(8)
        >>> read('max(b, a, 4, -1)').eval(new_env)
        Number(5)
        >>> read('add(mul(3, 4), b)').eval(new_env)
        Number(14)
        """
        try :
            oper = self.operator.eval(env)
            result = oper.apply([x.eval(env) for x in self.operands])
            return result
        except KeyError:
            raise NameError

    def __str__(self):
        function = str(self.operator)
        args = '(' + comma_separated(self.operands) + ')'
        if isinstance(self.operator, LambdaExpr):
            return '(' + function + ')' + args
        else:
            return function + args

class Value:
    """
    Значения — результат вычисления выражений. На диаграммах окружения они бывают
    справа (прямо во фрейме, или после стрелочки).

    В этом интерпретаторе три типа значений:
        - числа (например, 42)
        - лямбда-функции, которые получаются из лямбда-выражений
        - простые функции, те, что встроены в интерпретатор (например add)

    У класса `Value` есть три подкласса: Number, LambdaFunction и PrimitiveFunction.
    """

    def __init__(self, *args):
        self.args = args

    def apply(self, arguments):
        """
        Каждый подкласс Value имеет собственный метод apply.

        Помни, что apply имеет смысл только для функций; попытка вызвать apply у
        экземпляра `Number` (как, например, в выражении 4(2, 3)) должна поднимать исключение.

        Для функций `arguments` — это список экземпляров `Value` — аргументов функции.

        Метод должен вернуть экземпляр `Value` — результат применения функции
        к аргументам.
        """
        raise NotImplementedError

    def __str__(self):
        """
        Возвращает человекочитаемое представление значения (то, что вводят в интерпретатор).
        """
        raise NotImplementedError

    def __repr__(self):
        """
        Возвращает техническое представление выражения.
        """
        args = '(' + comma_separated([repr(arg) for arg in self.args]) + ')'
        return type(self).__name__ + args

class Number(Value):
    """Просто число. Вызов apply у числа `Number` приводит к исключению.

    Атрибут `value` —  Python-число, представляющее этот экземпляр.
    """
    def __init__(self, value):
        Value.__init__(self, value)
        self.value = value

    def apply(self, arguments):
        raise TypeError("Не могу вызвать {} с аргументами {}".format(
            self.value, comma_separated(arguments)))

    def __str__(self):
        return str(self.value)

class LambdaFunction(Value):
    """Лямбда-функция, её экземпляры создаются в методе LambdaExpr.eval.
    Лямбда-функция — это лямбда-выражение, которое «знает» окружение, в котором
    оно было обработано.

    Атрибут `parameters` — список имён переменных (список строк).
    Атрибут `body` — экземпляр `Expr` — тело функции.
    Атрибут `parent` — окружение, словарь с именами переменных (ключи) и экземпляры
    класса Value (значения).
    """
    def __init__(self, parameters, body, parent):
        Value.__init__(self, parameters, body, parent)
        self.parameters = parameters
        self.body = body
        self.parent = parent

    def apply(self, arguments):
        """
        >>> from reader import read
        >>> add_lambda = read('lambda x, y: add(x, y)').eval(global_env)
        >>> add_lambda.apply([Number(1), Number(2)])
        Number(3)
        >>> add_lambda.apply([Number(3), Number(4)])
        Number(7)
        >>> sub_lambda = read('lambda add: sub(10, add)').eval(global_env)
        >>> sub_lambda.apply([Number(8)])
        Number(2)
        >>> add_lambda.apply([Number(8), Number(10)]) # Проверь, что сделана копия env
        Number(18)
        >>> read('(lambda x: lambda y: add(x, y))(3)(4)').eval(global_env)
        Number(7)
        >>> read('(lambda x: x(x))(lambda y: 4)').eval(global_env)
        Number(4)
        """
        if len(self.parameters) != len(arguments):
            raise TypeError("Количество параметров {} не совпадает с количеством аргументов {}".format(
                comma_separated(self.parameters), comma_separated(arguments)))
        int_j, new_env = 0, self.parent.copy()
        while int_j < len(self.parameters) :
            new_env[self.parameters[int_j]] = arguments[int_j]
            int_j += 1
        return self.body.eval(new_env)



    def __str__(self):
        definition = LambdaExpr(self.parameters, self.body)
        return '<function {}>'.format(definition)

class PrimitiveFunction(Value):
    """Встроенная функция. Чтобы увидеть полный список встроенных функций, смотри
    `global_env` в конце этого файла.

    Атрибут `operator` —  Python-функция, принимающая Python-числа и возвращающая
    Python-число.
    """
    def __init__(self, operator):
        Value.__init__(self, operator)
        self.operator = operator

    def apply(self, arguments):
        for arg in arguments:
            if type(arg) != Number:
                raise TypeError("Неверные аргументы {} в {}".format(
                    comma_separated(arguments), self))
        return Number(self.operator(*[arg.value for arg in arguments]))

    def __str__(self):
        return '<primitive function {}>'.format(self.operator.__name__)

# Окружение, в котором REPL (цикл «чтение—вычисление—вывод») вычисляет выражения.
global_env = {
    'abs': PrimitiveFunction(operator.abs),
    'add': PrimitiveFunction(operator.add),
    'float': PrimitiveFunction(float),
    'floordiv': PrimitiveFunction(operator.floordiv),
    'int': PrimitiveFunction(int),
    'max': PrimitiveFunction(max),
    'min': PrimitiveFunction(min),
    'mod': PrimitiveFunction(operator.mod),
    'mul': PrimitiveFunction(operator.mul),
    'pow': PrimitiveFunction(pow),
    'sub': PrimitiveFunction(operator.sub),
    'truediv': PrimitiveFunction(operator.truediv),
}