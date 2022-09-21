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
    int nbrPro;
};

struct Stock
{
    int revenu;
    int nbrProduit;
    struct HistoryAchat historyAchat[1000];
};
void printDecor()
{
    system("cls");
    system("COLOR 7B");
    printf("\t \t*******************************************************************\n");
    printf("\t\t =====================# Gestion de Pharmacie #===================== \n");
    printf("\t \t*******************************************************************\n");
    printf("\n \n \n \n \n");
}
int recherche(int code, struct Produit produit[])
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (produit[i].code == code)
        {
            return (i);
            break;
        }
        else
        {
            count++;
        }
    }
    if (count == n)
    {
        return -1;
    }
}
// ajouter un nouveau produit saisie par l'utilisateur
void ajouterUnProduit(struct Produit produit[])
{
    int code;
    printf("ajouter le code de produit :\n");
    scanf("%d", &code);
    int i = recherche(code, produit);
    if (i == -1)
    {   if(code>0){
        produit[n].code = code;
        fflush(stdin);
        printf("ajouter le nom de produit :\n");
        scanf("%[^\n]%*c", produit[n].nom);
        fflush(stdin);
        printf("ajouter le prix de produit:\n");
        scanf("%d", &produit[n].prix);
        printf("ajouter la quantite de produit:\n");
        scanf("%d", &produit[n].quantite);
        produit[n].TTC = produit[n].prix * 0.15 + produit[n].prix;
        printf("le prix TTC est %d\n", produit[n].TTC);
        n++;
        }else{
            printf("veuille entrer un code qui ne contient pas - ");
        }
    }
    else
    {
        printf("vous avez entre un code d'un produit qui deja existe");
    }
}

void afficherProduits(struct Produit produit[])
{
    printf("\t\t\t_________________________________________________________________\n");
    printf("\t\t\t||numero|code       |nom        |prix    |quantite |TCC          ||\n");
    printf("\t\t\t||_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _||\n");

    for (int i = 0; i < n; i++)
    {
        printf("\t\t\t|| %d   %d       %s          %d       %d       %d           ||\n", i + 1, produit[i].code, produit[i].nom, produit[i].prix, produit[i].quantite, produit[i].TTC);
        printf("\t\t\t__________________________________________________________________\n");
    }
}

// cette fonction fait un tri par bull d'ordre alphabitique croissant

void triProduitsAlphabetique(struct Produit produit[])
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
void triProduitsPrix(struct Produit produit[])
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

int rechercheQuantite(int quantite, struct Produit produit[])
{
    printf("\t\t\t|code   |nom      |quantite    |prix");
    printf("\t\t\t||_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _||\n");
    for (int i = 0; i < n; i++)
    {
        if (produit[i].quantite == quantite)
        {
            printf("\t\t\t|%d    %s      %d        %d", produit[i].code, produit[i].nom, produit[i].quantite, produit[i].prix);
            printf("\t\t\t______________________________________");
        }
    }
}

// acheter un produit

void acheterProduit(struct Produit produit[], struct Stock *stock, int code)
{
    int quantite;
    int valide;
    time_t timeV;
    time(&timeV);
    int i = recherche(code, produit);
    if (i == (-1))
    {
        printf("se produit n'existe pas");
    }
    else
    {
        do
        {
            printf("est ce que le produit que vous voulez acheter:%s avec le code %d n entrer 1 si oui ou entrer 0 si non \t", produit[i - 1].nom, produit[i - 1].code);
            scanf("%d", &valide);
            switch (valide)
            {

            case 1:
                printf("enter la quantite que vous voulez\n");
                scanf("%d", &quantite);
                if(quantite<=0){
                printf("veuille entrer un nombre positive qui est different de 0\n");
                }else{
                if (produit[i].quantite >= quantite)
                {
                    produit[i].quantite -= quantite;
                    stock->revenu += produit[i].TTC * quantite;
                    stock->historyAchat[npa].time = timeV;
                    stock->historyAchat[npa].nbrPro = i;
                    stock->historyAchat[npa].quantite = quantite;
                    stock->historyAchat[npa].prixTotale = produit[i].TTC * quantite;
                    npa++;
                }
                else
                {
                    printf("la quantite que vous avez demander est superieur de se qu'on a dans le stock :%d\n", produit[i].quantite);
                }
                }
                break;
            case 0:
                printf("vous avez choisi de ne pas continuer cette operation\n");
                break;
            default:
                printf("entrer soit 1 soit 0\n");
                valide = 3;
                break;
            }
        } while (valide == 3);
    }
}

//
void affichageAchat(struct Stock *stock, struct Produit produit[])
{
    printf("\t\t\t___________________________________________________________________________________\n");
    printf("\t\t\t||number |code   |nom               |prix    |quantite |totale prix|time d'achat              ||\n");
    printf("\t\t\t||_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ ||\n");
    for (int j = 0; j < npa; j++)
    {
        int i = stock->historyAchat[j].nbrPro;
        printf("\t\t\t||%d   %d   %s       %d      %d       %d         %s                        \n", j, produit[i].code, produit[i].nom, produit[i].prix, stock->historyAchat[j].quantite, stock->historyAchat[j].prixTotale, ctime(&stock->historyAchat[j].time));
        printf("\t\t\t____________________________________________________________________________________\n");
    }
}

// alimenter
void alimenterStock(struct Produit produit[], int code)
{
    int quantite;
    int i = recherche(code, produit);
    if (i == -1)
    {
        printf("se produit n'existe pas\n");
    }
    else
    {
        printf("enter la contite que vous voulez ajouter dans le stock de se produit\n");
        scanf("%d", &quantite);

        produit[i].quantite += quantite;
    }
}

// supprimer un produit
void supprimerProduit(struct Produit produit[], int code)
{
    int i = recherche(code, produit);
    if (i == -1)
    {
        printf("se produit n'existe pas\n");
    }
    else
    {

        for (int j = i; j < n; j++)
        {
            produit[j] = produit[j + 1];
        }
        n--;
    }
}

// statitsique
void totaleRevenuJournee(struct Stock *stock)
{
    printf("le revenu totale est :%d\n", stock->revenu);
}
// statitsique
void moyenneRevenuJournee(struct Stock *stock)
{
    int sp = 0, sprixTotale = 0;
    float moyenne;
    for (int i = 0; i < npa; i++)
    {
        sprixTotale += stock->historyAchat[i].prixTotale;
        sp += stock->historyAchat[i].quantite;
    }
    moyenne = (float)sprixTotale / sp;
    printf("le max revenu est :%f\n", moyenne);
}
// statitsique
void maxRevenuJournee(struct Stock *stock,struct Produit produit[])
{
    int max = 0, position = 0,sprixTotale[100];
    for (int i = 0; i < npa; i++)
    {   
        sprixTotale[i]=stock->historyAchat[i].prixTotale;
        for(int j=i+1;j<npa;i++){
            if(produit[stock->historyAchat[i].nbrPro].code==produit[stock->historyAchat[j].nbrPro].code){
                sprixTotale[i]+=stock->historyAchat[j].prixTotale;
            }
        } 
        if(sprixTotale[i]>max){
            max=sprixTotale[i];
            position=i;
        }
          
    }

    printf("le meilleur niche avec un prix totale de  :%d est le produit avec le code %d et le nom %s\n", max,produit[stock->historyAchat[position].nbrPro].code,produit[stock->historyAchat[position].nbrPro].nom);
}
// statitsique
void minRevenuJournee(struct Stock *stock,struct Produit produit[])
{
    int min = 0, position = 0,sprixTotale[100];
    for (int i = 0; i < npa; i++)
    {  sprixTotale[i]=stock->historyAchat[i].prixTotale;
        for(int j=i+1;j<npa;i++){
            if(produit[stock->historyAchat[i].nbrPro].code==produit[stock->historyAchat[j].nbrPro].code){
                sprixTotale[i]+=stock->historyAchat[j].prixTotale;
            }
        }   
      if(sprixTotale[i]<min){
            min=sprixTotale[i];
            position=i;
        }
    }
    printf("le meilleur niche avec un prix totale de  :%d est le produit avec le code %d et le nom %s\n", min,produit[stock->historyAchat[position].nbrPro].code,produit[stock->historyAchat[position].nbrPro].nom);
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
            printDecor();
            // ajouter un seul produit
            ajouterUnProduit(produit);
            break;
        case 2:
            printDecor();
            // ajouter plusieur produit
            printf("entrer le nombre de produits que vous voulez saisir\n");
            scanf("%d", &nbr);
            for (int i = 0; i < nbr; i++)
            {
                ajouterUnProduit(produit);
            }
            break;
        case 3:
            printDecor();
            triProduitsAlphabetique(produit);
            break;
        case 4:
            printDecor();
            triProduitsPrix(produit);
            break;
        case 5:
            printDecor();
            afficherProduits(produit);
            printf("entrer le code de produit que vous voulez acheter\n");
            scanf("%d", &nbr);
            acheterProduit(produit, stock, nbr);
            break;
        case 6:
            printDecor();
            printf("entrer le code de produit que vous voulez acheter\n");
            scanf("%d", &nbr);
            int i = recherche(nbr, produit);
            if (i == -1)
            {
                printf("produit n'existe pas");
            }
            else
            {
                printf("\t\t\t_________________________________________________________\n");
                printf("\t\t\t||numero|code   |nom              |prix    |TCC        ||\n");
                printf("\t\t\t||_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _||\n");
                printf("\t\t\t|| %d  %d     %s          %d      %d        \n", i, produit[i].code, produit[i].nom, produit[i].prix, produit[i].TTC);
                printf("\t\t\t||_____________________________________________________||\n");
            }
            break;
        case 7:
            printDecor();
            printf("entrer le code de produit que vous voulez acheter\n");
            scanf("%d", &nbr);
            alimenterStock(produit, nbr);
            afficherProduits(produit);
            break;
        case 8:
            printDecor();
            printf("entrer le code de produit que vous voulez acheter\n");
            scanf("%d", &nbr);
            supprimerProduit(produit, nbr);
            afficherProduits(produit);
            break;
        case 9:
            printDecor();
            totaleRevenuJournee(stock);
            break;
        case 10:
            printDecor();
            moyenneRevenuJournee(stock);
            break;
        case 11:
            printDecor();
            maxRevenuJournee(stock,produit);
            break;
        case 12:
            printDecor();
            minRevenuJournee(stock,produit);
            break;
        case 13:
            printDecor();
            affichageAchat(stock, produit);
            break;
        default:
            printf("s'il vous plait entrer un nombre entre 1 et 12");
            break;
        }
         system("pause");
    } while (choix != 0);
}
int main()
{
    struct Produit produit[100];
    struct Stock stock;
    Menu(produit, &stock);
}