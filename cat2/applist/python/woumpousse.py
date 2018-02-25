def solve(page_size, state, launches):
    result = 0
    
    for launch in launches:
        i = state.index(launch)

        result += i // page_size

        if i > 0:
            state[i-1], state[i] = state[i], state[i-1]

    return result


n = int(input())

for index in range(1, n+1):
    page_size, _, _ = map(int, input().split(' '))
    state = list(map(int, input().split(' ')))
    launches = list(map(int, input().split(' ')))
    solution = solve(page_size, state, launches)

    print(f"{index} {solution}")
