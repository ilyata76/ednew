n = int(input())


def commonPrefix(str1 : str , str2 : str) -> str :
    min_str = min(str1, str2)
    prefix = ""
    for i in range (0, len(min_str)) :
        if str1[i] == str2[i] :
            prefix += str1[i]
        else :
            break
    return prefix


prev = input()
prefix = prev

for i in range (1, n):
    curr = input()
    prefix = commonPrefix(prefix, curr)
    prev = curr

print(prefix)
