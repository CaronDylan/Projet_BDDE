SPOOL Resultat_OLAP.txt;
SET ECHO ON;
SET SERVEROUTPUT ON SIZE 2000;



--******************************************************
--****************Requête 1*****************************
--******************************************************

--Permet de voir les degats causés sur les propriétes par chacun des types d'intempérie pour chaque mois et voir les degats totaux sur l'année

SELECT mois_debut, type_tempete, SUM(dommage_sur_propriete)
FROM Faits f, Tempete t, Periode p, Dommage d
WHERE f.id_tempete = t.id_tempete AND f.id_periode = p.id_periode AND f.id_dommage = d.id_dommage
GROUP BY ROLLUP(mois_debut, type_tempete); 

--******************************************************
--****************Requête 2*****************************
--******************************************************

--Permet de voir les degats causés par les types de tempete sur chacun des mois et les  degats totaux provoqué par l'ensemble des intempéries sur chacun des mois

SELECT mois_debut, type_tempete, SUM(dommage_sur_propriete  + dommage_sur_champs) AS dommage_cause
FROM Faits f, Tempete t, Periode p, Dommage d
WHERE f.id_tempete = t.id_tempete AND f.id_periode = p.id_periode AND f.id_dommage = d.id_dommage
GROUP BY CUBE(mois_debut, type_tempete);


--******************************************************
--****************Requête 3*****************************
--******************************************************

--Donne le nombre de tempete signalé par mois et par état 

SELECT etat, mois_debut, COUNT(*) AS nb_tempete
FROM Periode p, Lieu l, Faits f
WHERE f.id_lieu = l.id_lieu AND f.id_periode = p.id_periode
GROUP BY (mois_debut,etat)
ORDER BY (mois_debut);

--******************************************************
--****************Requête 4*****************************
--******************************************************

--Donne le nombre d'intempéries par Etats durant l'année et le nombre de tempete par mois aux Etats-Unis

SELECT etat, mois_debut, SUM(nb_tempete) AS nb_tempete
FROM (
	SELECT etat, mois_debut, COUNT(*) AS nb_tempete
	FROM Periode p, Lieu l, Faits f
	WHERE f.id_lieu = l.id_lieu AND f.id_periode = p.id_periode
	GROUP BY (mois_debut,etat)
	ORDER BY (mois_debut)
	)
GROUP BY GROUPING SETS((etat),(mois_debut),());

--******************************************************
--****************Requête 5*****************************
--******************************************************

--Classe les etats en fonction des degats subis sur les champs

SELECT etat, SUM(dommage_sur_champs) AS SUM_champs,
	rank() over (order by SUM(dommage_sur_champs) desc) AS Rank
FROM Faits f, Lieu l, Dommage d
WHERE f.id_lieu = l.id_lieu AND f.id_dommage = d.id_dommage
GROUP BY (etat);

--******************************************************
--****************Requête 6*****************************
--******************************************************

--Donne les 10 etats ayant subi le plus de degats sur leurs infrastructures

SELECT etat, damage_property
FROM (
	SELECT etat, SUM(dommage_sur_propriete) AS damage_property
	FROM Faits f, Lieu l, Dommage d
	WHERE f.id_lieu = l.id_lieu AND f.id_dommage = d.id_dommage
	GROUP BY (etat)
	ORDER BY SUM(dommage_sur_propriete) DESC
	)
WHERE ROWNUM <=10;

--******************************************************
--****************Requête 7*****************************
--******************************************************

--Classe les etats en fonction du nombre de tempete qu'ils ont subis et la colonne permet de savoir que par exemple la moitie des etats ont subi 223 intempéries.
SELECT etat, nb_tempete, NTILE(4) over(order by nb_tempete DESC) AS Quart
FROM (
	SELECT etat, COUNT(*) AS nb_tempete
	FROM Lieu l, Faits f
	WHERE f.id_lieu = l.id_lieu
	GROUP BY (etat)
	);

--******************************************************
--****************Requête 8*****************************
--******************************************************

--Donne le nombre de tempete qui on causer 5M de degats sur les infrastructures par Etat (dans l'année) ou par Mois (tout Etat confondu)

SELECT mois_debut, etat, SUM(nb_tempete) AS nb_temp, GROUPING(mois_debut) AS mois, GROUPING(etat) AS state
FROM (
	SELECT mois_debut, etat, COUNT(*) AS nb_tempete
	FROM Lieu l, Faits f, Periode p, Dommage d
	WHERE f.id_lieu = l.id_lieu AND f.id_periode = p.id_periode AND f.id_dommage = d.id_dommage AND dommage_sur_propriete ='5000000'
	GROUP BY (etat,mois_debut)
	)
GROUP BY GROUPING SETS((mois_debut),(etat))
ORDER BY nb_temp DESC;

--******************************************************
--****************Requête 9*****************************
--******************************************************

--Donne le nombre de tempètes par mois ainsi que le cumul.

SELECT mois_debut, COUNT(*) AS nb_tempete, SUM(COUNT(*)) over(order by mois_debut rows unbounded preceding) AS Cumul
FROM Faits f, Periode p
WHERE f.id_periode = p.id_periode
GROUP BY mois_debut;
 
SPOOL OFF;
