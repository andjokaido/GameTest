#include "TableDeVente.h"

TableDeVente::TableDeVente() {
	Vente tmp;
	m_nb_vente=1;
	m_liste_vente=(Vente**)malloc(m_nb_vente*sizeof(&tmp));
	for (int i=0;i<m_nb_vente;i++)
		m_liste_vente[i]=new Vente();
}
	
TableDeVente::~TableDeVente() {
	for (int i=0;i<m_nb_vente;i++)	
		delete m_liste_vente[i];
}

int TableDeVente::getNbVente() const {
	return m_nb_vente;
}

Vente** TableDeVente::getListeVente() const {
	return m_liste_vente;
}

void TableDeVente::afficherTableDeVente() const {
	for (int i=0;i<m_nb_vente;i++) {
		cout << "Vente n°" << i << endl;
		m_liste_vente[i]->afficherVente();
	}
}
