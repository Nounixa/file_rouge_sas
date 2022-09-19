# include<stdlib.h>
# include<stdio.h>
# include<string.h>

int n=0;

struct Produit{
    int code;
    char nom[100];
    int prix;
    int TTC;
};

// ajouter un nouveau produit saisie par l'utilisateur
void ajouterUnProduit(struct Produit produit[100]){
    printf("ajouter le code de produit :\n");
    scanf("%d",&produit[n].code);
    printf("ajouter le nom de produit :\n");
    scanf("%s",&produit[n].nom);
    printf("ajouter le prix de produit:\n");
    scanf("%d",&produit[n].prix);
    produit[n].TTC=produit[n].prix*0.15+produit[n].prix;
    printf("le prix TTC est %d\n",produit[n].TTC);
    n++;
}

void afficherProduits(struct Produit produit[100]){
 for(int i=0;i<n;i++){
    printf("***********\n");
    printf("produit numero %d :",i+1);
    printf("nom:%d\n",produit[i].code);
    printf("nom:%s\n",produit[i].nom);
    printf("prix:%d\n",produit[i].prix);
    printf("prix TTC:%d\n",produit[i].TTC);
    printf("***********\n");
    }
}

// cette fonction fait un tri par bull d'ordre alphabitique croissant

void triProduitsAlphabetique(struct Produit produit[100]){
    struct Produit p;
      for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
        if(strcmp(produit[i].nom,produit[j].nom)>0){
             p=produit[i];
             produit[i]=produit[j];
             produit[j]=p;
        }
       }
      }
   afficherProduits(produit);
}

// cette fonction fait un tri par bull l'ordre decroissant de prix
void triProduitsPrix(struct Produit produit[100]){
    struct Produit p;
      for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
        if(produit[i].prix<produit[j].prix){
             p=produit[i];
             produit[i]=produit[j];
             produit[j]=p;
        }
       }
      }
   afficherProduits(produit);
}

// fonction de display de menu 
void Menu(struct Produit produit[100]){
    int choix,nbr;
    do{ 
        printf("ajouter un produit entrer 1\n");
        printf("ajouter plusieurs nouveaux produits au meme temps entrer2\n");
        printf("afficher tous les produits selon l'ordre alphabetique croissant du nom entrer 3\n");
        printf("afficher tous les produits selon l'ordre decroissant du prix entrer 4\n");
        printf("acheter un produit entrer 5\n");
        printf("rechercher les produits par code/quantite/etat de stock entrer 6\n");
        printf("alimenter le stock entrer 7\n");
        printf("supprimer les produits par code entrer 8\n");
        printf("afficher le totale de prix des produits vendus en journee courante entrer 9\n");
        printf("afficher la moyenne de prix des produits vendus en journee courante entrer 10\n");
        printf("afficher le max de prix des produits vendus en journee courante entrer 11\n");
        printf("afficher le min de prix des produits vendus en journee courante entrer 12\n");
        printf("entrer un nombre de votre choix et si vous voulez sortir du programme entrer 0\n");
        scanf("%d",&choix);

    switch(choix){
        case 1:
        // ajouter un seul produit 
        ajouterUnProduit(produit);
        break;
        case 2:
        // ajouter plusieur produit 
        printf("entrer le nombre de produits que vous voulez saisir\n");
        scanf("%d",&nbr);
        for(int i=0;i<nbr;i++){
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
        break;
        case 6:
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
        default: 
        printf("s'il vous plait entrer un nombre entre 1 et 12");
        break;
    }
}while(choix!=0);
}
int main(){
    struct Produit produit[100];
    Menu(produit);
}