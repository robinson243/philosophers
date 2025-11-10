# 🧩 PLAN HYPER DÉTAILLÉ — PHILOSOPHERS

**Arguments du programme :**
```
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>
```

---

## 🗂️ ÉTAPE 0 — Préparation & Structure du projet

**Dossier racine :** `philo/`

**Fichiers à créer :**
- `philo.h` → structs + prototypes de toutes les fonctions
- `main.c` → parsing des arguments, allocation initiale, lancement de la simulation
- `init.c` → initialisation des structures, allocation mémoire, initialisation des mutexes
- `threads.c` → création des threads philosophes et du thread moniteur, joins
- `routine.c` → boucle principale de chaque philosophe
- `monitor.c` → thread de surveillance (détection de mort)
- `utils.c` → fonctions utilitaires (temps, affichage thread-safe, sleep)
- `Makefile` → compilation avec `-lpthread`

**Structures finales dans `philo.h` :**

```c
typedef struct s_philo
{
    pthread_t       philo_id;
    int             id;
    int             left_fork;
    int             right_fork;
    long long       last_meal;
    int             alive;
    t_table         *table;
}                   t_philo;

typedef struct s_table
{
    int             len_philo;
    long long       start_sim;
    int             time_to_eat;
    int             time_to_sleep;
    int             time_to_die;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    t_philo         *philos;
    int             should_stop;
}                   t_table;
```

---

## ⚙️ ÉTAPE 1 — Parsing et validation des arguments

**Fichier : `main.c`**

**Objectif :** Valider que le programme a été lancé avec exactement 4 arguments et que tous sont des entiers positifs.

**Détail des vérifications :**

1. Vérifier que `argc == 5` (4 arguments + nom du programme)
2. Pour chaque argument :
   - Vérifier que c'est une chaîne de caractères valide
   - Vérifier que ce n'est que des chiffres (pas de caractères, pas de signe moins)
   - Convertir en entier long (pour éviter les débordements)
   - Vérifier que la valeur convertie est positive (> 0)
   - Si une vérification échoue : afficher un message d'erreur et quitter
3. Une fois tout validé, passer les valeurs à la fonction d'initialisation

**En cas d'erreur :** Afficher un message clair et retourner 1 (exit failure)

**Résultat :** Les 4 valeurs sont validées et prêtes pour l'initialisation

---

## 🏗️ ÉTAPE 2 — Allocation et initialisation globales

**Fichier : `init.c`**

**Objectif :** Allouer toute la mémoire nécessaire et initialiser les structures de base.

**Étapes détaillées :**

### Phase 1 : Allocation de la structure principale

- Allouer une structure `t_table` (ou la déclarer statiquement si tu préfères)
- Stocker les 4 valeurs d'arguments (nombre de philos, time_to_die, time_to_eat, time_to_sleep)

### Phase 2 : Allocation des tableaux

- Allouer un tableau de `len_philo` structures `t_philo`
- Allouer un tableau de `len_philo` mutexes `pthread_mutex_t` (les fourchettes)
- Stocker les adresses dans `t_table->philos` et `t_table->forks`

### Phase 3 : Initialisation des mutexes

- Boucler sur chaque fourchette (de 0 à len_philo - 1)
- Pour chaque fourchette : appeler `pthread_mutex_init(&forks[i], NULL)`
- Initialiser `print_lock` avec `pthread_mutex_init`
- (Optionnel) Initialiser un `stop_lock` pour protéger le flag `should_stop`
- Vérifier que chaque `pthread_mutex_init` retourne 0 (succès)

### Phase 4 : Initialisation des variables de contrôle

- Mettre `should_stop = 0` (la simulation n'est pas stoppée)
- **NE PAS ENCORE FIXER `start_sim`** (ce sera fait juste avant de lancer les threads)

**En cas d'erreur :** Si une allocation ou un `pthread_mutex_init` échoue, nettoyer ce qui a été alloué et quitter.

**Résultat :** La table est prête, toute la mémoire est allouée, tous les mutexes existent et sont initialisés

---

## 🧍‍♂️ ÉTAPE 3 — Initialisation des philosophes

**Fichier : `init.c`** (suite ou fonction séparée)

**Objectif :** Remplir le tableau de philosophes avec ses données personnelles.

**Pour chaque philosophe (boucle de 0 à len_philo - 1) :**

1. **ID personnel :** `philo[i].id = i`
   - C'est un index numérique simple (0, 1, 2, ...)
   - Utilisé pour l'affichage et la logique

2. **Thread ID :** `philo[i].philo_id = 0`
   - Sera rempli plus tard par `pthread_create`
   - Pour l'instant, laisser à 0

3. **Fourchette gauche :** `philo[i].left_fork = i`
   - Le philosophe i prend la fourchette à l'index i

4. **Fourchette droite :** `philo[i].right_fork = (i + 1) % len_philo`
   - Crée une table circulaire
   - Le dernier philosophe (len_philo - 1) a pour droite la fourchette 0
   - Le philosophe 0 a pour droite la fourchette 1

5. **État vivant :** `philo[i].alive = 1`
   - Le philosophe commence vivant

6. **Dernier repas :** `philo[i].last_meal = 0`
   - Sera mis à jour au premier repas (ou initialiser à start_sim au démarrage)

7. **Pointeur vers la table :** `philo[i].table = data`
   - Permet à chaque philosophe d'accéder aux timings et aux mutexes

**Résultat :** Tous les philosophes sont initialisés avec leur configuration propre

---

## ⏰ ÉTAPE 4 — Fixation du temps de démarrage

**Fichier : `main.c` (juste avant de créer les threads)**

**Objectif :** Enregistrer le moment exact où la simulation commence.

**Détail :**

- Appeler une fonction `get_current_time_ms()` pour récupérer le temps actuel en millisecondes
- Stocker cette valeur dans `data->start_sim`
- À partir de ce moment, tous les calculs de timing sont relatifs à cette valeur
- **Cela doit être fait immédiatement avant de créer les premiers threads**

**Raison :** Si tu fixes `start_sim` trop tôt, il y aura du temps mort entre l'initialisation et le vrai démarrage.

**Résultat :** Le point de référence temporal de la simulation est défini

---

## 🔁 ÉTAPE 5 — Création des threads des philosophes

**Fichier : `threads.c`**

**Objectif :** Lancer chaque philosophe dans sa routine (chaque philosophe devient un thread).

**Étapes :**

1. **Boucle sur tous les philosophes :** De 0 à len_philo - 1

2. **Pour chaque philosophe :**
   - Appeler `pthread_create` avec ces paramètres :
     - Adresse où stocker le thread ID : `&data->philos[i].philo_id`
     - Attributs : `NULL` (utiliser les defaults)
     - Fonction à exécuter : `philosopher_routine`
     - Argument à passer : adresse du philosophe `&data->philos[i]`
   - Vérifier que `pthread_create` retourne 0
   - Si erreur : nettoyer et quitter

3. **Le thread démarre immédiatement** et exécute la fonction `philosopher_routine`

**Important :**
- Tous les threads sont lancés **après** que `start_sim` soit défini
- Les threads tournent en parallèle (pas d'ordre garantie)
- Ils accèdent tous à la même `t_table` (données partagées)

**Résultat :** len_philo threads sont créés et exécutent `philosopher_routine`

---

## 👀 ÉTAPE 6 — Création du thread moniteur

**Fichier : `threads.c`** (après création des philosophes)

**Objectif :** Lancer un thread séparé qui surveille l'état de la simulation.

**Étapes :**

1. Après que tous les threads philosophes soient créés

2. Appeler `pthread_create` pour le thread moniteur :
   - Adresse où stocker le thread ID : `&monitor_thread_id`
   - Attributs : `NULL`
   - Fonction à exécuter : `monitor_routine`
   - Argument : pointeur vers `data` (pour accéder à tous les philosophes)

3. Vérifier que `pthread_create` retourne 0

**Rôle du moniteur :**
- Boucle infinie qui vérifie l'état de chaque philosophe
- Détecte si un philosophe est mort (n'a pas mangé assez longtemps)
- Signale l'arrêt de la simulation si nécessaire

**Résultat :** Un thread moniteur supplémentaire tourne en parallèle

---

## 🍽️ ÉTAPE 7 — Routine du philosophe

**Fichier : `routine.c`**

**Objectif :** Implémenter le cycle infini de chaque philosophe.

**Fonction :** `void *philosopher_routine(void *arg)`

**Paramètre reçu :** Pointeur vers un `t_philo` (le philosophe courant)

### Boucle principale

La routine boucle infiniment tant que :
- La simulation n'est pas arrêtée (`should_stop == 0`)
- Le philosophe est vivant (`alive == 1`)

### Étape 1 : Prendre les fourchettes

**Prendre la fourchette gauche :**
- Appeler `pthread_mutex_lock(&table->forks[philo->left_fork])`
- Ce call bloque jusqu'à ce que le mutex soit disponible
- Afficher un message : "a pris une fourchette" (via fonction d'affichage thread-safe)

**Prendre la fourchette droite :**
- Appeler `pthread_mutex_lock(&table->forks[philo->right_fork])`
- Afficher à nouveau : "a pris une fourchette"

**Important :** L'ordre est crucial. Tous les philosophes doivent prendre gauche puis droite pour éviter les deadlocks.

### Étape 2 : Manger

- Mettre à jour le timestamp du dernier repas : `philo->last_meal = get_current_time_ms()`
- Afficher : "est en train de manger"
- Dormir pendant `table->time_to_eat` millisecondes (via `ft_usleep`)
- À la fin du repas, le philosophe a mangé (incrémenter un compteur si nécessaire)

### Étape 3 : Poser les fourchettes

**Poser la fourchette droite :**
- Appeler `pthread_mutex_unlock(&table->forks[philo->right_fork])`
- La fourchette devient disponible pour les autres

**Poser la fourchette gauche :**
- Appeler `pthread_mutex_unlock(&table->forks[philo->left_fork])`
- La fourchette devient disponible pour les autres

**Important :** Débloquer dans l'ordre inverse du verrouillage (droite puis gauche).

### Étape 4 : Dormir

- Afficher : "dort"
- Dormir pendant `table->time_to_sleep` millisecondes (via `ft_usleep`)

### Étape 5 : Penser

- Afficher : "pense"
- Pas de sleep (ou très court selon le sujet)
- Retour au début de la boucle

### Condition de sortie

La boucle s'arrête quand :
- `should_stop == 1` (la simulation a été arrêtée par le moniteur)
- Ou `alive == 0` (le philosophe est mort)

**Résultat :** Chaque philosophe mange, dort, pense en boucle sans deadlock

---

## 💀 ÉTAPE 8 — Routine du moniteur

**Fichier : `monitor.c`**

**Objectif :** Surveiller les philosophes et arrêter la simulation si un meurt.

**Fonction :** `void *monitor_routine(void *arg)`

**Paramètre reçu :** Pointeur vers `t_table` (accès à tous les philosophes)

### Boucle de surveillance

Le moniteur boucle infiniment et effectue ces vérifications :

**Pour chaque philosophe :**

1. Récupérer le temps actuel : `current_time = get_current_time_ms()`

2. Calculer le temps depuis le dernier repas : `elapsed = current_time - philo->last_meal`

3. Vérifier si le philosophe est mort :
   - Si `elapsed > table->time_to_die`
   - Alors : le philosophe a faim depuis trop longtemps, il meurt

4. Si un philosophe est mort :
   - Afficher : "est mort" (ou similaire selon le sujet)
   - Mettre `philo->alive = 0`
   - Mettre `should_stop = 1` (arrêter la simulation)
   - Quitter la boucle et terminer le thread moniteur

### Fréquence de vérification

- Après chaque itération, dormir très peu de temps (ex : 10 ms)
- Cela permet de laisser les autres threads travailler tout en vérifiant régulièrement

### Condition d'arrêt du moniteur

- Quitter boucle et thread si `should_stop == 1`
- Ou si un philosophe est détecté mort

**Résultat :** La mort est détectée, la simulation s'arrête proprement

---

## 🔄 ÉTAPE 9 — Arrêt et synchronisation des threads

**Fichier : `threads.c` (après création des threads)**

**Objectif :** Attendre que tous les threads se terminent proprement.

### Joins des philosophes

- Boucler sur tous les philosophes (de 0 à len_philo - 1)
- Pour chaque philosophe : appeler `pthread_join(philo[i].philo_id, NULL)`
- Chaque `pthread_join` bloque jusqu'à ce que le thread correspondant se termine
- Vérifier que `pthread_join` retourne 0

### Join du moniteur

- Appeler `pthread_join(monitor_thread_id, NULL)` pour attendre la fin du moniteur

### Résultat

- Tous les threads ont terminé leur exécution
- On peut maintenant nettoyer sans risque de race conditions

---

## 🧹 ÉTAPE 10 — Nettoyage et libération mémoire

**Fichier : `init.c` ou `main.c`** (dans une fonction `cleanup`)

**Objectif :** Libérer proprement toutes les ressources allouées.

### Destruction des mutexes

**Boucler sur tous les mutexes fourchettes :**
- De 0 à len_philo - 1
- Pour chaque fourchette : `pthread_mutex_destroy(&forks[i])`
- Vérifier que chaque `pthread_mutex_destroy` retourne 0

**Détruire les autres mutexes :**
- `pthread_mutex_destroy(&print_lock)`
- (Optionnel) `pthread_mutex_destroy(&stop_lock)`

### Libération de la mémoire

- `free(table->philos)` (tableau de philosophes)
- `free(table->forks)` (tableau de mutexes)
- (Optionnel) `free(table)` si la table a été allouée dynamiquement

### Retour

- Retourner 0 (succès) ou 1 (erreur)

**Résultat :** Zéro leak mémoire, tous les mutexes correctement détruits

---

## 🕒 ÉTAPE 11 — Fonctions utilitaires

**Fichier : `utils.c`**

### Fonction : Récupérer l'heure actuelle

**Nom :** `long long get_current_time_ms(void)`

**Objectif :** Retourner le temps actuel en millisecondes

**Détail :**
- Utiliser `gettimeofday()` ou `clock_gettime()` (selon préférence)
- Convertir le résultat en millisecondes
- Retourner un `long long` (assez grand pour contenir de grands nombres)

### Fonction : Dormir avec précision

**Nom :** `void ft_usleep(long ms)`

**Objectif :** Dormir exactement un nombre donné de millisecondes (plus précis que `usleep`)

**Détail :**
- Enregistrer le temps actuel
- Boucler jusqu'à ce que le temps écoulé égale ou dépasse `ms`
- À l'intérieur de la boucle : appeler `usleep(100)` ou `usleep(500)` pour ne pas spammer
- Quand le temps atteint `ms`, quitter la boucle

### Fonction : Affichage thread-safe

**Nom :** `void print_status(t_table *table, t_philo *philo, char *msg)`

**Objectif :** Afficher un message formaté sans que deux threads n'écrivent en même temps

**Détail :**
- Verrouiller `print_lock` : `pthread_mutex_lock(&table->print_lock)`
- Récupérer le temps écoulé depuis le début : `elapsed = get_current_time_ms() - table->start_sim`
- Afficher un message formaté (exemple) : `[elapsed_ms] Philosopher id msg`
- Déverrouiller `print_lock` : `pthread_mutex_unlock(&table->print_lock)`

### Fonction : Vérifier l'arrêt

**Nom :** `int is_simulation_stopped(t_table *table)`

**Objectif :** Lire de manière thread-safe le flag `should_stop`

**Détail :**
- (Optionnel) Verrouiller un mutex si tu veux être strict
- Lire la valeur de `should_stop`
- (Optionnel) Déverrouiller
- Retourner la valeur

**Résultat :** Ensemble de fonctions utilitaires centralisées et réutilisables

---

## 🧪 ÉTAPE 12 — Tests et validation

**Fichier : Terminal**

### Test 1 : Un seul philosophe

```
./philo 1 800 200 200
```

**Comportement attendu :**
- Le philosophe prend la fourchette gauche
- Essaie de prendre la fourchette droite (mais elle n'existe pas / est la même fourchette)
- Après ~800 ms : affiche "est mort"
- Le programme se termine

### Test 2 : Deux philosophes

```
./philo 2 610 200 200
```

**Comportement attendu :**
- Les deux philosophes se lancent
- Ils prennent chacun une fourchette
- Impossible pour l'un d'eux de manger
- Après ~610 ms : un philosophe meurt
- Le programme se termine

### Test 3 : Quatre philosophes (normal)

```
./philo 4 410 200 200
```

**Comportement attendu :**
- 4 philosophes mangent en ordre raisonnable
- Aucun deadlock
- Les affichages sont ordonnés (pas de charabia)
- La simulation se termine sans qu'aucun ne meurt (normalement)

### Test 4 : Valgrind (vérifier les fuites mémoire)

```
valgrind --leak-check=full --show-leak-kinds=all ./philo 4 500 100 100
```

**Comportement attendu :**
- Zéro leak détecté
- Zéro erreur de mémoire
- Tous les allocations/libérations sont appairées

### Test 5 : Helgrind (vérifier les race conditions)

```
valgrind --tool=helgrind ./philo 4 500 100 100
```

**Comportement attendu :**
- Pas de data race détecté
- Ou data races acceptables selon le design

**Résultat :** Le programme passe tous les tests

---

## ⚠️ Points critiques à respecter

### Deadlock

**Problème :** Si deux philosophes voisins verrouillent dans un ordre différent, ils peuvent se bloquer mutuellement.

**Solution :** Tous les philosophes doivent toujours verrouiller dans le même ordre (gauche puis droite).

### Affichages

**Problème :** Si deux threads affichent en même temps, les caractères s'entrelacent et le message devient illisible.

**Solution :** Utiliser `print_lock` pour synchroniser tous les affichages.

### Timing

**Problème :** `usleep()` standard peut être imprécis. Si on dort trop peu, la simulation va trop vite. Si on dort trop longtemps, on rate les événements.

**Solution :** Implémenter `ft_usleep` pour une précision milliseconde.

### Dernier repas

**Problème :** Le moniteur lit `last_meal` pendant que le philosophe l'écrit. Risque de lire une valeur corrompue.

**Solution :** Accepter le risque (une milliseconde de décalage c'est négligeable) ou protéger avec un mutex.

### Arrêt propre

**Problème :** Si un philosophe dort (`ft_usleep`), il ne peut pas immédiatement arrêter quand `should_stop` devient 1.

**Solution :** Vérifier `should_stop` dans les bonnes conditions (avant de manger, avant de dormir).

---

## 📋 Résumé des fichiers et responsabilités

| Fichier | Responsabilités |
|---------|-----------------|
| `philo.h` | Définir les structs, déclarer les prototypes |
| `main.c` | Parsing arguments, orchestration générale, appel du nettoyage |
| `init.c` | Allocation mémoire, initialisation structures, init mutexes |
| `threads.c` | Création threads, joins, synchronisation |
| `routine.c` | Boucle philosophe (manger, dormir, penser) |
| `monitor.c` | Thread de surveillance, détection de mort |
| `utils.c` | Temps, affichage, sleep, vérifications |
| `Makefile` | Compilation avec `-lpthread` |

---

## 📊 Flux global d'exécution

```
1. main() : Parsing arguments
            ↓
2. Allocation et init (init.c)
            ↓
3. Fixer start_sim
            ↓
4. Créer threads philosophes (threads.c)
            ↓
5. Créer thread moniteur
            ↓
6. Boucle parallèle :
   - Chaque philosophe exécute routine_philosophe (mange/dort/pense)
   - Moniteur vérifie les morts
            ↓
7. Un philosophe meurt → should_stop = 1
            ↓
8. Tous les threads sortent de leur boucle
            ↓
9. Joins de tous les threads (routine.c)
            ↓
10. Nettoyage (init.c/main.c)
            ↓
11. Retour 0
```
