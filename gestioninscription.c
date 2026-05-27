#include <stdio.h>
#include <stdlib.h>

#define MAX_ETU 4

struct etudiant
{
    char nom[30];
    char prenoms[50];
    char jour[3];
    char mois[3];
    char annee[5];
    char adresse[30];
    char niveau[3];
};

struct temp
{
    int nom[30];  // tableau d'entiers pour stocker les valeurs des lettres
};

void rechargement(struct etudiant *etu, int *N);
void entrer(struct etudiant *etu, int *N);
void sauvegarde(struct etudiant *etu, int N);
void afficher(struct etudiant *etu, int N);
void tri_nom(struct etudiant *etu, struct temp *t, int N);
void copier_chaine(char *dest, char *src, int taille);
int  lettre_en_val(char c);

int lettre_en_val(char c)
{
    switch(c)
    {
        case 'a': case 'A': return 1;
        case 'b': case 'B': return 2;
        case 'c': case 'C': return 3;
        case 'd': case 'D': return 4;
        case 'e': case 'E': return 5;
        case 'f': case 'F': return 6;
        case 'g': case 'G': return 7;
        case 'h': case 'H': return 8;
        case 'i': case 'I': return 9;
        case 'j': case 'J': return 10;
        case 'k': case 'K': return 11;
        case 'l': case 'L': return 12;
        case 'm': case 'M': return 13;
        case 'n': case 'N': return 14;
        case 'o': case 'O': return 15;
        case 'p': case 'P': return 16;
        case 'q': case 'Q': return 17;
        case 'r': case 'R': return 18;
        case 's': case 'S': return 19;
        case 't': case 'T': return 20;
        case 'u': case 'U': return 21;
        case 'v': case 'V': return 22;
        case 'w': case 'W': return 23;
        case 'x': case 'X': return 24;
        case 'y': case 'Y': return 25;
        case 'z': case 'Z': return 26;
        default: return 0;
    }
}


void copier_chaine(char *dest, char *src, int taille)
{
    int i;
    for (i = 0; i < taille - 1 && src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
}

void tri_nom(struct etudiant *etu, struct temp *t, int N)
{
    int i, j, k;
    struct etudiant tmp;  
    for (i = 0; i < N; i++)
        for (j = 0; j < 30; j++)
            t[i].nom[j] = lettre_en_val(etu[i].nom[j]);

    for (i = 0; i < N - 1; i++) 
    {
        for (j = i + 1; j < N; j++)
        {
            k = 0;
            while (k < 30 && t[i].nom[k] == t[j].nom[k])
            {
              k++;
            }

            if (k < 30 && t[i].nom[k] > t[j].nom[k])
            {
                copier_chaine(tmp.nom, etu[i].nom,     30);
                copier_chaine(tmp.prenoms, etu[i].prenoms, 50);
                copier_chaine(tmp.jour, etu[i].jour,     3);
                copier_chaine(tmp.mois, etu[i].mois,     3);
                copier_chaine(tmp.annee, etu[i].annee,    5);
                copier_chaine(tmp.adresse, etu[i].adresse, 30);
                copier_chaine(tmp.niveau, etu[i].niveau,   3);

                copier_chaine(etu[i].nom, etu[j].nom,     30);
                copier_chaine(etu[i].prenoms, etu[j].prenoms, 50);
                copier_chaine(etu[i].jour, etu[j].jour,     3);
                copier_chaine(etu[i].mois, etu[j].mois,     3);
                copier_chaine(etu[i].annee, etu[j].annee,    5);
                copier_chaine(etu[i].adresse, etu[j].adresse, 30);
                copier_chaine(etu[i].niveau, etu[j].niveau,   3);

                copier_chaine(etu[j].nom, tmp.nom,     30);
                copier_chaine(etu[j].prenoms, tmp.prenoms, 50);
                copier_chaine(etu[j].jour, tmp.jour,     3);
                copier_chaine(etu[j].mois, tmp.mois,     3);
                copier_chaine(etu[j].annee, tmp.annee,    5);
                copier_chaine(etu[j].adresse, tmp.adresse, 30);
                copier_chaine(etu[j].niveau, tmp.niveau,   3);

                for (k = 0; k < 30; k++)  // Merci Claude pour cette partie
                {
                    int val_tmp    = t[i].nom[k];
                    t[i].nom[k]   = t[j].nom[k];
                    t[j].nom[k]   = val_tmp;
                }
            }
        }
    }
    sauvegarde(etu, N);
    printf("Tri alphabetique effectué.\n");
}

void rechargement(struct etudiant *etu, int *N)
{
    *N = 0;
    FILE *monfichier = fopen("liste_etudiants.txt", "r");
    if (monfichier == NULL)
    {
        printf("Fichier introuvable, liste vide.\n");
        return;
    }
    while (*N < MAX_ETU)
    {
        int lu = fscanf(monfichier, "%29s %49s %2s %2s %4s %29s %2s",
          etu[*N].nom,
          etu[*N].prenoms,
          etu[*N].jour,
          etu[*N].mois,
          etu[*N].annee,
          etu[*N].adresse,
          etu[*N].niveau);
        if (lu != 7) break;
        (*N)++;
    }
    fclose(monfichier);
    printf("%d etudiant(s) entre(s).\n", *N);
}

void entrer(struct etudiant *etu, int *N)
{
    if (*N >= MAX_ETU)
    {
        printf("Liste pleine (%d etudiants max).\n", MAX_ETU);
        return;
    }

    printf("Nom : ");
    scanf("%29s", etu[*N].nom);

    printf("Prenoms : ");
    scanf("%49s", etu[*N].prenoms);

    {
      char date[11];
      printf("Date de naissance (jj/mm/aaaa) : ");
      scanf("%10s", date);

      int i = 0, j = 0; //copie jour
      while (date[i] != '/' && date[i] != '\0' && j < 2)
      {etu[*N].jour[j++] = date[i++];
        etu[*N].jour[j] = '\0';
        if (date[i] == '/') i++;
      }

      j = 0;// réinitialisaton de j et copie mois
      while (date[i] != '/' && date[i] != '\0' && j < 2)
      {etu[*N].mois[j++] = date[i++];
      etu[*N].mois[j] = '\0';
      if (date[i] == '/') i++;
      } 
      j = 0;//copie annee
      while (date[i] != '\0' && j < 4)
      {etu[*N].annee[j++] = date[i++];
      etu[*N].annee[j] = '\0';
      }
    }

    printf("Adresse : ");
    scanf("%29s", etu[*N].adresse);

    printf("Niveau : ");
    scanf("%2s", etu[*N].niveau);

    (*N)++;
    sauvegarde(etu, *N);
    printf("Etudiant ajoute. Total : %d\n", *N);
}

void sauvegarde(struct etudiant *etu, int N)
{
    FILE *monfichier = fopen("liste_etudiants.txt", "w");
    if (monfichier == NULL)
    {
      printf("Erreur d'ouverture du fichier.\n");
      return;
    }
    for (int i = 0; i < N; i++)
    {
      fprintf(monfichier, "%s %s %s %s %s %s %s\n",
        etu[i].nom,
        etu[i].prenoms,
        etu[i].jour,
        etu[i].mois,
        etu[i].annee,
        etu[i].adresse,
        etu[i].niveau);
    }
    fclose(monfichier);
}

void afficher(struct etudiant *etu, int N)
{
    if (N == 0) { printf("Aucun etudiant enregistre.\n"); return; }
    printf("\n--- Liste des etudiants (%d) ---\n", N);
    for (int i = 0; i < N; i++)
    {
      printf("%d. %s %s  naissance: %s/%s/%s  adresse: %s  niveau: %s\n",
        i + 1,
        etu[i].nom, etu[i].prenoms,
        etu[i].jour, etu[i].mois, etu[i].annee,
        etu[i].adresse, etu[i].niveau);
    }
}

int main()
{
    struct etudiant etu[MAX_ETU];
    struct temp     t[MAX_ETU];
    int N = 0;
    int choix;

    rechargement(etu, &N);

    do
    {
      printf("\n====== Menu ======\n");
      printf("  [1] Entrer un etudiant\n");
      printf("  [2] Trier par ordre alphabetique\n");
      printf("  [3] Afficher la liste\n");
      printf("  [4] Quitter\n");
      printf("Votre choix : ");
      scanf("%d", &choix);

      switch(choix)
      {
          case 1: entrer(etu, &N);break;
          case 2: tri_nom(etu, t, N);
                  afficher(etu, N);break;
          case 3: afficher(etu, N);break;
          case 4: printf("Au revoir.\n");break;
          default: printf("Choix invalide, reessayez.\n");break;
      }
    } while (choix != 0 || choix !=1 || choix != 2 || choix != 3 || choix !=4);
    return 0;
    
}
