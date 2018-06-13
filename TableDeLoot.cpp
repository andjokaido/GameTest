#include "TableDeLoot.h"

TableDeLoot::TableDeLoot() {
	Loot tmp;
	m_nb_loot=1;
	m_table=(Loot**)malloc(1*sizeof(&tmp));
	for (int i=0;i<m_nb_loot;i++)
		m_table[i]=new Loot();
}

TableDeLoot::~TableDeLoot() {
	for (int i=0;i<m_nb_loot;i++) {
		delete m_table[i];
	}
}

Loot** TableDeLoot::getTable() const {
	return m_table;
}

int TableDeLoot::getNbLoot() const {
	return m_nb_loot;
}

void TableDeLoot::afficherTable() const {
	for (int i=0;i<m_nb_loot;i++) {
		cout << "Loot n°" << i << " : " << endl;
		m_table[i]->afficherLoot();
	}
}