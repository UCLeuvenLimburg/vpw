#python v2


letters = int(raw_input())
for _ in range(letters):
    positie, woord = raw_input().rstrip().split()
    print(woord[int(positie) - 1])