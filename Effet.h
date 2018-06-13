#ifndef EFFET_H
#define EFFET_H

#include <iostream>

class Effet {
public:
	Effet();
	Effet(int degats);

private:
	int m_degats;
	int m_temps_rechargement;
	struct effet* m_effet;
	int m_nb_effets;

};

#endif