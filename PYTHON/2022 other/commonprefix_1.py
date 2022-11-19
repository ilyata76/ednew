n = int(input())
strs = []

for i in range (0, n):
    strs += [input()]

strs.sort()

prefix = ""

for i in range(0, len(strs[-1])) :
    if strs[-1][i] != strs[0][i] :
        break
    else :
        prefix += strs[-1][i]
        
print(prefix)