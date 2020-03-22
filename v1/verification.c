#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
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
   int yy = (monPoint->y* monPoint->y)%maCourbe->mod;
   int  courbe=((monPoint->x*monPoint->x*monPoint->x)+(maCourbe->a*monPoint->x)+maCourbe->b)%maCourbe->mod;
   //printf(" yy = %d\n", yy);
   //²printf(" courbe = %d\n",courbe); 
   if (yy == courbe){
     // printf("P(%d;%d) est bien sur la courbe\n",monPoint->x,monPoint->y);
       return 0;
   }
   else{
        
     // printf("P(%d;%d) n'est pas sur la courbe\n",monPoint->x,monPoint->y);
       return 1;
   }

}
