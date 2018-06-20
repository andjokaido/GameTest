#include <iostream>
#include <string>

#include "Jeu.h"

using namespace std;

/*
Changer le traitement d'une attaque fait a un monstre et a un personnage
*/

//Fonction qui marque une transition entre chaque tour
void transition(int tour) {
    cout << endl << "------------------" << endl << endl;
    cout << "Tour n°" << tour << endl << endl;
}

void clear_screen() {
    for (int i=0; i<50;i++)
        cout << endl;
}


int main(void) {
    int test; //Varible de test pour stoper le programme avec un cin >> test
    int numero1,numero2,numero3;
    char option;
    Jeu jeu;
    Attaque* tmp_atq;

    //Debut du jeu
    do {
        cout << "0 : Combat !" << endl
             << "1 : Inventaire" << endl
             << "2 : PNJ (vente/achat)" << endl
             << "3 : Arbre de competence" << endl
             //<< "4 : Arbre de statistiques" << endl
             << "Q/q : Quitter" << endl;
        cin >> option;
        //clear_screen();

        switch (option) {
            case '0' :
                jeu.changerMonstre();
                //On entre dans le boucle seulement si le joueur et le monstre est vivant
                while (jeu.getMonstre()->enVie() && jeu.getJoueur()->enVie()) {
                    //Transition pour montrer en meme temps à quel tour nous sommes
                    transition(jeu.getTour());
                    //Affichage les statistiques du personnages
                    jeu.getJoueur()->afficherEtat();

                    //Si il y a des attaques disponibles pour le joueur
                    if (jeu.getJoueur()->attaqueDisponible(jeu.getTour())) {
                        //Recupération du numéro d'attaque que le joueur veut utiliser
                        do {
                            do {
                                cout << "Quel attaque utiliser ? :";
                                cin >> numero1;
                            //Tant que le joueur ne donne pas une attaque qui existe ou lui redemande
                            } while (numero1<0 || numero1>=jeu.getJoueur()->getNbAttaque());
                        //On test par la suite si le joueur a suffisament de mana ou que la capacité soit rechargée
                            tmp_atq=jeu.getJoueur()->getAttaque(numero1);
                        } while (jeu.getJoueur()->getManaCourrant()<tmp_atq->getManaRequit() || jeu.getTour()<tmp_atq->getPossibiliteReutilisation());

                        //Attaque du joueur avec la capacité demandé
                        jeu.getJoueur()->attaquer(jeu.getMonstre(),jeu.getJoueur()->getAttaque(numero1));
                        //Mise en place du temps de rechargement de l'attaque
                        (jeu.getJoueur()->getAttaque(numero1))->setPossibiliteReutilisation(jeu.getTour());
                    } else {
                        cout << "Vous n'avez pas d'attaque disponible" << endl
                             << "Le monstre joue un tour" << endl << endl;
                    }

                    //Test pour savoir si le monstre peut attaquer
                    if (jeu.getMonstre()->enVie() && jeu.getMonstre()->getChargement()<=jeu.getTour()) {
                        //Attaque du monstre sur le joueur
                        jeu.getMonstre()->attaquer(jeu.getJoueur());
                        //Mise en place de son temps de rechargement
                        jeu.getMonstre()->setChargement(jeu.getTour());
                    }

                    //Affichage des statistique du monstre
                    jeu.getMonstre()->afficherEtat();
                    //Augmentetion du nombre de tour
                    jeu.addTour();
                    //Soin de mana a chaque tour
                    jeu.getJoueur()->addManaCourrant(10);
                }
                //Soin du joueur après avoir battue un monstre si il est enore en vie
                if (jeu.getJoueur()->enVie())
                    jeu.getJoueur()->addVieCourrante(90);
            break;

            case '1' :
                jeu.getJoueur()->getInventaire()->afficherInventaire();
                cout << endl << endl;
            break;

            case '2' :
                cout << "Bonjour je suis le PNJ." << endl
                     << "Voulez vous acheter ou vendre ? a/v" << endl;
                do {
                    cin >> option;
                } while (option != 'a' && option != 'v');

                if (option == 'a') {
                    if (jeu.getJoueur()->getInventaire()->plein())
                        cout << "Videz d'abord votre inventaire" << endl;
                    else {
                        jeu.getVendeur()->afficherVendeur();
                        do {
                            cout << "Quel objet voulez-vous acheter ?";
                            cin >> numero1;
                        } while (numero1<0 || numero1>=jeu.getVendeur()->getTableDeVente()->getNbVente());
                        if (jeu.getJoueur()->getInventaire()->getNbOr()>=jeu.getVendeur()->getTableDeVente()->getListeVente()[numero1]->getPrixVente()) {
                            jeu.getJoueur()->achatPNJ(jeu.getVendeur()->getTableDeVente()->getListeVente()[numero1]);
                            cout << "Voici " 
                                 << jeu.getVendeur()->getTableDeVente()->getListeVente()[numero1]->getQuantiteVente() << " "
                                 << jeu.getVendeur()->getTableDeVente()->getListeVente()[numero1]->getItemVente()->getNomObjet() << endl;
                        } else {
                            cout << "Vous n'avez pas assez d'argent pour m'acheter celà." << endl;
                        }
                    }
                } else {
                    jeu.getJoueur()->getInventaire()->afficherInventaire();
                    cout << endl << endl;
                    cout << "Quel objet voulez-vous me vendre ?" << endl;
                    numero3=jeu.getJoueur()->getInventaire()->getNbEmplacement();
                    do {
                        cout << "Ligne : ";
                        cin >> numero1;
                    } while (numero1<0 || numero1 > (int)(numero3/10));
                    numero3-=numero1*10;
                    do {
                        cout << "Colonne :";
                        cin >> numero2;
                    } while (numero2<0 || numero2>numero3);
                    if (jeu.getJoueur()->getInventaire()->getInventaire()[numero1][numero2]->getQuantite()==0) {
                        cout << "Vous me proposer du vide !" << endl;
                    } else if (jeu.getJoueur()->getInventaire()->getInventaire()[numero1][numero2]->getQuantite()==1) {
                        cout << "Voici " << jeu.getJoueur()->getInventaire()->getInventaire()[numero1][numero2]->getItem()->getPrixPNJ() << " pièce d'or" << endl;
                    } else {
                        do {
                            cout << "Combien voulez-vous m'en vendre ?";
                            cin >> numero3;
                        } while (numero3 < 1 || numero3 > jeu.getJoueur()->getInventaire()->getInventaire()[numero1][numero2]->getQuantite());

                        cout << "Très bien voici ";
                        if (numero3*jeu.getJoueur()->getInventaire()->getInventaire()[numero1][numero2]->getItem()->getPrixPNJ()==1) {
                            cout << " pièce d'or." << endl;
                        } else {
                            cout << numero3*jeu.getJoueur()->getInventaire()->getInventaire()[numero1][numero2]->getItem()->getPrixPNJ()
                                 << " pièces d'or." << endl;
                        }
                    }
                    jeu.getJoueur()->getInventaire()->vendreObjetPNJ(numero1,numero2,numero3);
                }
            break;

            case '3' :
                jeu.getJoueur()->getArbreDeCompetence()->afficherBranches();
                do {
                    cout << endl << "Quel branche souhaitez vous voir ?";
                    cin >> numero1;
                } while(numero1 < 0 || numero1 > jeu.getJoueur()->getArbreDeCompetence()->getNbBranche()-1);
                //clear_screen();
                jeu.getJoueur()->getArbreDeCompetence()->getBranche()[numero1]->afficherBranche();
                cout << "Point de competence : ";
                cout << jeu.getJoueur()->getPointCompetenceUtilisee() << " / "
                     << jeu.getJoueur()->getNiveau() << endl;
                if (jeu.getJoueur()->getPointCompetenceUtilisee()<jeu.getJoueur()->getNiveau()) {
                    cout << "Voulez-vous débloquer une recompense ? o/n : ";
                    cin >> option;
                    cout << endl;
                    if (option == 'o') {
                        do {
                            cout << "Quel attaque debloquer ?";
                            cin >> numero2;
                        } while(numero2<0 || numero2 > jeu.getJoueur()->getArbreDeCompetence()->getBranche()[numero1]->getNbCompetence()-1);
                        if (!(jeu.getJoueur()->getArbreDeCompetence()->getBranche()[numero1]->getCompetence()[numero2]->getDebloque()))
                            jeu.getJoueur()->debloquerCompetence(numero1,numero2);
                    }
                }
            break;
            /*
            case '4' :
                cout << "Not yet available" << endl;
            break;
            */
        }

        //clear_screen();

    } while (option != 'q' && option != 'Q');

    return 0;
}

/*
Monsieur  Alexandre Quin, Le Pyrobarbare des pyrobarbare, le conquérant des commandes blocks et des architectures démentiels dans le monde des blocks et des pixels, le mathématiciens fou dans l'âme fou perdu en prépa, l'ami d'un ami (si c'est pas d'un ami en +) devenu ami (enfin je crois °-°) tout cour, le célebre, que dis-je l'illustre Monsieur Quinou
J'ai avec immence honeur et une volonté infinie le plaisir de vous annoncer aujourd'hui après un temps de travail inouïe
la sortie mondiale en ce jour d'un jeu révolutionnaire de cette année 
dont son aventure a commencé il y a de celà "nine thousands" années
dont vous serez le premier testeur dont le but est de ... euh bas de tuer des mobs ....,
Mais réalisé par mes soins :)
N'hésite pas si tu as le time !
A far far quiet friend 
Yann :D
*/