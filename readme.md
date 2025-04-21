# Résumé du Projet : Gestion de Tâches avec Dépendances

## Objectif du projet
Ce projet vise à développer un système de gestion de tâches sous forme de graphe, où chaque tâche a une durée spécifique, et les tâches peuvent avoir des dépendances entre elles. L'objectif est de modéliser ces tâches et leurs relations, puis de calculer le rang des tâches ainsi que leurs marges totales et libres. Ce projet inclut des opérations telles que le tri des tâches en fonction de divers critères, la prune des dépendances inutiles, et le calcul de la marge.

## Fonctionnalités principales
1. **Lecture des tâches depuis un fichier**
   - Les tâches sont lues depuis un fichier .dta contenant les informations sur les tâches nom et durée ainsi que les dépendances entre elles.

2. **Tri des tâches**
   - Les tâches sont triées en fonction de leur degré d'entrée et de leur rang, grâce à une fonction de tri rapide.

3. **Calcul des rangs**
   - Chaque tâche reçoit un rang qui reflète son ordre dans le processus de travail, en prenant en compte les dépendances.

4. **Prune des dépendances inutiles**
   - La fonction prune permet d’éliminer certaines dépendances non nécessaires afin d'optimiser le graphe.

5. **Calcul des marges**
   - Les marges totales et libres des tâches sont calculées. La marge totale détermine le délai maximal pendant lequel une tâche peut être retardée sans affecter le projet, tandis que la marge libre représente l’espace de manœuvre d’une tâche sans interférer avec les autres.

## Fonctionnement du Programme

1. **Structure des données**
   - **Tâches (`job_t`)** : Chaque tâche contient un titre, une durée (`life`), un rang, des listes de précédence et de postériorité, ainsi que des informations sur les dépendances (degré entrant et sortant).
   - **Graphe (`list_t`)** : Le graphe est implémenté comme une liste de tâches. Chaque tâche peut être liée à d’autres tâches en fonction de leurs dépendances.

2. **Algorithmes utilisés**
   - **Quicksort** : Un tri rapide est utilisé pour trier les tâches en fonction de leur degré d’entrée et de leur rang.
   - **Calcul des rangs** : Les rangs des tâches sont calculés en tenant compte des tâches qui les précèdent.
   - **Prune** : Cette fonction permet de simplifier le graphe en retirant les dépendances redondantes ou inutiles.
   - **Calcul des marges** : Le programme calcule les marges totales et libres des tâches afin de déterminer les possibilités de planification flexible.

## Technologies utilisées
- **Langage** : C
- **Structure des données** : Listes chaînées, Graphes dirigés
- **Algorithmes** : Tri rapide (quicksort), calcul de rangs et de marges

## Exécution du programme
1. Le programme prend en entrée un fichier `.dta` contenant les informations sur les tâches et leurs dépendances.
2. Il génère et affiche plusieurs informations : les tâches triées, leurs rangs, les marges totales et libres, ainsi que les dépendances après la fonction prune.
3. Il est possible de compiler et exécuter le programme via un `Makefile` ou directement via la ligne de commande.

## Exemple de fichier d’entrée (graph.dta)
(different de celui du cours avec l'exemple du cours boucle infini)

```plaintext
4
DS 2
DC 4
PC 4
P 5
0 1
2 1
1 2
2 3
