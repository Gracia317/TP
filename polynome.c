#include<stdio.h> /*./calculer y=2x+1 pour x=5
                    y=2x^3+'x^2-1 pour x=6*/
#include<stdlib.h>
#include<math.h>
#include <string.h>

void aff_coef(char **T);
void calcul(char **T, int x);

void  aff_puis(char **T)
{
  printf("coef %c\n", T[1][2]);
}

void calcul( char **T, int x)
{
  int i=2;
  float y=0;
  while(T[1][i]!= '\0')
  {
    if (T[1][i]!='x' && T[1][i+2]=='^')
    {
      y += T[1][i]*pow(x,T[1][i+3]);
      i+=5;
    }
    else if (T[1][i]!='x' && T[1][i+2]!='^')
    {
      y += T[1][i]*x;
      i+=4;
    }
    else if (T[1][i]!='x' && T[1][i+2]=='^')
    {
      y += pow(x,T[1][i+3]);
      i+=5;
    }
    else if (T[1][i]!='x' && T[1][i+3]!='^')
    {
      y += T[1][i+1]*x;
      i+=3;
    }
    else if (T[1][i]!='x' && T[1][i+3]=='^')
    {
      y += T[1][i+1]*pow(x,T[1][i+4]);
      i+=6;
    }
    else if (T[1][i]=='x' && T[1][i+1]=='^')
    {
      y += pow(x,T[1][i+2]) ;
      i+=4;
    }
    else if (T[1][i]=='x' && T[1][i+1]!='^')
    {
      y += x ;
      i+=2;
    }
  }
  printf("y=%2.f\n", y);
}

int main(int argc, char *argv[])
{
  int x;
  x=atoi(argv[5]);

  // printf("Len %ld", strlen(argv[1]));
  // for(int i=0;i<argc;i++)
  // {
  //   printf("%c\n",argv[1][i]);
  // }
  aff_puis(argv);
  calcul(argv, x);
  return (0);
}
