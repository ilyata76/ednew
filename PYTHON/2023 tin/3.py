length : int = int(input())
string : str = input()
min_good_substring_length = None
needs : dict = {'a' : False, 'b' : False, 'c' : False, 'd' : False}

# будем идти по строке, например, вправо
# как только найдём все символы, запомним её длину

def check_needs(needs : dict) :
    for key in needs :
        if not needs[key] :
            return False
    return True 

def clear_needs(needs : dict) :
    for key in needs :
        needs[key] = False
    return True

for i in range(0, len(string)) :
    # взяли начало, теперь дальше
    for j in range(i, len(string)) :
        needs[string[j]] = True
        if check_needs(needs) :
            min_good_substring_length = (j - i + 1) if min_good_substring_length is None else min(min_good_substring_length, j - i + 1)
    
    clear_needs(needs)
        
print(-1 if min_good_substring_length is None else min_good_substring_length)