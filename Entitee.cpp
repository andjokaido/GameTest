#include "Entitee.h"

Entitee::Entitee() {
	m_nom="Gerald";
	m_vie_max = 100;
	m_vie_courrante = m_vie_max;
	m_mana_max = 100;
	m_mana_courrant = m_mana_max;
	m_degats_naturel=50;
	m_niveau=1;
	m_recompence_xp=50;
}

Entitee::~Entitee() {}

Entitee::Entitee(string nom, int degats_naturel, int niveau, int recompense_xp) {
	m_nom=nom;
	m_degats_naturel=degats_naturel;
	m_vie_max = VIE(niveau);
	m_vie_courrante = m_vie_max;
	m_mana_max = MANA(niveau);
	m_mana_courrant = m_mana_max;
	m_niveau=niveau;
	m_recompence_xp=recompense_xp;
}

Entitee::Entitee(string nom, int vie_max, int mana_max, int degats_naturel, int niveau, int recompense_xp) {
	m_nom=nom;
	m_degats_naturel=degats_naturel;
	m_vie_max = vie_max;
	m_vie_courrante = m_vie_max;
	m_mana_max = mana_max;
	m_mana_courrant = m_mana_max;
	m_niveau=niveau;
	m_recompence_xp=recompense_xp;	
}

void Entitee::attaquer(Entitee* cible) {
	cible->recevoirDegats(m_degats_naturel);
}

void Entitee::recevoirDegats(int degats) {
	m_vie_courrante-=degats;
	if (m_vie_courrante<0) {
		m_vie_courrante=0;
	}
}

string Entitee::getNom() const {
	return m_nom;
}

int Entitee::getDegatsNaturel() const {
	return m_degats_naturel;
}

int Entitee::getVieMax() const {
	return m_vie_max;
}

int Entitee::getVieCourrante() const {
	return m_vie_courrante;
}

int Entitee::getManaMax() const {
	return m_mana_max;
}

int Entitee::getManaCourrant() const {
	return m_mana_courrant;
}

int Entitee::getNiveau() const {
	return m_niveau;
}

int Entitee::getRecompenseXP() const {
	return m_recompence_xp;
}

bool Entitee::enVie() const {
	if (m_vie_courrante>0) {
		return true;
	} else
		return false;
}

void Entitee::afficherEtat() const {
	cout << m_nom << " :" << endl;
	cout << "vie : " << m_vie_courrante << "/" << m_vie_max << endl;
	cout << "mana : " << m_mana_courrant << "/" << m_mana_max << endl;
	cout << endl;
}
