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
        mpz_set(maCourbe->courbe,courbe); 
        mpz_clear(xxx);
        mpz_clear(courbe); 
        maCourbe->compute=1;
   }
    return maCourbe->compute;
}

int strLen(char *str){
    int i;
    for(i=0;;i++){
        if( str[i]=='\0'){
            return i;
        }
    }
}

char* alloc(int taille){ // RECUPERATION DE CODE DE RT2
    //On fera notre Malloc et on renverra le pointeur de notre tableau
    char* pointeur = NULL; //Declaration de notre pointeur
    pointeur = (char*) malloc(taille * sizeof(char)); //Allocation de la memoire malloc avec cast du void*(renvoyer par malloc) => int*
    // On check si c'est ok
    if(pointeur == NULL){ //check de si ca n'a pas marché
        printf("MALLOC FAIL");
        exit(0);
    }
    return  pointeur; //Retourne le pointeur
}

void remove0x(char *new, char *old, int taille){
    int i;
    int a; 
    a=0;
    for (i=2;i<taille; i++){
        new[a]=old[i];
        a++;
    } 
    


}




int set_str(mpz_t *cible, char *chaine){
    if(chaine[0]=='0'){
       if(chaine[1]=='x'){
            int taille;
            taille = strLen(chaine);
            char* new_char;
            new_char= alloc(taille);
            remove0x(new_char, chaine, taille);
            mpz_set_str(*cible, new_char, 16);
            return 0;
       }else{
           mpz_set_str(*cible, chaine, 10);
           return 0;
       }
    }else{
        mpz_set_str(*cible, chaine, 10);
        return 0;

    }
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
int findq(mpz_t q, mpz_t s){
// q, s = p - 1, 0
//    while q % 2 == 0:
//        s += 1
//        q //= 2
    mpz_t stmp;
    mpz_init(stmp);
    mpz_set_ui(stmp,0);
  //  printf("\non a init stmp");
    mpz_t modq;
    mpz_init(modq);

    while(mpz_mod_ui(modq,q,2)==0){
        mpz_add_ui(stmp,stmp,1);
        mpz_fdiv_q_ui(q,q,2);
        
        
    }
   // printf("q= ");
   // mpz_out_str(stdout, 10,q);
   // printf("\n");
    return 0;


}

// Calcul le residu quadratic mais en vrai je sais pas trop ce que sait return -1 ou 1, -1 si c'est bon, et 1 si pas bon, sachant que res prend sera soit -1 soit la valeur de legendre_s
int legendre_Symbole(mpz_t *res, mpz_t *a, mpz_t *mod){
    // On va stocker le resultat ici
   // printf("Je suis dans legrendre\n");
    mpz_t legendre_s;
    mpz_init(legendre_s);
    //On va stocker le resultat de (p-1)/2 ici
    mpz_t puissance;
    mpz_init(puissance);
    mpz_t tmp;
    mpz_init(tmp); 
    mpz_sub_ui(tmp, *mod,1); //p-1
    mpz_div_ui(puissance, tmp,2); //(p-1)/2
    //FIN DE (p-1)/2
    mpz_powm(legendre_s, *a, puissance, *mod);
    //printf("\n legendre_s");
    //mpz_out_str(stdout, 10,legendre_s);

    if(mpz_cmp(legendre_s, tmp)==0){
        char moinsun[]="-1";
        mpz_set_str(*res,moinsun,10); 
        return -1;
    }
    else{
        mpz_set(*res,legendre_s);
        return 1;
    }
}
// retourne 0 si solution et -1 si pas de solution, solution dispo dans res1 et res2
int TonnelliShanks(mpz_t *res1, mpz_t *res2, mpz_t *a, mpz_t *mod){
    /*
    printf("a= ");
    mpz_out_str(stdout, 10,*a);
    printf("\nmod= ");
    mpz_out_str(stdout, 10,*mod);
*/

    //a%mod
    mpz_t aMODOLUmod;
    mpz_init(aMODOLUmod);
    mpz_mod(aMODOLUmod,*a,*mod);

    //si a = 0 alors solution = 0
    if(mpz_cmp_ui(aMODOLUmod,0)==0){
        mpz_set_ui(*res1,0);
        mpz_set_ui(*res2,0);
        mpz_clear(aMODOLUmod);
        return 0;
    }
    //si a = 2 alors solution = 2
    if(mpz_cmp_ui(aMODOLUmod,2)==0){
        mpz_set(*res1,*a);
        mpz_set_ui(*res2,0);
        mpz_clear(aMODOLUmod);
        return 0;
    }
    mpz_set(*a, aMODOLUmod);
    mpz_clear(aMODOLUmod);

    
    //Si legendre_Symbole(a,mod) est different de 1 pas de solution
    mpz_t res;
    mpz_init(res);
    legendre_Symbole(&res, a, mod);
    if(mpz_cmp_ui(res,1)!=0){
        return -1;
    }
    mpz_clear(res);

    
    //Si mod%4= 3 alors solution= (a^(mod+1)/4)modulo(mod) et solution = mod-((a^(mod+1)/4)modulo(mod))
    mpz_t modMODULOquatre;
    mpz_init(modMODULOquatre);
    mpz_mod_ui(modMODULOquatre,*mod,4);
    if(mpz_cmp_ui(modMODULOquatre,3)==0){
        // solution= (a^(mod+1)/4)modulo(mod)
        mpz_t tmp1;
        mpz_init(tmp1);
        mpz_add_ui(tmp1,*mod,1); //mod+1
        mpz_t tmp2;
        mpz_init(tmp2);
        mpz_div_ui(tmp2, tmp1,4); //(mod+1)/4
        mpz_powm(*res1, *a, tmp2, *mod); //(a^(mod+1)/4)%mod
        
        mpz_sub(*res2, *mod, *res1);
        mpz_clear(modMODULOquatre);

        return 0; 
    }
    mpz_clear(modMODULOquatre);


    //
    //
    //Sinon le gros algo:
    //
    //q = mod - 1
    mpz_t q;
    mpz_init(q);
    mpz_sub_ui(q,*mod, 1);
    //printf("mod= ");
    //mpz_out_str(stdout, 10,*mod);
    //printf("\n q");
    //mpz_out_str(stdout, 10,q);

    //s = 0
    mpz_t s;
    mpz_init(s);
    findq(q,s); 
    //z = 1
    mpz_t z;
    mpz_init(z);
    mpz_set_ui(z,1);
    

    mpz_t ls;
    mpz_init(ls);
    legendre_Symbole(&ls,&z, mod);
    while( mpz_cmp_si(ls, -1) !=0 ){
    //tant que legendre_symbole(z,mod) != -1{
    // z =z + 1
       mpz_t ztmp;
       mpz_init(ztmp);
       mpz_add_ui(ztmp, z, 1);
       mpz_set(z, ztmp);
       mpz_clear(ztmp);
       legendre_Symbole(&ls,&z, mod);
    //}
    }
  //  printf("z=");
  //  mpz_out_str(stdout, 10,z);
  //  printf("\n");

    //
    //c = (z^q)%mod
    mpz_t c;
    mpz_init(c);
    mpz_powm(c, z,q,*mod);
    //
  //  printf("c=");
  //  mpz_out_str(stdout, 10,c);
  //  printf("\n");
    //x= (a^((q+1))/2)%p
  //  printf("q=");
  //  mpz_out_str(stdout, 10,q);
  //  printf("\n");

    mpz_t x; 
    mpz_init(x);
    
    mpz_t qPlusUn;
    mpz_init(qPlusUn);
    mpz_add_ui(qPlusUn, q,1); //q+1


    mpz_t qPlusUnDiv2;
    mpz_init(qPlusUnDiv2);
    mpz_div_ui(qPlusUnDiv2,qPlusUn,2); // (q+1)/2
    mpz_powm(x, *a,qPlusUnDiv2,*mod);
  //  printf("x=");
  //  mpz_out_str(stdout, 10,x);
  //  printf("\n");



    //t= (a^q)%p
    mpz_t t;
    mpz_init(t);
    mpz_powm(t, *a,q,*mod);
   // printf("t=");
   // mpz_out_str(stdout, 10,t);
   // printf("\n");
    //
    //m = s ?? btw
    mpz_t m;
    mpz_init(m);
    mpz_set(m, s);
    //
    //
    mpz_t i;
    mpz_init(i);

    while(mpz_cmp_ui(t,1)!=0){

    //tant que t != 1{
    //  i = 1 
        mpz_set_ui(i,0);
    //  e = 2
        mpz_t e;
        mpz_init(e);
        mpz_set_ui(e,2);
    
    //  pour i allant de 1 à m {
        while(mpz_cmp(i,m)!=0){
            mpz_add_ui(i,i,1);
            mpz_powm(t,t,e,*mod);
        
        //      si (t^e)%mod == 1{
            if(mpz_cmp_ui(t,1)==0){
//          fin du for
  //              printf("coucou");
                break;
  //      sinon{
            }else{
   //         e = e*2
            mpz_mul_ui(e,e,2);
            }

        } 
    //  on cree de nouvelle valeurs:
    //  b= (c expo(m-i-1))%p
        
        mpz_t b;
        mpz_init(b);
        mpz_t miun;
        mpz_init(miun);
        mpz_sub(miun, m,i);
        mpz_sub_ui(miun,miun, 1);
        mpz_powm(b,c,miun,*mod);
        mpz_clear(miun);
    //  x= (x*b)%p
        mpz_mul(x,x,b);
        mpz_mod(x,x,*mod);

    //  t= (t*b*b)%p
        mpz_mul(t,t,b);
        mpz_mul(t,t,b);
        mpz_mod(t,t,*mod);
    //  c= (b*b)%p
        mpz_mul(c,b,b);
        mpz_mod(c,c,*mod);
    //  m=i
        mpz_set(m,i);
//        printf("Etape tmp \n");

    //
    //}
    //
    }
    mpz_set(*res1,x);

    mpz_t modmoinsx;
    mpz_init(modmoinsx);
    mpz_sub(modmoinsx, *mod,x);
    mpz_set( *res2, modmoinsx);
    mpz_clear(modmoinsx);
    return 0;
    //return x et p-x
    //
    



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
      
   printf("\ny^2= ");
   mpz_out_str(stdout,10,yy);
   printf("\ncourbe= ");
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
