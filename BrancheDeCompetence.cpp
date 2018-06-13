#include "BrancheDeCompetence.h"

BrancheDeCompetence::BrancheDeCompetence() {
	Competence tmp;
	m_nom_branche="Première";
	m_nb_competence=1;
	m_competence=(Competence**)malloc(m_nb_competence*sizeof(&tmp));
	for (int i=0;i<m_nb_competence;i++)
		m_competence[i]=new Competence();
}

BrancheDeCompetence::BrancheDeCompetence(BrancheDeCompetence* branche) {
	Competence tmp;
	m_nom_branche=branche->getNomBranche();
	m_nb_competence=branche->getNbCompetence();
	m_competence=(Competence**)malloc(m_nb_competence*sizeof(&tmp));
	for (int i=0;i<m_nb_competence;i++)
		m_competence[i]=new Competence(branche->getCompetence()[i]);
}

BrancheDeCompetence::BrancheDeCompetence(string nom_branche, Competence** competence, int nb_competence) {
	Competence tmp;
	m_nom_branche=nom_branche;
	m_nb_competence=nb_competence;
	m_competence=(Competence**)malloc(m_nb_competence*sizeof(&tmp));
	for (int i=0;i<m_nb_competence;i++)
		m_competence[i]=new Competence(competence[i]);
}

string BrancheDeCompetence::getNomBranche() const {
	return m_nom_branche;
}

Competence** BrancheDeCompetence::getCompetence() const {
	return m_competence;
}

int BrancheDeCompetence::getNbCompetence() const {
	return m_nb_competence;
}

void BrancheDeCompetence::afficherBranche() const {
	cout << m_nom_branche << endl;
	for (int i=0;i< m_nb_competence;i++) {
		cout << "n°" << i << " : " << endl;
		m_competence[i]->afficherCompetence();
		cout << endl;
	}
}