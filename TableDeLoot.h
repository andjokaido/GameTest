#ifndef TABLE_DE_LOOT_H
#define TABLE_DE_LOOT_H

#include "Loot.h"

class TableDeLoot {
public:
	TableDeLoot();
	~TableDeLoot();
	Loot** getTable() const;
	int getNbLoot() const;
	void afficherTable() const;

private:
	Loot** m_table;
	int m_nb_loot;

};

#endif
