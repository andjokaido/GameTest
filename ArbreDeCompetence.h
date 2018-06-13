#ifndef ARBRE_DE_COMPETENCE_H
#define ARBRE_DE_COMPETENCE_H

#include <iostream>
#include <string>

#include "BrancheDeCompetence.h"

class ArbreDeCompetence {
public:
	ArbreDeCompetence();
	ArbreDeCompetence(ArbreDeCompetence* arbre);
	ArbreDeCompetence(BrancheDeCompetence** branche, int nb_branche);
	int getNbBranche() const;
	BrancheDeCompetence** getBranche() const;
	void afficherBranches() const;
	void afficherArbre() const;

private:
	BrancheDeCompetence** m_branche;
	int m_nb_branche;

};

using namespace std;

#endif
