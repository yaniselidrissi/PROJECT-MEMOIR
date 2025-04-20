# Projet MPM - Gestion de tâches avec dépendances

## 📌 Description

Ce projet implémente une application en langage C permettant de lire, analyser, trier et afficher des graphes de dépendances entre tâches (ou jobs), typiquement utilisés pour la planification de projets (type MPM : méthode des potentiels au plus tôt / au plus tard).

Chaque tâche peut dépendre d'autres tâches, et est représentée sous forme de **job** dans un graphe orienté. Le programme permet notamment :

- La lecture d'un fichier de données décrivant le graphe
- L'affichage du graphe (successeurs, antécédents)
- Le tri topologique (classement des tâches par rang)
- Le calcul des marges et du chemin critique

## 📁 Structure du projet

```
PROJET/
├── main.c                  # Point d'entrée du programme
├── Makefile                # Script de compilation
├── README.md               # Ce fichier
├── data/
│   └── graph2.dta          # Exemple de fichier de données
├── include/                # Fichiers d'en-tête (.h)
│   ├── job.h
│   ├── list.h
│   ├── list_1.h
│   ├── list_2.h
│   └── io.h
└── canevas/                # Fichiers sources (.c)
    ├── job.c               # Fonctions liées à la structure de job
    ├── list.c              # Liste doublement chaînée (gestion des jobs)
    ├── io.c                # Lecture du graphe + tri rapide
    └── rank.c              # Fonctions de classement et calcul des marges
```

## ⚙️ Compilation

Assurez-vous d’avoir **MinGW** installé (pour Windows) et que `mingw32-make` est accessible depuis votre terminal.

Pour compiler le programme :
```bash
mingw32-make
```

Cela crée un exécutable dans le dossier `bin/` nommé `mpm`.

## ▶️ Exécution

Une fois compilé, vous pouvez exécuter le programme avec la commande :
```bash
mingw32-make run
```

Par défaut, le programme lit le fichier `data/graph2.dta`. Vous pouvez modifier cette valeur dans le `Makefile` si besoin.

## 🧠 Fonctionnalités

- **Lecture d’un graphe** : le fichier `.dta` décrit les tâches (nom + durée) et les dépendances entre elles.
- **Affichage** : toutes les tâches et leurs dépendances sont affichées de manière lisible.
- **Tri topologique** : les tâches sont classées en fonction de leurs dépendances.
- **Calcul des marges** :
  - Au plus tôt (`au_plus_tot`)
  - Au plus tard (`au_plus_tard`)
  - Marge totale
- **Détection du chemin critique** : les jobs critiques sont signalés dans l'affichage.

## 📥 Format du fichier `.dta`

Voici un exemple de format attendu dans `graph2.dta` :

```
JOB A 4
JOB B 3
JOB C 2
LINK A B
LINK A C
LINK B C
```

Chaque ligne décrit soit un `JOB` (nom + durée), soit un `LINK` indiquant une dépendance entre deux jobs.

## 🛠️ Auteurs

Projet développé dans le cadre d’un cours d’algorithmique et de programmation en C.

## 📌 À faire / améliorations possibles

- Ajouter un affichage graphique du graphe
- Détecter les cycles dans le graphe (non autorisé en MPM)
- Export des résultats au format `.dot` ou `.json`
