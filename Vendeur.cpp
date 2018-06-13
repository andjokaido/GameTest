#include "Vendeur.h"

Vendeur::Vendeur() : Entitee("Vendeur de potion",100,10,10,5,0) {
	m_table_vente=new TableDeVente();
}

Vendeur::~Vendeur() {
	delete m_table_vente;
}

TableDeVente* Vendeur::getTableDeVente() const {
	return m_table_vente;
}

void Vendeur::afficherVendeur() const {
	cout << m_nom << " : niveau : " << m_niveau << endl;
	m_table_vente->afficherTableDeVente();
	cout << endl;
}