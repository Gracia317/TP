#include <stdio.h>
#include <stdlib.h>

/* Algorithme TriangleNumerique

1
1 1
2 3 1
3 6 6 1
4 8 10 8 1
5 10 15 15 10 1

Variables
    n, i, j, milieu : entier
    tpas, tnum : tableaux de n+1 lignes et n+1 colonnes

Début

    Lire n

    // Construction du triangle de Pascal
    Pour (i=0, i< n, i=i+1) faire
        tpas[i][0] = 1
        tpas[i][i] = 1

        Pour (j=1,  j<=i-1, j=j+1) faire
            tpas[i][j] ← tpas[i-1][j-1] + tpas[i-1][j]
        FinPour
    FinPour


    // Construction du triangle numérique
    Pour (i=0, i<n , i=i+1) faire

        Si (i = 0) alors
            tnum[i][0] = 1

        Sinon si (i = 1) alors
            tnum[i][0] = 1
            tnum[i][1] = 1

        Sinon
            tnum[i][0] = i
            tnum[i][1] = 2 × i

            milieu = i / 2

            // Construction jusqu'au milieu
            Pour (j=2, j<milieu, j=j+1) faire
                tnum[i][j] = tpas[i][j-1] + tpas[i][j]
            FinPour

            // Symétrie
            Pour (j=milieu+1 , j<=i-1, j=j+1) faire
                tnum[i][j] = tnum[i][i-j]
            FinPour

            tnum[i][i] = 1
        FinSi

    FinPour


    // Affichage
    Pour (i=0, j<=n, j=j+1) faire
        Pour (j=0, j<=i, j=j+1) faire
            Afficher tnum[i][j]
        FinPour
        Retour à la ligne
    FinPour

Fin
*/

int entier(int n);
int** pas(int n);
void triangle(int n);

int entier(int n)
{
    if (n<=0)
    {
        int rt;
        printf("Donner n : ");
        rt = scanf("%d", &n);

        while (rt <= 0)
        {
            while (getchar() != '\n'); 
            printf("Donner n : ");
            rt = scanf("%d", &n);
        }
      return n;
    }
    else
    {
      return n;
    }
}

int** pas(int n)
{
    int** tpas = malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++)
    {
        tpas[i] = malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++)
    {
        tpas[i][0] = 1;
        tpas[i][i] = 1;

        for (int j = 1; j < i; j++)
        {
            tpas[i][j] = tpas[i - 1][j - 1] + tpas[i - 1][j];
        }
    }
    return tpas;
}

void triangle(int n)
{
    int** tpas = pas(n);
    
    int** tnum = malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++)
    {
        tnum[i] = malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++)
    {
        if (i == 0)
        {
            tnum[i][0] = 1;
        }
        else if (i == 1)
        {
            tnum[i][0] = 1;
            tnum[i][1] = 1;
        }
        else
        {
            tnum[i][0] = i;
            tnum[i][1] = 2 * i;

            int milieu = i / 2;

            for (int j = 2; j <= milieu; j++)
            {
                tnum[i][j] = tpas[i][j - 1] + tpas[i][j];
            }

            for (int j = milieu + 1; j < i; j++)
            {
                tnum[i][j] = tnum[i][i - j];
            }

            tnum[i][i] = 1;
        }
    }
    
    printf("\nTriangle numerique :\n");
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            printf("%d ", tnum[i][j]);
        }
        printf("\n");
    }

    //Free
    for (int i = 0; i <= n; i++)
    {
        free(tpas[i]);
        free(tnum[i]);
    }
    free(tpas);
    free(tnum);
}

int main(int argc, char *argv[])
{
    int n=0;
    
    if (argc>1)
    {
      n=atoi(argv[1]);
    }
    
    n=entier(n);
    
    triangle(n);
    return 0;
}
