#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <unistd.h>
#include "verification.h"
// Pour debuter, on veux juste faire des verifications si des points sont sur la courbe 
int compute(courbe_s *maCourbe, point_s *monPoint){
    if( maCourbe->compute==0){ 
        mpz_t xxx;
        mpz_init(xxx);
        mpz_t courbe;
        mpz_init(courbe);
        mpz_t ax;
        mpz_init(ax);
        mpz_pow_ui(xxx, monPoint->x,3); // x^3
        mpz_mul(ax,maCourbe->a,monPoint->x); //ax 
        mpz_add(courbe, xxx,ax); //courbe = x^3+ax
        mpz_add(courbe, courbe, maCourbe->b); // courbe = x^3 + ax + b 
        mpz_mod(courbe,courbe,maCourbe-> mod);
        mpz_set(maCourbe->courbe,courbe);  
        maCourbe->compute=1;
   }
    return maCourbe->compute;
}

int delta(mpz_t *valDelta, courbe_s *maCourbe){
    //b^2-4ac ON aura toujours une fonction f(x)= x^2-courbe
    //a=1 b=0 c=-courbe donc 
    //valDelta= 0^2 -4*-courbe
    mpz_t moinsCourbe;
    mpz_init(moinsCourbe);
    mpz_mul_si(moinsCourbe, maCourbe->courbe, -1);
    mpz_mul_si(*valDelta, moinsCourbe,-4);
    if(mpz_cmp_ui(*valDelta,0)==0){
        return 0;
    }
    if(mpz_cmp_ui(*valDelta,0)>0){
        return 1;

    }
    if(mpz_cmp_ui(*valDelta,0)<0){
        return -1;

    }
    return 0;
}

int calculSoluce(mpz_t *valDelta, mpz_t *x1, mpz_t *x2){

    mpz_t racineDelta;
    mpz_init(racineDelta);

    mpz_t moinsRacineDelta;
    mpz_init(moinsRacineDelta);

    mpz_sqrt(racineDelta,*valDelta);
    mpz_div_ui(*x1, racineDelta,2);

    //x2
    mpz_mul_si(moinsRacineDelta, racineDelta, -1);
    mpz_div_ui(*x2, moinsRacineDelta,2);
    return 0;


    
             


}


















int verif(courbe_s *maCourbe, point_s *monPoint){

 //  printf("on est dans verif\n");
   mpz_t yy;
   mpz_init(yy);
  // printf("1\n");
  
 
   
   //y^2%p
   mpz_powm_ui(yy,monPoint->y,2,maCourbe->mod);  
   //yy=  (monPoint->y* monPoint->y)%maCourbe->mod;
  // char *cyy;
  // mpz_out_str(stdout,10,yy);
   compute(maCourbe, monPoint);
      
   printf("y^2=");
   mpz_out_str(stdout,10,yy);
   printf("\n courbe = ");
   mpz_out_str(stdout,10,maCourbe->courbe);
   printf("\n"); 

   // int  courbe=((monPoint->x*monPoint->x*monPoint->x)+(maCourbe->a*monPoint->x)+maCourbe->b)%maCourbe->mod;
   
  
  
  
//    printf("bite");
    //printf(" yy = %d\n", yy);
   //²printf(" courbe = %d\n",courbe);
   
   if (mpz_cmp(yy,maCourbe->courbe)==0){
     // printf("P(%d;%d) est bien sur la courbe\n",monPoint->x,monPoint->y);
       return 0;
   }
   else{
        
     // printf("P(%d;%d) n'est pas sur la courbe\n",monPoint->x,monPoint->y);
       return 1;
   }

}
