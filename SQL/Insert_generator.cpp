#include <iostream>
#include <fstream>

using namespace std;


//Structure pour la table Période
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
	return(p1);
}

//Structure pour la table Lieu
struct lieu {
	string etat;
	string ville;
};

lieu init_lieu() {
	lieu l1;
	l1.etat="";
	l1.ville="";
	return(l1);
}

//Structure pour la table Temepete
struct tempete {
	string type_tempete;
};

tempete init_tempete() {
	tempete t1;
	t1.type_tempete="";
	return(t1);
}

//Structure pour la table Dommage
struct dommage {
	string propriete;
	string agriculture;
};

dommage init_dommage() {
	dommage d1;
	d1.propriete="";
	d1.agriculture="";
	return(d1);
}

//Structure pour la table Faits
struct faits {
	string resume;
};

faits init_faits() {
	faits f1;
	f1.resume="";
	return(f1);
}


int main(int argc, char const *argv[]) {
	ifstream read(argv[1], ios::in);
	ofstream write(argv[2], ios::out | ios::trunc);
	
	//Limite du nombre de tuples
	int LIMIT;
	cout << "Combien de tuples à generer ? " <<endl;
	cin >> LIMIT;

	//Initialisation des structures
	periode pcurrent=init_periode();
	lieu lcurrent=init_lieu();
	tempete tcurrent=init_tempete();
	dommage dcurrent=init_dommage();
	faits fcurrent=init_faits();
	
	string insert[6];
	insert[0] = "INSERT INTO Periode VALUES(";
	insert[1] = "INSERT INTO Lieu VALUES(";
	insert[2] = "INSERT INTO Tempete VALUES(";
	insert[3] = "INSERT INTO Dommage VALUES(";
	insert[4] = "INSERT INTO Faits VALUES(";

	if (read && write) {
		//Enleve la lecture de la première ligne
		string line="";
		getline(read,line);

		//Initialisation des compteurs utiles à la mise en forme des données
		//Character courant
		char caracter;

		//ID pour les tuples
		int id=0;
		
		//Compteur utiles à la mise en forme des données pour la table Période
		int cptvirgule = 0;
		int cptanne_month_deb = 0;
		int cptanne_month_fin = 0;
		int cpth_min_deb =0;
		int cpth_min_fin =0;
		int in_attribut =0;
			
		while(id<LIMIT && read.get(caracter)){
			if(caracter==',' && in_attribut==0) {cptvirgule++;} else {
				if(caracter=='\n') {
					//Fin de la lecture d'une ligne
	
					id++;
					write << insert[0] +to_string(id)+","+pcurrent.annee_debut+","+pcurrent.mois_debut+","+pcurrent.jour_debut+","+/*pcurrent.heure_debut+","+pcurrent.min_debut+","+*/pcurrent.annee_fin+","+pcurrent.mois_fin+","+pcurrent.jour_fin+/*","+pcurrent.heure_fin+","+pcurrent.min_fin+*/");" <<endl;
					write << insert[1] +to_string(id)+","+lcurrent.etat+","+lcurrent.ville+");"<<endl;
					write << insert[2] +to_string(id)+","+tcurrent.type_tempete+");"<<endl;
					write << insert[4] +to_string(id)+","+to_string(id)+","+to_string(id)+","+to_string(id)+","+dcurrent.propriete+","+dcurrent.agriculture+");"<<endl;
					write <<endl;

					//Reinitialisation des variables propres a chacunes des lignes
					cptvirgule = 0;
					cptanne_month_deb = 0;
					cptanne_month_fin = 0;
					cpth_min_deb =0;
					cpth_min_fin =0;

					//Reinitialisation des structures
					pcurrent=init_periode();
					lcurrent=init_lieu();
					tcurrent=init_tempete();
					dcurrent=init_dommage();
					fcurrent=init_faits();
				} else {

					//Chaque commentaire qui suis fais reference à une colonne du CSV

					//BEGIN_YEARMONTH			
					if(cptvirgule==0) {
						cptanne_month_deb++;
						if(cptanne_month_deb <= 4) {pcurrent.annee_debut += caracter;} 
						else {pcurrent.mois_debut += caracter;}
					}
		
					//BEGIN_DAY
					if(cptvirgule==1) pcurrent.jour_debut += caracter;
	
					//BEGIN_TIME
					if(cptvirgule==2){
						cpth_min_deb++;
						if(cpth_min_deb <= 2) {pcurrent.heure_debut += caracter;}
						else {pcurrent.min_debut += caracter;}
					}

					//END_YEARMONTh
					if(cptvirgule==3) {
						cptanne_month_fin++;
						if(cptanne_month_fin <= 4) {pcurrent.annee_fin += caracter;} 
						else {pcurrent.mois_fin += caracter;}
					}
	
					//END_DAY
					if(cptvirgule==4) pcurrent.jour_fin += caracter;
						
					//END_TIME
					if(cptvirgule==5){
						cpth_min_fin++;
						if(cpth_min_fin <= 2) {pcurrent.heure_fin += caracter;}
						else {pcurrent.min_fin += caracter;}
					}
					//EPISODE_ID ---> cptvirgule == 6
					//EVENT_ID ---> cptvirgule == 7

					//STATE
					if(cptvirgule==8){
							if(caracter=='\"') {
								lcurrent.etat += '\'';
								in_attribut++;
								if(in_attribut ==2) in_attribut =0;

							}else if(caracter =='\'') {
								lcurrent.etat +="\\'";		
							
							}else{
								lcurrent.etat +=caracter;
							}
					}

					//STATE_FIPS ---> cptvirgule == 9
					//YEAR ---> cptvirgule == 10
					//MONTH_NAME ---> cptvirgule == 11
					
					//EVENT_TYPE
					if(cptvirgule==12){
						if(caracter=='\"') {
							tcurrent.type_tempete += '\'';
							in_attribut++;
							if(in_attribut ==2) in_attribut =0;
						}else if(caracter =='\'') {
							tcurrent.type_tempete +="\\'";
						}else {
							tcurrent.type_tempete +=caracter;
						}
					}
					
					//CZ_TYPE ---> cptvirgule == 13
					//CZ_FIPS ---> cptvirgule == 14

					//CZ_NAME
					if(cptvirgule==15) {
						if(caracter=='\"') {
							lcurrent.ville += '\'';
							in_attribut++;
							if(in_attribut ==2) in_attribut =0;
						}else if(caracter =='\'') {
							lcurrent.ville +="\\'";
						}else{
							lcurrent.ville +=caracter;
						}
					}
					
					//WFO  ---> cptvirgule == 16
					//BEGIN_DATE_TIME  ---> cptvirgule == 17
					//CZ_TIMEZONE  ---> cptvirgule == 18
					//END_DATE_TIME  ---> cptvirgule == 19
					//INJURIES_DIRECT  ---> cptvirgule == 20
					//INJURIES_INDIRECT  ---> cptvirgule == 21
					//DEATHS_DIRECT  ---> cptvirgule == 22
					//DEATHS_INDIRECT  ---> cptvirgule == 23
				
					//DAMAGE_PROPERTY
					if(cptvirgule==24){
						if(caracter=='\"' || caracter=='M' || caracter=='K') {
							if (caracter=='\''){dcurrent.propriete += '\'';}
							if (caracter=='M'){dcurrent.propriete += "000000";}
							if (caracter=='K'){dcurrent.propriete +="000";}
						}else {
							dcurrent.propriete +=caracter;
						}
					}

					//DAMAGE_CROPS
					if(cptvirgule==25){
						if(caracter=='\"' || caracter=='M' || caracter=='K') {
							if (caracter=='\''){dcurrent.agriculture += '\'';}
							if (caracter=='M'){dcurrent.agriculture += "000000";}
							if (caracter=='K'){dcurrent.agriculture +="000";}
						}else {
							dcurrent.agriculture +=caracter;
						}
					}
	
					//SOURCE  ---> cptvirgule == 26
					//MAGNITUDE  ---> cptvirgule == 27
					//MAGNITUDE_TYPE  ---> cptvirgule == 28
					//FLOOD_CAUSE  ---> cptvirgule == 29
					//CATEGORY  ---> cptvirgule == 30
					//TOR_F_SCALE  ---> cptvirgule == 31
					//TOR_WIDTH  ---> cptvirgule == 32
					//TOR_OTHER_WFO  ---> cptvirgule == 33
					//TOR_OTHER_CZ_STATE  ---> cptvirgule == 34
					//TOR_OTHER_CZ_FIPS  ---> cptvirgule == 35	
					//TOR_OTHER_CZ_NAME  ---> cptvirgule == 36
					//BEGIN_RANGE  ---> cptvirgule == 37
					//BEGIN_AZIMUTH  ---> cptvirgule == 38
					//BEGIN_LOCATION  ---> cptvirgule == 39
					//END_RANGE  ---> cptvirgule == 40
					//END_AZIMUTH  ---> cptvirgule == 41
					//END_LOCATION  ---> cptvirgule == 42
					//BEGIN_LAT  ---> cptvirgule == 43
					//BEGIN_LON  ---> cptvirgule == 44
					//END_LAT  ---> cptvirgule == 45
					//END_LON  ---> cptvirgule == 46
					//EPISODE_NARRATIVE  ---> cptvirgule == 47

					//EVENT NARRATIVE
					/*if(cptvirgule==48){
						if(stop_resume == 0) {
							if (!(caracter == ',' || nb_dquote_resume ==2)){
								if(caracter=='\"') {
									fcurrent.resume += '\'';
								}else if(caracter=='\'') {
									fcurrent.resume +="\\'";
								}else {
									fcurrent.resume += caracter;
								}
							} else {
								stop_resume++;
							}
						}
					}*/				
					
				}
				
			}
		}
	}
}
