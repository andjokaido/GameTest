#include "ArbreDeCompetence.h"

ArbreDeCompetence::ArbreDeCompetence() {
	BrancheDeCompetence tmp;
	m_nb_branche=1;
	m_branche=(BrancheDeCompetence**)malloc(m_nb_branche*sizeof(&tmp));
	for (int i=0;i<m_nb_branche;i++)
		m_branche[i]=new BrancheDeCompetence();
}

ArbreDeCompetence::ArbreDeCompetence(BrancheDeCompetence** branche, int nb_branche) {
	BrancheDeCompetence tmp;
	m_nb_branche=nb_branche;
	m_branche=(BrancheDeCompetence**)malloc(m_nb_branche*sizeof(&tmp));
	for (int i=0;i<m_nb_branche;i++)
		m_branche[i]=new BrancheDeCompetence(branche[i]->getNomBranche(),
											 branche[i]->getCompetence(),
											 branche[i]->getNbCompetence());
}

ArbreDeCompetence::ArbreDeCompetence(ArbreDeCompetence* arbre) {
	BrancheDeCompetence tmp;
	m_nb_branche=arbre->getNbBranche();
	m_branche=(BrancheDeCompetence**)malloc(m_nb_branche*sizeof(&tmp));
	for (int i=0;i<m_nb_branche;i++) {
		m_branche[i]=new BrancheDeCompetence(arbre->getBranche()[i]);
	}
}

int ArbreDeCompetence::getNbBranche() const {
	return m_nb_branche;
}
	
BrancheDeCompetence** ArbreDeCompetence::getBranche() const {
	return m_branche;
}

void ArbreDeCompetence::afficherArbre() const {
	for (int i=0;i<m_nb_branche;i++) {
		cout << "Branche n°" << i << " : ";
		m_branche[i]->afficherBranche();
		cout << "------" << endl;
	}
}

void ArbreDeCompetence::afficherBranches() const {
	for (int i=0;i<m_nb_branche;i++) {
		cout << "Branche n°" << i << " : "
			 << m_branche[i]->getNomBranche() << endl;
	}
}