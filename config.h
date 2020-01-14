#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
        char nom[20];
        char valeur[50];
} Ligne;


class Config
{

private:
    Ligne l[9];
    int nbLigne;
public:
    void LireValeur(char nom[9], char valeur[9]);
    void ModifierValeur(char nom[9], char valeur[9]);
    void Afficher();
    Config(char nomFichier[100]);
};


#endif
