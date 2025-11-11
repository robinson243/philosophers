# 🧠 PLAN HYPER DÉTAILLÉ — PROJET PHILOSOPHERS (École 42)

---

## 🧩 1. STRUCTURES ET HEADER

### 🎯 Objectif
Définir toutes les données nécessaires à la simulation.

### Contenu
- **t_philo**
  - `id`
  - `pthread_t philo_id`
  - `left_fork`, `right_fork`
  - `last_meal`
  - `struct s_table *table`

- **t_table**
  - `len_philo`
  - `time_to_eat`, `time_to_sleep`, `time_to_die`
  - `start_sim`
  - `someone_died`
  - `pthread_mutex_t *forks`
  - `pthread_mutex_t print_lock`
  - `pthread_mutex_t death_lock`
  - `t_philo *philos`

---

## ⚙️ 2. PARSING ET INITIALISATION

### 🎯 Objectif
Lire et valider les arguments, puis allouer et initialiser les structures.

### Étapes
1. **Parsing**
   - Vérifier le nombre d’arguments.
   - Vérifier que tous les arguments sont numériques et positifs.
   - Convertir les arguments avec `ft_atoi`.

2. **Initialisation de la table (`init_table`)**
   - Allouer les `pthread_mutex_t` des fourchettes.
   - Initialiser tous les mutex.
   - Mettre `someone_died = 0`.
   - Enregistrer les durées (`time_to_*`).

3. **Initialisation des philosophes (`init_philos`)**
   - Allouer le tableau `philos` dans la table.
   - Attribuer à chaque philosophe :
     - un `id`
     - ses `left_fork` et `right_fork`
     - un pointeur vers `table`
     - `last_meal = start_sim`
   - Convention : `left_fork = id`, `right_fork = (id + 1) % len_philo`.

---

## 🚀 3. DÉMARRAGE DE LA SIMULATION

### 🎯 Objectif
Créer les threads des philosophes et démarrer le timer global.

### Étapes
1. Enregistrer `start_sim = get_time()`.
2. Créer un thread pour chaque philosophe :
   - Fonction : `routine(void *arg)`.
   - Argument : pointeur vers `t_philo`.
3. Lancer un thread de **surveillance (monitor)** qui observe la mort des philosophes.

---

## 🍽️ 4. ROUTINE D’UN PHILOSOPHE

### 🎯 Objectif
Définir le comportement cyclique d’un philosophe.

### Boucle principale
1. **Prendre les fourchettes**
   - Lock gauche et droite.
   - Afficher “has taken a fork” deux fois.
   - Ordre stratégique (pair → left puis right, impair → right puis left).

2. **Manger**
   - Afficher “is eating”.
   - Mettre à jour `last_meal`.
   - Dormir `time_to_eat`.

3. **Relâcher les fourchettes**
   - Unlock des deux mutex.

4. **Dormir**
   - Afficher “is sleeping”.
   - Dormir `time_to_sleep`.

5. **Penser**
   - Afficher “is thinking”.

➡️ Boucle infinie **jusqu’à `someone_died == 1`**.

---

## 👁️ 5. THREAD DE SURVEILLANCE (MONITOR)

### 🎯 Objectif
Vérifier si un philosophe est mort.

### Étapes
1. Tant que `someone_died == 0` :
   - Parcourir tous les philosophes.
   - Calculer `current_time - last_meal`.
2. Si > `time_to_die` :
   - Lock `death_lock`
   - `someone_died = 1`
   - Afficher “<time> <id> died”
   - Unlock `death_lock`
   - Fin de la simulation.

---

## 🔒 6. SYNCHRONISATION ET AFFICHAGE

### 🎯 Objectif
Empêcher les messages mélangés et gérer les arrêts.

### Règles
- Tous les `printf` passent sous `print_lock`.
- Avant d’afficher, vérifier `if (someone_died) return;`.
- Après un décès, plus aucun affichage ne doit apparaître.

---

## 🧹 7. ARRÊT DE LA SIMULATION

### 🎯 Objectif
Nettoyer proprement les threads et la mémoire.

### Étapes
1. `pthread_join` sur tous les philosophes.
2. `pthread_join` du monitor.
3. Détruire tous les mutex (`pthread_mutex_destroy`).
4. Libérer :
   - `forks`
   - `philos`
   - `table`

---

## 🧰 8. FONCTIONS UTILITAIRES

### 🎯 Objectif
Regrouper les outils indépendants de la logique principale.

### Fonctions typiques
- `get_time()` → retourne le temps en millisecondes.
- `precise_usleep(ms)` → dort avec précision.
- `print_action(philo, action)` → affiche proprement.
- Fonctions parsing : `ft_atoi`, `ft_numeric`, `ft_isdigit`, etc.

---

## 🧪 9. TESTS ET VALIDATION

### 🎯 Objectif
S’assurer que le programme respecte toutes les contraintes.

### Cas à tester
- 1 philosophe → doit mourir après `time_to_die`.
- 2 philosophes → alternance correcte.
- 5+ philosophes → pas de deadlock.
- Valgrind → aucune fuite mémoire.
- Helgrind / DRD → aucun data race.

---

## ⭐ 10. BONUS (facultatif)

### Idées
- Ajouter `nb_must_eat` pour arrêter quand tous ont assez mangé.
- Colorer les messages d’action.
- Passer à `philo_bonus` avec processus + sémaphores.

---

## 📁 Structure conseillée du projet
