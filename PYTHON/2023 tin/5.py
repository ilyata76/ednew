# будем идти слева направо по каждому дню, набирая "разумные отрезки"
# как найдём разумный отрезок, будем идти по индексу влево и вправо для получения всех связанных
# с ним нормальных отрезков
# после этого всё в какой-нибудь set с уникальными ключами

length : int = int(input())
numbers = [int(i) for i in input().split()]

brainness : set = set()

for i in range(length) :
    # взяли число, берём конец
    for j in range(i, length) : # i:j - j не вкл для кого это сделано?
        
        if sum(numbers[i:j + 1]) == 0 and len(numbers[i:j + 1]) > 0 :
            # мы должны по индексу влево и вправо идти и добавлять подпоследовательности
            for k in range(length) :
                if i - k >= 0 :
                    brainness.add(numbers[i - k:j + 1].__str__()) # будем хранить строковое представление, потому что сам список не хешируется
                if j + 1 + k < length :
                    brainness.add(numbers[i:j + 1 + k].__str__())

print(len(brainness))