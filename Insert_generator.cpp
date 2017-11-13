#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct periode {
	string annee_debut;
	string mois_debut;
	string jour_debut;
	string heure_debut;
	string min_debut;
	string annee_fin;
	string mois_fin;
	string jour_fin;
	string heure_fin;
	string min_fin;
};

bool eq_periode(periode p1, periode p2) {
	return (p1.annee_debut==p2.annee_debut && p1.mois_debut==p2.mois_debut && p1.jour_debut==p2.jour_debut && p1.heure_debut==p2.heure_debut && p1.min_debut==p2.min_debut && p1.annee_fin==p2.annee_fin && p1.mois_fin==p2.mois_fin && p1.jour_debut==p2.jour_fin && p1.heure_fin==p2.heure_fin && p1.min_fin==p2.min_fin);
}

periode init_periode() {
	periode p1;
	p1.annee_debut="";
	p1.mois_debut="";
	p1.jour_debut="";
	p1.heure_debut="";
	p1.min_debut="";
	p1.annee_fin="";
	p1.mois_fin="";
	p1.jour_fin="";
	p1.heure_fin="";
	p1.min_fin="";
}


int main(int argc, char const *argv[]) {
	ifstream read(argv[1], ios::in);
	ofstream write(argv[2], ios::out | ios::trunc);

	periode pcurrent=init_periode();
	stringstream ss;
	string car;
	
	string insert[5];
	insert[0] = "INSERT INTO Periode VALUES(";
	insert[1] = "INSERT INTO Lieu VALUES(";
	insert[2] = "INSERT INTO Tempete VALUES(";
	insert[3] = "INSERT INTO Faits VALUES(";

	if (read && write) {
		string line="";
		
		getline(read,line);
		getline(read,line);
		char caracter;
		int cptvirgule = 0;
		int cptanne_month = 0;
		while(read.get(caracter)){
			car = string(caracter);//probleme car--string
			if(car=",") {cptvirgule++;}
			if(cptvirgule==0) {
				cptanne_month++;
				if(cptanne_month <= 4){
					
				}
			}
			
		}
	}
}
