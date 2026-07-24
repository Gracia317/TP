#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_MAT 4

struct Etudiant{
        char nom[50];
        char prenom[50];
        int age;
        char matricule[20];
        float notes[MAX_MAT];
        float moyenne;
};

int nb(void);
void saisirUnEtudiant(struct Etudiant *e);
void saisirEtudiant(struct Etudiant e[], int n);
float somme(struct Etudiant *e);
void moyenne(struct Etudiant e[], int n);
void showall(struct Etudiant e[], int n);

int nb(void)
{
    int n;
    do {
	printf("Combien d'étudiants voulez-vous saisir : ");
	scanf("%d", &n);
    } while (n < 1);
    getchar(); /* absorbe le '\n' laissé par scanf avant le premier fgets */
    return n;
}

void saisirUnEtudiant(struct Etudiant *e)
{
    printf("Nom : ");
    fgets(e->nom, sizeof(e->nom), stdin);
    e->nom[strcspn(e->nom, "\n")] = '\0';
    printf("Prenom : ");
    fgets(e->prenom, sizeof(e->prenom), stdin);
    e->prenom[strcspn(e->prenom, "\n")] = '\0';
	for (int j = 0; j < MAX_MAT; j++) {
        printf("note %d : ", j + 1);
        scanf("%f", &e->notes[j]);
    }
    getchar();
}

void saisirEtudiant(struct Etudiant e[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("Etudiant %d\n", i + 1);
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

void showall(struct Etudiant e[], int n)
{
    printf("Liste des étudiants :\n");
    for (int i = 0; i < n; i++) {
        printf("%s %s : %.2f\n", e[i].nom, e[i].prenom, e[i].moyenne);
    }
}

void modifier(struct Etudiant e[], int n)
{
	printf("Numero de l'etudiant que vous voulez modifier : ");
	int num;
	//amelioration possible: ajout de gestion d'erreur de saisie de numero ohatra rhf sanatria vide na stanatria tsy numero ilay izy
	scanf("%d", &num);
	if (num<1 || num>n) {
		printf("Numero invalide");
		return;
	}
	getchar();
	saisirUnEtudiant(&e[num-1]);
	printf("\n");
	showall(e, n);
}	

void rechercher(struct Etudiant e[], int n)
{
	printf("\n");
	printf("Un motif de l'etudiant que vous souhaitez rechercher : ");
	struct Etudiant *motif;
	motif = malloc(sizeof(struct Etudiant));
 
	if (motif == NULL) {
		printf("Erreur memoire\n");
		return;
	}
 
	fgets(motif->nom, sizeof(motif->nom), stdin);
	motif->nom[strcspn(motif->nom, "\n")] = '\0';
 
	int trouve = 0;
	for (int i = 0; i < n; i++) {
		if (strstr(e[i].nom, motif->nom) != NULL || strstr(e[i].prenom, motif->nom) != NULL)
	       	{		
			printf("\n");
			printf("Etudiant %d\n", i + 1);
			printf("%s %s : %.2f\n", e[i].nom, e[i].prenom, e[i].moyenne);
			printf("\n");
			trouve = 1;
		}
	}
	if (!trouve) {
		printf("Aucun etudiant correspondant\n");
	}
	free(motif);
}

int main()
{
	struct Etudiant *classe;

	int n = nb();

	classe = malloc(n * sizeof(struct Etudiant));

	if (classe==NULL) {
                printf("Erreur mémoire\n");
                return 1;
        }

    	saisirEtudiant(classe, n);
	moyenne(classe, n);
	showall(classe, n);
	printf("\n");
	modifier(classe, n);
	rechercher(classe, n);

	free (classe);
	return 0;
}

