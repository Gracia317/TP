#include <stdio.h>

/* Algorithme TriangleNumerique

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

int main()
{
    int n;
    int i, j, milieu;

    printf("Donner n : ");
    scanf("%d", &n);

    int tpas[n + 1][n + 1];
    int tnum[n + 1][n + 1];

    //TRIANGLE DE PASCAL

    for (i = 0; i <= n; i++)
    {
        tpas[i][0] = 1;
        tpas[i][i] = 1;

        for (j = 1; j < i; j++)
        {
            tpas[i][j] =
                tpas[i - 1][j - 1] +
                tpas[i - 1][j];
        }
    }
    
    //TRIANGLE NUMERIQUE

    for (i = 0; i <= n; i++)
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
            //Première colonne
            tnum[i][0] = i;

            // Deuxième colonne
            tnum[i][1] = 2 * i;

            milieu = i / 2;

            //Partie gauche
            for (j = 2; j <= milieu; j++)
            {
                tnum[i][j] =
                    tpas[i][j - 1] +
                    tpas[i][j];
            }

            // Partie droite par symétrie
            for (j = milieu + 1; j < i; j++)
            {
                tnum[i][j] = tnum[i][i - j];
            }

            // Dernier élément
            tnum[i][i] = 1;
        }
    }
    
    //AFFICHAGE

    printf("\nTriangle numerique :\n");

    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= i; j++)
        {
            printf("%d ", tnum[i][j]);
        }

        printf("\n");
    }

    return 0;
}
