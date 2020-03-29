import math

def resolv():
    a=31
    b=17
    mod=97
    x= 63
    courbe=(x*x*x)+a*x+b
    y=0
    print(int(math.sqrt(courbe))%mod)
    for i in range(0, mod):
        res = y + (i*mod)
        #print(res%mod)

        if res%mod == int(math.sqrt(courbe))%mod:
            print(y)
        y=y+1



resolv()
