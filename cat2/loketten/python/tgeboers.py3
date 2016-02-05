#python v3


class Time:
    def __init__(self, hours, minutes):
        self.hours = hours
        self.minutes = minutes

    def add(self, minutes):
        self.minutes += minutes
        minutes = self.minutes % 60
        extra_hours = self.minutes // 60
        self.minutes = minutes
        self.hours += extra_hours

    def __str__(self):
        return str(self.hours) + " " + str(self.minutes)

    def __sub__(self, other):
        return (self.hours - other.hours) * 60 + self.minutes - other.minutes

    def __lt__(self, other):
        return self - other < 0

    def __gt__(self, other):
        return other < self

    def __le__(self, other):
        return not (self > other)

    def __ge__(self, other):
        return not (self < other)

    def __eq__(self, other):
        return self.diff(other) == 0

    def __ne__(self, other):
        return not (self == other)



cases = int(input())
for index in range(1, cases + 1):
    result = str(index)+ " "
    longest = 0
    ls = [Time(8,0) for _ in range(int(input()))]
    for _ in range(int(input())):
        h, m = input().rstrip().split()
        h, m = int(h), int(m)
        time = Time(h, m)
        l = int(input())

        first = ls.pop(0)
        wait = first - time

        if first < time:
            first = time 
        if wait > longest:
            longest = wait 

        result += str(first) + " "
        first.add(l)
        ls.append(first)
        ls.sort() 
    result += str(longest)
    print(result)
