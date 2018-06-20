#include "Jeu.h"

Jeu::Jeu() {
    //Déclaration des variables pour stocker les informations dans les fichiers
    //Variable pour le le joueur
	    string nom;
        int niveau, experience;
	    int degats_naturel, nb_attaque;
        int nb_or, or_max;
	    Attaque** attaque;
	    EmplacementInventaire*** inventaire;
	    int nb_emplacement, id_objet, quantite;
	    EmplacementInventaire tmp_inventaire;
	    ArbreDeCompetence* arbre_de_competence;
    //Variable temporaire pour connaitre la taille de l'adresse d'une Attaque (probablement inutile)
    	Attaque tmp_attaque;
    //Variable pour les attaques et pour arbre de compétences
	    string nom_attaque;
	    int degats_attaque, mana_requit, temps_rechargement, possibilite_reutilisation;

    //Variable pour l'arbre de compétences
	    BrancheDeCompetence tmp_branche;
	    Competence tmp_competence;
		BrancheDeCompetence** branche;
		int nb_branche;
		string nom_branche;
		Competence** competence;
		int nb_competence;
		bool debloque;

	//Variable pour la liste d'objet
		Item tmp_objet;
		Item**** liste_objet_tmp;
		int i_max, j_max, k_max;
		string nom_objet;
        int prix_pnj;

    int test;

	//Lecture de l'arbre de compétence pour connaitre les attaque existantes
    ifstream arbre_competence("arbre_de_competence.dat",ios::in);

    if (arbre_competence) {
    	arbre_competence >>	nb_branche;
    	branche=(BrancheDeCompetence**)malloc(nb_branche*sizeof(&tmp_branche));
    	for (int i=0;i<nb_branche;i++) {
    		getline(arbre_competence,nom_branche);
    		getline(arbre_competence,nom_branche);
    		arbre_competence >> nb_competence;
    		competence=(Competence**)malloc(nb_competence*sizeof(tmp_competence));
    		for (int j=0;j<nb_competence;j++) {
    			getline(arbre_competence, nom_attaque);
    			getline(arbre_competence, nom_attaque);
    			arbre_competence >> degats_attaque >> mana_requit >> temps_rechargement;
    			competence[j]=new Competence(new Attaque(nom_attaque,degats_attaque,mana_requit,temps_rechargement),
    										 false);
    		}
    		branche[i]=new BrancheDeCompetence(nom_branche,competence,nb_competence);
    		for (int j=0;j<nb_competence;j++) {
    			delete competence[j];
    		}
    		free(competence);
    	}
    	m_arbre_de_competence=new ArbreDeCompetence(branche, nb_branche);
    	for (int i=0;i<nb_branche;i++) {
    		delete branche[i];
    	}
    	free(branche);
    } else {
    	cout << "Erreur : pas d'arbre de compétence" << endl;
        exit (0);
    }

    arbre_competence.close();

    ifstream liste_objet("liste_objet.dat", ios::in);

    if (liste_objet) {
    	liste_objet >> i_max;
	    liste_objet_tmp=(Item****)malloc(i_max*sizeof(&tmp_objet));
	    for (int i=0;i<i_max;i++) {
            getline(liste_objet,nom_objet);
            getline(liste_objet,nom_objet);
	    	liste_objet >> j_max;
	    	liste_objet_tmp[i]=(Item***)malloc(j_max*sizeof(&tmp_objet));
	    	for (int j=0;j<j_max;j++) {
	    		liste_objet >> k_max;
	    		liste_objet_tmp[i][j]=(Item**)malloc(k_max*sizeof(&tmp_objet));
	    		for (int k=0;k<k_max;k++){
                    getline(liste_objet,nom_objet);
	    			getline(liste_objet,nom_objet);
                    liste_objet >> prix_pnj;
                    switch(i) {
	    				case 0:
	    					liste_objet_tmp[i][j][k]=new Item((i<<16|j<<8|k)&0xFFFFFF,nom_objet,prix_pnj,1);
	    				break;
                        case 1:
                            liste_objet_tmp[i][j][k]=new Item((i<<16|j<<8|k)&0xFFFFFF,nom_objet,prix_pnj,1);
                        break;
                        case 2:
                            liste_objet_tmp[i][j][k]=new Item((i<<16|j<<8|k)&0xFFFFFF,nom_objet,prix_pnj,128);
                        break;
                        case 4:
                            liste_objet_tmp[i][j][k]=new Item((i<<16|j<<8|k)&0xFFFFFF,nom_objet,prix_pnj,32);
                        break;
                        default:
                            liste_objet_tmp[i][j][k]=new Item((i<<16|j<<8|k)&0xFFFFFF,nom_objet,prix_pnj,32);
	    			}
	    		}
	    	}
	    }

	    m_liste_objet=liste_objet_tmp;
    } else {
    	cout << "erreur" << endl;
    	exit (1);
    }

    liste_objet.close();

    ifstream personnage("personnage.dat", ios::in); //J'ouvre le fichier du personnage


    //Si le fichier s'ouvre
    if (personnage) {
    	arbre_de_competence=new ArbreDeCompetence(m_arbre_de_competence);
        //Recuperation du nom de personnage
        getline(personnage,nom);
        //Recuperation du niveau du joueur
        personnage >> niveau >> experience;
        //Récupération des dégats naturels
        personnage >> degats_naturel;
        //Récupération de la bourse (nb_or ,or_max)
        personnage >> nb_or >> or_max;
        //Recupération de l'inventaire du joueur
        personnage >> nb_emplacement;
        if (nb_emplacement<=10) {
        	inventaire=(EmplacementInventaire***)malloc(1*sizeof(&tmp_inventaire));
        	inventaire[0]=(EmplacementInventaire**)malloc(nb_emplacement*sizeof(&tmp_inventaire));
        	for (int i=0;i<nb_emplacement;i++) {
                personnage >> id_objet >> quantite;
                if (quantite) {
                    int a = id_objet>>16;
                    int b = (id_objet>>8)&0xFF;
                    int c = id_objet&0xFF;
                    inventaire[0][i]=new EmplacementInventaire(new Item(id_objet,
                                                                        m_liste_objet[a][b][c]->getNomObjet(),
                                                                        m_liste_objet[a][b][c]->getPrixPNJ(),
                                                                        m_liste_objet[a][b][c]->getQuantiteMax()),
                                                               quantite);
                } else {
                    inventaire[0][i]=new EmplacementInventaire();
                }
	        }
        } else {
            cout << "jeu.cpp l130 : faire pour un inv > 10 emplacement" << endl;
            exit (0);
        }

        nb_attaque=0;
        for (int i=0;i<arbre_de_competence->getNbBranche();i++) {
        	for (int j=0;j<arbre_de_competence->getBranche()[i]->getNbCompetence();j++) {
        		personnage>>debloque;
        		if (debloque) {
        			arbre_de_competence->getBranche()[i]->getCompetence()[j]->setDebloque();
        			nb_attaque++;
        		}
        	}
        }

        //Création du joueur avec toutes les données récupérée
        m_joueur=new Personnage(nom,degats_naturel,niveau,experience,nb_attaque,inventaire,nb_emplacement,arbre_de_competence,nb_or,or_max);

    //Si le fichier n'est pas lu
    //Ce qui veut dire que le personnage n'existe pas
    } else {
        //Oveture/Creation du fichier personnage.dat
        ofstream personnage("personnage.dat", ios::out | ios::trunc);
        //Allocation d'un nouveau Personnage
        m_joueur = new Personnage(m_arbre_de_competence);
    }

    //Fermeture du fichier
    personnage.close();

    //Ouverture du fichier de jeu
    ifstream fichier("jeu.dat",ios::in);
    //Si le fichier s'ouvre
    if (fichier) {
        //Lecture du numéro du tour
        fichier >> m_tour;
    //Si le fichier ne s'ouvre pas
    } else {
        //Creation d'un fichier jeu.dat
        ofstream fichier("jeu.dat", ios::out);
        //Initialisation du numéro de tour a 1
        m_tour=1;
    }
    //Fermeture du fichier de jeu
    fichier.close();

    m_vendeur=new Vendeur();
	m_monstre=new Monstre();
}

Jeu::~Jeu() {
	ofstream fichier("jeu.dat", ios::out | ios::trunc);

    fichier << m_tour << endl;

    fichier.close();

    ofstream personnage("personnage.dat", ios::out | ios::trunc);

    personnage << m_joueur->getNom() << endl
               << m_joueur->getNiveau() << " "
               << m_joueur->getXP() << endl
               << m_joueur->getDegatsNaturel() << endl
               << m_joueur->getInventaire()->getNbOr() << " "
               << m_joueur->getInventaire()->getOrMax() << endl
               << m_joueur->getInventaire()->getNbEmplacement() << endl;

	for (int i=0;i<m_joueur->getInventaire()->getNbEmplacement();i++) {
        if (m_joueur->getInventaire()->getInventaire()[(int)(i/10)][i%10]->EmplacementVide()) {
            personnage << "0 0" << endl;
        } else {
            personnage << m_joueur->getInventaire()->getInventaire()[(int)(i/10)][i%10]->getItem()->getID() << " "
                       << m_joueur->getInventaire()->getInventaire()[(int)(i/10)][i%10]->getQuantite() << endl;
        }
	}

	for (int i=0;i<m_joueur->getArbreDeCompetence()->getNbBranche();i++) {
		for (int j=0;j<m_joueur->getArbreDeCompetence()->getBranche()[i]->getNbCompetence();j++) {
			personnage << m_joueur->getArbreDeCompetence()->getBranche()[i]->getCompetence()[j]->getDebloque() << " ";
		}
		personnage << endl;
	}

    personnage.close();

    delete m_liste_objet;
    delete m_arbre_de_competence;
	delete m_joueur;
	delete m_monstre;
    delete m_vendeur;
}

void Jeu::changerMonstre() {
	delete m_monstre;
	m_monstre=new Monstre();
}

/*
void Jeu::changerMonstre(Monstre* monstre) {
	delete m_monstre;
	m_monstre=new Monstre(monstre);
}*/

void Jeu::addTour() {
	m_tour+=1;
}

int Jeu::getTour() const {
	return m_tour;
}

Personnage* Jeu::getJoueur() const {
	return m_joueur;
}

Monstre* Jeu::getMonstre() const {
	return m_monstre;
}

ArbreDeCompetence* Jeu::getArbreDeCompetence() const {
	return m_arbre_de_competence;
}

Item**** Jeu::getListeObjet() const {
	return m_liste_objet;
}

Vendeur* Jeu::getVendeur() const {
    return m_vendeur;
}
