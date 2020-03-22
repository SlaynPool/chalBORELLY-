#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <unistd.h>
#include "verification.h"
// Pour debuter, on veux juste faire des verifications si des points sont sur la courbe 

int verif(courbe_s *maCourbe, point_s *monPoint){
  /* courbe_s maCourbe;
   point_s monPoint;
   maCourbe.a = atoi(argv[1]);
   maCourbe.b = atoi(argv[2]);
   maCourbe.mod = atoi(argv[3]);
   monPoint.x = atoi( argv[4]);
   monPoint.y = atoi(argv[5]);
   */
   //printf("a= %d,b=%d,mod =%d \n",maCourbe->a,maCourbe->b, maCourbe->mod); 
   mpz_t yy;
   mpz_init(yy);
   //y^2%p
   mpz_t tmp;
   mpz_init(tmp);
   mpz_set_ui(tmp,2);
   mpz_powm(yy,monPoint->y,tmp,maCourbe->mod);  
   //yy=  (monPoint->y* monPoint->y)%maCourbe->mod;
  
  
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
 
 
   // int  courbe=((monPoint->x*monPoint->x*monPoint->x)+(maCourbe->a*monPoint->x)+maCourbe->b)%maCourbe->mod;
   
  
  
    printf("bite"); 
    char *cyy;
    printf("%s\n",mpz_get_str(cyy,10,yy));
    printf("bite");
    char *ccourbe; 
    printf("%s\n",mpz_get_str(ccourbe,10,courbe));


   //printf(" yy = %d\n", yy);
   //²printf(" courbe = %d\n",courbe);
   printf("%d",mpz_cmp(yy,courbe)); 
   if (mpz_cmp(yy,courbe)==0){
     // printf("P(%d;%d) est bien sur la courbe\n",monPoint->x,monPoint->y);
       return 0;
   }
   else{
        
     // printf("P(%d;%d) n'est pas sur la courbe\n",monPoint->x,monPoint->y);
       return 1;
   }

}
