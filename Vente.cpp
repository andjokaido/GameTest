#include "Vente.h"

Vente::Vente() {
	m_item_vente=new PotionDeVie();
	m_prix_vente=50;
	m_quantite_vente=1;
}

Item* Vente::getItemVente() const {
	return m_item_vente;
}

int Vente::getPrixVente() const {
	return m_prix_vente;
}

int Vente::getQuantiteVente() const {
	return m_quantite_vente;
}

void Vente::afficherVente() const {
	cout << m_quantite_vente << " ";
	m_item_vente->afficherItem();
	cout << "  " << m_prix_vente << " pièces d'or" << endl;
}
