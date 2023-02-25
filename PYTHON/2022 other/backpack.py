def greedy(costs, weights, M) :
    result = 0
    used = []

    for iteration in range(3) :
        N = len(costs)
        choice = None
        for i in range(N):
            if weights[i] <= M :
                if choice is not None :
                    if costs[i] > costs[choice] or (costs[i] == costs[choice] and weights[i] < weights[choice]):
                        if i not in used : choice = i
                else :
                    if i not in used : choice = i
            else :
                continue
        print(choice)

        if choice is not None :
            used.append(choice)
            result += costs[choice]
            M -= weights[choice]
            choice = None
        # costs.remove(choice)
        # weights.remove(choice)

    print('costs', costs)
    print('weights', weights)
    print('used', used)

    print('\n\n\n GREEDY RESULT', result if result > 0 else -1, '\n\n')


# это правильно?
def dynamic(costs, weights, M) :
    result = 0
    N = len(costs)

    matrix = [[0 for j in range(M + 1)] for i in range(N)]
    # это таблица

    print(matrix)

    for item in range(N) : # для каждого предмета (строка в матрице)
        for column in range(M + 1) : # для каждого столбца матрицы (всего 3 столбцов) (строка - вместимость рюкзака)
            
            if weights[item] <= column :

                if item == 0 :
                    matrix[item][column] = costs[item]

                else : # item > 0
                    print(item, ',', column, ',', column - weights[item], end='\t', sep='')
                    matrix[item][column] = max(costs[item] + (matrix[item - 1][column - weights[item]] if matrix[item- 1][column - weights[item]] is not None else 0), matrix[item - 1][column] if matrix[item - 1][column] is not None else 0)

                # (matrix[item][M - column] if matrix[item][M - column] is not None else 0)


            else :
                matrix[item][column] = matrix[item - 1][column] if item > 0 else None
                print(item, ',', column, ',', M - column, end='\t', sep='')
            


        print('')

    for i in matrix :
        for j in i :
            print(j, end='\t')
        print('')

    print('\n\n\n DYNAMIC RESULT', matrix[-1][-1], '\n\n')

def head_on(costs, weights, M) :
    result = -1
    N = len(costs)
    print(N)

    for i in range(N) :
        current_M = M

        if weights[i] <= current_M :
            first = costs[i]
        else :
            continue        

        for j in range(N) :
            current_M = M - weights[i]

            if j == i :
                continue

            if weights[j] <= current_M:
                second = costs[j]
            else :
                result = max(result, first)
                continue

            for k in range(N) :
                current_M = current_M - weights[j]
                                
                if k == j or k == i :
                    result = max(result, first + second)
                    continue

                if weights[k] <= current_M :
                    third = costs[k]
                else :
                    continue

                result = max(result, first + second + third)

    print('\n\n\n HEAD ON RESULT', result)

if __name__ == '__main__' :
    costs = [int(i) for i in input().split()]  # стоимости
    weights = [int(i) for i in input().split()]  # веса
    M = int(input())  # предельная масса
    dynamic(costs, weights, M)
    greedy(costs, weights, M)
    head_on(costs, weights, M)