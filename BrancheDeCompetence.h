#ifndef BRANCHE_DE_COMPETENCE_H
#define BRANCHE_DE_COMPETENCE_H

#include <iostream>
#include <string>

#include "Competence.h"

using namespace std;

class BrancheDeCompetence {
public:
	BrancheDeCompetence();
	BrancheDeCompetence(BrancheDeCompetence* branche);
	BrancheDeCompetence(string nom_branche, Competence** competence, int nb_competence);
	string getNomBranche() const;
	Competence** getCompetence() const;
	int getNbCompetence() const;
	void afficherBranche() const;

private:
	string m_nom_branche;
	Competence** m_competence;
	int m_nb_competence;

};

#endif
