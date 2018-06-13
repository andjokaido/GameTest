#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

using namespace std;

class Item {
public:
	Item();
	Item(Item* tmp);
	Item(int id, string nom, int prix_pnj, int quantite_max);
	int getID() const;
	int getPrixPNJ() const;
	string getNomObjet() const;
	int getQuantiteMax() const;
	void afficherItem() const;

private:
	//Identifiant de l'objet
	int m_id;
	//Nom de l'objet
	string m_nom_objet;
	//Prix de revente à un pnj
	int m_prix_pnj;
	//Quantite max transporté dans un slot d'inventaire
	int m_quantite_max;

};

#endif
