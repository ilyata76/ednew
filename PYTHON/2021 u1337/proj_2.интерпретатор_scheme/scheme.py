"""Интерпретатор Scheme и его цикл считать-вычислить-напечатать."""
from __future__ import print_function
#from typing_extensions import TypeVarTuple  # совместимость с Python 2

from scheme_builtins import *
from scheme_reader import *

###########################
# Вычисление / Применение #
###########################

def scheme_eval(expr, env, _=None): # Третий опциональный аргумент игнорируется
    """Вычисляет Scheme-выражение EXPR в окружении ENV.

    >>> expr = read_line('(+ 2 2)')
    >>> expr
    Pair('+', Pair(2, Pair(2, nil)))
    >>> scheme_eval(expr, create_global_frame())
    4
    """

    if scheme_symbolp(expr):
        return env.lookup(expr)
    elif self_evaluating(expr):
        return expr

    # Все остальные выражения — списки (комбинации)
    if not scheme_listp(expr):
        raise SchemeError('неформатный список: {0}'.format(repl_str(expr)))
    first, rest = expr.first, expr.second
    if scheme_symbolp(first) and first in SPECIAL_FORMS:
        return SPECIAL_FORMS[first](rest, env)
    else : 
        fun = scheme_eval(first, env)
        check_procedure(fun)
        args = rest.map(lambda x: scheme_eval(x, env= env))
        return scheme_apply(fun, args, env)
        # КОНЕЦ ЗАДАЧИ 5

def self_evaluating(expr):
    """Проверяет, что выражение EXPR имеет значение равное самому себе."""
    return (scheme_atomp(expr) and not scheme_symbolp(expr)) or expr is None

def scheme_apply(procedure, args, env):
    """Применяет PROCEDURE к значениям аргументов ARGS (Scheme-список)
    в окружении ENV."""
    check_procedure(procedure)
    if isinstance(procedure, BuiltinProcedure):
        return procedure.apply(args, env)
    else:
        new_env = procedure.make_call_frame(args, env)
        return eval_all(procedure.body, new_env)

def eval_all(expressions, env):
    """Вычисляет все выражения в Scheme-списке EXPRESSIONS
    в окружении ENV и возвращает результат последнего."""
    # НАЧАЛО ЗАДАЧИ 8  
    if expressions == nil :
        return None
    if expressions.second == nil :
        return scheme_eval(expressions.first, env)
    else :
        scheme_eval(expressions.first, env)
        return eval_all(expressions.second, env)
    # КОНЕЦ ЗАДАЧИ 8

#############
# Окружения #
#############

class Frame(object):
    """Фрейм окружения, связывающий Scheme-символы со Scheme-значениями."""

    def __init__(self, parent):
        """Фрейм окружения, связывающий Scheme-символы со Scheme-значениями."""
        self.bindings = {}
        self.parent = parent

    def __repr__(self):
        if self.parent is None:
            return '<Global Frame>' # Глобальный фрейм
        s = sorted(['{0}: {1}'.format(k, v) for k, v in self.bindings.items()])
        return '<{{{0}}} -> {1}>'.format(', '.join(s), repr(self.parent))

    def define(self, symbol, value):
        """Связывание Scheme-символа SYMBOL со значением VALUE."""
        # НАЧАЛО ЗАДАЧИ 3
        self.bindings[symbol] = value
        # КОНЕЦ ЗАДАЧИ 3

    def lookup(self, symbol):
        """Возвращает значение, связанное с символом SYMBOL.
        Ошибка, если SYMBOL не найден."""
        # НАЧАЛО ЗАДАЧИ 3
        if symbol in self.bindings :
            return self.bindings[symbol]
        elif self.parent :
            return self.parent.lookup(symbol)
        else:
        # КОНЕЦ ЗАДАЧИ 3
            raise SchemeError('неизвестный идентификатор: {0}'.format(symbol))

    def make_child_frame(self, formals, vals):
        """Возвращает новый локальный фрейм, чей родитель — SELF,
        в котором символы из Scheme-списка формальных параметров FORMALS
        связаны со Scheme-значениями из Scheme-списка VALS.
        Поднимает исключение, если дано слишком много или
        слишком мало значений аргументов.

        >>> env = create_global_frame()
        >>> formals, expressions = read_line('(a b c)'), read_line('(1 2 3)')
        >>> env.make_child_frame(formals, expressions)
        <{a: 1, b: 2, c: 3} -> <Global Frame>>
        """
        # НАЧАЛО ЗАДАЧИ 11
        if len(formals) != len(vals) : raise SchemeError('неверное кол-во аргументов')
        child_frame = Frame(self)
        while formals != nil and vals != nil :
            child_frame.define(formals.first, vals.first)
            formals = formals.second
            vals = vals.second
        return child_frame
        # КОНЕЦ ЗАДАЧИ 11

#############
# Процедуры #
#############

class Procedure(object):
    """Супертип для всех Scheme-процедур."""

def scheme_procedurep(x):
    return isinstance(x, Procedure)

class BuiltinProcedure(Procedure):
    """Scheme-процедура, определённая как Python-функция."""

    def __init__(self, fn, use_env=False, name='builtin'):
        self.name = name
        self.fn = fn
        self.use_env = use_env

    def __str__(self):
        return '#[{0}]'.format(self.name)

    def apply(self, args, env):
        """Применяет SELF к аргументам ARGS (Scheme-список) в окружении ENV.

        >>> env = create_global_frame()
        >>> plus = env.bindings['+']
        >>> twos = Pair(2, Pair(2, nil))
        >>> plus.apply(twos, env)
        4
        """
        if not scheme_listp(args):
            raise SchemeError('аргументы не являются списком: {0}'.format(args))
        # Конвертирует Scheme-список в Python-список
        python_args = []
        while args is not nil:
            python_args.append(args.first)
            args = args.second
        # НАЧАЛО ЗАДАЧИ 4
        try :
            if self.use_env :
                python_args.append(env)
            return self.fn(*python_args)
        except TypeError:
            raise SchemeError('неверное количество аргументов в функции')
        # КОНЕЦ ЗАДАЧИ 4

class LambdaProcedure(Procedure):
    """Процедура, определенная лямбда-выражением или формой define."""

    def __init__(self, formals, body, env):
        """Процедура со Scheme-списком формальных параметров FORMALS,
        Scheme-списком выражений тела BODY и родительским окружением, которое
        начинается с фрейма ENV."""
        self.formals = formals
        self.body = body
        self.env = env

    def make_call_frame(self, args, env):
        """Создаёт фрейм, в котором формальные параметры ARGS связываются со
        Scheme-списком значений, для вызова с лексической областью видимости,
        выполняющегося в окружении ENV."""
        # НАЧАЛО ЗАДАЧИ 12
        return Frame(self.env.make_child_frame(formals=self.formals, vals=args))
        # КОНЕЦ ЗАДАЧИ 12

    def __str__(self):
        return str(Pair('lambda', Pair(self.formals, self.body)))

    def __repr__(self):
        return 'LambdaProcedure({0}, {1}, {2})'.format(
            repr(self.formals), repr(self.body), repr(self.env))

class MacroProcedure(LambdaProcedure):
    """Макрос — особая форма, которая действует на невычисленные операнды,
    для создания выражения, которое будет вычисляться вместо вызова."""

    def apply_macro(self, operands, env):
        """Применяет макрос к выражениям операндов."""
        return complete_apply(self, operands, env)

def add_builtins(frame, funcs_and_names):
    """Добавляет во фрейм окружения FRAME связи из FUNCS_AND_NAMES
    в качестве встроенных процедур. Каждый элемент в FUNCS_AND_NAMES задан
    в форме (ИМЯ, PYTHON-ФУНКЦИЯ, ВНУТРЕННЕЕ-ИМЯ)."""
    for name, fn, proc_name in funcs_and_names:
        frame.define(name, BuiltinProcedure(fn, name=proc_name))

################
# Особые формы #
################

# Все следующие функции вида do_xxx_form первым аргументом expressions принимают
# cdr выражения особой формы — Scheme-список особой формы без указания
# начального символа (if, lambda, quote, ...). Второй аргумент env — окружение,
# в котором выполняется особая форма.

def do_define_form(expressions, env):
    """Обработка формы define."""
    check_form(expressions, 2)
    target = expressions.first
    if scheme_symbolp(target):
        check_form(expressions, 2, 2)
        # НАЧАЛО ЗАДАЧИ 6
        env.define(target, scheme_eval(expressions.second.first, env))
        return target
        # КОНЕЦ ЗАДАЧИ 6
    elif isinstance(target, Pair) and scheme_symbolp(target.first):
        # НАЧАЛО ЗАДАЧИ 10
        env.define(expressions.first.first, LambdaProcedure(expressions.first.second, expressions.second, env))
        return expressions.first.first
        # КОНЕЦ ЗАДАЧИ 10
    else:
        bad_target = target.first if isinstance(target, Pair) else target
        raise SchemeError('не символ: {0}'.format(bad_target))

def do_quote_form(expressions, env):
    """Обработка формы quote."""
    check_form(expressions, 1, 1)
    # НАЧАЛО ЗАДАЧИ 7
    return expressions.first
    # КОНЕЦ ЗАДАЧИ 7

def do_begin_form(expressions, env):
    """Обработка формы begin."""
    check_form(expressions, 1)
    return eval_all(expressions, env)

def do_lambda_form(expressions, env):
    """Обработка формы lambda."""
    check_form(expressions, 2)
    formals = expressions.first
    check_formals(formals)
    # НАЧАЛО ЗАДАЧИ 9
    return LambdaProcedure(formals, expressions.second, env)
    # КОНЕЦ ЗАДАЧИ 9

def do_if_form(expressions, env):
    """Обработка формы if."""
    check_form(expressions, 2, 3)
    if scheme_truep(scheme_eval(expressions.first, env)):
        return scheme_eval(expressions.second.first, env)
    elif len(expressions) == 3:
        return scheme_eval(expressions.second.second.first, env)

def do_and_form(expressions, env):
    """Обработка формы and (с минимальным вычислением)."""
    # НАЧАЛО ЗАДАЧИ 13
    if expressions is nil:
        return True
    
    while expressions.second is not nil:
        val = scheme_eval(expressions.first, env)
        if scheme_falsep(val) : 
            return False
        expressions = expressions.second
    return scheme_eval(expressions.first, env)
    # КОНЕЦ ЗАДАЧИ 13

def do_or_form(expressions, env):
    """Обработка формы or (с минимальным вычислением)."""
    # НАЧАЛО ЗАДАЧИ 13
    if expressions is nil:
        return False
    
    while expressions.second is not nil:
        val = scheme_eval(expressions.first, env)
        if scheme_truep(val) : 
            return val
        expressions = expressions.second
    return scheme_eval(expressions.first, env)    
    # КОНЕЦ ЗАДАЧИ 13

def do_cond_form(expressions, env):
    """Обработка формы cond."""
    while expressions is not nil:
        clause = expressions.first
        check_form(clause, 1)
        if clause.first == 'else':
            predicate = True
            if expressions.second != nil:
                raise SchemeError('else должен быть в конце')
        else:
            predicate = scheme_eval(clause.first, env)
        if scheme_truep(predicate):
            # НАЧАЛО ЗАДАЧИ 14
            if clause.second != nil :
                return eval_all(clause.second, env)
            else :
                return predicate
            # КОНЕЦ ЗАДАЧИ 14
        expressions = expressions.second
    return None  

def do_let_form(expressions, env):
    """Обработка формы let."""
    check_form(expressions, 2)
    let_env = make_let_frame(expressions.first, env)
    return eval_all(expressions.second, let_env)

def make_let_frame(bindings, env):
    """Создаёт дочерний для ENV фрейм, содержащий определения из BINDINGS.
    Scheme-список BINDINGS должен быть корректным списком связей выражения let:
    каждый элемент — список, содержащий символ и Scheme-выражение."""
    if not scheme_listp(bindings):
        raise SchemeError('некорректный список связей в форме let')
    # НАЧАЛО ЗАДАЧИ 15
    new_env = Frame(env)
    while bindings != nil :
        check_form(bindings.first, 2, 2)
        check_formals(bindings.first.first)
        new_env.define(bindings.first.first, scheme_eval(bindings.first.second.first, env))
        bindings = bindings.second 
    return new_env
    # КОНЕЦ ЗАДАЧИ 15

def do_define_macro(expressions, env):
    """Обработка формы define-macro."""
    # НАЧАЛО ЗАДАЧИ 21
    "*** ТВОЙ КОД ЗДЕСЬ ***"
    # КОНЕЦ ЗАДАЧИ 21


def do_quasiquote_form(expressions, env):
    """Обработка формы quasiquote с параметрами EXPRESSIONS
    в окружении ENV."""
    def quasiquote_item(val, env, level):
        """Вычисляет вложенное Scheme-выражение VAL глубины LEVEL
        в особой форме quasiquote в окружении ENV."""
        if not scheme_pairp(val):
            return val
        if val.first == 'unquote':
            level -= 1
            if level == 0:
                expressions = val.second
                check_form(expressions, 1, 1)
                return scheme_eval(expressions.first, env)
        elif val.first == 'quasiquote':
            level += 1
        first = quasiquote_item(val.first, env, level)
        second = quasiquote_item(val.second, env, level)
        return Pair(first, second)

    check_form(expressions, 1, 1)
    return quasiquote_item(expressions.first, env, 1)

def do_unquote(expressions, env):
    raise SchemeError('unquote вне quasiquote')


SPECIAL_FORMS = {
    'and': do_and_form,
    'begin': do_begin_form,
    'cond': do_cond_form,
    'define': do_define_form,
    'if': do_if_form,
    'lambda': do_lambda_form,
    'let': do_let_form,
    'or': do_or_form,
    'quote': do_quote_form,
    'define-macro': do_define_macro,
    'quasiquote': do_quasiquote_form,
    'unquote': do_unquote,
}

# Вспомогательные функции для проверки структуры Scheme-программ

def check_form(expr, min, max=float('inf')):
    """Проверяет, что выражение EXPR является форматным списком с длиной
    не меньше чем MIN, и не больше, чем MAX (по умолчанию: без ограничений).
    Поднимает исключение SchemeError если это не так.

    >>> check_form(read_line('(a b)'), 2)
    """
    if not scheme_listp(expr):
        raise SchemeError('некорректное выражение: ' + repl_str(expr))
    length = len(expr)
    if length < min:
        raise SchemeError('в форме слишком мало операндов')
    elif length > max:
        raise SchemeError('в форме слишком много операндов ')

def check_formals(formals):
    """Check that FORMALS is a valid parameter list, a Scheme list of symbols
    in which each symbol is distinct. Raise a SchemeError if the list of
    formals is not a well-formed list of symbols or if any symbol is repeated.

    Проверяет, что FORMALS — корректный список формальных параметров —
    Scheme-список уникальных символов.
    Поднимает исключение SchemeError, если этот список неформатный, или если
    есть повторение символов.

    >>> check_formals(read_line('(a b c)'))
    """
    symbols = set()
    def check_and_add(symbol):
        if not scheme_symbolp(symbol):
            raise SchemeError('не символ: {0}'.format(symbol))
        if symbol in symbols:
            raise SchemeError('дублирование символа: {0}'.format(symbol))
        symbols.add(symbol)

    while isinstance(formals, Pair):
        check_and_add(formals.first)
        formals = formals.second

    if formals != nil:
        check_and_add(formals)

def check_procedure(procedure):
    """Проверяет, что PROCEDURE — корректная Scheme-процедура."""
    if not scheme_procedurep(procedure):
        raise SchemeError('{0} не может быть вызвана: {1}'.format(
            type(procedure).__name__.lower(), repl_str(procedure)))

##################################
# Динамическая область видимости #
##################################

class MuProcedure(Procedure):
    """
    Процедура, определенная с помощью mu-выражения,
    имеющая динамическую область видимости.
     ________________
    < Scheme крутой! >
     ----------------
            \   ^__^
             \  (oo)\_______
                (__)\       )\/\
                    ||----w |
                    ||     ||
    """

    def __init__(self, formals, body):
        """Процедура со Scheme-списком формальных параметров FORMALS и
        Scheme-списком выражений тела BODY.
        """
        self.formals = formals
        self.body = body

    def make_call_frame(self, args, env) :
        new_frame = env.make_child_frame(self.formals, args)
        return new_frame

    def __str__(self):
        return str(Pair('mu', Pair(self.formals, self.body)))

    def __repr__(self):
        return 'MuProcedure({0}, {1})'.format(
            repr(self.formals), repr(self.body))

def do_mu_form(expressions, env):
    """Обработка формы mu."""
    check_form(expressions, 2)
    formals = expressions.first
    check_formals(formals)
    # НАЧАЛО ЗАДАЧИ 16
    return MuProcedure(formals, expressions.second)
    # КОНЕЦ ЗАДАЧИ 16

SPECIAL_FORMS['mu'] = do_mu_form

##########
# Потоки #
##########

class Promise(object):
    """Промис."""
    def __init__(self, expression, env):
        self.expression = expression
        self.env = env

    def evaluate(self):
        if self.expression is not None:
            self.value = scheme_eval(self.expression, self.env.make_child_frame(nil, nil))
            self.expression = None
        return self.value

    def __str__(self):
        return '#[promise ({0}forced)]'.format(
                'not ' if self.expression is not None else '')

def do_delay_form(expressions, env):
    """Обработка формы delay."""
    check_form(expressions, 1, 1)
    return Promise(expressions.first, env)

def do_cons_stream_form(expressions, env):
    """Обработка формы cons-stream."""
    check_form(expressions, 2, 2)
    return Pair(scheme_eval(expressions.first, env),
                do_delay_form(expressions.second, env))

SPECIAL_FORMS['cons-stream'] = do_cons_stream_form
SPECIAL_FORMS['delay'] = do_delay_form

######################
# Хвостовая рекурсия #
######################

class Thunk(object):
    """Выражение EXPR, которое надо вычислить в окружении ENV."""
    def __init__(self, expr, env):
        self.expr = expr
        self.env = env

def complete_apply(procedure, args, env):
    """Применяет процедуру procedure к аргументам args в окружении env;
    проверяет, что результат не Thunk."""
    val = scheme_apply(procedure, args, env)
    if isinstance(val, Thunk):
        return scheme_eval(val.expr, val.env)
    else:
        return val

def optimize_tail_calls(original_scheme_eval):
    """Возвращает версию функции eval c оптимизацией хвостовой рекурсии."""
    def optimized_eval(expr, env, tail=False):
        """Вычисляет Scheme-выражение EXPR в окружении ENV. Если TAIL,
        возвращает Thunk, содержащий выражение для дальнейшего вычисления.
        """
        # if scheme_symbolp(expr):
        #     return env.lookup(expr)
        # elif self_evaluating(expr):
        #     return expr

        if tail and not scheme_symbolp(expr) and not self_evaluating(expr):
            return Thunk(expr, env)

        result = Thunk(expr, env)
        # НАЧАЛО                         
        return original_scheme_eval(result.expr, result.env, False)
        # КОНЕЦ
    return optimized_eval

################################################################################
# Раскомментируй следующую строку для включения оптимизации хвостовой рекурсии #
################################################################################
#scheme_eval = optimize_tail_calls(scheme_eval)


############################
# Дополнительные процедуры #
############################

def scheme_map(fn, s, env):
    check_type(fn, scheme_procedurep, 0, 'map')
    check_type(s, scheme_listp, 1, 'map')
    return s.map(lambda x: complete_apply(fn, Pair(x, nil), env))

def scheme_filter(fn, s, env):
    check_type(fn, scheme_procedurep, 0, 'filter')
    check_type(s, scheme_listp, 1, 'filter')
    head, current = nil, nil
    while s is not nil:
        item, s = s.first, s.second
        if complete_apply(fn, Pair(item, nil), env):
            if head is nil:
                head = Pair(item, nil)
                current = head
            else:
                current.second = Pair(item, nil)
                current = current.second
    return head

def scheme_reduce(fn, s, env):
    check_type(fn, scheme_procedurep, 0, 'reduce')
    check_type(s, lambda x: x is not nil, 1, 'reduce')
    check_type(s, scheme_listp, 1, 'reduce')
    value, s = s.first, s.second
    while s is not nil:
        value = complete_apply(fn, scheme_list(value, s.first), env)
        s = s.second
    return value

##############
# Ввод/Вывод #
##############

def read_eval_print_loop(next_line, env, interactive=False, quiet=False,
                         startup=False, load_files=(), report_errors=False):
    """Читает и обрабатывает ввод до завершения файлаили до прерывания
    с клавиатуры."""
    if startup:
        for filename in load_files:
            scheme_load(filename, True, env)
    while True:
        try:
            src = next_line()
            while src.more_on_line:
                expression = scheme_read(src)
                result = scheme_eval(expression, env)
                if not quiet and result is not None:
                    print(repl_str(result))
        except (SchemeError, SyntaxError, ValueError, RuntimeError) as err:
            if report_errors:
                if isinstance(err, SyntaxError):
                    err = SchemeError(err)
                    raise err
            if (isinstance(err, RuntimeError) and
                'maximum recursion depth exceeded' not in getattr(err, 'args')[0]):
                raise
            elif isinstance(err, RuntimeError):
                print('Ошибка: достигнута максимальная глубина рекурсии')
            else:
                print('Ошибка:', err)
        except KeyboardInterrupt:  # <Control>-C
            if not startup:
                raise
            print()
            print('Прервано с клавиатуры')
            if not interactive:
                return
        except EOFError:  # <Control>-D и так далее
            print()
            return

def scheme_load(*args):
    """
    Считывает исходный файл Scheme. Аргументы ARGS должны быть в виде (SYM, ENV)
    или (SYM, QUIET, ENV). Файл с именем SYM загружается в окружение ENV,
    с текстовым выводом, определяемым QUIET (по умолчанию true)."""
    if not (2 <= len(args) <= 3):
        expressions = args[:-1]
        raise SchemeError('неверное количество аргументов в «load»: '
                          '{0}'.format(len(expressions)))
    sym = args[0]
    quiet = args[1] if len(args) > 2 else True
    env = args[-1]
    if (scheme_stringp(sym)):
        sym = eval(sym)
    check_type(sym, scheme_symbolp, 0, 'load')
    with scheme_open(sym) as infile:
        lines = infile.readlines()
    args = (lines, None) if quiet else (lines,)
    def next_line():
        return buffer_lines(*args)

    read_eval_print_loop(next_line, env, quiet=quiet, report_errors=True)

def scheme_open(filename):
    """Если FILENAME или FILENAME.scm является именем существующего файла,
    возвращает открытый Python-файл. Иначе поднимает ошибку."""
    try:
        return open(filename)
    except IOError as exc:
        if filename.endswith('.scm'):
            raise SchemeError(str(exc))
    try:
        return open(filename + '.scm')
    except IOError as exc:
        raise SchemeError(str(exc))

def create_global_frame():
    """Создает и возвращает окружение из одного глобального фрейма
    со встроенными именами и дополнительными процедурами."""
    env = Frame(None)
    env.define('eval',
               BuiltinProcedure(scheme_eval, True, 'eval'))
    env.define('apply',
               BuiltinProcedure(complete_apply, True, 'apply'))
    env.define('load',
               BuiltinProcedure(scheme_load, True, 'load'))
    env.define('procedure?',
               BuiltinProcedure(scheme_procedurep, False, 'procedure?'))
    env.define('map',
               BuiltinProcedure(scheme_map, True, 'map'))
    env.define('filter',
               BuiltinProcedure(scheme_filter, True, 'filter'))
    env.define('reduce',
               BuiltinProcedure(scheme_reduce, True, 'reduce'))
    env.define('undefined', None)
    add_builtins(env, BUILTINS)
    return env

def run(*argv):
    import argparse
    parser = argparse.ArgumentParser(description=\
                                     'Твой собственный Scheme-интерпретатор')
    parser.add_argument('-load', '-i', action='store_true',
                       help='интерактивное исполнение файла')
    parser.add_argument('file', nargs='?',
                        type=argparse.FileType('r'), default=None,
                        help='Scheme-файл для запуска')
    args = parser.parse_args()

    next_line = buffer_input
    interactive = True
    load_files = []

    if args.file is not None:
        if args.load:
            load_files.append(getattr(args.file, 'name'))
        else:
            lines = args.file.readlines()
            def next_line():
                return buffer_lines(lines)
            interactive = False

    read_eval_print_loop(next_line, create_global_frame(), startup=True,
                         interactive=interactive, load_files=load_files)
    tscheme_exitonclick()

if __name__ == '__main__':
    import sys
    args = sys.argv[1:]
    run(*args)

def try_print(f):
    try:
        f()
    except Exception as e:
        print(type(e))

def scm_fixture():
    _frame = create_global_frame()
    def eval_line(code_line):
        try:
            exp = read_line(code_line)
            result = scheme_eval(exp, _frame)
            print(repl_str(result))
        except Exception as e:
            print(type(e))
        return
    return eval_line