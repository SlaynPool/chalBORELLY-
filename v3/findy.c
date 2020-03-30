#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "verification.h"

int main(int argc, char *argv[]){
   courbe_s maCourbe;
   maCourbe.compute= 0;
   point_s monPoint;
   mpz_inits(maCourbe.a, maCourbe.b, maCourbe.mod, maCourbe.courbe, monPoint.x, monPoint.y, NULL);
   

//PARAMETRE DE LA COUBRE JEU DE donné NIST P-192//
/*
   char a[]="-3";
   char b[]="2455155546008943817740293915197451784769108058161191238065";
   char mod[]="6277101735386680763835789423207666416083908700390324961279";
   char x[]="4186469355574186740522149727049440186996809918465310609521"; 
*/
/////////////////////////////////////////////////

//PARAMETRE DE LA COUBRE Jeu de donné secp521r1 2.6.1//
   char a[]="0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC";
   char b[]="0x51953EB9618E1C9A1F929A21A0B68540EEA2DA725B99B315F3B8B489918EF109E156193951EC7E937B1652C0BD3BB1BF073573DF883D2C34F1EF451FD46B503F00";
   char mod[]="0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
   char x[]="5643160416518163681998572717474472531537062926119805907462451943276389080336747116833706857713415576423540238778062829890660938581438215463331638935315181824"; 
/////////////////////////////////////////////////


// Jeu de donné de l'ennocé
/*
   char a[]="31";
   char b[]="17";
   char mod[]="97";
   char x[]="63";
*/
   //x=63,a=31,b=17 et p=97
   //
   set_str(&maCourbe.a, a);
   set_str(&maCourbe.a,a);
   set_str(&maCourbe.b,b);
   set_str(&maCourbe.mod,mod);
   set_str(&monPoint.x,x);

   printf(" \n a =");
   mpz_out_str(stdout,10,maCourbe.a);
   printf(" \n b =");
   mpz_out_str(stdout,10,maCourbe.b);
   printf(" \n mod =");
   mpz_out_str(stdout,10,maCourbe.mod);
   printf(" \n x =");
   mpz_out_str(stdout,10,monPoint.x);
   printf("\n");


/* En faite on n'a juste à resoudre le polynome y^2-courbe = 0 
 * si  b² – 4ac  < 0 pas de solution;
 * si b² - 4ac = 0, une solution −b/2a
 * si delta > 0 x1=−b−sqrt(Δ)/(2a) et x2=−b+sqrt(Δ)/2a
 */


   
    compute( &maCourbe,&monPoint);
    mpz_t res1;
    mpz_t res2;
    mpz_init(res1);
    mpz_init(res2);
   
    if(TonnelliShanks(&res1,&res2, &maCourbe.courbe, &maCourbe.mod)==0){
        printf("\n2solutions\n y=");
        mpz_out_str(stdout,10,res1);
        printf("\n y= ");
        mpz_out_str(stdout,10,res2);
        printf("\n ");
    
    }else{
        printf("Pas de Solution");
    }
    
    int check;
    mpz_set(monPoint.y,res1);

    check=verif(&maCourbe, &monPoint);
    if (check==0){
        printf("resultat verifié\n");
    }
    mpz_set(monPoint.y,res2);

    check=verif(&maCourbe, &monPoint);
    if (check==0){
        printf("resultat verifié\n");
    }








/*    mpz_t valDelta;
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


*/


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
