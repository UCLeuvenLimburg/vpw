from recordclass import recordclass


def readint():
    return int(input())

def readints():
    return [ int(token) for token in input().split() ]

Emmer = recordclass('Emmer', 'inhoud capaciteit')


n = readint()

for i in range(n):
    emmers = [ Emmer(*readints()) for _ in range(readint()) ]

    for _ in range(readint()):
        van, naar = readints()
        van -= 1
        naar -= 1

        transferred = min( emmers[van].inhoud, emmers[naar].capaciteit - emmers[naar].inhoud )
        emmers[van].inhoud -= transferred
        emmers[naar].inhoud += transferred

    print(" ".join([ str(i+1) ] + [ str(emmer.inhoud) for emmer in emmers ]))
    

    
