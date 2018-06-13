#include "Competence.h"

Competence::Competence() {
	m_attaque=new Attaque();
	m_debloque=false;
}

Competence::Competence(Competence* competence) {
	m_debloque=competence->getDebloque();
	m_attaque=new Attaque(competence->getAttaque());
}

Competence::Competence(Attaque* attaque, bool debloque) {
	m_debloque=debloque;
	m_attaque=new Attaque(attaque);
}

void Competence::setDebloque() {
	m_debloque=true;
}

Attaque* Competence::getAttaque() const {
	return m_attaque;
}

bool Competence::getDebloque() const {
	return m_debloque;
}

void Competence::afficherCompetence() const {
	m_attaque->afficherAttaque();
	if (m_debloque) 
		cout << "Debloque : true" << endl;
	else
		cout << "Debloque : false" << endl;
}