#include "config.h"
#include <stdio.h>
#include "mbed.h"

Config::Config(char nomFichier[100])
{
    FILE * fp = fopen(nomFichier, "r");
    int i=0;
        do {
            fscanf(fp,"%s\t%s\n\r",l[i].nom,l[i].valeur);
            i++;
        } while(!feof(fp));
        nbLigne=i;
        fclose(fp);
}

void Config::Afficher()
{
    Serial pc(USBTX, USBRX); // tx, rx
    for(int i=0; i<nbLigne; i++) {
        pc.printf("%s : %s\n\r",l[i].nom,l[i].valeur);
    }
}

void Config::LireValeur(char nom[9], char valeur[9])
{
    int i = 0;
    bool ok=false;
    do {
        if(strcmp(l[i].nom,nom)==0) {
            strcpy(valeur,l[i].valeur);
            ok=true;
        }
        i++;
    } while(ok==false && i<10);
}

void Config::ModifierValeur(char nom[9], char valeur[9])
{
    Serial pc(USBTX, USBRX); // tx, rx
    pc.printf("%s %s\n\r",nom,valeur);
    int i = 0;
    bool ok=false;
    do {
        if(strcmp(l[i].nom,nom)==0) // le tableau l va chercher à 0 et voir le nom. si c ok alors ligne trouvee sinon incremente ++ jusqu'a trouver le nom et la modifier
        {
            pc.printf("ligne trouvee : %d %s\n\r",i,l[i].nom);
            strcpy(l[i].valeur,valeur);
            ok=true;
        }
        else
        {
            pc.printf("Ligne %d : %s\n\r",i,l[i].nom);
        }
        i++;
    } while(ok==false && i<10);    
    FILE * fp = fopen("/local/config.txt", "w");
    for(i=0; i<nbLigne; i++) 
    {
            fprintf(fp,"%s\t%s\r\n",l[i].nom,l[i].valeur);
    }
    fclose(fp);
}
