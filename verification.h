#ifndef VERIFICATION_H
#define VERIFICATION_H
typedef struct point_t{
    mpz_t x;
   
    mpz_t  y;
  
}point_s;
typedef struct courbe_t{
    mpz_t a;
    mpz_t  b;
    mpz_t  mod;
   
}courbe_s;

int verif(courbe_s *maCourbe, point_s *monPoint);
#endif