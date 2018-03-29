import sys


def solve(string):
    for n in range(1, 1 + len(string) // 2):
        k = int(string[0:n])
        i = 0

        while string[i:].startswith(str(k)):
            i += len(str(k))
            k += 1

        if i == len(string):
            continue
        
        missing = k
        k += 1

        while string[i:].startswith(str(k)):
            i += len(str(k))
            k += 1

        if i == len(string):
            return missing

    return None


if __name__ == '__main__':
    n = int(sys.stdin.readline())

    for index in range(1, n+1):
        string = sys.stdin.readline().rstrip()
        solution = solve(string)

        if solution:
            print(f"{index} {solution}")
        else:
            print(f"{index} geen ontbrekend getal")
            
