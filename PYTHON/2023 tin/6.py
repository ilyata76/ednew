count, max_ball = map(int, input().split())
childs : list = []
current_ball : int = 0
maximum : int = 0
minimum : int = 10**9
result : int = 0

for i in range(count):
    l, r = list(map(int, input().split()))
    current_ball += l
    minimum = min(min(minimum, r), l)
    maximum = max(max(maximum, l), r)
    childs.append([l, r])

childs.sort()
bank = max_ball - current_ball
our_guess : bool = False



for guess in range(minimum, maximum) :
    # т.к. перебором не получается, будем пытаться угадывать
    # главное требование - количество получаемых должно быть > n//2 (4 для 7, т.к. первая пара и будет медианой)
    # далее - будем накидывать баллы на минимум, забирая из банка, чтобы получить медиану

    choosen : list = []
    current_bank = bank
    our_guess = True

    for x in childs :
        if x[1] >= guess :
            choosen.append(x)
    
    # когда собрали choosen теперь надо попробовать распределить очки до guess
    # если удастся, то наш случай, если нет, то нет

    if len(choosen) > count // 2 : 
        for x in choosen :
            if x[0] < guess :
                current_bank -= guess - x[0]
                if current_bank < 0 :
                    our_guess = False
                    break
                # x[0] = guess
                
    else :
        our_guess = False

    if our_guess :
        result = max(result, guess)

    choosen.clear()

print(result)
