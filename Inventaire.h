#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include "EmplacementInventaire.h"

class Inventaire {
public:
	Inventaire();
	Inventaire(EmplacementInventaire*** inventaire ,int nb_place, int nb_or, int or_max);
	void ajouterObjet(Item* recu);
	void ajouterOr(int qte);
	void retirerOr(int qte);
	void vendreObjetPNJ(int ligne, int colonne, int quantite);
	bool plein() const;
	int getNbEmplacement() const;
	int getNbOr() const;
	int getOrMax() const;
	EmplacementInventaire*** getInventaire() const;
	void afficherInventaire() const;

private:
	int m_nb_place;
	EmplacementInventaire*** m_inventaire;
	int m_emplacement_occupee;
	int m_nb_or;
	int m_or_max;

};

#endif
