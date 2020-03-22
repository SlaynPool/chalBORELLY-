#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <unistd.h>
#include "verification.h"
// Pour debuter, on veux juste faire des verifications si des points sont sur la courbe 

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
 

  
 //x^3+ax+b%p
   mpz_t courbe;
   mpz_init(courbe);
   mpz_t xxx;
   mpz_init(xxx);
   mpz_pow_ui(xxx, monPoint->x,3);
   
   mpz_t ax;
   mpz_init(ax);
   mpz_mul(ax,maCourbe->a,monPoint->x);
   mpz_add(courbe, xxx,ax);
   mpz_add(courbe, courbe, maCourbe->b);
   mpz_mod(courbe,courbe,maCourbe-> mod);
   printf("y^2=");
   mpz_out_str(stdout,10,yy);
   printf("\n courbe = ");
   mpz_out_str(stdout,10,courbe);
   printf("\n"); 

   // int  courbe=((monPoint->x*monPoint->x*monPoint->x)+(maCourbe->a*monPoint->x)+maCourbe->b)%maCourbe->mod;
   
  
  
  
//    printf("bite");
    //printf(" yy = %d\n", yy);
   //²printf(" courbe = %d\n",courbe);
   
   if (mpz_cmp(yy,courbe)==0){
     // printf("P(%d;%d) est bien sur la courbe\n",monPoint->x,monPoint->y);
       return 0;
   }
   else{
        
     // printf("P(%d;%d) n'est pas sur la courbe\n",monPoint->x,monPoint->y);
       return 1;
   }

}
