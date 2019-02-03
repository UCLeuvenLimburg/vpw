from sys import stdin


def next_generation(current_generation, arcs):
    result = [ 0 ] * len(current_generation)

    for i in range(len(current_generation)):
        destinations = arcs[i]
        per_destination = current_generation[i] // len(destinations)
        leftover = current_generation[i] % len(destinations)

        for destination in destinations:
            result[destination] += per_destination

        result[i] += leftover

    return tuple(result)


def solve(initial, arcs):
    history = { initial: 0 }

    current = next_generation(initial, arcs)
    i = 1

    while current not in history:
        history[current] = i
        i += 1
        current = next_generation(current, arcs)

    return i - history[current]


def main():
    n = int(stdin.readline())

    for index in range(1, n+1):
        n_nodes = int(stdin.readline())
        initial = tuple( int(stdin.readline()) for _ in range(n_nodes) )
        n_arcs = int(stdin.readline())
        arcs = [ [] for _ in range(n_nodes) ]

        for _ in range(n_arcs):
            x, y = stdin.readline().split(' ')
            x = int(x) - 1
            y = int(y) - 1
            arcs[x].append(y)
            arcs[y].append(x)

        solution = solve(initial, arcs)

        print(solution)


main()