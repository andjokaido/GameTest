#include "Personnage.h"

Personnage::Personnage(ArbreDeCompetence* arbre) :
			Entitee("Gérald",50,1,50) {
	m_nb_attaque=0;	
	m_experience=0;
	m_exp_max=M_EXP_MAX(m_niveau);
	m_inventaire=new Inventaire();
	m_arbre_de_competence=new ArbreDeCompetence(arbre);
	m_point_competence_utilisee=0;
}

Personnage::Personnage(string nom, int degats_naturel, int niveau, int experience, int nb_attaque, EmplacementInventaire*** inventaire, int nb_emplacement, ArbreDeCompetence* arbre, int nb_or, int or_max) :
			Entitee(nom,VIE(niveau),MANA(niveau),degats_naturel,niveau,1000) {
	Attaque tmp;
	int compteur=0;

	m_point_competence_utilisee=0;
	m_arbre_de_competence=new ArbreDeCompetence(arbre);
	m_nb_attaque=nb_attaque;
	m_attaque=(Attaque**)malloc(m_nb_attaque*sizeof(&tmp));
	for (int i=0;i<m_arbre_de_competence->getNbBranche();i++) {
		for (int j=0;j<m_arbre_de_competence->getBranche()[i]->getNbCompetence();j++) {
			if (m_arbre_de_competence->getBranche()[i]->getCompetence()[j]->getDebloque()) {
				m_attaque[compteur]=new Attaque(m_arbre_de_competence->
												getBranche()[i]->
												getCompetence()[j]->
										 		getAttaque());
				compteur++;
				m_point_competence_utilisee++;
			}
		}
	}
	
	m_inventaire=new Inventaire(inventaire,nb_emplacement,nb_or,or_max);
	m_experience=experience;
	m_exp_max=M_EXP_MAX(m_niveau);
}

Personnage::~Personnage() {
	for (int i=0;i<m_nb_attaque;i++) {
		delete m_attaque[i];
	}
	delete m_inventaire;
	delete m_arbre_de_competence;
}

void Personnage::addVieCourrante(int quantite) {
	m_vie_courrante+=quantite;
	if (m_vie_courrante>m_vie_max)
		m_vie_courrante=m_vie_max;
}

void Personnage::addManaCourrant(int quantite) {
	m_mana_courrant+=quantite;
	if (m_mana_courrant>m_mana_max)
		m_mana_courrant=m_mana_max;
}

void Personnage::soin() {
	m_vie_courrante=m_vie_max;
	m_mana_courrant=m_mana_max;
}

void Personnage::attaquer(Monstre* cible, Attaque* attaque) {
	cible->recevoirDegats(m_degats_naturel+attaque->getDegatsAttaque());
	m_mana_courrant-=attaque->getManaRequit();
	if (!(cible->enVie())) {
		ajoutExp(cible->getRecompenseXP());
		recupererLoot(cible);
	}
}

void Personnage::ajoutExp(int exp) {
	m_experience+=exp;
	while (m_experience>=m_exp_max) {
		m_experience-=m_exp_max;
		augmentationNiveau();
	}
}

void Personnage::recupererLoot(Monstre* cible) {
	srand (time(NULL));
	TableDeLoot* tmp_table = cible->getTableDeLoot();
	Loot* tmp_loot;
	for (int i=0;i<tmp_table->getNbLoot();i++) {
		tmp_loot=tmp_table->getTable()[i];
		for (int j=0;j<tmp_loot->getQuantiteMax();j++) {
			if (rand()%100 < tmp_loot->getChanceDrop()*100) {
				tmp_loot->getItem()->afficherItem();
				m_inventaire->ajouterObjet(tmp_loot->getItem());
			} else {
				break;
			}
		}
	}
}

void Personnage::augmentationNiveau() {
	m_niveau++;
	m_exp_max=M_EXP_MAX(m_niveau);
	m_vie_max=M_VIE(m_niveau);
	m_vie_courrante=m_vie_max;
	m_mana_max=M_MANA(m_niveau);
	m_mana_courrant=m_mana_max;
}

void Personnage::debloquerCompetence(int num_branche, int num_competence) {
	Attaque tmp;
	Attaque* temp;
	Attaque* temp2;
	int compteur=0;
	int i=0,j=0;

	m_arbre_de_competence->getBranche()[num_branche]->getCompetence()[num_competence]->setDebloque();
	m_nb_attaque++;
	m_point_competence_utilisee++;

	if (m_nb_attaque==0) {
		cout << "Erreur m_nb_attaque=0 : Impossible" << endl;
		exit(1);
	//Si le joueur n'avait pas d'attaque
	} else if (m_nb_attaque==1) {
		//Allocation du tableau pour stocker les attaques
		m_attaque=(Attaque**)malloc(m_nb_attaque*sizeof(&tmp));
		//Création d'une attaque par rapport a celle choisi par le joueur
		m_attaque[0]=new Attaque(m_arbre_de_competence->
								 getBranche()[num_branche]->
								 getCompetence()[num_competence]->
								 getAttaque());
	//Si le joueur avait qu'une seule attaque
	} else if (m_nb_attaque==2) {
		//Redéfinition du tableau
		m_attaque=(Attaque**)realloc(m_attaque,m_nb_attaque*sizeof(&tmp));
		//Si le joueur a choisi une compétence dans la première branche
		if (num_branche==0) {
			//Si le joueur a choisi la première compétence
			if (num_competence==0) {
				//Stockage de l'attaque actuelle
				temp=m_attaque[0];
				//Création de l'attaque choisi par le joueur
				m_attaque[0]=new Attaque(m_arbre_de_competence->
										 getBranche()[0]->
										 getCompetence()[0]->
										 getAttaque());
				//Remise de l'attaque stocké dans le tableau des attaques
				m_attaque[1]=temp;
			} else {
				for (j=0;j<num_competence;j++) {
					if (m_arbre_de_competence->getBranche()[0]->getCompetence()[j]->getDebloque())
						compteur++;
				}
				if (compteur==0) {
					m_attaque[1]=m_attaque[0];
					m_attaque[0]=new Attaque(m_arbre_de_competence->
											 getBranche()[num_branche]->
										 	 getCompetence()[num_competence]->
										 	 getAttaque());
				} else {
					m_attaque[1]=new Attaque(m_arbre_de_competence->
											 getBranche()[num_branche]->
										 	 getCompetence()[num_competence]->
										 	 getAttaque());
				}
			}
		} else {
			if (num_competence==0) {
				for (i=0;i<num_branche;i++) {
					cout << i << endl;
					for (j=0;j<m_arbre_de_competence->getBranche()[i]->getNbCompetence();j++) {
						if (m_arbre_de_competence->getBranche()[i]->getCompetence()[j]->getDebloque()) {
							compteur++;
						}
					}
				}
				if (compteur==0) {
					m_attaque[1]=m_attaque[0];
					m_attaque[0]=new Attaque(m_arbre_de_competence->
											 getBranche()[num_branche]->
										 	 getCompetence()[num_competence]->
										 	 getAttaque());
				} else {
					m_attaque[1]=new Attaque(m_arbre_de_competence->
											 getBranche()[num_branche]->
										 	 getCompetence()[num_competence]->
										 	 getAttaque());
				}
			} else {
				for (i=0;i<num_branche;i++) {
					for (j=0;j<m_arbre_de_competence->getBranche()[i]->getNbCompetence();j++) {
						if (m_arbre_de_competence->getBranche()[i]->getCompetence()[j]->getDebloque())
							compteur++;
					}
				}
				for (j=0;j<num_competence;j++) {
					if (m_arbre_de_competence->getBranche()[i]->getCompetence()[j]->getDebloque())
						compteur++;
				}
				if (compteur==0) {
					m_attaque[1]=m_attaque[0];
					m_attaque[0]=new Attaque(m_arbre_de_competence->
											 getBranche()[num_branche]->
										 	 getCompetence()[num_competence]->
										 	 getAttaque());
				} else {
					m_attaque[1]=new Attaque(m_arbre_de_competence->
											 getBranche()[num_branche]->
										 	 getCompetence()[num_competence]->
										 	 getAttaque());
				}
			}
		}
	//Si le joueur avait plus de 2 attaques
	} else {
		//Redéfinition du tableau
		m_attaque=(Attaque**)realloc(m_attaque,m_nb_attaque*sizeof(&tmp));
		//Si le joueur choisi la 1ère branche
		if (num_branche==0) {
			//Si le joueur a choisi la première compétence
			if (num_competence==0) {
				temp=m_attaque[0];
				m_attaque[0]=new Attaque(m_arbre_de_competence->
										 getBranche()[num_branche]->
									 	 getCompetence()[num_competence]->
									 	 getAttaque());
				for (i=1;i<m_nb_attaque-1;i++) {
					temp2=m_attaque[i];
					m_attaque[i]=temp;
					temp=temp2;
				}
				m_attaque[i]=temp;
			//SI le joueur a choisi autre chose que la 1ère compétence
			} else {
				for (j=0;j<num_competence;j++) {
					if (m_arbre_de_competence->getBranche()[0]->getCompetence()[j]->getDebloque())
						compteur++;
				}
				if (compteur==0) {
					temp=m_attaque[0];
					m_attaque[0]=new Attaque(m_arbre_de_competence->
											 getBranche()[num_branche]->
										 	 getCompetence()[num_competence]->
										 	 getAttaque());
					for (i=1;i<m_nb_attaque-1;i++) {
						temp2=m_attaque[i];
						m_attaque[i]=temp;
						temp=temp2;
					}
					m_attaque[i]=temp;
				} else {
					temp=m_attaque[compteur];
					for (i=compteur+1;i<m_nb_attaque-1;i++) {
						m_attaque[i]=temp;
						temp=m_attaque[i+1];
					}
					m_attaque[i+1]=temp;
				}
			}
		} else {
			if (num_competence==0) {
				for (i=0;i<num_branche;i++) {
					for (j=0;j<m_arbre_de_competence->getBranche()[i]->getNbCompetence();j++) {
						if (m_arbre_de_competence->getBranche()[i]->getCompetence()[j]->getDebloque())
							compteur++;
					}
				}
				if (compteur == m_nb_attaque-1) {
					m_attaque[compteur]=new Attaque(m_arbre_de_competence->
													getBranche()[num_branche]->
													getCompetence()[num_competence]->
													getAttaque());
				} else if (compteur == m_nb_attaque-2) {
					m_attaque[compteur]=temp;
					m_attaque[compteur]=new Attaque(m_arbre_de_competence->
													getBranche()[num_branche]->
													getCompetence()[num_competence]->
													getAttaque());
					m_attaque[compteur+1]=temp;
				} else {
					m_attaque[compteur]=temp;
					m_attaque[compteur]=new Attaque(m_arbre_de_competence->
													getBranche()[num_branche]->
													getCompetence()[num_competence]->
													getAttaque());
					for (i=compteur+1;i<m_nb_attaque-1;i++) {
						temp2=m_attaque[i];
						m_attaque[i]=temp;
						temp=temp2;
					}
					m_attaque[i]=temp;
				}
			} else {
				for (i=0;i<num_branche;i++) {
					for (j=0;j<m_arbre_de_competence->getBranche()[i]->getNbCompetence();j++) {
						if (m_arbre_de_competence->getBranche()[i]->getCompetence()[j]->getDebloque())
							compteur++;
					}
				}
				for (j=0;j<num_competence;j++) {
					if (m_arbre_de_competence->getBranche()[i]->getCompetence()[j]->getDebloque())
							compteur++;
				}
				if (compteur==m_nb_attaque-1) {
					m_attaque[compteur]=new Attaque(m_arbre_de_competence->
													getBranche()[num_branche]->
													getCompetence()[num_competence]->
													getAttaque());
				} else if (compteur == m_nb_attaque-2) {
					m_attaque[compteur]=temp;
					m_attaque[compteur]=new Attaque(m_arbre_de_competence->
													getBranche()[num_branche]->
													getCompetence()[num_competence]->
													getAttaque());
					m_attaque[compteur+1]=temp;
				} else {
					m_attaque[compteur]=temp;
					m_attaque[compteur]=new Attaque(m_arbre_de_competence->
													getBranche()[num_branche]->
													getCompetence()[num_competence]->
													getAttaque());
					for (i=compteur+1;i<m_nb_attaque-1;i++) {
						temp2=m_attaque[i];
						m_attaque[i]=temp;
						temp=temp2;
					}
					m_attaque[i]=temp;
				}
			}
		}
	}
}

void Personnage::achatPNJ(Vente* tmp) {
	for (int i=0;i<tmp->getQuantiteVente();i++)
		m_inventaire->ajouterObjet(tmp->getItemVente());
	m_inventaire->retirerOr(tmp->getPrixVente());
}

bool Personnage::attaqueDisponible(int tour) const {
	for (int i=0;i<m_nb_attaque;i++) {
		if (m_attaque[i]->getPossibiliteReutilisation()<=tour)
			return true;
	}

	return false;
}

Attaque* Personnage::getAttaque(int numero) const {
	return m_attaque[numero];
}

int Personnage::getNbAttaque() const {
	return m_nb_attaque;
}

int Personnage::getXP() const {
	return m_experience;
}

unsigned short Personnage::getPointCompetenceUtilisee() const {
	return m_point_competence_utilisee;
}

Inventaire* Personnage::getInventaire() const {
	return m_inventaire;
}

ArbreDeCompetence* Personnage::getArbreDeCompetence() const {
	return m_arbre_de_competence;
}

void Personnage::afficherEtat() const {
	cout << m_nom << " : " << endl
		 << "Niveau " << m_niveau << endl
		 << "Exp : " << m_experience << " / " << m_exp_max << endl
		 << "Vie : " << m_vie_courrante << "/" << m_vie_max << endl
		 << "Mana : " << m_mana_courrant << "/" << m_mana_max << endl
		 << "Degats naturels : " << m_degats_naturel << endl
		 << "Attaque(s) :" << endl;
	for (int i=0;i<m_nb_attaque;i++) {
		cout << "Attaque (" << i << ") : ";
		m_attaque[i]->afficherAttaque();
		cout << endl;
	}
}
