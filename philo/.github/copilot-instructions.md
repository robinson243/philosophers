# Copilot Instructions for 42 Philosophers Project

## Vue d'ensemble
Ce projet implémente le problème des philosophes avec threads et mutex en C, selon les standards de l'école 42. Il est structuré autour de la synchronisation des accès aux fourchettes (ressources partagées) et la gestion de la vie des philosophes (threads).

## Architecture principale
- **main.c** : Point d'entrée, initialise les structures, lance les threads et le moniteur.
- **philo.h** : Définitions des structures (`t_args`, `t_philo`) et prototypes de fonctions.
- **philosophers.c** : Logique de vie d'un philosophe (penser, prendre les fourchettes, manger, dormir).
- **monitors.c** : Thread de surveillance, détecte la mort ou la fin de la simulation.
- **mutex.c** : Initialisation et destruction des mutex (fourchettes, print).
- **parse.c** : Analyse des arguments de la ligne de commande.
- **utils.c / utils2.c** : Fonctions utilitaires (temps, affichage, conversions).

## Flux de données et synchronisation
- Les philosophes sont des threads (`pthread_t`) stockés dans `t_philo`.
- Les fourchettes sont des mutex dans un tableau dynamique.
- Un mutex `print_mutex` protège l'affichage pour éviter les collisions de sortie.
- La structure `t_args` centralise la configuration et l'état global.
- Le thread moniteur surveille la faim et la mort des philosophes.

## Build & Exécution
- **Compilation** : Utiliser `make` (voir `Makefile`).
    - Commande principale : `make`
    - Nettoyage : `make clean` / `make fclean`
    - Rebuild : `make re`
- **Exécution** : `./philo <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> [must_eat]`
    - Exemple : `./philo 5 800 200 200 7`

## Conventions spécifiques
- Affichage formaté : chaque action affiche le timestamp relatif au début de la simulation.
- Les accès à l'état global (`finished`, `eat_count`, etc.) sont toujours protégés par mutex.
- Les threads sont joints proprement à la fin de la simulation.
- Les erreurs critiques (échec de création de thread, malloc, etc.) sont affichées sur stderr.
- Les fourchettes sont prises dans un ordre déterminé pour éviter le deadlock (voir `determine_fork_order`).

## Points d'intégration et dépendances
- Utilisation exclusive de la bibliothèque standard C et POSIX (`pthread`, `unistd`, etc.).
- Pas de dépendances externes ou de frameworks.
- Aucun test automatisé ou script de vérification inclus par défaut.

## Exemples de patterns
- **Protection d'affichage** :
  ```c
  pthread_mutex_lock(&args->print_mutex);
  // ... printf ...
  pthread_mutex_unlock(&args->print_mutex);
  ```
- **Vérification de la mort** :
  ```c
  if (current_time - last_meal > time_to_die) { /* ... */ }
  ```
- **Initialisation des philosophes** :
  ```c
  init_philosophers(&args, &philos);
  ```

## Fichiers clés à lire pour comprendre
- `main.c`, `philo.h`, `philosophers.c`, `monitors.c`, `mutex.c`

---

**Mettez à jour ce fichier si des conventions changent ou si des tests/scripts sont ajoutés.**
