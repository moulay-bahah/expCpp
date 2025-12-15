# Présentation du Système de Gestion des Étudiants Simple

## 1. Introduction

### Aperçu
Le **Système de Gestion des Étudiants Simple** est une application console légère conçue pour aider les établissements d'enseignement ou les particuliers à gérer efficacement les dossiers des étudiants. Construit en **C++**, ce projet met l'accent sur la simplicité et la facilité de compréhension, évitant les paradigmes complexes de programmation orientée objet (POO) au profit d'une approche procédurale directe.

### Objectif
L'objectif principal de ce système est de fournir une solution numérique pour :
*   **Stocker les Données des Étudiants** : Suivre les noms, identifiants, âges, filières et moyennes générales (GPA) des étudiants.
*   **Gestion des Données** : Permettre aux utilisateurs d'Ajouter, Voir, Rechercher, Modifier et Supprimer des dossiers d'étudiants.
*   **Persistance des Données** : Assurer que les données sont sauvegardées et récupérées à partir d'un fichier, afin que les dossiers ne soient pas perdus à la fermeture du programme.

### Public Cible
*   **Étudiants & Débutants** : Une excellente ressource d'apprentissage pour comprendre les bases du C++ comme les tableaux, la gestion des fichiers et les fonctions.
*   **Petites Institutions** : Un outil de base pour le suivi d'un petit nombre d'étudiants sans les coûts des systèmes de base de données complexes.

---

## 2. Comment ça Marche

### Technologie Principale
*   **Langage** : C++ (Compatible Standard 98/11).
*   **Stockage** : Gestion de fichiers texte de bas niveau (`students_simple.txt`).
*   **Interface** : Interface en Ligne de Commande (CLI) pour une compatibilité universelle.

### Structure de Données
Le système utilise une simple `struct` C++ pour définir un Étudiant :
```cpp
struct Student {
    int id;         // Identifiant unique
    string name;    // Nom complet de l'étudiant
    int age;        // Âge de l'étudiant
    string major;   // Domaine d'étude
    double gpa;     // Moyenne Générale (Grade Point Average)
};
```
Ces dossiers d'étudiants sont gérés en mémoire à l'aide d'un **Tableau** de taille fixe (`Student students[100]`), offrant un accès rapide et une simplicité.

### Fonctionnalités Clés & Flux de Travail

1.  **Boucle du Menu Principal** : 
    Le programme s'exécute dans une boucle continue, affichant un menu d'options jusqu'à ce que l'utilisateur choisisse de "Quitter". Cela garantit que l'application est interactive et prête pour plusieurs commandes.

2.  **Ajout d'Étudiants** : 
    *   Le système vérifie d'abord s'il y a de la place dans le tableau.
    *   Il génère automatiquement un ID unique pour éviter les doublons.
    *   La validation des entrées assure que l'Âge (1-150) et la Moyenne (0.0-4.0) sont réalistes.

3.  **Persistance des Fichiers (Sauvegarder & Charger)** :
    *   **Chargement** : Au démarrage du programme, il lit automatiquement `students_simple.txt`. Il analyse chaque ligne, séparant les données par le délimiteur `|` pour reconstruire les dossiers utilisateurs.
    *   **Sauvegarde** : Après chaque modification (Ajout, Modification, Suppression), le système réécrit tout le tableau dans le fichier texte. Cette fonctionnalité de "Sauvegarde Automatique" protège les données contre les plantages.

    *Exemple de Format de Fichier :*
    ```text
    1|John Doe|20|Informatique|3.5
    ```

4.  **Recherche & Modification** :
    *   **Recherche** : Itère à travers le tableau pour trouver des correspondances partielles pour les noms (par exemple, rechercher "John" trouve "John Doe").
    *   **Modification/Suppression** : Localise un étudiant par son ID unique. La suppression est gérée en décalant tous les éléments suivants du tableau d'une position vers la gauche pour combler le vide.

---

## 3. Conclusion

### Résumé
Ce projet démontre avec succès comment construire une application de gestion de données fonctionnelle en utilisant des concepts de programmation de base. Il équilibre simplicité et utilité, fournissant toutes les fonctionnalités standard "CRUD" (Créer, Lire, Mettre à jour, Supprimer) tout en maintenant une base de code facile à lire et à modifier. En utilisant le stockage de fichiers persistant, il imite le comportement des logiciels du monde réel.

### Améliorations Futures
Bien que fonctionnel, le système peut être étendu à l'avenir :
*   **Mémoire Dynamique** : Remplacer les tableaux fixes par `std::vector` pour permettre un nombre illimité d'étudiants.
*   **Recherche Avancée** : Implémenter des filtres pour la Filière ou la plage de Moyenne.
*   **Tri** : Capacité de trier la liste par ordre alphabétique ou par Moyenne la plus élevée.
*   **Authentification** : Ajouter un système de connexion pour la sécurité de l'administrateur.

### Dernières Pensées
Le Système de Gestion des Étudiants Simple est un point de départ robuste pour tout développeur cherchant à maîtriser le C++. Il comble le fossé entre les connaissances théoriques et la création d'applications pratiques.
