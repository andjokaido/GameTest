#ifndef JEU_H
#define JEU_H

#include <iostream>
#include <string>
#include <fstream>

#include "Entitee.h"
#include "Vendeur.h"
#include "Monstre.h"
#include "Personnage.h"
#include "Attaque.h"
#include "ArbreDeCompetence.h"
#include "BrancheDeCompetence.h"
#include "Competence.h"
#include "Item.h"
#include "EmplacementInventaire.h"
#include "Inventaire.h"
//#include "Effet.h" A venir

using namespace std;

class Jeu {
public:
	Jeu();
	~Jeu();
	void changerMonstre();
	//void changerMonstre(Monstre* monstre);
	void addTour();
	int getTour() const;
	Personnage* getJoueur() const;
	Monstre* getMonstre() const;
	ArbreDeCompetence* getArbreDeCompetence() const;
	Item**** getListeObjet() const;
	Vendeur* getVendeur() const;

private:
	int m_tour;
	ArbreDeCompetence* m_arbre_de_competence;
	Personnage* m_joueur;
	Monstre* m_monstre;
	Item**** m_liste_objet;
	Vendeur* m_vendeur;

};

#endif