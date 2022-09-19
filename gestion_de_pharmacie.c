#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int n = 0, npa = 0;

struct Produit
{
    int code;
    char nom[100];
    int quantite;
    int prix;
    int TTC;
};

struct HistoryAchat
{
    time_t time;
    int quantite;
    int prixTotale;
    struct Produit produit;
};

struct Stock
{
    int revenu;
    int nbrProduit;
    struct HistoryAchat historyAchat[1000];
};
// ajouter un nouveau produit saisie par l'utilisateur
void ajouterUnProduit(struct Produit produit[100])
{
    printf("ajouter le code de produit :\n");
    scanf("%d", &produit[n].code);
    printf("ajouter le nom de produit :\n");
    scanf("%s", &produit[n].nom);
    printf("ajouter le prix de produit:\n");
    scanf("%d", &produit[n].prix);
    printf("ajouter la quantite de produit:\n");
    scanf("%d", &produit[n].quantite);
    produit[n].TTC = produit[n].prix * 0.15 + produit[n].prix;
    printf("le prix TTC est %d\n", produit[n].TTC);
    n++;
}

void afficherProduits(struct Produit produit[100])
{
    for (int i = 0; i < n; i++)
    {
        printf("\t\t\t_________________________________________________________________\n");
        printf("\t\t\t||numero|code   |nom        |prix    |quantite |TCC||\n");
        printf("\t\t\t|| %d  ", i + 1);
        printf("\t\t\t%d     ", produit[i].code);
        printf("\t\t\t%s     ", produit[i].nom);
        printf("\t\t\t%d    ", produit[i].prix);
        printf("\t\t\t%d     ", produit[i].quantite);
        printf("\t\t\t%d     ||\n", produit[i].TTC);
        printf("\t\t\t__________________________________________________________________\n");
    }
}

// cette fonction fait un tri par bull d'ordre alphabitique croissant

void triProduitsAlphabetique(struct Produit produit[100])
{
    struct Produit p;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(produit[i].nom, produit[j].nom) > 0)
            {
                p = produit[i];
                produit[i] = produit[j];
                produit[j] = p;
                break;
            }
        }
    }
    afficherProduits(produit);
}

// cette fonction fait un tri par bull l'ordre decroissant de prix
void triProduitsPrix(struct Produit produit[100])
{
    struct Produit p;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (produit[i].prix < produit[j].prix)
            {
                p = produit[i];
                produit[i] = produit[j];
                produit[j] = p;
            }
        }
    }
    afficherProduits(produit);
}

int recherche(int code, struct Produit produit[100])
{
    int count = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (produit[i].code == code)
        {
            return (i + 1);
            break;
        }
        else
        {
            count++;
        }
    }
    if (count == n)
    {
        return 0;
    }
}

// acheter un produit

void acheterProduit(struct Produit produit[100], struct Stock *stock, int code)
{
    int quantite;
    time_t timeV;
    time(&timeV);
    int i = recherche(code, produit);
    if (i == 0)
    {
        printf("se produit n'existe pas");
    }
    else
    {
        printf("enter la contite que vous voulez");
        scanf("%d", &quantite);
        if (produit[i - 1].quantite >= quantite)
        {
            produit[i - 1].quantite -= quantite;
            stock->revenu += produit[i - 1].TTC * quantite;
            stock->historyAchat[npa].time = timeV;
            stock->historyAchat[npa].produit = produit[i - 1];
            stock->historyAchat[npa].quantite = quantite;
            stock->historyAchat[npa].prixTotale = produit[i - 1].TTC * quantite;
            printf("\t\t\t_________________________________________________________________\n");
            printf("\t\t\t||code   |nom        |prix    |quantite |la quantite restant|totale prix|time d'achat ||\n");
            printf("\t\t\t%d     ", npa);
            printf("%d     ", stock->historyAchat[npa].produit.code);
            printf("%s     ", stock->historyAchat[npa].produit.nom);
            printf("%d     ", stock->historyAchat[npa].produit.prix);
            printf("%d     ", stock->historyAchat[npa].quantite);
            printf("%d     ", produit[i - 1].quantite);
            printf("%d    ", stock->historyAchat[npa].prixTotale);
            printf("%s    \n", ctime(&stock->historyAchat[npa].time));
            printf("\t\t\t__________________________________________________________________\n");
            npa++;
        }
        else
        {
            printf("la quantite que vous avez demander est superieur de se qu'on a dans le stock :%d", produit[i - 1].quantite);
        }
    }
}

//
void affichageAchat(struct Stock *stock)
{

    for (int j = 0; j < npa; j++)
    {
        printf("\t\t\t_________________________________________________________________\n");
        printf("\t\t\t||code   |nom        |prix    |quantite |totale prix|time d'achat ||\n");
        printf("\t\t\t%d     ", j);
        printf("%d     ", stock->historyAchat[j].produit.code);
        printf("%s     ", stock->historyAchat[j].produit.nom);
        printf("%d     ", stock->historyAchat[j].produit.prix);
        printf("%d     ", stock->historyAchat[j].quantite);
        printf("%d    ", stock->historyAchat[j].prixTotale);
        printf("%s    \n", ctime(&stock->historyAchat[j].time));
        printf("\t\t\t__________________________________________________________________\n");
    }
}

// fonction de display de menu
void Menu(struct Produit produit[100], struct Stock *stock)
{
    int choix, nbr, codeProduit;
    do
    {
        printf("\t\t\t************************************************************************************\n");
        printf("\t\t\t____________________________________________________________________________________\n");
        printf("\t\t\t|ajouter un produit entrer 1                                                        |\n");
        printf("\t\t\t____________________________________________________________________________________\n");
        printf("\t\t\t|ajouter plusieurs nouveaux produits au meme temps entrer2                          |\n");
        printf("\t\t\t____________________________________________________________________________________\n");
        printf("\t\t\t|afficher tous les produits selon l'ordre alphabetique croissant du nom entrer 3    |\n");
        printf("\t\t\t____________________________________________________________________________________\n");
        printf("\t\t\t|afficher tous les produits selon l'ordre decroissant du prix entrer 4              |\n");
        printf("\t\t\t____________________________________________________________________________________\n");
        printf("\t\t\t|acheter un produit entrer 5                                                        |\n");
        printf("\t\t\t____________________________________________________________________________________\n");
        printf("\t\t\t|rechercher les produits par code/quantite/etat de stock entrer 6                   |\n");
        printf("\t\t\t____________________________________________________________________________________\n");
        printf("\t\t\t|alimenter le stock entrer 7                                                        |\n");
        printf("\t\t\t____________________________________________________________________________________\n");
        printf("\t\t\t|supprimer les produits par code entrer 8                                           |\n");
        printf("\t\t\t____________________________________________________________________________________\n");
        printf("\t\t\t|afficher le totale de prix des produits vendus en journee courante entrer 9        |\n");
        printf("\t\t\t____________________________________________________________________________________\n");
        printf("\t\t\t|afficher la moyenne de prix des produits vendus en journee courante entrer 10      |\n");
        printf("\t\t\t____________________________________________________________________________________\n");
        printf("\t\t\t|afficher le max de prix des produits vendus en journee courante entrer 11          |\n");
        printf("\t\t\t____________________________________________________________________________________\n");
        printf("\t\t\t|afficher le min de prix des produits vendus en journee courante entrer 12          |\n");
        printf("\t\t\t____________________________________________________________________________________\n");
        printf("\t\t\t|entrer un nombre de votre choix et si vous voulez sortir du programme entrer 0     |\n");
        printf("\t\t\t____________________________________________________________________________________\n");
        printf("\t\t\t************************************************************************************\n");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            // ajouter un seul produit
            ajouterUnProduit(produit);
            break;
        case 2:
            // ajouter plusieur produit
            printf("entrer le nombre de produits que vous voulez saisir\n");
            scanf("%d", &nbr);
            for (int i = 0; i < nbr; i++)
            {
                ajouterUnProduit(produit);
            }
            break;
        case 3:
            triProduitsAlphabetique(produit);
            break;
        case 4:
            triProduitsPrix(produit);
            break;
        case 5:
            printf("entrer le code de produit que vous voulez acheter\n");
            scanf("%d", &nbr);
            acheterProduit(produit, stock, nbr);
            break;
        case 6:
            printf("entrer le code de produit que vous voulez acheter\n");
            scanf("%d", &nbr);
            int i = recherche(nbr, produit);
            if (i == 0)
            {
                printf("produit n'existe pas");
            }
            else
            {
                printf("\t\t\t_________________________________________________________________\n");
                printf("\t\t\t||numero|code   |nom        |prix    |TCC||\n");
                printf("\t\t\t|| %d  ", i);
                printf("\t\t\t%d     ", produit[i - 1].code);
                printf("\t\t\t%s     ", produit[i - 1].nom);
                printf("\t\t\t%d    ", produit[i - 1].prix);
                printf("\t\t\t%d     ||\n", produit[i - 1].TTC);
                printf("\t\t\t__________________________________________________________________\n");
            }
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
        case 13:
            affichageAchat(stock);
            break;
        default:
            printf("s'il vous plait entrer un nombre entre 1 et 12");
            break;
        }
    } while (choix != 0);
}
int main()
{
    struct Produit produit[100];
    struct Stock stock;
    time_t now;
    time(&now);
    Menu(produit, &stock);
}