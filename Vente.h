#ifndef VENTE_H
#define VENTE_H

#include "Item.h"
#include "PotionDeVie.h"

class Vente {
public:
	Vente();
	Item* getItemVente() const;
	int getPrixVente() const;
	int getQuantiteVente() const;
	void afficherVente() const;

private:
	Item* m_item_vente;
	int m_prix_vente;
	int m_quantite_vente;

};

#endif