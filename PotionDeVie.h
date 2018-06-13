#ifndef POTION_DE_VIE_H
#define POTION_DE_VIE_H

#include "Item.h"

class PotionDeVie : public Item {
public:
	PotionDeVie();
	int getRegeneVie() const;

private:
	int m_regene_vie;

};

#endif
