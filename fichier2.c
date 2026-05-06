#include<stdio.h>
#include<stdlib.h>

void premier();
void stats(FILE *monfichier, int *U, int nbchange);

void stats(FILE *monfichier, int *U, int nbchange)
{
  int l;
  fprintf(monfichier,"============================================================\n");
  fprintf(monfichier,"======Statistiques des changements des occurences de 5======\n");
  fprintf(monfichier,"============================================================\n");
  fprintf(monfichier,"Nombre de changements: %d\n", nbchange);
  fprintf(monfichier,"Sur les lignes:\n");
  for (l=0; l<nbchange; l++)
  {
      fprintf(monfichier,"%d\n", U[l]);
  }
}

void premier()
{
  int i, j=0, compte_diviseur, ligne=0, n, temp, nbchange=0;
  int l;
  char T[17][4];
  int U[10];//tableau hametrahana ny numero anle ligne misy changement es occurences de 5
  FILE *monfichier;
  monfichier = fopen("devoir1erMai.txt","w");
  for (n=2; ligne<=50; n++)
  {
    compte_diviseur=0;
    for(i=1; i<=n; i++)
    {
      if (n%i==0)
      {
        compte_diviseur++;
      }
    }
    if (compte_diviseur==2)
    {
      ligne++;
      if (ligne%3 == 0)
      {
        int nbchiffres = 0;
        int k;
        temp = n;//temporairement à calculer
        while (temp > 0)
        {
          nbchiffres++;
          temp = temp / 10;
        }
        temp = n;//andeha averina @ laoniny
        k = nbchiffres - 1;
        l=0;
        while (temp > 0)
        {
          T[j][k] = (temp % 10) + '0';/*raha tsy misy +'0' dia manjary tsy ilay valeur no eo
                                       fa zavatra hafa, merci my friend de me l'avoir rappelé*/
          if (T[j][k] == '5')
          {
            T[j][k] = 'V';
            U[nbchange]=ligne;
            nbchange++;
          }
          k--;
          temp = temp / 10;
        }
        T[j][nbchiffres]= '\0';
        fprintf(monfichier, "%s\n", T[j]);
        j++;
      }
    }
  }
  stats (monfichier, U, nbchange);
  fclose (monfichier);
}

int main()
{
  premier();
  return(0);
}
