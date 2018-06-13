#ifndef ENTITEE_H
#define ENTITEE_H

#include <iostream>

#define VIE(niveau) 80+niveau*20
#define MANA(niveau) 50+niveau*10
#define M_VIE(m_niveau) 80+m_niveau*20
#define M_MANA(m_mana) 50+m_niveau*10

using namespace std;

class Entitee {
public:
	Entitee();
	Entitee(string nom, int degats_naturel, int niveau, int recompence_xp);
	Entitee(string nom, int vie_max, int mana_max, int degats_naturel, int niveau, int recompense_xp);
	~Entitee();
	void attaquer(Entitee* cible);
	void recevoirDegats(int degats);
	string getNom() const;
	int getDegatsNaturel() const;
	int getVieMax() const;
	int getVieCourrante() const;
	int getManaMax() const;
	int getManaCourrant() const;
	int getNiveau() const;
	int getRecompenseXP() const;
	bool enVie() const;
	void afficherEtat() const;

protected:
	string m_nom;
	int m_vie_max;
	int m_mana_max;
	int m_vie_courrante;
	int m_mana_courrant;
	int m_degats_naturel;
	int m_niveau;
	unsigned long m_recompence_xp;
};

#endif
