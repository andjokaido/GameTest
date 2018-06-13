#include "EmplacementInventaire.h"

EmplacementInventaire::EmplacementInventaire() {
	m_quantite=0;
}

EmplacementInventaire::EmplacementInventaire(Item* item, int quantite) {
	m_quantite=quantite;
	m_item=new Item(item);
}

void EmplacementInventaire::addQuantite(int nb) {
	m_quantite+=nb;
	if (m_quantite>m_item->getQuantiteMax())
		m_quantite=m_item->getQuantiteMax();
}

void EmplacementInventaire::diminuerQuantite(int qte) {
	m_quantite-=qte;
	if (m_quantite<0)
		m_quantite=0;
}

Item* EmplacementInventaire::getItem() const {
	return m_item;
}

int EmplacementInventaire::getQuantite() const {
	return m_quantite;
}

bool EmplacementInventaire::EmplacementVide() const {
	if (m_quantite==0)
		return true;
	
	return false;
}

void EmplacementInventaire::afficherEmplacement() const {
	if (EmplacementVide()) {
		cout << "vide" << endl;
	} else {
		cout << m_quantite << " ";
		m_item->afficherItem();
	}
}