#ifndef ATTAQUE_H
#define ATTAQUE_H

#include <iostream>
#include <string>
//#include "Effet.h"

using namespace std;

/*struct effet {
		Effet* nom;
		int chance_effet;
};*/

class Attaque {
public:
	Attaque();
	Attaque(Attaque* attaque);
	Attaque(string nom_attaque, int degats, int mana_requit, int temps_rechargement);
	void setPossibiliteReutilisation(int tour);
	int getDegatsAttaque() const;
	string getNomAttaque() const;
	int getTempsRechargement() const;
	int getManaRequit() const;
	int getPossibiliteReutilisation() const;
	void afficherAttaque() const;

private:
	string m_nom_attaque;
	int m_degats_attaque;
	int m_temps_rechargement;
	int m_mana_requit;
	int m_possibilite_reutilisation;
	//struct effet* m_effet;
	//int m_nb_effets;

};

#endif
