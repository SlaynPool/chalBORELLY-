def test(p):
    q, s = p - 1, 0
    while q % 2 == 0:
        s += 1
        print("s="+str(s));
        q //= 2
    return q

print(test(97))
