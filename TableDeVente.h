#ifndef TABLE_DE_VENTE_H
#define TABLE_DE_VENTE_H

#include "Vente.h"

class TableDeVente {
public:
	TableDeVente();
	~TableDeVente();
	int getNbVente() const;
	Vente** getListeVente() const;
	void afficherTableDeVente() const;

private:
	Vente** m_liste_vente;
	int m_nb_vente;

};

#endif
