--CREATE SEQUENCE for_id START WITH 1 INCREMENT BY 1;
CREATE TABLE Dommage(
	id_dommage INT,
	dommage_sur_propriete VARCHAR2(10),
	dommage_sur_champs VARCHAR2(10),
	CONSTRAINT key_dommage PRIMARY KEY(id_dommage));

CREATE TABLE Lieu(
	id_lieu INT,
	etat VARCHAR2(30),
	ville VARCHAR2(30),
	CONSTRAINT key_lieu PRIMARY KEY(id_lieu));

CREATE TABLE Periode(
	id_periode INT,
	annee_debut INT,
	mois_debut INT,
	jour_debut INT,
	annee_fin INT,
	mois_fin INT,
	jour_fin INT,
	CONSTRAINT key_periode PRIMARY KEY(id_periode));

CREATE TABLE Tempete(
	id_tempete INT,
	type_tempete VARCHAR2(30),
	CONSTRAINT key_tempete PRIMARY KEY(id_tempete));

CREATE TABLE Faits(
	id_faits INT,
	id_dommage INT,
	id_lieu INT,
	id_periode INT,
	id_tempete INT,
	CONSTRAINT key_faits PRIMARY KEY(id_faits),
	CONSTRAINT foreign_key_dommage FOREIGN KEY(id_dommage) REFERENCES Dommage(id_dommage),
	CONSTRAINT foreign_key_lieu FOREIGN KEY(id_lieu) REFERENCES Lieu(id_lieu),
	CONSTRAINT foreign_key_periode FOREIGN KEY(id_periode) REFERENCES Periode(id_periode),
	CONSTRAINT foreign_key_tempete FOREIGN KEY(id_tempete) REFERENCES Tempete(id_tempete));	
