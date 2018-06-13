#include "Loot.h"

Loot::Loot() {
	m_quantite_max=3;
	m_chance_drop=0.8f;
	m_item=new Item(0x10000,"Fil d'araignée",1,128);
}

Loot::~Loot() {
	delete m_item;
}

Item* Loot::getItem() const {
	return m_item;
}

float Loot::getChanceDrop() const {
	return m_chance_drop;
}

int Loot::getQuantiteMax() const {
	return m_quantite_max;
}

void Loot::afficherLoot() const {
	m_item->afficherItem();
	cout << "Chance drop : " << m_chance_drop << endl
		 << "Quantite max de drop : " << m_quantite_max << endl;
}