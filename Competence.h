#ifndef COMPETENCE_H
#define COMPETENCE_H

#include <iostream>
#include <string>

#include "Attaque.h"

using namespace std;

class Competence {
public:
	Competence();
	Competence(Competence* competence);
	Competence(Attaque* attaque, bool debloque);
	void setDebloque();
	Attaque* getAttaque() const;
	bool getDebloque() const;
	void afficherCompetence() const;

private:
	Attaque* m_attaque;
	bool m_debloque;

};

#endif
