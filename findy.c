#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "verification.h"

int main(int argc, char *argv[]){
   courbe_s maCourbe;
   maCourbe.compute= 0;
   point_s monPoint;

   mpz_init(maCourbe.a);
   mpz_init(maCourbe.b);
   mpz_init(maCourbe.mod);
   mpz_init(monPoint.x); 
   mpz_init(monPoint.y);


   char a[]="-3";
   char b[]="2455155546008943817740293915197451784769108058161191238065";
   char mod[]="6277101735386680763835789423207666416083908700390324961279";
   char x[]="4186469355574186740522149727049440186996809918465310609521"; 
 /*
   char a[]="31";
   char b[]="17";
   char mod[]="97";
   char x[]="63";*/

   //x=63,a=31,b=17 et p=97
   mpz_set_str(maCourbe.a,a, 10);
   mpz_set_str(maCourbe.b,b, 10);
   mpz_set_str(maCourbe.mod,mod, 10);
   mpz_set_str(monPoint.x,x, 10);
 

/* En faite on n'a juste à resoudre le polynome y^2-courbe = 0 
 * si  b² – 4ac  < 0 pas de solution;
 * si b² - 4ac = 0, une solution −b/2a
 * si delta > 0 x1=−b−sqrt(Δ)/(2a) et x2=−b+sqrt(Δ)/2a
 */
    compute( &maCourbe,&monPoint);
    mpz_t valDelta;
    mpz_init(valDelta);
    int d=delta(&valDelta, &maCourbe);
    if(d==0){
        printf("Une Solution y=0 \n"); // Je peux le prouver
    } 
    if(d<0){
        printf("Pas De solution \n");

    }
    if( d> 0){
        mpz_t x1;
        mpz_t x2;
        mpz_init(x1);
        mpz_init(x2);
        printf(" 2solutions\n");
        calculSoluce(&valDelta, &x1,&x2);
        printf("Delta = "); 
        mpz_out_str(stdout,10,valDelta);
        printf( "\n y1=");
        mpz_out_str(stdout,10,x1);
        printf(" \n y2 =");
        mpz_out_str(stdout,10,x2);
        printf("\n");

    }





   /*
   mpz_t y;
   mpz_init(y);
   mpz_set_ui(y,0);
   mpz_t un;
   mpz_init(un);
   mpz_set_ui(un,1);


  for ( y ;mpz_cmp( maCourbe.mod,y)==1;mpz_add(y,y,un)){
       //monPoint.y = *y;
       mpz_set(monPoint.y,y);
       int result;
       result=verif(&maCourbe, &monPoint);
       if(result==0){
           //printf("bite au cas ou ");
           char * result;
           //mpz_get_str(result,10,y);
           printf("%s est une solution \n",mpz_get_str(result,10,y));
           //printf("%s est une solution\n", result);
       }else{
            char *cy;
            //mpz_get_str(cy,10,y);
           // printf("%s\n",mpz_get_str(cy,10,y));

       }    
   }
*/   
return 0;
}
