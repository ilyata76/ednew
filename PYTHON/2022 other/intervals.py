str_in = input().split()
k, n = int(str_in[0]), int(str_in[1])
t1, t2 = 0, 0
intervals = []

for i in range(0, k) :
    str_in = input().split()
    intervals.append([int(str_in[0]), int(str_in[1])])
        
intervals.sort(key= lambda x: x[0])

res = [intervals[0]]

print(intervals)

for i in range(1, len(intervals)) :
    curr = intervals[i]
    prev = res[len(res) - 1]
    if curr[0] <= prev[1]:
        prev[1] = max(prev[1], curr[1])
    else :
        res.append(curr)

print(res)

# >  python py.py
# 4 80
# 10 100
# 50 125
# 130 470
# 70 110
# [[10, 100], [50, 125], [70, 110], [130, 470]]
# [[10, 125], [130, 470]]