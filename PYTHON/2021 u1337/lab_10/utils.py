def comma_separated(xs):
    """Конвертирует последовательность значений xs в строку, где значения
    перечислены через запятую.

    >>> comma_separated(['spam', 5, False])
    'spam, 5, False'
    >>> comma_separated([5])
    '5'
    >>> comma_separated([])
    ''
    """
    return ', '.join([str(x) for x in xs])