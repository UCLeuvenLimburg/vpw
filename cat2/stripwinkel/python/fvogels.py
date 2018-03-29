def show(ns):
    ns = sorted(list(set(ns)))

    if not ns:
        return ''
    
    pairs = [ (ns[0], ns[0]) ]

    for n in ns[1:]:
        x, y = pairs[-1]
        
        if y + 1 == n:
            pairs[-1] = (x, y+1)
        else:
            pairs.append( (n, n) )

    strings = []

    for x, y in pairs:
        if x == y:
            strings.append(str(x))
        elif x + 1 == y:
            strings.append(f"{x} {y}")
        else:
            strings.append(f"{x}-{y}")

    return ' '.join(strings)


n = int(input())

for index in range(1, n+1):
    ks = list(map(int, input().split(' ')[1:]))
    deltas = list(map(int, input().split(' ')[1:]))

    print(f"{index} {show(ks)}")
    
    for delta in deltas:
        if delta > 0:
            ks.append(delta)
        else:
            ks.remove(-delta)

        print(f"{index} {show(ks)}")

            
            
