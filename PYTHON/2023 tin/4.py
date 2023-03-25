length : int = int(input())
numbers = [int(i) for i in input().split()]

# будем идти по числам и собирать из в dict
# каждый раз будем проверять, является ли префикс "скучным"
# и нет ни одного повода останавливаться до конца массива (вдруг последнее число всё изменит)
# ключ - число, значение - количество повторений

nums : dict = {}
max_length : int = 2

# здесь будем проверять, скучный ли префикс по dict'y
def check_prefix(nums : dict) :
    # создадим ещё массив частот  
    freq = list(nums.values())

    # [3, 3, 3, 4]
    # [3,3,3,3] [4,4,4,4,3,3]
    # если все одинаковые, то min == max
    # если есть различие только в 1, то min == max - 1
    # но нужно проверить, что оно одно такое значение через count

    minimal = min(freq)
    maximum = max(freq)

    return (minimal == maximum) \
            or ((minimal == maximum - 1) and (freq.count(maximum) == 1)) \
            or (minimal == 1 and freq.count(minimal) == 1 and freq.count(maximum) == len(freq) - 1) # если у нас [1, 3, 3, 3, 3]

# идём по числам
for i in range(len(numbers)) :
    x = numbers[i]
    if x in nums :
        nums[x] += 1
    else :
        nums[x] = 1
    
    if check_prefix(nums) :
        max_length = max(max_length, i + 1)


print(max_length)