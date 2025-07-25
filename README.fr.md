# PROJET PHILOSOPHERS POUR 42
Par chdonnat (Christophe Donnat de 42 Perpignan, France)

[🇬🇧 Go to English version](README.md)

## BUT DU PROJET :

Le ou les programmes doivent prendre les arguments suivants :
- number_of_philosophers,
qui est le nombre de philosophes et de fourchettes
- time_to_die en millisecondes,
qui est le temps qu'un philosophe peut passer sans manger depuis son dernier repas ou le début de la simulation avant de mourir
- time_to_eat en millisecondes,
qui est le temps que met un philosophe pour manger, pendant lequel il doit tenir deux fourchettes
- time_to_sleep en millisecondes,
qui est le temps qu'un philosophe passe à dormir
- number_of_times_each_philosopher_must_eat,
qui est optionnel et spécifie que
si tous les philosophes ont mangé ce nombre de fois, la simulation s'arrête
Si cet argument n'est pas fourni, la simulation s'arrête lorsqu'un philosophe meurt.

Chaque philosophe a un numéro de 1 à number_of_philosophers. Le philosophe numéro 1 est assis à côté du philosophe numéro number_of_philosophers.

Les journaux du programme doivent afficher tout changement d'état d'un philosophe dans le format suivant : timestamp_in_ms X has taken a fork, timestamp_in_ms X is eating, timestamp_in_ms X is sleeping, timestamp_in_ms X is thinking, ou timestamp_in_ms X died. Remplacez timestamp_in_ms par l'horodatage actuel en millisecondes et X par le numéro du philosophe. Un message d'état ne doit pas en chevaucher un autre, et un message de décès doit apparaître au plus tard 10 millisecondes après le décès réel du philosophe.

Les philosophes doivent éviter de mourir. Le philosophe numéro N est assis entre le philosophe numéro N - 1 et le philosophe numéro N + 1.

Les règles spécifiques pour la partie obligatoire incluent que chaque philosophe doit être un thread. Il y a une fourchette entre chaque paire de philosophes, ce qui signifie que s'il y a plusieurs philosophes, chacun a une fourchette à sa gauche et à sa droite. S'il n'y a qu'un seul philosophe, il n'y a qu'une seule fourchette sur la table. L'état des fourchettes doit être protégé par un mutex pour éviter la duplication.

**Notez que la libft est interdite !**

**Notez également que philo et philo_bonus ont chacun leur propre makefile dans leur propre répertoire !**

### PARTIE BONUS :

Le programme de la partie bonus prend les mêmes arguments que le programme obligatoire
et doit respecter les exigences du chapitre des règles globales.
Dans la partie bonus, toutes les fourchettes sont placées au milieu de la table.
Elles n'ont pas d'états individuels en mémoire, et le nombre de fourchettes disponibles est représenté par un sémaphore.
Chaque philosophe doit être implémenté comme un processus, mais le processus principal ne doit pas agir en tant que philosophe.

### À PROPOS DE MON PROJET :

Pour ce projet, j'ai choisi de réutiliser les fonctions de liste doublement chaînée circulaire que j'avais créées pour le projet push_swap, mais j'en ai fait des fonctions génériques. Ces fonctions utilisent une structure qui peut être appliquée à n'importe quel projet, ne contenant que :
- un pointeur vers next
- un pointeur vers previous
- un pointeur vers void *data, lui permettant d'accepter n'importe quel type de données
Bien sûr, ce n'est pas le choix le plus simple (un tableau de structures serait suffisant), mais je voulais profiter de ce projet pour affiner mes fonctions de liste doublement chaînée circulaire, que je prévois d'intégrer directement dans ma libft plus tard.

## QUELQUES COMMANDES QUE VOUS POUVEZ UTILISER :

compiler le programme et supprimer les fichiers .o :
(vous devez être dans le répertoire `philo/` pour la partie obligatoire ou `philo_bonus` pour la partie bonus)

	make && make clean

exécuter le programme (vous devez passer 4 ou 5 arguments)

	./philo <number_of_philosophers> <time_to_die in milliseconds> <time_to_eat in milliseconds> <time_to_sleep in milliseconds> <optional: number_of_times_each_philosopher_must_eat>

 par exemple : exécuter le programme avec 6 philosophes, 500 ms pour mourir, 200 ms pour manger, 200 ms pour dormir, et le programme s'arrête lorsque chaque philosophe a mangé 5 fois

	./philo 6 500 200 200 5

## ARCHITECTURE :

- répertoire philo/ avec les fichiers pour la partie obligatoire
	- répertoire src/ pour les fichiers principaux du projet
	- répertoire utils/ pour les fichiers secondaires
	- répertoire include/ pour les en-têtes
	- Makefile
- répertoire philo_bonus/ avec les fichiers pour la partie bonus
	- répertoire src/ pour les fichiers principaux du projet
	- répertoire utils/ pour les fichiers secondaires
	- répertoire include/ pour les en-têtes
	- Makefile
- readme.md pour une explication rapide et les commandes principales du projet

## DOCUMENTATION :

### thread
Un thread est une seule unité d'exécution au sein d'un processus.
Il permet à un programme d'effectuer plusieurs tâches simultanément, en partageant le même espace mémoire et les mêmes ressources (telles que les descripteurs de fichiers) que le processus parent.
Chaque thread a son propre contexte d'exécution, comprenant un compteur de programme, une pile et des variables locales, mais il partage les variables globales avec les autres threads du même processus.
Les threads sont couramment utilisés pour améliorer les performances des applications en effectuant des opérations telles que les E/S, les calculs ou l'attente d'événements en parallèle, sans bloquer le flux d'exécution principal du programme.
Plusieurs threads au sein du même processus sont souvent appelés multithreading, ce qui peut conduire à une utilisation plus efficace des ressources système, en particulier sur les processeurs multi-cœurs.


Il est essentiel d'attendre la fin de chaque thread avant de terminer un programme pour garantir une gestion correcte des ressources et la stabilité du programme.
Ne pas le faire peut entraîner des fuites de ressources, des opérations incomplètes ou des données corrompues si un thread est interrompu prématurément lors de l'accès à des ressources partagées.
Les fonctions de synchronisation comme pthread_join() dans les threads POSIX permettent au thread principal d'attendre que des threads spécifiques terminent leur exécution, garantissant que toutes les tâches nécessaires sont terminées avant la fin du programme.
Cette pratique empêche également la création de threads orphelins, qui continuent de s'exécuter en arrière-plan et de consommer inutilement des ressources système.
La gestion correcte du cycle de vie des threads garantit un comportement robuste et prévisible du programme.

---

### timestamp
Un timestamp (horodatage) est une séquence de caractères représentant la date et l'heure auxquelles un événement spécifique s'est produit. Il est généralement formaté comme une combinaison d'année, de mois, de jour, d'heure, de minute et de seconde, souvent dans un format standard comme le temps UNIX (le nombre de secondes depuis le 1er janvier 1970, UTC). Les timestamps sont largement utilisés en informatique pour suivre les événements, synchroniser les processus et gérer les opérations sensibles au temps telles que la journalisation, les modifications de fichiers et les entrées de base de données.

---

### gettimeofday()
> #include <sys/time.h>

	int gettimeofday(struct timeval *tv, struct timezone *tz);

La fonction gettimeofday récupère l'heure actuelle depuis l'époque UNIX (1er janvier 1970, 00:00:00 UTC) avec une précision à la microseconde.

Arguments :
- un pointeur vers une struct timeval, où les secondes (tv_sec) et les microsecondes (tv_usec) sont stockées
- un paramètre optionnel struct timezone, qui est généralement défini sur NULL car il est obsolète

La fonction renvoie 0 en cas de succès ou -1 en cas d'échec.
Elle est couramment utilisée pour mesurer le temps écoulé ou ajouter des horodatages précis aux journaux.
Bien qu'elle offre une précision à la microseconde, la précision réelle dépend du système.
Pour une précision plus élevée ou une synchronisation monotone, clock_gettime est une meilleure alternative.

### structure timeval
La structure timeval est utilisée pour représenter un point spécifique dans le temps avec une précision allant jusqu'à la microseconde.
Elle contient deux champs :
- tv_sec, qui stocke le nombre de secondes depuis l'époque UNIX (1er janvier 1970)
- tv_usec, qui stocke le temps restant en microsecondes (allant de 0 à 999999)

Cette structure est couramment utilisée avec des fonctions comme gettimeofday pour récupérer l'heure actuelle ou calculer des intervalles de temps.
Elle offre un moyen simple de représenter des horodatages à haute résolution,
mais pour certaines applications, des structures ou des fonctions alternatives peuvent offrir plus de fonctionnalités ou une plus grande précision.

---

### pthread_create()
> #include <pthread.h>

	int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

pthread_create() est utilisée pour créer un nouveau thread dans un programme.
Elle permet l'exécution d'une fonction simultanément avec le thread principal.
La fonction prend quatre arguments :
- un pointeur vers une variable pthread_t, où l'ID du thread sera stocké
- un pointeur optionnel vers une structure pthread_attr_t pour spécifier les attributs du thread, ou NULL pour les attributs par défaut
- un pointeur vers la fonction que le thread exécutera
- un pointeur vers l'argument qui sera passé à la fonction.

La fonction renvoie 0 en cas de succès et un code d'erreur positif en cas d'échec.

### structure pthread_attr_t
La structure pthread_attr_t est utilisée pour spécifier les attributs d'un thread lors de sa création avec pthread_create().
Elle vous permet de personnaliser divers aspects du comportement du thread, tels que
sa taille de pile, sa politique d'ordonnancement et s'il est joignable ou détaché.
Par défaut, si pthread_attr_t est défini sur NULL dans pthread_create, le thread sera créé avec les attributs par défaut du système.
Les attributs qui peuvent être définis à l'aide de cette structure incluent :
- Taille de la pile : La quantité de mémoire allouée pour la pile du thread
- Politique d'ordonnancement : Définit comment le thread est ordonnancé par le système (par exemple, SCHED_FIFO, SCHED_RR ou SCHED_OTHER)
- Priorité d'ordonnancement : Une valeur de priorité qui peut affecter l'ordonnancement du thread
- Détaché ou joignable : Si le thread est joignable (peut être attendu par d'autres threads) ou détaché (les ressources sont automatiquement libérées à sa fin)
- Portée du thread : Détermine si l'exécution du thread est liée à un processeur (pour les systèmes avec affinité processeur)

Pour définir ces attributs, la structure pthread_attr_t doit être initialisée à l'aide de pthread_attr_init() et peut être modifiée à l'aide d'autres fonctions comme pthread_attr_setstacksize(), pthread_attr_setschedpolicy(), etc. Une fois le thread créé, les attributs ne sont plus utilisés, et leur modification après la création n'affecte pas le thread déjà créé.

---

### pthread_detach()
> #include <pthread.h>

	int pthread_detach(pthread_t thread);

pthread_detach() est utilisée pour détacher un thread, ce qui signifie qu'il s'exécutera de manière indépendante et que ses ressources seront automatiquement libérées une fois son exécution terminée.
Cette fonction évite la nécessité pour un autre thread d'appeler pthread_join() pour nettoyer le thread détaché.
Elle est généralement utilisée lorsque vous n'avez pas besoin d'attendre la fin d'un thread ou de récupérer son résultat.
L'argument est l'identifiant du thread (pthread_t) à détacher.
La fonction renvoie 0 en cas de succès et un code d'erreur positif en cas d'échec.

---

### pthread_join()
> #include <pthread.h>

	int pthread_join(pthread_t thread, void **retval);

pthread_join() est utilisée pour faire attendre le thread appelant qu'un thread spécifié termine son exécution.
Elle permet à l'appelant de récupérer éventuellement la valeur de retour du thread joint.
Les arguments sont
- l'identifiant du thread (pthread_t) à attendre
- un pointeur vers une variable où la valeur de retour du thread peut être stockée (ou NULL si ce n'est pas nécessaire).
La fonction renvoie 0 en cas de succès et un code d'erreur positif en cas d'échec, par exemple si le thread est déjà détaché ou invalide.

---

### mutex
Un mutex (abréviation de "mutual exclusion") est une primitive de synchronisation utilisée pour empêcher plusieurs threads d'accéder simultanément à des ressources partagées,
ce qui pourrait entraîner une corruption ou une incohérence des données.
Il garantit qu'un seul thread peut entrer dans une section critique de code à la fois,
tandis que les autres threads qui tentent d'accéder à la même section sont bloqués jusqu'à ce que le mutex soit libéré.

Le fonctionnement de base d'un mutex implique deux fonctions principales :
- Verrouillage (pthread_mutex_lock) :
Un thread doit verrouiller le mutex avant d'entrer dans la section critique.
Si le mutex est déjà verrouillé par un autre thread, le thread demandeur sera bloqué jusqu'à ce que le mutex soit disponible.
- Déverrouillage (pthread_mutex_unlock) :
Une fois que le thread a terminé son travail dans la section critique, il doit déverrouiller le mutex, permettant ainsi aux autres threads d'accéder à la ressource.

En plus de ces opérations de base, il existe d'autres fonctionnalités, telles que trylock (qui permet à un thread de tenter de verrouiller un mutex sans se bloquer) et la prévention des interblocages (en s'assurant que les mutex sont correctement déverrouillés).

Les mutex sont souvent utilisés pour protéger les structures de données ou les ressources partagées dans les programmes multithread afin de maintenir l'intégrité des données. Cependant, une utilisation incorrecte des mutex peut entraîner des problèmes tels que des interblocages, où deux threads ou plus attendent l'un l'autre pour libérer un mutex, provoquant le gel du programme.


Déverrouiller et détruire correctement tous les mutex avant de terminer un programme est crucial pour maintenir l'intégrité des ressources et assurer la stabilité du système.
Si les mutex restent verrouillés, d'autres threads peuvent être bloqués indéfiniment, entraînant des interblocages et des fuites de ressources.
Le déverrouillage des mutex permet à tous les threads en attente de terminer leurs opérations, tandis que l'appel à pthread_mutex_destroy() garantit que les ressources système associées au mutex sont libérées.
Ne pas détruire les mutex peut entraîner des fuites de mémoire et un comportement indéfini, en particulier dans les applications à longue durée de vie ou gourmandes en ressources.
Le nettoyage correct des mutex est une bonne pratique en programmation multithread pour une exécution robuste et prévisible du programme.

---

### pthread_mutex_init()
> #include <pthread.h>

	int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);

pthread_mutex_init() est utilisée pour initialiser un mutex.
La fonction prend deux arguments :
- un pointeur vers une variable pthread_mutex_t, qui contiendra le mutex initialisé
- un pointeur optionnel vers une structure pthread_mutexattr_t pour définir des attributs personnalisés pour le mutex (ou NULL pour les attributs par défaut)
La fonction renvoie 0 en cas de succès et un code d'erreur positif en cas d'échec.

---

### structure pthread_mutexattr_t
La structure pthread_mutexattr_t est utilisée pour définir les attributs d'un mutex dans le threading POSIX.
Elle permet de personnaliser le comportement du mutex, par exemple en définissant son type (par exemple, normal, récursif ou à vérification d'erreur) ou en définissant son comportement de partage entre processus.
La structure est opaque, ce qui signifie que ses variables internes ne sont pas directement accessibles par les programmeurs, et elle est gérée par l'implémentation de la bibliothèque POSIX.
Cependant, les attributs peuvent être modifiés via des fonctions spécifiques telles que pthread_mutexattr_settype() et sont utilisés pour définir le comportement du mutex.
Les principaux attributs incluent le type de mutex
(par exemple, PTHREAD_MUTEX_NORMAL, PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_ERRORCHECK et PTHREAD_MUTEX_DEFAULT)
et les options de partage entre processus
(PTHREAD_PROCESS_PRIVATE pour une utilisation au sein du même processus et PTHREAD_PROCESS_SHARED pour le partage entre processus).
Ces attributs sont configurés à l'aide de fonctions comme pthread_mutexattr_init(), pthread_mutexattr_settype() et pthread_mutexattr_setpshared().
Bien que la structure elle-même ne puisse pas être examinée directement, ses attributs peuvent être modifiés à l'aide des fonctions API disponibles.
La structure est généralement initialisée à l'aide de pthread_mutexattr_init() et peut être modifiée avec des fonctions comme pthread_mutexattr_settype().

---

### pthread_mutex_destroy()
> #include <pthread.h>

	int pthread_mutex_destroy(pthread_mutex_t *mutex);

pthread_mutex_destroy() est utilisée pour détruire un mutex précédemment initialisé.
Après la destruction d'un mutex, il ne peut plus être utilisé et ses ressources sont libérées.
La fonction prend un pointeur vers une variable pthread_mutex_t qui identifie le mutex à détruire.
Il est important de s'assurer qu'aucun thread ne détient le mutex lors de l'appel à pthread_mutex_destroy, car cela pourrait entraîner un comportement indéfini.
La fonction renvoie 0 en cas de succès et un code d'erreur positif en cas d'échec.

---

### pthread_mutex_lock()
> #include <pthread.h>

	int pthread_mutex_lock(pthread_mutex_t *mutex);

pthread_mutex_lock() est utilisée pour verrouiller un mutex, garantissant qu'un seul thread peut accéder à une section critique à la fois.
Si le mutex est déjà verrouillé par un autre thread, le thread appelant sera bloqué jusqu'à ce que le mutex soit disponible.
La fonction prend un pointeur vers une variable pthread_mutex_t, qui représente le mutex à verrouiller.
La fonction renvoie 0 en cas de succès et un code d'erreur positif en cas d'échec, par exemple lorsque le mutex est invalide ou déjà verrouillé.

---

### pthread_mutex_unlock()
> #include <pthread.h>

	int pthread_mutex_unlock(pthread_mutex_t *mutex);

pthread_mutex_unlock est utilisée pour déverrouiller un mutex précédemment verrouillé, permettant aux autres threads d'accéder à la section critique qui était protégée par le mutex. La fonction prend un pointeur vers une variable pthread_mutex_t, qui représente le mutex à déverrouiller. Il est important que le thread appelant cette fonction ait précédemment verrouillé le mutex. La fonction renvoie 0 en cas de succès et un code d'erreur positif en cas d'échec, par exemple lorsque le mutex n'est pas verrouillé par le thread appelant.

---

### la création de processus
> Pour une introduction rapide aux processus, consultez le readme de mon projet minitalk sur github :
> https://github.com/donnatchris/minitalk

La création de processus est un aspect fondamental de la gestion des applications multitâches sur les systèmes d'exploitation modernes.
Un processus représente un programme en cours d'exécution, avec son propre espace mémoire, son espace d'adressage et ses ressources.
Lorsqu'un programme souhaite exécuter une tâche parallèle ou une sous-tâche, il peut créer un nouveau processus en dupliquant le processus appelant, ce qui est exactement ce que fait la fonction fork().
Ce mécanisme permet de créer des processus indépendants qui peuvent s'exécuter en parallèle.

#### différences entre la création de fork() et de thread
Les différences entre la création de fork() et de thread sont principalement liées à la manière dont les processus et les threads gèrent l'exécution, la mémoire et les ressources.
fork() crée un nouveau processus indépendant avec son propre espace mémoire, ses descripteurs de fichiers et son contexte d'exécution.
Le processus enfant est une copie du parent au moment de la création, mais après l'appel à fork(), les deux processus s'exécutent indépendamment.
En revanche, un thread crée une unité d'exécution au sein du même processus, partageant le même espace mémoire et les mêmes ressources que le thread principal.
Les threads sont plus légers que les processus et partagent un environnement d'exécution commun.


Lorsque fork() est appelé, chaque processus (parent et enfant) a sa propre mémoire séparée après l'appel à fork().
Cependant, avant l'exécution de fork(), les deux processus partagent la mémoire, mais une fois que fork() est appelé, les modifications apportées dans l'un n'affectent pas l'autre (sauf pour les optimisations comme le "copy-on-write").
Les threads, en revanche, partagent la même mémoire, y compris les variables globales et les ressources. Cela peut rendre la gestion de la mémoire plus complexe car des mécanismes de synchronisation comme les mutex doivent être utilisés pour éviter les conflits d'accès concurrents.

Le processus enfant créé avec fork() hérite des descripteurs de fichiers et autres ressources du parent, mais il peut les modifier indépendamment.
Chaque processus peut également avoir ses propres ressources système, comme les ID de processus. En revanche, tous les threads d'un processus partagent les ressources du processus, telles que la mémoire et les descripteurs de fichiers.
Ils ont des ID de thread distincts, mais les autres ressources sont partagées.


La création d'un nouveau processus avec fork() est plus coûteuse en termes de temps et de ressources car elle implique la duplication du processus parent.
En revanche, la création d'un thread est généralement moins coûteuse que la création d'un processus car il n'y a pas de duplication complète de la mémoire et des ressources ; seul un nouvel environnement d'exécution est ajouté au processus existant.


Les processus parent et enfant créés avec fork() s'exécutent indépendamment.
Ils peuvent continuer leur travail sans se bloquer mutuellement, mais chaque processus a son propre contexte d'exécution.
Les threads s'exécutent simultanément dans le même processus et peuvent facilement partager des données, mais ils doivent être correctement synchronisés pour éviter des problèmes comme les conditions de course.


Lorsque le processus enfant se termine après un fork(), il ne termine pas le processus parent.
Les deux processus peuvent continuer à s'exécuter indépendamment, et la fin des processus enfants doit être gérée à l'aide de wait() ou waitpid() dans le parent.
Lorsqu'un thread termine son exécution, le processus principal ne se termine pas nécessairement, mais il doit s'assurer que tous les threads ont terminé avant de se fermer.
Le processus attend que tous les threads aient terminé avant de se fermer.


La communication entre les processus avec fork() se fait généralement à l'aide de mécanismes IPC (Inter-Process Communication), tels que les pipes, les files de messages ou la mémoire partagée.
Cela implique des mécanismes plus complexes que pour les threads, où la communication entre threads peut se faire à l'aide de variables partagées.
Cependant, cela nécessite une synchronisation pour éviter les conflits d'accès concurrents.


fork() permet une exécution parallèle entre le parent et l'enfant.
Chaque processus peut s'exécuter sur un processeur distinct dans les systèmes multiprocesseurs.
Les threads permettent également une exécution parallèle, mais tous les threads s'exécutent dans le même espace mémoire, ce qui les rend plus légers mais potentiellement plus sujets aux problèmes de synchronisation.


En résumé, fork() crée un nouveau processus avec sa propre mémoire et ses propres ressources, plus coûteux en termes de temps et de gestion, et généralement utilisé pour des tâches indépendantes. Les threads créent une unité d'exécution au sein du même processus, partageant la mémoire et les ressources, plus légers mais nécessitant des mécanismes de synchronisation pour éviter les problèmes liés à l'accès concurrent aux données. Chaque méthode a ses avantages et ses inconvénients en fonction des besoins de l'application (parallélisme, partage de données, coût des ressources, etc.).


Pour terminer correctement un processus enfant à l'aide de waitpid() et exit(), commencez par créer le processus enfant avec fork().
Le parent et l'enfant continuent d'exécuter leur code respectif après le fork.

Dans le processus enfant, effectuez les tâches nécessaires.
Appelez exit(status) pour terminer correctement.
Le statut est une valeur entière, souvent EXIT_SUCCESS ou EXIT_FAILURE, qui sera renvoyée au parent.

Dans le processus parent, utilisez waitpid() pour attendre que le processus enfant se termine et récupérer son statut de sortie.
Vérifiez si l'enfant s'est terminé normalement avec la macro WIFEXITED(status) et obtenez le statut de sortie à l'aide de WEXITSTATUS(status).

---

### fork()
> #include <unistd.h>

	pid_t fork(void);
 
La fonction fork() crée un nouveau processus en dupliquant le processus appelant.
Elle est disponible sur les systèmes Unix et de type Unix.
Le processus nouvellement créé, appelé processus enfant, fonctionne indépendamment du processus parent.


Lorsque fork() est appelé, un nouveau processus enfant est créé.
Le processus enfant hérite de la mémoire, des descripteurs de fichiers et du contexte d'exécution du processus parent.
Les deux processus continuent leur exécution à partir de l'instruction qui suit l'appel à fork().
Ils peuvent effectuer des tâches différentes en fonction des conditions définies après le fork().

#### Valeurs de retour
- Dans le processus parent, fork() renvoie l'identifiant du processus enfant (un entier positif).
- Dans le processus enfant, fork() renvoie 0.
- En cas d'erreur (échec de la création du processus), fork() renvoie -1 et définit errno (nécessite stdio.h pour errno).

#### Cas d'utilisation pratiques
- Serveurs concurrents : fork() est utilisé pour gérer plusieurs clients simultanément, chaque client étant géré par un processus enfant distinct.
- Traitement parallèle : Il permet de répartir des calculs intensifs sur plusieurs processus pour améliorer les performances.
- Shells comme bash : Lorsqu'une commande est exécutée, le shell crée un processus enfant avec fork() pour exécuter la commande tout en gardant le processus parent disponible.
- Gestion des pipelines (ls | grep) : Chaque commande du pipeline est exécutée dans un processus distinct créé avec fork().

---

### waitpid()
> #include <sys/types.h>

> #include <sys/wait.h>

	pid_t waitpid(pid_t pid, int *status, int options)
 

La fonction waitpid() est utilisée pour attendre la fin d'un processus enfant spécifique et récupérer son statut de fin.
Contrairement à wait(), qui attend n'importe quel processus enfant, waitpid() permet de cibler un enfant spécifique.
Le paramètre pid spécifie quel processus attendre.
- Une valeur supérieure à 0 attend le processus avec l'identifiant spécifié.
- Une valeur de -1 est équivalente à wait(), attendant n'importe quel processus enfant.
- Une valeur de 0 attend un processus enfant du même groupe de processus que le parent.
- Une valeur inférieure à -1 attend un enfant dont le groupe de processus correspond à la valeur absolue de pid.
  
Le paramètre status est un pointeur vers une variable entière utilisée pour stocker le statut de fin du processus enfant.
Des macros comme WIFEXITED(status) peuvent être utilisées pour interpréter ce statut.
Le paramètre options permet d'ajuster le comportement de la fonction.
Une valeur de 0 indique le comportement par défaut, bloquant le parent jusqu'à ce que le processus enfant se termine.
L'option WNOHANG empêche le blocage si aucun processus enfant ne s'est terminé. L'option WUNTRACED signale les processus enfants qui ont été arrêtés mais non terminés.
La fonction renvoie le pid du processus terminé si elle réussit.
Si aucune condition n'est remplie et que WNOHANG est utilisé, elle renvoie 0.
En cas d'erreur, elle renvoie -1 et définit errno.

---

### sémaphores

Les sémaphores sont des primitives de synchronisation utilisées en programmation concurrente pour contrôler l'accès aux ressources partagées. Ce sont des compteurs qui aident à gérer combien de threads ou de processus peuvent accéder à une section critique en même temps. Il existe deux principaux types de sémaphores : les sémaphores binaires, qui agissent comme de simples verrous n'autorisant qu'un seul thread à la fois, et les sémaphores de comptage, qui permettent à un nombre spécifié de threads ou de processus d'accéder simultanément à la ressource.

Les opérations de base des sémaphores sont wait (souvent appelée P ou sem_wait) et signal (également appelée V ou sem_post). L'opération wait décrémente le sémaphore et peut bloquer le thread appelant si la valeur du sémaphore est nulle, indiquant que la ressource est entièrement occupée. L'opération signal incrémente le sémaphore, débloquant potentiellement un thread en attente. Les sémaphores sont particulièrement utiles pour synchroniser les processus dans des environnements multithread ou multiprocessus, prévenant les conditions de course et garantissant l'intégrité des données.

---

### sem_open()

> #include <semaphore.h>

	sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);

sem_open() est une fonction utilisée pour créer ou ouvrir des sémaphores nommés, qui sont des sémaphores accessibles entre différents processus.
Les sémaphores nommés sont identifiés par un nom de chaîne unique et sont particulièrement utiles lorsque les processus doivent se synchroniser sans partager directement la mémoire.

La fonction sem_open() accepte les paramètres suivants :
- const char *name : Une chaîne qui identifie de manière unique le sémaphore nommé.
Le nom doit commencer par un / suivi de caractères alphanumériques, comme "/my_semaphore".
- int oflag : Spécifie l'action à effectuer.
O_CREAT crée le sémaphore s'il n'existe pas déjà.
O_EXCL provoque une erreur si O_CREAT est utilisé et que le sémaphore existe déjà.
- mode_t mode (optionnel) : Utilisé uniquement si O_CREAT est spécifié.
Il définit les autorisations d'accès pour le sémaphore selon les valeurs Unix standard (par exemple, 0666 pour les autorisations de lecture/écriture pour tous les utilisateurs).
- unsigned int value (optionnel) : Utilisé uniquement si O_CREAT est spécifié.
Il définit la valeur initiale du sémaphore (le compteur des ressources disponibles).

sem_open() renvoie un pointeur vers l'objet sémaphore en cas de succès, ou SEM_FAILED en cas d'erreur.
Une fois terminé, il est important de fermer le sémaphore avec sem_close() et de le dissocier avec sem_unlink() pour libérer les ressources système.
