Bonjour,

Voici un petit exercice de programmation et de mathématiques :))

La cryptographie sur les courbes elliptiques (ECC) utilise les propriétés
des courbes elliptiques sur les corps finis (entiers modulo p) respectant
l'équation de WEIERSTRASS suivante:

      y^2=x^3+ax+b (mod p)

https://fr.wikipedia.org/wiki/Cryptographie_sur_les_courbes_elliptiques

Par exemple pour la courbe avec a=-1,b=0 et p=61.
https://en.wikipedia.org/wiki/Elliptic_curve#/media/File:Elliptic_curve_on_Z61.svg
Les points P1(x=8,y=4), P2(x=48,y=16) et P3(x=28,y=56) sont sur la courbe.

On peut le vérifier assez facilement en faisant un petit programme qui calcule
les 2 cotés de l'équation et qui vérifie ensuite s'il y a bien égalité (voir cb-ecc.py).

Courbe elliptique y^2=x^3-x mod 61
 x^3-x=504=16 mod 61
 y^2=4^2=16=16 mod 61
 Le point (x=8,y=4) est bien sur la courbe
Courbe elliptique y^2=x^3-x mod 61
 x^3-x=110544=12 mod 61
 y^2=16^2=256=12 mod 61
 Le point (x=48,y=16) est bien sur la courbe
Courbe elliptique y^2=x^3-x mod 61
 x^3-x=21924=25 mod 61
 y^2=56^2=3136=25 mod 61
 Le point (x=28,y=56) est bien sur la courbe

Mais comment peut-on trouver les valeurs de y (vérifiant l'équation d'une courbe elliptique) à partir de x ?
Par exemple si x=52 comment trouver les 2 valeurs de y vérifiant l'équation de la courbe avec a=-1,b=0 et p=61 ?
c.à.d. y2=52^3-52=140556=12 mod 61=y0^2 mod 61=y1^2 mod 61 => y0=16 et y1=45

Ecrire alors un programme (dans le langage que vous preferez) qui calcule
les valeurs de y (si elles existent) à partir de x,a,b et p.

*Vérifier celui-ci pour x=63,a=31,b=17 et p=97

*Même question pour x=4186469355574186740522149727049440186996809918465310609521
sur la courbe NIST P-192 D.1.2.1 page 90 (99/130)
https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.186-4.pdf
a=-3
b=0x64210519e59c80e70fa7e9ab72243049feb8deecc146b9b1
p=6277101735386680763835789423207666416083908700390324961279

*Même question pour x=5643160416518163681998572717474472531537062926119805907462451943276389080336747116833706857713415576423540238778062829890660938581438215463331638935315181824
sur la courbe secp521r1 2.6.1 page 15-16/37 SEC2v2 http://www.secg.org/sec2-v2.pdf
p=0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
a=0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC
b=0x51953EB9618E1C9A1F929A21A0B68540EEA2DA725B99B315F3B8B489918EF109E156193951EC7E937B1652C0BD3BB1BF073573DF883D2C34F1EF451FD46B503F00

Vous pouvez m'envoyer vos programmes par mail.

Bonne recherches et bonne programmation !
