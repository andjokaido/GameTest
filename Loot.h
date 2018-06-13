#ifndef LOOT_H
#define LOOT_H

#include "Item.h"

class Loot {
public:
	Loot();
	~Loot();
	Item* getItem() const;
	int getQuantiteMax() const;
	float getChanceDrop() const;
	void afficherLoot() const;

private:
	Item* m_item;
	int m_quantite_max;
	float m_chance_drop;

};

#endif
