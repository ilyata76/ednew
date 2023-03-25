growths = [int(i) for i in input().split()]
asc : bool = True
dsc : bool = True

for i in range(len(growths) - 1) :
    if growths[i] < growths[i + 1] :
        dsc = False
    if growths[i] > growths[i + 1] :
        asc = False

print('YES' if asc or dsc else 'NO')