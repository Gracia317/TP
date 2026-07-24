#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_MAT 4
#define FICHIER "etudiants.txt"

struct Etudiant{
	char nom[50];
        char prenom[50];
        float notes[MAX_MAT];
        float moyenne;
};

int nb(void);
void saisirUnEtudiant(struct Etudiant *e);
void saisirEtudiant(struct Etudiant e[], int n);
float somme(struct Etudiant *e);
void moyenne(struct Etudiant e[], int n);
void sauvegarder(struct Etudiant e[], int n, const char *nomFichier);
int relire(struct Etudiant **e, const char *nomFichier);
void afficherFichier(struct Etudiant e[], int n);

int nb(void)
{
	int n;
   	do {
        	printf("Nombre d'etudiants : ");
        	scanf("%d", &n);
   	 } while (n < 1);
    	getchar();
    	return n;
}

void saisirUnEtudiant(struct Etudiant *e)
{
    /*permet la siasie d'un etudiat*/
    printf("Nom : ");
    fgets(e->nom, sizeof(e->nom), stdin);
    e->nom[strcspn(e->nom, "\n")] = '\0';

    printf("Prenom : ");
    fgets(e->prenom, sizeof(e->prenom), stdin);
    e->prenom[strcspn(e->prenom, "\n")] = '\0';

    for (int j = 0; j < MAX_MAT; j++) {
        printf("Note %d : ", j + 1);
        scanf("%f", &e->notes[j]);
    }
    getchar();
}

void saisirEtudiant(struct Etudiant e[], int n)
{
    for (int i = 0; i < n; i++) {
	    saisirUnEtudiant(&e[i]);
            printf("\n");
    }
}

float somme(struct Etudiant *e)
{
    float s = 0;
    for (int k = 0; k < MAX_MAT; k++) {
        s += e->notes[k];
    }
    return s;
}

void moyenne(struct Etudiant e[], int n)
{
    for (int i = 0; i < n; i++) {
        e[i].moyenne = somme(&e[i]) / MAX_MAT;
    }
}

void sauvegarder(struct Etudiant e[], int n, const char *nomFichier)
{
	FILE *fichier = fopen(nomFichier, "w");
        if (fichier == NULL) {
            printf("Erreur : impossible d'ouvrir %s en ecriture\n", nomFichier);
            return;
        }

    fprintf(fichier, "%d Etudiants\n", n);
    fprintf(fichier, "---------------------------------------\n");
    for (int i = 0; i < n; i++) {
        fprintf(fichier, "%s\n%s\n%.2f\n", e[i].nom, e[i].prenom, e[i].moyenne);
    }

    fclose(fichier);
    printf("\nDonnees sauvegardees dans %s.\n", nomFichier);
}

/* Relit le fichier et alloue dynamiquement le tableau d'etudiants correspondant. Retourne le nombre d'etudiants lus (0 en cas d'erreur). */
int relire(struct Etudiant **e, const char *nomFichier)
{
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir %s en lecture\n", nomFichier);
        return 0;
    }

    int n;
    if (fscanf(fichier, "%d", &n) != 1) {
        printf("Erreur : fichier %s mal forme\n", nomFichier);
        fclose(fichier);
        return 0;
    }

    *e = malloc(n * sizeof(struct Etudiant));
    if (*e == NULL) {
        printf("Erreur memoire\n");
        fclose(fichier);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        fgets((*e)[i].nom, sizeof((*e)[i].nom), fichier);
        (*e)[i].nom[strcspn((*e)[i].nom, "\n")] = '\0';

        fgets((*e)[i].prenom, sizeof((*e)[i].prenom), fichier);
        (*e)[i].prenom[strcspn((*e)[i].prenom, "\n")] = '\0';

        fscanf(fichier, "%f", &(*e)[i].moyenne);
    }

    fclose(fichier);
    return n;
}

void afficherFichier(struct Etudiant e[], int n)
{
    printf("\nLecture du fichier :\n");
    for (int i = 0; i < n; i++) {
        printf("%s | %s | Moyenne : %.2f\n", e[i].nom, e[i].prenom, e[i].moyenne);
    }
}

int main(void)
{
        struct Etudiant *classe;

        int n = nb();

        classe = malloc(n * sizeof(struct Etudiant));
        if (classe == NULL) {
            printf("Erreur memoire\n");
            return 1;
        }

       saisirEtudiant(classe, n);
       moyenne(classe, n);

       sauvegarder(classe, n, FICHIER);
       free(classe);

       struct Etudiant *relu = NULL;
       int nRelu = relire(&relu, FICHIER);
       if  (nRelu > 0) {
           afficherFichier(relu, nRelu);
           free(relu);
       }

	return 0;
}
