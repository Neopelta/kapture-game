 ____  __.              __
|    |/ _|____  _______/  |_ __ _________   ____
|      < \__  \ \____ \   __\  |  \_  __ \_/ __ \
|    |  \ / __ \|  |_> >  | |  |  /|  | \/\  ___/
|____|__ (____  /   __/|__| |____/ |__|    \_____
       \/    \/|__|
Projet Kapture

1. Démarrer le Logiciel

Prérequis :

- Compilateur `g++` avec support C++17
- CMake version 3.30 minimum
- make

Étapes :

1. Ouvrir un terminal dans le répertoire racine du projet.
2. Compiler le projet :
   ```bash
   make
   ```
3. Exécuter le jeu :
   ```bash
   make run
   ```

2. Auteurs

- Maxime MARCHIVE
- Ronan PLUTA

Université de Poitiers - UFR Sciences - Master 1 Informatique

3. Comment Jouer

Le jeu Kapture est un jeu de plateau stratégique en tour par tour.

Types d'unités :

- Éclaireur (E) : 5 cases de déplacement max, ne peut pas capturer le drapeau
- Troupe de choc (T) : 2 cases de déplacement max
- Chair à canon (C) : 3 cases de déplacement max

Types de terrain et coûts de déplacement :

- Terrain nu ( ) : 1 point de déplacement
- Forêt (#) : 2 points de déplacement
- Rivière (~) : Coût maximal de déplacement de l'unité

Couleurs des unités :

- Vert : Unité normale
- Violet : Unité portant le drapeau

Règles de combat :

- Éclaireur vs Éclaireur : Match nul
- Chair à canon/Troupe de choc vs Éclaireur : Éclaireur perd
- Troupe de choc vs Chair à canon : Chair à canon perd
- Chair à canon vs Chair à canon : 50% de chance de victoire
- Troupe de choc vs Troupe de choc : Les deux reculent d'une case
- Une unité portant le drapeau se comporte comme un éclaireur en combat

Commandes disponibles :

- `select <y,x>` : Sélectionner une unité aux coordonnées (y,x) (origine 0,0 en haut à gauche)
- `mv <steps> <direction>` : Déplacer l'unité sélectionnée dans la direction spécifiée

Directions possibles :

- `n` ou `north` : Nord
- `s` ou `south` : Sud
- `e` ou `east` : Est
- `w` ou `west` : Ouest
- `nw` ou `northwest` : Nord-Ouest
- `ne` ou `northeast` : Nord-Est
- `sw` ou `southwest` : Sud-Ouest
- `se` ou `southeast` : Sud-Est

Autres commandes :

- `stop` : Désélectionner l'unité
- `end` : Terminer le tour et passer au joueur suivant
- `quit` : Quitter la partie

Objectif du Jeu :

- Capturer le drapeau ennemi et le ramener à votre base sans perdre votre propre drapeau.

Structure du Projet

4. Organisation des dossiers :

- src/ : Code source
- include/ : Fichiers d'en-tête
- test/ : Tests unitaires

- data.txt : Terrain de jeu

5. Fonctionnalités Implémentées

- [x] Implémentation des commandes pour sélectionner une unité et la déplacer (Ronan)
- [x] Les unités peuvent se déplacer dans toutes les directions (8 connexités) (Maxime et Ronan)
- [x] Gestion des combats (Maxime)
- [x] Brouillard de guerre (Maxime)
- [x] Chargement d'une carte (Maxime)
- [x] Makefile fonctionnel (Ronan)
- [x] Capture du drapeau (Ronan)
- [x] Victoire si le drapeau est ramené et que le sien est présent (Ronan)
- [x] Sélection des unités via leurs coordonnées (Maxime et Ronan)
- [x] Fin d'un tour pour passer au joueur suivant (Ronan)
- [x] Retour aux coordonnées d'origine en cas de défaite d'une unité (Maxime et Ronan)
- [x] Une unité avec drapeau devient éclaireur (Maxime)
- [x] Different type de terrain (nu, foret et rivière) avec les couts de déplacement

6. Fonctionnalités Non Fonctionnelles et bug

- [ ] Gestion du drapeau qui tombe lorsque l'unité portant le drapeau perd un combat
- [ ] Sauvegarde de la partie

7. Licence

Projet académique - Université de Poitiers (2025)

---

Dernière mise à jour : 06 Janvier 2025
