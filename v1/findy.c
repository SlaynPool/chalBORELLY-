#include <stdio.h>
#include <stdlib.h>
#include "verification.h"

int main(int argc, char *argv[]){
   courbe_s maCourbe;
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
   maCourbe.a = 31;
   maCourbe.b = 17;
   maCourbe.mod = 97;
   monPoint.x = 63;
   
   int  y;
   for ( y=0 ;y < maCourbe.mod;y++){
       monPoint.y = y;
       if(verif(&maCourbe, &monPoint)==0){
           printf("%d est une solution\n", y);
       }
   }
return 0;
}
