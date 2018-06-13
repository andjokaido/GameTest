#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <iostream>

#include "Entitee.h"
#include "Monstre.h"
#include "Attaque.h"
#include "ArbreDeCompetence.h"
#include "Inventaire.h"
#include "Vente.h"

#define M_EXP_MAX(m_niveau) m_niveau*m_niveau*100

using namespace std;

class Personnage : public Entitee {
public:
	Personnage(ArbreDeCompetence* arbre);
	Personnage(string nom, int degats_naturel, int niveau, int experience, int nb_attaque, EmplacementInventaire*** inventaire, int nb_emplacement, ArbreDeCompetence* arbre, int nb_or, int or_max);
	~Personnage();
	void attaquer(Monstre* cible, Attaque* attaque);
	void ajoutExp(int exp);
	void recupererLoot(Monstre* cible);
	void augmentationNiveau();
	void addVieCourrante(int quantite);
	void addManaCourrant(int quantite);
	void soin();
	void debloquerCompetence(int num_branche, int num_competence);
	void achatPNJ(Vente* tmp);
	bool attaqueDisponible(int tour) const;
	int getNbAttaque() const;
	int getXP() const;
	unsigned short getPointCompetenceUtilisee() const;
	Attaque* getAttaque(int numero) const;
	Inventaire* getInventaire() const;
	ArbreDeCompetence* getArbreDeCompetence() const;
	void afficherEtat() const;

private:
	Attaque** m_attaque;
	Inventaire* m_inventaire;
	ArbreDeCompetence* m_arbre_de_competence;
	int m_nb_attaque;
	unsigned short m_point_competence_utilisee;
	unsigned long m_experience;
	unsigned long m_exp_max;
};

#endif
