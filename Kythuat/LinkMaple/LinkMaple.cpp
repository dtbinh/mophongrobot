#include <stdio.h>
#include <stdlib.h>
#include "maplec.h"
#pragma comment(lib, "maplec.lib")

/* callback used for directing result output */
static void M_DECL textCallBack( void *data, int tag, char *output )
{
    printf("%s\n",output);
}

int main( int argc, char *argv[] )
{
    char err[2048];      
   MKernelVector kv;  /* Maple kernel handle */
    MCallBackVectorDesc cb = {  textCallBack, 0, 0, 0, 0,  0, 0,  0 };
   ALGEB r, l;  /* Maple data-structures */

   /* initialize Maple */
   if( (kv=StartMaple (argc,argv,&cb,NULL,NULL,err)) == NULL ) {
      printf("Fatal error, %s\n",err);
      return( 1 );
   }

   char s[] = "int(x^2+1,x);";
   printf("Evaluate an integral: %s\n\t", s);
   r = EvalMapleStatement (kv, s);

   StopMaple(kv);

   return( 0 );
}
