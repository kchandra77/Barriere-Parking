#include "mbed.h"
#include "config.h"

DigitalOut myled(LED1);
using namespace std;
DigitalOut laled1(LED1),laled2(LED2),laled3(LED3),laled4(LED4);
Serial pc(USBTX, USBRX); // tx, rx
LocalFileSystem local("local"); // Create the local filesystem under the name "local"
char c, code[50];

void fonction_ouverture()
{
    pc.printf("\r\nOuverture barriere\r\n");
//    laled1 = 1;
//    wait(1);
//    laled2 = 1;
//    wait(1);
//    laled3 = 1;
//    wait(1);
//    //laled4 = 1;
    wait(3);
    char date [13]="";
    char heure [7]="";
    Config c ("/local/config.txt");
    c.LireValeur("DATE",date);
    c.LireValeur("HEURE",heure);
    
    FILE* fichier = NULL;
 
    fichier = fopen("/local/histo.txt", "a");
 
    if (fichier != NULL)
    {
        fprintf(fichier,"%s\t%s\t%s\t<\r\n",date,heure,code);
        fclose(fichier);
        wait(2);
//        pc.printf("histo mis a jour");
    }else{
        perror("Failed ");}
}

void fonction_fermeture()
{
    pc.printf("\r\nFermeture barriere\r\n");
//    laled1 = 0;
//    wait(1);
//    laled2 = 0;
//    wait(1);
//    laled3 = 0;
//    wait(1);
//    //laled4 = 0;
    wait(3);
   char date [13] = "";
    char heure [7]= "";
    Config c ("/local/config.txt");
    c.LireValeur("DATE",date);
    c.LireValeur("HEURE",heure);
//    pc.printf("date : %s\n\r",date);
//    pc.printf("heure : %s\n\r",heure);
    
    FILE* fichier = NULL;
 
    fichier = fopen("/local/histo.txt", "a");
 
    if (fichier != NULL)
    {
        fprintf(fichier,"%s\t%s\t%s\t>\r\n",date,heure,code);
        fclose(fichier);
        wait(2);
        pc.printf("Fichier historique mis a jour\r\n");
    }else{
        perror("Failed ");}
}

int main() 
{
    pc.printf("Bienvenue\r\n");
    FILE * access;
    char buffer[10]; // un tableau, c'est un pointeur vers la première case
    // Tableau à 2 dimensions ?
    char * tab[100]; // char * ? un pointeur pour chaque chaine de caractere #doublepointeur

    // Initialisation des 100 chaînes de caractères
    for(int i=0 ; i<100 ; i++) {
        tab[i] = new char[10]; // creer un tableau pour chaque ligne
    }
    
    pc.scanf("%c",&c);

    if(c=='a') {
        pc.printf("Arrivee d'une voiture\r\n");
        wait(2);
        //arrivée d'une voiture
        pc.printf("Veuillez indiquer le code :\r\n ");
        pc.scanf("%s",code); //écriture du code
        pc.printf("=%s=\r\n",code); //affichage du code entré
        access = fopen("/local/access.txt", "r");  // Ouverture et lecture du fichier "access.txt"
        //pc.printf("ouverture fichier\r\n");
        wait(2);
        // Lecture d'une ligne du fichier
        int i=0;
        do {
            fscanf(access, "%s", buffer);  // recherche dans le fichier access le code entré avec le buffer
            strcpy(tab[i],buffer);
            i++; // Copie 'buffer' dans tab[i] -> strcpy
        } while(!feof(access)|| i==100); // jusqu'à la fin du fichier

        //pc.printf("Ligne lue : =%s=\r\n", buffer); // verification si c'est bien lu et stocker dans buffer
        pc.printf("verification du code...\r\n");
        wait(2);
        // Comparaison entre buffer et code
        for(int i=0; i<100; i++) {
            strcpy(buffer,tab[i]);
            if(!strcmp(code,buffer)) {
                // comparaison du code rentré dans "code" et "buffer" et si c'est le même alors c'est ok
                pc.printf("Codes identiques\r\n");
                fonction_ouverture();
                fonction_fermeture();
                pc.printf("\r\nMerci d'avoir choisi notre parking, a bientot\r\n");
                i=100;
            }// sinon c'est faux fin de la condition
            if(strcmp(code,buffer)){
                pc.printf("Code incorrecte\r\n");
                i=100;
            }
        }
        fclose(access);

    }
}
