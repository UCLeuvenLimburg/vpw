alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"


class InfiniteString:
    def __len__(self):
        return 99999

    def __gt__(self, other):
        return True

    def __str__(self):
        return "onmogelijk"

def swap(s, i, j):
    cs = list(s)

    temp = cs[i]
    cs[i] = cs[j]
    cs[j] = temp

    return "".join(cs)


def code(i, j):
    return alphabet[i] + alphabet[j]


def shortest(strings):
    strings = strings + [ InfiniteString() ]
    smallest_length = min(len(s) for s in strings)
    smallest_strings = [ s for s in strings if len(s) == smallest_length ]
    return sorted(smallest_strings)[0]
    
def solve(s1, s2):
    table = {}

    def compute(i, s1, s2, acc):
        if not s1:
            return acc
        elif s1[0] == s2[0]:
            return aux(i + 1, s1[1:], s2[1:], acc)
        else:
            indices = [ i for i in range(1, len(s1)) if s1[i] != s2[i] ]

            return shortest( [ aux(i + 1, swap(s1, 0, j)[1:], s2[1:], acc + code(i, i + j)) for j in indices ] )


    def aux(i, s1, s2, acc):
        if not (s1, s2) in table:
            table[(s1, s2)] = compute(i, s1, s2, acc)

        return table[(s1, s2)]

    return aux(0, s1, s2, "")


n = int(input())

for index in range(1, n + 1):
    s1 = input()
    s2 = input()

    if len(s1) == len(s2):
        solution = solve(s1, s2)
    else:
        solution = "onmogelijk"

    if not solution:
        solution = "correct"

    print("{} {}".format(index, solution))
