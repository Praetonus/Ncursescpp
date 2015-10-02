# Ncursescpp

Une interface C++ à ncurses respectant le RAII.

Les fonctionnalités de ncurses supportées par ncursescpp sont :

* Affichage de texte
* Saisie clavier
* Couleurs et attributs
* Fenêtres
* Sous-fenêtres

Ncursescpp est en développement et des fonctionnalités supplémentaires seront ajoutées au fur et à mesure.

## Philosophie

L'objectif de ncursescpp est de permettre l'utilisation de ncurses à travers une interface respectant le principe de gestion de ressources de C++, le RAII. Chaque objet de ncurses (fenêtres, couleurs, etc) est géré de manière automatique et transparente.

## Installation

L'installation de ncursescpp requiert un compilateur supportant le standard C++11 et se fait via [CMake](http://www.cmake.org).

## Licence

Ncursescpp est distribué sous licence CeCILL-B (similaire à la licence MIT). Référez-vous au fichier LICENCE ou à http://www.cecill.info pour plus d'informations.

## Documentation

Vous pouvez générer la documentation de ncursescpp avec [Doxygen](http://www.doxygen.org/index.html). Lancez la commande `doxygen Doxyfile` depuis le dossier `doc/` La documentation contient uniquement les informations sur ncursescpp, ncurses étant déjà documenté.
