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
    mpz_t courbe;
    int compute; 
}courbe_s;
int compute(courbe_s *maCourbe, point_s *monPoint);
int verif(courbe_s *maCourbe, point_s *monPoint);
int delta(mpz_t *valDelta, courbe_s *maCourbe);
int calculSoluce(mpz_t *valDelta, mpz_t *x1, mpz_t *x2);
#endif
