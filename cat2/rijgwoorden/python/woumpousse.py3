def solve(parts):
    free = [ True ] * len(parts)
    results = []

    def register(x):
        nonlocal results

        if not results:
            results.append(x)
        elif len(results[0]) == len(x):
            results.append(x)
        elif len(results[0]) < len(x):
            results = [x]
            
    def aux(n, acc):
        if n > 1:
            register(acc)
        
        for i in range(len(parts)):
            if free[i] and ((not acc) or parts[i][0] == acc[-1]):
                free[i] = False
                aux(n + 1, acc + parts[i])
                free[i] = True

    aux(0, "")

    results = sorted(list(set(results)))

    return results


if __name__ == '__main__':
    n = int(input())

    for index in range(n):
        parts = input().split(' ')[1:]
        solution = solve(parts)

        if solution:
            solution = " ".join(solution)
        else:
            solution = "geen oplossing"
            
        print(f"{index+1} {solution}")
                
                
