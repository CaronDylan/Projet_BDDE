# Projet Entrepôt de données

L'entrepôt regroupe toutes les tempêtes (tornade, grèle, canicule ,etc.) qui se sont déroulées au Etats Unies. Le schéma de l'entrepôt se trouve dans le Rapport (c'est aussi le fichier Schema BDD.dia).

Lien des données : https://www.ncdc.noaa.gov/stormevents/ftp.jsp

L'entrepôt de données est réalisé en SQL avec Oracle.


Détails sur les fichiers se trouvant ici :
* Le fichier Create.sql regroupe les requêtes permettant de créer l'Entrepôt de données.
* Le fichier Insert_genrator.cpp est un programme en C++ permettant de générer le fichier Insert.sql à partir du CSV. 
* Le fichier Insert.sql regroupe les requêtes permettant l'insertion des tuples dans l'Entrepôt de données.
* Le fichier Drop.sql regroupe les requêtes permettant de supprimer l'Entrepôt de données.
* Le fichier OLAP.sql regroupe toutes les requêtes OLAP pour avoir des informations sur le nombre de tornades, les degats causés etc.
* Le fichier Resultat_OLAP.txt regroupe les résultats des requêtes OLAP.

Pour compiler le fichier Insert_generator.cpp : g++ -Wall Insert_generator.cpp -o Insert_generator.exe

Pour exécuter le fichier Insert_generator.exe : ./Insert_generator.exe ../CSV/StormEvents_details-ftp_v1.0_d1994_c20170717.csv Insert.sql
