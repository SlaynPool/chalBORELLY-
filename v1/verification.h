#ifndef VERIFICATION_H
#define VERIFICATION_H
typedef struct point_t{
    int x;
    int  y;
}point_s;
typedef struct courbe_t{
    int a;
    int  b;
    int  mod;
}courbe_s;

int verif(courbe_s *maCourbe, point_s *monPoint);
#endif
