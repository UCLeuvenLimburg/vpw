#python v3

letters = int(input())
for _ in range(letters):
    positie, woord = input().rstrip().split()
    print(woord[int(positie) - 1])