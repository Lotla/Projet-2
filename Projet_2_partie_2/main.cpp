#include "header.h"
/*
Etapes: les turbines
Variables d'etat: le debit d'eau restant a repartir
Variables de decisions: le debit d'eau par centrales
*/
int Sn[32];
//int Sn = debit restant a repartir
    Centrale centrale1;
    Centrale centrale2;
    Centrale centrale3;
    Centrale centrale4;
    Centrale centrale5;
    //resolution (double debit_total, double elevation_amont){};
int main()
{


    ifstream in("feuille.csv"); //Importe les donnees
    string line, field;

    vector< vector<string> > array; //Le tableau qui stoque les donnees
    vector<string> v;   //

    while ( getline(in,line) )  //On remplis lignes par lignes
    {
        v.clear();
        stringstream ss(line);

        while (getline(ss,field,' '))  //On separt les elements de la ligne par des espaces
        {
            v.push_back(field); //On remplis la ligne
        }

        array.push_back(v); //On ajoute le petit tableau au grand
    }

    //Pour afficher la feuille
    for (size_t i=0; i<array.size(); ++i)
    {
        for (size_t j=0; j<array[i].size(); ++j)
        {
            cout << array[i][j] << "|"; //On affiche les elements du grand tableau, qu'on separe avec des "|"
        }
        cout << "\n";
    }

    for (size_t i=0; i<array.size(); i++)
    {
        centrale1.HauteurDeChuteNette[i] = array[17][i];
        centrale2.HauteurDeChuteNette[i] = array[18][i];
        centrale3.HauteurDeChuteNette[i] = array[19][i];
        centrale4.HauteurDeChuteNette[i] = array[20][i];
        centrale5.HauteurDeChuteNette[i] = array[21][i];

    }

    for (int i=0; i<33; i++)    // 160/5=32
    {
        Sn[i] = 5*i;
    };

    //Calcul De F1

        P5(Sn[],centrale5.HauteurDeChuteNette[]);

    return 0;
}
