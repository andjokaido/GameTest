but: fighter

CXX = g++
CXXFLAGS = 

O_FILES = main.o Jeu.o \
		  Entitee.o Vendeur.o Monstre.o Personnage.o Attaque.o \
		  Competence.o BrancheDeCompetence.o ArbreDeCompetence.o \
		  Item.o Vente.o TableDeVente.o Loot.o TableDeLoot.o EmplacementInventaire.o Inventaire.o \
		  PotionDeVie.o

SRC= $(O_FILES:.o=.cpp)


Attaque.o: Attaque.cpp Attaque.h
Entitee.o: Entitee.cpp Entitee.h
Vendeur.o: Vendeur.cpp Vendeur.h Entitee.h TableDeVente.h PotionDeVie.h
Personnage.o: Personnage.cpp Personnage.h Entitee.h Monstre.h ArbreDeCompetence.h Inventaire.h Attaque.h Vente.h
Competence.o: Competence.cpp Competence.h Attaque.h
BrancheDeCompetence.o: BrancheDeCompetence.cpp BrancheDeCompetence.h Competence.h
ArbreDeCompetence.o: ArbreDeCompetence.cpp ArbreDeCompetence.h BrancheDeCompetence.h
Item.o: Item.cpp Item.h
PotionDeVie.o : PotionDeVie.cpp PotionDeVie.h Item.h
Vente.o: Vente.cpp Vente.h Item.h
TableDeVente.o: TableDeVente.cpp TableDeVente.h Vente.h
Loot.o: Loot.cpp Loot.h Item.h
TableDeLoot.o : TableDeLoot.h Loot.h
EmplacementInventaire.o: EmplacementInventaire.cpp EmplacementInventaire.h Item.h
Inventaire.o: Inventaire.cpp Inventaire.h EmplacementInventaire.h
Monstre.o: Monstre.cpp Monstre.h Entitee.h TableDeLoot.h
Jeu.o: Jeu.cpp Entitee.h Vendeur.h Monstre.h Personnage.h Attaque.h \
	   Competence.h BrancheDeCompetence.h ArbreDeCompetence.h \
	   Item.h EmplacementInventaire.h Inventaire.h \
	   Loot.h TableDeLoot.h
main.o: main.cpp Jeu.h


fighter : $(O_FILES)
	$(CXX) -o fighter $(O_FILES)


clean :
	-rm -f $(O_FILES) fighter

test :
	./fighter

.PHONY : but clean