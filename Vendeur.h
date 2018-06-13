#ifndef VENDEUR_H
#define VENDEUR_H

#include "Entitee.h"
#include "TableDeVente.h"


class Vendeur : public Entitee {
public:
	Vendeur();
	~Vendeur();
	TableDeVente* getTableDeVente() const;
	void afficherVendeur() const;

protected:
	TableDeVente* m_table_vente;
};

#endif
