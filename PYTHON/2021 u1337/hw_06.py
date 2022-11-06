class Fib():
    """Число Фибоначчи.

    >>> start = Fib()
    >>> start
    0
    >>> start.next()
    1
    >>> start.next().next()
    1
    >>> start.next().next().next()
    2
    >>> start.next().next().next().next()
    3
    >>> start.next().next().next().next().next()
    5
    >>> start.next().next().next().next().next().next()
    8
    >>> start.next().next().next().next().next().next() # Проверка, что start не изменился
    8
    """

    def __init__(self, value=0, secondvalue= 0):
        self.value = value
        self.secondvalue = secondvalue

    def next(self):
        if self.value == 0 :
            return Fib(1, 0)
        else :
            return Fib(self.value + self.secondvalue, self.value)

    def __repr__(self):
        return str(self.value)

class VendingMachine:
    """Торговый автомат, продающий некоторый товар по некоторой цене.
    
    >>> v = VendingMachine('яблоко', 10)
    >>> v.vend()
    'Товара нет в наличии.'
    >>> v.restock(2)
    'Количество товара «яблоко»: 2'
    >>> v.vend()
    'Нужно дополнительно внести 10 ₽.'
    >>> v.deposit(7)
    'Доступно: 7 ₽'
    >>> v.vend()
    'Нужно дополнительно внести 3 ₽.'
    >>> v.deposit(5)
    'Доступно: 12 ₽'
    >>> v.vend()
    'Получите яблоко и сдачу 2 ₽.'
    >>> v.deposit(10)
    'Доступно: 10 ₽'
    >>> v.vend()
    'Получите яблоко.'
    >>> v.deposit(15)
    'Товара нет в наличии. Вот твои деньги — 15 ₽.'

    >>> w = VendingMachine('лимонад', 2)
    >>> w.restock(3)
    'Количество товара «лимонад»: 3'
    >>> w.restock(3)
    'Количество товара «лимонад»: 6'
    >>> w.deposit(2)
    'Доступно: 2 ₽'
    >>> w.vend()
    'Получите лимонад.'
    """
    
    def __init__(self, str_object, int_cost) :
        self.object = str(str_object)
        self.cost = int(int_cost)
        self.bank = 0
        self.count = 0

    def restock(self, int_count):
        self.count += int(int_count)
        return 'Количество товара «{}»: {}'.format(self.object, self.count)

    def vend(self) :
        if self.bank >= self.cost and self.count:
            if self.bank == self.cost :
                self.bank = 0
                self.count -= 1
                return 'Получите {}.'.format(self.object)
            else :
                a = self.bank
                self.bank = 0
                self.count -= 1
                return 'Получите {} и сдачу {} ₽.'.format(self.object, a - self.cost)
        elif self.bank < self.cost and self.count:
            return 'Нужно дополнительно внести {} ₽.'.format(self.cost - self.bank)
        else :
            return 'Товара нет в наличии.'

    def deposit(self, int_value) :
        self.bank += int_value
        if self.count :
            return 'Доступно: {} ₽'.format(self.bank) 
        else :
            a = self.bank
            self.bank = 0
            return 'Товара нет в наличии. Вот твои деньги — {} ₽.'.format(a)
