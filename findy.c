#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "verification.h"

int main(int argc, char *argv[]){
   courbe_s maCourbe;
   maCourbe.compute= 0;
   point_s monPoint;
  /* maCourbe.a = atoi(argv[1]);
   maCourbe.b = atoi(argv[2]);
   maCourbe.mod = atoi(argv[3]);
   monPoint.x = atoi( argv[4]);
  */
   /*
   maCourbe.a = -3;
   maCourbe.b = 0x64210519e59c80e70fa7e9ab72243049feb8deecc146b9b1;
   maCourbe.mod = 6277101735386680763835789423207666416083908700390324961279;
   monPoint.x = 4186469355574186740522149727049440186996809918465310609521;
   Le PROBLEME est que meme dans un unsigned long long les nombres ne rentres pas
   Par ce que après le nombre d'operations max est egale à maCourbe.mod si on fait toute les operations il ya sans doute moyen de reduire le cout
   */
   /*
   maCourbe.a = 31;
   maCourbe.b = 17;
   maCourbe.mod = 97;
   monPoint.x = 63;
   */
   /*char a;
   char b; 
   char mod;
   char x;
   */
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
 /*  char y[]="37";
   mpz_set_str(monPoint.y,y,10);*/
   //x=63,a=31,b=17 et p=97
   mpz_set_str(maCourbe.a,a, 10);
   mpz_set_str(maCourbe.b,b, 10);
   mpz_set_str(maCourbe.mod,mod, 10);
   mpz_set_str(monPoint.x,x, 10);
  // printf ("%d",verif(&maCourbe, &monPoint));
       
  //mpz_set_ui(maCourbe.b,3);


  // int  y;
   /*int test;
   test= mpz_cmp(maCourbe.mod,y);
    char * cmod;
            //mpz_get_str(cy,10,y);
    printf("%s\n",mpz_get_str(cmod,10,maCourbe.mod));
    char *cy;
            //mpz_get_str(cy,10,y);
    printf("%s\n",mpz_get_str(cy,10,y));



   printf("%d",test);*/


/* En faite on n'a juste à resoudre le polynome courbe-y^2 = 0 
 * si  b² – 4ac  < 0 pas de solution;
 * si b² - 4ac = 0, une solution −b/2a
 * si delta > 0 x1=−b−sqrt(Δ)/(2a) et x2=−b+sqrt(Δ)/2a
 */
    compute( &maCourbe,&monPoint);
    mpz_t delta;
    mpz_init(delta);
    mpz_mul_ui(delta, maCourbe.courbe, 4); // vu que f(y)= -y^2+ courbe; a= -1, b= 0, c = courbe donc delta 0^2-4*-1*courbe = 4*courbe
    if(mpz_cmp_ui(delta, 0)==0){
        printf("Il n'y qu'une solution y = 0 ");

    }else{
    if(mpz_cmp_ui( delta, 0)>0){
        mpz_t x1;
        mpz_t x2; 
        mpz_init(x1);
        mpz_init(x2);
        mpz_root(x1,delta,20);// racine(delta)
        mpz_mul_si(x1, x1, -1); // -racine(delta)
        mpz_t deuxa; 
        mpz_init(deuxa);
        char c2a[]="-2";
        mpz_set_str(deuxa,c2a, 10);
        mpz_cdiv_q(x1,x1,deuxa); //-racine(delta)/2*-1 
        
        
        mpz_root(x2,delta,20);// racine(delta) // ,20 pour 20 nombres après la virgule
        mpz_cdiv_q(x1,x1,deuxa); //-racine(delta)/2*-1 
        printf("2 solutions: \n");
        printf("y1 = ");
        mpz_out_str(stdout,10,x1);
        printf("\ny2= ");
        mpz_out_str(stdout,10,x2);
        printf("\n");


   }else{
    printf(" PAS DE SOLUTION");

   }
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
