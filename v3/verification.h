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

typedef struct couple_t{
    mpz_t a;
    mpz_t b;
}couple_s;





int set_str(mpz_t *cible, char *chaine);
int compute(courbe_s *maCourbe, point_s *monPoint);
int verif(courbe_s *maCourbe, point_s *monPoint);
int delta(mpz_t *valDelta, courbe_s *maCourbe);
int calculSoluce(mpz_t *valDelta, mpz_t *x1, mpz_t *x2);
int TonnelliShanks(mpz_t *res1, mpz_t *res2, mpz_t *a, mpz_t *mod);
int cipolla(mpz_t *res1, mpz_t *res2, mpz_t *a, mpz_t *mod);
#endif
