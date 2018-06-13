#include "Item.h"

Item::Item() {
	m_id=0;
	m_nom_objet="Epée";
	m_prix_pnj=10;
	m_quantite_max=1;
}

Item::Item(Item* tmp) {
	m_id=tmp->getID();
	m_nom_objet=tmp->getNomObjet();
	m_prix_pnj=tmp->getPrixPNJ();
	m_quantite_max=tmp->getQuantiteMax();
}

Item::Item(int id, string nom, int prix_pnj, int quantite_max) {
	m_id=id;
	m_nom_objet=nom;
	m_prix_pnj=prix_pnj;
	m_quantite_max=quantite_max;
}
	
int Item::getID() const {
	return m_id;
}

int Item::getPrixPNJ() const {
	return m_prix_pnj;
}

string Item::getNomObjet() const {
	return m_nom_objet;
}

int Item::getQuantiteMax() const {
	return m_quantite_max;
}

void Item::afficherItem() const {
	cout << m_nom_objet << endl;
}
