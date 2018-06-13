#include "Attaque.h"

Attaque::Attaque() {
	m_nom_attaque="Coup d'épée";
	m_degats_attaque=50;
	m_temps_rechargement=1;
	m_mana_requit=0;
	m_possibilite_reutilisation=0;
	//m_nb_effet=0;
}

Attaque::Attaque(Attaque* attaque) {
	m_nom_attaque=attaque->getNomAttaque();
	m_degats_attaque=attaque->getDegatsAttaque();
	m_mana_requit=attaque->getManaRequit();
	m_temps_rechargement=attaque->getTempsRechargement();
	m_possibilite_reutilisation=attaque->getPossibiliteReutilisation();
}

Attaque::Attaque(string nom_attaque, int degats, int mana_requit, int temps_rechargement) {
	m_nom_attaque=nom_attaque;
	m_degats_attaque=degats;
	m_temps_rechargement=temps_rechargement;
	m_mana_requit=mana_requit;
	m_possibilite_reutilisation=0;
}

void Attaque::setPossibiliteReutilisation(int tour) {
	m_possibilite_reutilisation=tour+m_temps_rechargement;
}

int Attaque::getDegatsAttaque() const {
	return m_degats_attaque;
}

string Attaque::getNomAttaque() const {
	return m_nom_attaque;
}

int Attaque::getTempsRechargement() const {
	return m_temps_rechargement;
}

int Attaque::getManaRequit() const {
	return m_mana_requit;
}

int Attaque::getPossibiliteReutilisation() const {
	return m_possibilite_reutilisation;
}

void Attaque::afficherAttaque() const {
	cout << " " << m_nom_attaque 
		 << " | " << "Degats : " << m_degats_attaque
		 << " | " << "Mana requit : " << m_mana_requit << endl
		 << "   " << "Possibilité réutilisation/Temps de recharge : " << m_possibilite_reutilisation 
		 << "/" << m_temps_rechargement << endl;
}