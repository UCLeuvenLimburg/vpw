from collections import defaultdict

for index in range(1, int(input()) + 1):
    sum = 0
    target = defaultdict(int, { 0 : 1 })
    target2 = defaultdict(int, { 0 : 1 })
    
    for _ in range(0, int(input())):
        sum += int(input())
        target[sum] += 1
        if sum % 2 == 0:
            target2[sum] += target[sum // 2]

    solution = 0
    if sum % 3 == 0:
        solution = target2[sum * 2 // 3]

    print(f"{index} {solution}")
