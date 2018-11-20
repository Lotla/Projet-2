#include "stdio.h"
#include "math.h"
#include "Equations.h"
#include <iostream>
using namespace std;

#define DEBIT_MIN 0     //m^3/s
#define DEBIT_MAX 160   //m^3/s
#define N 5 //Le nombre de turbines
#define NOMBRE_DE_LIGNES 200    //Nombre de lignes dans la feuille excel
#define NOMBRE_DE_COLONNES 21   //Nombre de colonnes dans la feuille excel

#include <fstream>  //Utilise pour lire le fichier
#include <sstream>  //Utilise pour lire le fichier
#include <string>
#include <vector>

class Centrale
{public:
    double Sn [NOMBRE_DE_LIGNES];  //Le debit turbine par la turbines, Qi
    double elevation_amont [NOMBRE_DE_LIGNES];
    double HauteurDeChuteBrute [NOMBRE_DE_LIGNES];
    //double HauteurDeChuteNette [NOMBRE_DE_LIGNES];
    vector<double> HauteurDeChuteNette;
    double puissance [NOMBRE_DE_LIGNES];    //Pi
    double Qtot[NOMBRE_DE_LIGNES];
    double elevation_aval_en_fonction_du_debit_total[NOMBRE_DE_LIGNES];

    double CalculElevation_aval_en_fonction_du_debit_total()
    {
        for (int i=0; i<NOMBRE_DE_LIGNES; i++)
        {
            elevation_aval_en_fonction_du_debit_total[i] = -1*pow(10,-7)*pow(Qtot[i],3) + 0.0002*pow(Qtot[i],2) - 0.0897*Qtot[i] + 154.4;
        }
    };
    double CalculHauteurDeChuteBrute()
    {
        for (int i=0; i<NOMBRE_DE_LIGNES ; ++i)
            {
                this->HauteurDeChuteBrute[i] = elevation_amont[i] - elevation_aval_en_fonction_du_debit_total[i];
            }
    };
/*
    double CalculHauteurDeChuteNette(double elevation_amont[], double elevation_aval_en_fonction_du_debit_total[], double Sn[])
    {
        for (int i=0; i<NOMBRE_DE_LIGNES; i++)
        {
            this->HauteurDeChuteNette[i] = elevation_amont[i] - elevation_aval_en_fonction_du_debit_total[i] - 0.5*pow(10,-5)*pow(Sn[i],2);    //Eam-Eav(Qtot)-0.5e^-5*Q^2
        }
    };
*/
};

class Calcul : public Centrale
{   //La puissance prend en parametres Sn et la hauteur de chute nette de la centrale
    double P1 (double Sn[], double HauteurDeChuteNette[])
    {
        for (int i=0; i<NOMBRE_DE_LIGNES; i++)
        {
            this->puissance[i] =
            31.81                                                       //p00
            + 1.664*this->Sn[i]                                         //p10x
            + 16.48*this->HauteurDeChuteNette[i]                        //p01y
            - 0.0003209*pow(this->Sn[i],2)                              //p20x^2
            + 0.845*this->Sn[i]*this->HauteurDeChuteNette[i]            //p11xy
            - 3.338*pow(this->HauteurDeChuteNette[i],2)                 //p02y^2
            + 0.003004*pow(this->Sn[i],3)                               //p30x^3
            - 0.01117*pow(this->Sn[i],2)*this->HauteurDeChuteNette[i]   //p21x^2y
            + 0.03515*this->Sn[i]*pow(this->HauteurDeChuteNette[i],2)   //p12xy^2
            - 1.917*pow(this->HauteurDeChuteNette[i],3);                //p03y^3
        }

    }

    double P2 (double Sn[], double HauteurDeChuteNette[])
    {
        for (int i=0; i<NOMBRE_DE_LIGNES; i++)
        {
            this->puissance[i] =
            30.55                                                       //p00
            + 1.585*this->Sn[i]                                         //p10x
            + 19.95*this->HauteurDeChuteNette[i]                        //p01y
            - 0.004452*pow(this->Sn[i],2)                               //p20x^2
            + 1.005*this->Sn[i]*this->HauteurDeChuteNette[i]            //p11xy
            - 3.956*pow(this->HauteurDeChuteNette[i],2)                 //p02y^2
            - 0.02*pow(this->Sn[i],2)*this->HauteurDeChuteNette[i]      //p21x^2y
            + 0.1071*this->Sn[i]*pow(this->HauteurDeChuteNette[i],2)    //p12xy^2
            - 3.149*pow(this->HauteurDeChuteNette[i],3);                //p03y^3
        }

    }

    double P3 (double Sn[], double HauteurDeChuteNette[])
    {
        for (int i=0; i<NOMBRE_DE_LIGNES; i++)
        {
            this->puissance[i] =
            33.77                                                       //p00
            + 1.757*this->Sn[i]                                         //p10x
            + 16.24*this->HauteurDeChuteNette[i]                        //p01y
            - 0.008345*pow(this->Sn[i],2)                               //p20x^2
            + 0.9232*this->Sn[i]*this->HauteurDeChuteNette[i]           //p11xy
            - 4.186*pow(this->HauteurDeChuteNette[i],2)                 //p02y^2
            - 0.009276*pow(this->Sn[i],2)*this->HauteurDeChuteNette[i]  //p21x^2y
            + 0.08683*this->Sn[i]*pow(this->HauteurDeChuteNette[i],2)   //p12xy^2
            - 2.12*pow(this->HauteurDeChuteNette[i],3);                 //p03y^3
        }

    }

    double P4 (double Sn, double HauteurDeChuteNette[])
    {
        for (int i=0; i<NOMBRE_DE_LIGNES; i++)
        {
            this->puissance[i] =
            34.72                                                       //p00
            + 1.776*this->Sn[i]                                         //p10x
            + 19.08*this->HauteurDeChuteNette[i]                        //p01y
            - 0.007973*pow(this->Sn[i],2)                               //p20x^2
            + 1.131*this->Sn[i]*this->HauteurDeChuteNette[i]            //p11xy
            - 4.681*pow(this->HauteurDeChuteNette[i],2)                 //p02y^2
            - 0.007354*pow(this->Sn[i],2)*this->HauteurDeChuteNette[i]  //p21x^2y
            + 0.1529*this->Sn[i]*pow(this->HauteurDeChuteNette[i],2)    //p12xy^2
            - 2.808*pow(this->HauteurDeChuteNette[i],3);                //p03y^3
        }
    }

    double P5 (double Sn[], double HauteurDeChuteNette[])
    {
        for (int i=0; i<NOMBRE_DE_LIGNES; i++)
        {
            this->puissance[i] =
            32.18                                                       //p00
            + 1.88*this->Sn[i]                                          //p10x
            + 17.31*this->HauteurDeChuteNette[i]                        //p01y
            - 0.01801*pow(this->Sn[i],2)                                //p20x^2
            + 1.11*this->Sn[i]*this->HauteurDeChuteNette[i]             //p11xy
            - 3.355*pow(this->HauteurDeChuteNette[i],2)                 //p02y^2
            - 0.009932*pow(this->Sn[i],3)                               //p30x^3
            + 0.02361*pow(this->Sn[i],2)*this->HauteurDeChuteNette[i]   //p21x^2y
            + 0.0848*this->Sn[i]*pow(this->HauteurDeChuteNette[i],2)    //p12xy^2
            - 2.065*pow(this->HauteurDeChuteNette[i],3);                //p03y^3
        }
    };
};
