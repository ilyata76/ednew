# Запись в файл c использованием менеджера контекста

# with open("demo_1.txt", "w") as file:
#     file.write("1!")

# with open("demo_2.txt", "w") as file:
#     file.write("2!")


# реализуем классный считающий

import time

# Менеджер контекста часто определяется в отдельном файле.
# В этом конкретном случае это был файл Utils.py

class timer(object):
    def __enter__(self):
        self.t = time.clock()
        return self

    def __exit__(self, type, value, traceback):
        self.e = time.clock()

    def __float__(self):
        return float(self.e - self.t)

# Код в другом файле
with timer() as t1:
    …
    foo(...)
    …
print(t1)

with timer() as t2:
    …
    bar(...)
    …
print(t2)