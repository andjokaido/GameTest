#include "Monstre.h"

Monstre::Monstre() : Entitee("Spider",200,50,50,1,10) {
	Loot tmp;
	m_vitesse=2;
	m_chargement=m_vitesse;
	m_table_de_loot=new TableDeLoot();
}

/*
Monstre::Monstre(Monstre* monstre) {
	m_nom=monstre->getNom();
	m_vie_courrante=monstre->getVieCourrante();
	m_vie_max=monstre->getVieMax();
	m_mana_courrant=monstre->getManaCourrant();
	m_mana_max=monstre->getManaMax();
	m_degats_naturel=monstre->getDegatsNaturel();
	m_vitesse=monstre->getVitesse();
	m_recompence_xp=monstre->getRecompenseXP();
}

Monstre::Monstre(string nom, int vie_max, int mana_max, int degats_naturel, int niveau, int vitesse, int recompense_xp) :
		 Entitee(nom,vie_max,mana_max,degats_naturel,niveau,recompense_xp) {
	m_vitesse=vitesse;
	m_chargement=vitesse;
}*/

Monstre::~Monstre() {
	delete m_table_de_loot;
}

void Monstre::setChargement(int tour) {
	m_chargement=tour+m_vitesse;
}

TableDeLoot* Monstre::getTableDeLoot() const {
	return m_table_de_loot;
}

int Monstre::getVitesse() const {
	return m_vitesse;
}

int Monstre::getChargement() const {
	return m_chargement;
}

void Monstre::afficherEtat() const {
	cout << m_nom << " :" << endl;
	cout << "vie : " << m_vie_courrante << "/" << m_vie_max << endl;
	cout << "mana : " << m_mana_courrant << "/" << m_mana_max << endl;
	cout << "chargement attaque : " << m_chargement << endl;
	cout << endl;
}

void Monstre::afficherTableDeLoot() const {
	m_table_de_loot->afficherTable();
	cout << endl;
}
