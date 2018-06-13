#include "PotionDeVie.h"

PotionDeVie::PotionDeVie() : Item(0x30000,"Petite potion de vie",0,32) {
	m_regene_vie=50;
}

int PotionDeVie::getRegeneVie() const {
	return m_regene_vie;
}