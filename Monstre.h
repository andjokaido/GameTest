#ifndef MONSTRE_H
#define MONSTRE_H

#include <iostream>
#include "Entitee.h"
#include "TableDeLoot.h"

using namespace std;

class Monstre : public Entitee {
public:
	Monstre();
	//Monstre(Monstre* monstre);
	//Monstre(string nom, int vie_max, int mana_max, int degats_naturel, int niveau,  int recompense_xp, int vitesse);
	~Monstre();
	void setChargement(int tour);
	TableDeLoot* getTableDeLoot() const;
	int getVitesse() const;
	int getChargement() const;
	void afficherEtat() const;
	void afficherTableDeLoot() const;

private:
	int m_vitesse; //Temps avant de pouvoir reattaquer en tour
	int m_chargement;
	TableDeLoot* m_table_de_loot;
};

#endif
