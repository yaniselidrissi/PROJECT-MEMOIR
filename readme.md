# Projet de C – Gestion de jobs avec dépendances

## Description

Ce projet permet de gérer des tâches (appelées "jobs") qui dépendent les unes des autres. Le programme peut lire un fichier avec les données des jobs, afficher les infos, trier les jobs, calculer leur rang, enlever certains jobs, et donner les marges pour savoir s’il y a du retard possible.

## Fichiers importants

- `main.c` : le point de départ du programme.
- `job.c` : gère les infos sur chaque job (comme le titre, le rang, etc.).
- `io.c` : lit les fichiers, trie les jobs.
- `rank.c` : calcule les rangs, les marges et détecte les jobs critiques.
- `list.c` : gère une liste chaînée pour stocker les jobs.
- Les fichiers `.h` dans `include/` contiennent les définitions des fonctions.

## Comment ça marche

- Le programme lit un fichier `.dta` (comme `data/graph2.dta`) pour récupérer les jobs.
- Chaque job peut dépendre d’un ou plusieurs autres.
- Le programme trie les jobs et calcule des infos comme leur rang et leur marge.
- Il montre les jobs critiques (ceux qu’on ne peut pas retarder).

## Pour compiler

Si tu es sur Windows avec MinGW :

```bash
mingw32-make run
