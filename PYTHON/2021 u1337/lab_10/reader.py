import string

from buffer import Buffer
from expr import *

SYMBOL_STARTS = set(string.ascii_lowercase + string.ascii_uppercase + '_')
SYMBOL_INNERS = SYMBOL_STARTS | set(string.digits)
NUMERAL = set(string.digits + '-.')
WHITESPACE = set(' \t\n\r')
DELIMITERS = set('(),:')

def read(s):
    """Разбирает выражение в строке. Если строка не содержит выражения, возвращает
    None. Если строку невозможно распарсить, поднимается SyntaxError.

    >>> read('lambda f: f(0)')
    LambdaExpr(['f'], CallExpr(Name('f'), [Literal(0)]))
    >>> read('(lambda x: x)(5)')
    CallExpr(LambdaExpr(['x'], Name('x')), [Literal(5)])
    >>> read('(lambda: 5)()')
    CallExpr(LambdaExpr([], Literal(5)), [])
    >>> read('lambda x y: 10')
    Traceback (most recent call last):
      ...
    SyntaxError: expected ':' but got 'y'
    >>> read('  ')  # возвращает None
    """
    src = Buffer(tokenize(s))
    if src.current() is not None:
        return read_expr(src)

############
## Лексер ##
############
def tokenize(s):
    """Разделяет строку s на токены и возвращает их список.

    >>> tokenize('lambda f: f(0, 4.2)')
    ['lambda', 'f', ':', 'f', '(', 0, ',', 4.2, ')']
    """
    src = Buffer(s)
    tokens = []
    while True:
        token = next_token(src)
        if token is None:
            return tokens
        tokens.append(token)

def take(src, allowed_characters):
    result = ''
    while src.current() in allowed_characters:
        result += src.remove_front()
    return result

def next_token(src):
    take(src, WHITESPACE)  # игнорирование пробелов
    c = src.current()
    if c is None:
        return None
    elif c in NUMERAL:
        literal = take(src, NUMERAL)
        try:
            return int(literal)
        except ValueError:
            try:
                return float(literal)
            except ValueError:
                raise SyntaxError("'{}' не число".format(literal))
    elif c in SYMBOL_STARTS:
        return take(src, SYMBOL_INNERS)
    elif c in DELIMITERS:
        src.remove_front()
        return c
    else:
        raise SyntaxError("'{}' не токен".format(c))

def is_literal(s):
    return isinstance(s, int) or isinstance(s, float)

def is_name(s):
    return isinstance(s, str) and s not in DELIMITERS and s != 'lambda'

############
## Парсер ##
############
def read_expr(src):
    token = src.remove_front()
    if token is None:
        raise SyntaxError('Неполное выражение')
    elif is_literal(token):
        return read_call_expr(src, Literal(token))
    elif is_name(token):
        return read_call_expr(src, Name(token))
    elif token == 'lambda':
        params = read_comma_separated(src, read_param)
        src.expect(':')
        body = read_expr(src)
        return LambdaExpr(params, body)
    elif token == '(':
        inner_expr = read_expr(src)
        src.expect(')')
        return read_call_expr(src, inner_expr)
    else:
        raise SyntaxError("'{}' не начало выражения".format(token))

def read_comma_separated(src, reader):
    if src.current() in (':', ')'):
        return []
    else:
        s = [reader(src)]
        while src.current() == ',':
            src.remove_front()
            s.append(reader(src))
        return s

def read_call_expr(src, operator):
    while src.current() == '(':
        src.remove_front()
        operands = read_comma_separated(src, read_expr)
        src.expect(')')
        operator = CallExpr(operator, operands)
    return operator

def read_param(src):
    token = src.remove_front()
    if is_name(token):
        return token
    else:
        raise SyntaxError("Ожидалось имя параметра, но получено '{}'".format(token))