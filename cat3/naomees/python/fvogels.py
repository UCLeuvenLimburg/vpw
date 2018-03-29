def split(str, k):
    return (str[: k], str[k : len(str)-k], str[len(str)-k :])

def valid(str):
    def is_basic(str):
        return str in { 'ba', 'di', 'du' }

    def is_enclosed(str):
        def aux(k):
            (left, middle, right) = split(str, k)
            return left == right and valid(left) and valid(middle)

        return any(aux(k) for k in range(1, len(str)//2+1))
        
    return str == '' or is_basic(str) or is_enclosed(str)



n = int(input())

for index in range(1, n+1):
    result = " ".join("naomees" if valid(input()) else "onzin" for _ in range(5))

    print(f"{index} {result}")

