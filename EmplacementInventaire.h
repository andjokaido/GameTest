#ifndef EMPLACEMENT_INVENTAIRE_H
#define EMPLACEMENT_INVENTAIRE_H

#include "Item.h"

class EmplacementInventaire {
public:
	EmplacementInventaire();
	EmplacementInventaire(Item* item, int quantite);
	void addQuantite(int nb);
	void diminuerQuantite(int qte);
	bool EmplacementVide() const ;
	Item* getItem() const;
	int getQuantite() const;
	void afficherEmplacement() const;

private:
	Item* m_item;
	int m_quantite;

};

#endif
