#include "Inventaire.h"

Inventaire::Inventaire() {
	EmplacementInventaire tmp;
	m_inventaire=(EmplacementInventaire***)malloc(1*sizeof(&tmp));
	m_inventaire[0]=(EmplacementInventaire**)malloc(1*sizeof(&tmp));
	m_inventaire[0][0]=new EmplacementInventaire();
	m_nb_place=1;
	m_emplacement_occupee=0;
	m_nb_or=0;
	m_or_max=1000;
}

Inventaire::Inventaire(EmplacementInventaire*** inventaire ,int nb_place, int nb_or, int or_max) {
	EmplacementInventaire tmp;
	m_emplacement_occupee=0;
	int i;
	if (nb_place <=10) {
		m_inventaire=(EmplacementInventaire***)malloc(1*sizeof(&tmp));
		m_inventaire[0]=(EmplacementInventaire**)malloc(nb_place*sizeof(&tmp));
		for (i=0;i<nb_place;i++) {
			if (inventaire[0][i]->EmplacementVide()) {
				m_inventaire[0][i]=new EmplacementInventaire();
			} else {
				m_inventaire[0][i]=new EmplacementInventaire(inventaire[0][i]->getItem(),
															 inventaire[0][i]->getQuantite());
				m_emplacement_occupee++;
			}
		}
	} else {
		if (nb_place%10 == 0) {
			m_inventaire=(EmplacementInventaire***)malloc((int)(nb_place/10)*sizeof(&tmp));
		} else {
			m_inventaire=(EmplacementInventaire***)malloc(((int)(nb_place/10)+1)*sizeof(&tmp));
		}
		for (i=0;i<(int)(nb_place/10);i++) {
			m_inventaire[i]=(EmplacementInventaire**)malloc(10*sizeof(&tmp));
			for (int j=0;j<10;j++) {
				if (inventaire[i][j]->EmplacementVide()) {
					m_inventaire[i][j]=new EmplacementInventaire();
				} else {
					m_inventaire[i][j]=new EmplacementInventaire(inventaire[i][j]->getItem(),
																 inventaire[i][j]->getQuantite());
					m_emplacement_occupee++;
				}
			}
		}
		if (nb_place%10 != 0) {
			m_inventaire[i+1]=(EmplacementInventaire**)malloc(nb_place%10*sizeof(&tmp));
			for (int j=0;j<nb_place%10;j++) {
				if (inventaire[i][j]->EmplacementVide()) {
					m_inventaire[i][j]=new EmplacementInventaire();
				} else {
					m_inventaire[i+1][j]=new EmplacementInventaire(inventaire[i+1][j]->getItem(),
																   inventaire[i+1][j]->getQuantite());
					m_emplacement_occupee++;
				}
			}
		}
	}

	m_nb_or=nb_or;
	m_or_max=or_max;
	m_nb_place=nb_place;
}

void Inventaire::ajouterObjet(Item* recu) {
	EmplacementInventaire* tmp;
	bool loote=false; //Trouver un beau nom
	//Si l'inventaire a moins de 10 emplacements
	if (m_nb_place<=10) {
		//Pour i allant de 0 au nombre de places de l'inventaire
		//Et on vérifie si le l'objet n'est pas looté
		for (int i=0;i<m_nb_place && !loote;i++) {
			//On copie temporairement l'adresse de l'emplacement d'inventaire
			tmp=m_inventaire[0][i];
			//Si cette emplacement n'est pas vide
			if (!m_inventaire[0][i]->EmplacementVide()) {
				//On regarde si les deux ID sont les mêmes
				if (tmp->getItem()->getID()==recu->getID()) {
					//Si Le slot n'est pas déjà au max de ca capacité
					if (tmp->getQuantite()<recu->getQuantiteMax()) {
						//On aumente la quantité du slot
						m_inventaire[0][i]->addQuantite(1);
						//On dit que l'objet a été looté
						loote=true;
					}
				}
			}
		}
		//Si l'objet n'est pas encore looté
		if (!loote) {
			//On parcours l'inventaire
			for (int i=0;i<m_nb_place && !loote;i++) {
				//Copie temporaire de l'adresse de l'emplacement d'inventaire
				tmp=m_inventaire[0][i];
				//Si l'emplacement est vide
				if (m_inventaire[0][i]->EmplacementVide()) {
					//On supprime l'ancien emplacacement
					delete m_inventaire[0][i];
					//On crée un nouvel emplacement avec l'objet recu
					m_inventaire[0][i]=new EmplacementInventaire(recu,1);
					//On dit que l'objet est looté
					loote=true;
					//On ajoute le nombre d'emplacements occupé
					m_emplacement_occupee++;
				}
			}	
		}
	} else {
		cout << "Faire pour un inventaire plein sup à 10 emplacements" << endl;
	}
}

void Inventaire::ajouterOr(int qte) {
	m_nb_or+=qte;
	if (m_nb_or>m_or_max)
		m_nb_or=m_or_max;
}

void Inventaire::retirerOr(int qte) {
	m_nb_or=qte;
	if (m_nb_or<0)
		m_nb_or=0;
}

void Inventaire::vendreObjetPNJ(int ligne, int colonne, int quantite) {
	ajouterOr(quantite*m_inventaire[ligne][colonne]->getItem()->getPrixPNJ());
	m_inventaire[ligne][colonne]->diminuerQuantite(quantite);
	if (m_inventaire[ligne][colonne]->EmplacementVide())
		m_emplacement_occupee--;
}

bool Inventaire::plein() const {
	return m_emplacement_occupee==m_nb_place;
}

int Inventaire::getNbEmplacement() const {
	return m_nb_place;
}

int Inventaire::getNbOr() const {
	return m_nb_or;
}

int Inventaire::getOrMax() const {
	return m_or_max;
}

EmplacementInventaire*** Inventaire::getInventaire() const {
	return m_inventaire;
}

void Inventaire::afficherInventaire() const {
	cout << "Inventaire :" << endl;
	if (m_nb_place<=10) {
		for (int i=0; i<m_nb_place;i++) {
			cout << "Emplacement [0][" << i << "]" << endl;
			if (m_inventaire[0][i]->EmplacementVide())
				cout << "  emplacement vide" << endl;
			else  {
				cout << "  ";
				m_inventaire[0][i]->afficherEmplacement();
			}
		}
	} else {
		cout << "A faire pour un inv sup à 10 emplacements" << endl;
	}
	if (m_nb_or>1)
		cout << m_nb_or << " pièces d'or";
	else
		cout << m_nb_or << " pièce d'or";
}