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
	annee INT,
	saison VARCHAR2(10),
	mois INT,
	jour INT,
	date_debut DATE,
	date_fin DATE,
	CONSTRAINT key_periode PRIMARY KEY(id_periode),
	CONSTRAINT check_debut_inf_fin CHECK (date_debut <= date_fin),
	CONSTRAINT check_debut_not_null check (date_debut IS NOT NULL));

CREATE TABLE Tempete(
	id_tempete INT,
	type_tempete VARCHAR2(30),
	force VARCHAR2(1),
	CONSTRAINT key_tempete PRIMARY KEY(id_tempete));

CREATE TABLE Faits(
	id_faits INT,
	id_dommage INT,
	id_lieu INT,
	id_periode INT,
	id_tempete INT,
	description VARCHAR2(1000),
	CONSTRAINT key_faits PRIMARY KEY(id_faits),
	CONSTRAINT foreign_key_dommage FOREIGN KEY(id_dommage) REFERENCES Dommage(id_dommage),
	CONSTRAINT foreign_key_lieu FOREIGN KEY(id_lieu) REFERENCES Lieu(id_lieu),
	CONSTRAINT foreign_key_periode FOREIGN KEY(id_periode) REFERENCES Periode(id_periode),
	CONSTRAINT foreign_key_tempete FOREIGN KEY(id_tempete) REFERENCES Tempete(id_tempete));	
