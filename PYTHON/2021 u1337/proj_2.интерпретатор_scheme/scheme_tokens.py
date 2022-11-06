"""Модуль scheme_tokens предоставляет функции tokenize_line и tokenize_lines
для преобразования (итерируемых) строк в (итерируемые) списки
токенов. Токен может быть:

  * Числом (представленным типами int или float)
  * Булевой величиной (представленной типом bool)
  * Символом (представленным типом string)
  * Разделителем (скобки, точки и одиночные кавычки)

Файл также содержит реализацию некоторых возможностей языка Scheme, которые
не рассматриваются в курсе.
"""

from __future__ import print_function  # поддержка Python 2

import itertools
import string
import sys
import tokenize

_NUMERAL_STARTS = set(string.digits) | set('+-.')
_SYMBOL_CHARS = (set('!$%&*/:<=>?@^_~') | set(string.ascii_lowercase) |
                 set(string.ascii_uppercase) | _NUMERAL_STARTS)
_STRING_DELIMS = set('"')
_WHITESPACE = set(' \t\n\r')
_SINGLE_CHAR_TOKENS = set("()[]'`")
_TOKEN_END = _WHITESPACE | _SINGLE_CHAR_TOKENS | _STRING_DELIMS | {',', ',@'}
DELIMITERS = _SINGLE_CHAR_TOKENS | {'.', ',', ',@'}

def valid_symbol(s):
    """Проверяет, что s — корректный символ (строка)."""
    if len(s) == 0:
        return False
    for c in s:
        if c not in _SYMBOL_CHARS:
            return False
    return True

def next_candidate_token(line, k):
    """Тапл (tok, k'), где tok — следующая подстрока строки в (или после)
    позиции k, которая может быть токеном (предполагая, что она проходит
    проверку корректности), а k' — это позиция в строке следующая за этим
    токеном. Возвращает (None, len(line)), если токенов больше не осталось.
    """
    while k < len(line):
        c = line[k]
        if c == ';':
            return None, len(line)
        elif c in _WHITESPACE:
            k += 1
        elif c in _SINGLE_CHAR_TOKENS:
            if c == ']': c = ')'
            if c == '[': c = '('
            return c, k+1
        elif c == '#':  # Булевы величины #t и #f
            return line[k:k+2], min(k+2, len(line))
        elif c == ',': # Unquote; проверка на @
            if k+1 < len(line) and line[k+1] == '@':
                return ',@', k+2
            return c, k+1
        elif c in _STRING_DELIMS:
            if k+1 < len(line) and line[k+1] == c: # в Scheme нет тройных кавычек
                return c+c, k+2
            line_bytes = (bytes(line[k:], encoding='utf-8'),)
            gen = tokenize.tokenize(iter(line_bytes).__next__)
            next(gen) # Выбрасывает закодированный токен
            token = next(gen)
            if token.type != tokenize.STRING:
                raise ValueError("некорректная строка: {0}".format(token.string))
            return token.string, token.end[1]+k
        else:
            j = k
            while j < len(line) and line[j] not in _TOKEN_END:
                j += 1
            return line[k:j], min(j, len(line))
    return None, len(line)

def tokenize_line(line):
    """The list of Scheme tokens on line.  Excludes comments and whitespace."""
    result = []
    text, i = next_candidate_token(line, 0)
    while text is not None:
        if text in DELIMITERS:
            result.append(text)
        elif text == '#t' or text.lower() == 'true':
            result.append(True)
        elif text == '#f' or text.lower() == 'false':
            result.append(False)
        elif text == 'nil':
            result.append(text)
        elif text[0] in _SYMBOL_CHARS:
            number = False
            if text[0] in _NUMERAL_STARTS:
                try:
                    result.append(int(text))
                    number = True
                except ValueError:
                    try:
                        result.append(float(text))
                        number = True
                    except ValueError:
                        pass
            if not number:
                if valid_symbol(text):
                    result.append(text.lower())
                else:
                    raise ValueError("некорректное число или символ: {0}".format(text))
        elif text[0] in _STRING_DELIMS:
            result.append(text)
        else:
            print("предупреждение: некорректный токен: {0}".format(text), file=sys.stderr)
            print("    ", line, file=sys.stderr)
            print(" " * (i+3), "^", file=sys.stderr)
        text, i = next_candidate_token(line, i)
    return result

def tokenize_lines(input):
    """Итератор по списку токенов; один результат для каждой строки
    итерируемой входной последовательности."""
    return (tokenize_line(line) for line in input)

def count_tokens(input):
    """Подсчитывает количество токенов в input, игнорирует разделители."""
    return len(list(itertools.chain(*tokenize_lines(input))))

def run(*args):
    import argparse
    parser = argparse.ArgumentParser(description='Подсчет токенов Scheme.')
    parser.add_argument('file', nargs='?',
                        type=argparse.FileType('r'), default=sys.stdin,
                        help='входной файл для подсчета')
    args = parser.parse_args()
    print('найдено', count_tokens(args.file), 'токенов')

if __name__ == '__main__':
    run()