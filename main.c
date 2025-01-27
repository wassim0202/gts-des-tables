#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLES 5
#define MAX_RECORDS 10

char tables[MAX_TABLES][20];
int tableCount = 0;

void creerTable() {
    if (tableCount >= MAX_TABLES) {
        printf("Limite des tables atteinte.\n");
        return;
    }
    printf("Nom de la nouvelle table : ");
    scanf("%s", tables[tableCount]);
    tableCount++;
    printf("Table creee avec succes !\n");
}

void modifierTable() {
    int index;
    printf("Quelle table voulez-vous modifier (0 a %d) ? ", tableCount - 1);
    scanf("%d", &index);

    if (index >= 0 && index < tableCount) {
        printf("Nouveau nom pour la table %s : ", tables[index]);
        scanf("%s", tables[index]);
        printf("Table modifiee avec succes !\n");
    } else {
        printf("Index invalide.\n");
    }
}

void supprimerTable() {
    int index;
    printf("Quelle table voulez-vous supprimer (0 à %d) ? ", tableCount - 1);
    scanf("%d", &index);

    if (index >= 0 && index < tableCount) {
        for (int i = index; i < tableCount - 1; i++) {
            strcpy(tables[i], tables[i + 1]);
        }
        tableCount--;
        printf("Table supprimee avec succes !\n");
    } else {
        printf("Index invalide.\n");
    }
}

typedef struct {
    int id;
    char nom[20];
} Enregistrement;

Enregistrement enregistrements[MAX_RECORDS];
int recordCount = 0;

void creerEnregistrement() {
    if (recordCount >= MAX_RECORDS) {
        printf("Limite des enregistrements atteinte.\n");
        return;
    }
    printf("ID : ");
    scanf("%d", &enregistrements[recordCount].id);
    printf("Nom : ");
    scanf("%s", enregistrements[recordCount].nom);
    recordCount++;
    printf("Enregistrement cree avec succes !\n");
}

void lireEnregistrements() {
    printf("\nListe des enregistrements :\n");
    for (int i = 0; i < recordCount; i++) {
        printf("ID : %d, Nom : %s\n", enregistrements[i].id, enregistrements[i].nom);
    }
}

void mettreAJour() {
    int id, found = 0;
    printf("ID de l'enregistrement a mettre a jour : ");
    scanf("%d", &id);

    for (int i = 0; i < recordCount; i++) {
        if (enregistrements[i].id == id) {
            printf("Nouveau nom : ");
            scanf("%s", enregistrements[i].nom);
            printf("Enregistrement mis a jour !\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Enregistrement introuvable.\n");
    }
}

void supprimerEnregistrement() {
    int id, found = 0;
    printf("ID de l'enregistrement a supprimer : ");
    scanf("%d", &id);

    for (int i = 0; i < recordCount; i++) {
        if (enregistrements[i].id == id) {
            for (int j = i; j < recordCount - 1; j++) {
                enregistrements[j] = enregistrements[j + 1];
            }
            recordCount--;
            printf("Enregistrement supprime !\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Enregistrement introuvable.\n");
    }
}

void sauvegarderDonnees() {
    FILE *fichier = fopen("donnees.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fprintf(fichier, "%d\n", tableCount);
    for (int i = 0; i < tableCount; i++) {
        fprintf(fichier, "%s\n", tables[i]);
    }

    fprintf(fichier, "%d\n", recordCount);
    for (int i = 0; i < recordCount; i++) {
        fprintf(fichier, "%d %s\n", enregistrements[i].id, enregistrements[i].nom);
    }

    fclose(fichier);
    printf("Données sauvegardees avec succes !\n");
}

void chargerDonnees() {
    FILE *fichier = fopen("donnees.txt", "r");
    if (fichier == NULL) {
        printf("Aucune donne e charger.\n");
        return;
    }

    fscanf(fichier, "%d", &tableCount);
    for (int i = 0; i < tableCount; i++) {
        fscanf(fichier, "%s", tables[i]);
    }

    fscanf(fichier, "%d", &recordCount);
    for (int i = 0; i < recordCount; i++) {
        fscanf(fichier, "%d %s", &enregistrements[i].id, enregistrements[i].nom);
    }

    fclose(fichier);
    printf("Données chargees avec succes !\n");
}

void trierEnregistrements() {
    for (int i = 0; i < recordCount - 1; i++) {
        for (int j = i + 1; j < recordCount; j++) {
            if (strcmp(enregistrements[i].nom, enregistrements[j].nom) > 0) {
                Enregistrement temp = enregistrements[i];
                enregistrements[i] = enregistrements[j];
                enregistrements[j] = temp;
            }
        }
    }
    printf("Enregistrements tries par nom !\n");
}

void rechercherEnregistrement() {
    char nom[20];
    printf("Nom a rechercher : ");
    scanf("%s", nom);

    for (int i = 0; i < recordCount; i++) {
        if (strcmp(enregistrements[i].nom, nom) == 0) {
            printf("ID : %d, Nom : %s\n", enregistrements[i].id, enregistrements[i].nom);
            return;
        }
    }
    printf("Aucun enregistrement trouve.\n");
}

void menuPrincipal() {
    int choix;
    chargerDonnees();

    do {
        printf("\n1. Gestion des tables\n2. Operations CRUD\n3. Sauvegarder les donnees\n4. Trier les enregistrements\n5. Rechercher un enregistrement\n6. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n1. Creer une table\n2. Modifier une table\n3. Supprimer une table\n");
                printf("Votre choix : ");
                int sousChoix;
                scanf("%d", &sousChoix);
                if (sousChoix == 1) creerTable();
                else if (sousChoix == 2) modifierTable();
                else if (sousChoix == 3) supprimerTable();
                else printf("Choix invalide.\n");
                break;
            case 2:
                printf("\n1. Creer un enregistrement\n2. Lire les enregistrements\n3. Mettre à jour\n4. Supprimer\n");
                printf("Votre choix : ");
                scanf("%d", &sousChoix);
                if (sousChoix == 1) creerEnregistrement();
                else if (sousChoix == 2) lireEnregistrements();
                else if (sousChoix == 3) mettreAJour();
                else if (sousChoix == 4) supprimerEnregistrement();
                else printf("Choix invalide.\n");
                break;
            case 3: sauvegarderDonnees(); break;
            case 4: trierEnregistrements(); break;
            case 5: rechercherEnregistrement(); break;
            case 6: printf("Au revoir !\n"); sauvegarderDonnees(); break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 6);
}

int main() {
    menuPrincipal();
    return 0;
}
