# Informatique Temps Réel (ITR)

Travaux dirigés pour le cours _Informatique temps Réel_.

## Compilation

Un `makefile` est disponible. Pour compiler tous les TDs:

```
make
```

L'exécutable de chaque exercice se trouve dans le dossier correspondant à son TD, et se nomme `q*`, où `*` est la lettre de l'exercice. Par exemple l'exercice b) du TD3 se trouve à `td3/qb`.
Sauf pour le td6 dont l'exécutable se nomme `active`.

Voici la liste des commandes pour exécuter ces binaires:

```
./td1/qa
./td1/qb
./td1/qc
./td1/qd

./td2/qa
./td2/qb
./td2/qc

./td3/qa
./td3/qb
./td3/qc

./td4/qa
./td4/qb
./td4/qc
./td4/qd

./td6/active
```

## TD1

### a) Gestion simplifiée du temps Posix

Les fonctions utilitaires de gestion du temps sont définies dans `libtime.h` et implémentées dans `libtime.cc`.
Pour chaque timestamp manipulé, on vérifie que `tv_nsec` est entre 0 et 1000000000 (exclu).

On teste ces fonctions avec des tests unitaires dans `qa.cc`.
Si l'exécutable n'affiche rien, c'est que tous les tests passent.

### b) Timers avec callback

Le fichier `qb.cc` implémente un timer en suivant l'exemple du cours.

### c) Fonction simple consommant du CPU

Le fichier `qc.cc` implémente une fonction simple incrémentant un compteur sur un nombre de boucles défini par l'utilisateur.

On exécute cette fonction avec 1,000,000,000 boucles:
```
./td1/qc 1000000000
```

On obtient le résultat suivant:
```
1000000000.000000 in 1.253268 seconds
```

### d) Mesure du temps d’exécution d’une fonction

Le fichier `4d.cc` propose une modélisation affine du nombre de boucles de la fonction de l'exercice précédent par rapport à son temps d'exécution.

Dans un premier temps, on mesure le nombre de boucles calculées pendant un interval de temps donné, en interrompant la fonction `incr` lorsqu'un timer arrive à échéance. Pour celà, on utilise une varaible booléenne `stop` qui est modifiée par le timer et lue par `incr`.
Il faut déclarer `stop` comme _volatile_, car celui-ci est modifié par un autre thread.

L'exécution de cette fonction pour 4 secondes donne le nombre d'incréments suivants:

```
3237265763.000000 in 4.000191 seconds
```

Dans un second temps, on calibre les paramètres du modèle affine en effectuant deux mesures du nombre de boucle pour deux durées différentes.

On obtient les résultats suivants:

```
a: 3.53056e+08
b: 5.76607e+07
Estimated loop number: 3588223232
Real loop number: 3728146160
Model error: 3.75315%
```

Note: la calibration rate parfois, probablement à cause d'autres programmes tournant sur la machine. Il est donc possible qu'une nouvelle éxecution du programme donne une erreur de modèle de plus de 50%.

### e) Amélioration des mesures

Cet exercice a été mis de côté d'après les consignes reçues en cours.

## TD2

### a) Exécution sur plusieurs tâches sans mutex

En executant la fonction plusieurs fois avec le même paramètre, on obtient parfois le mauvais résultat:

```
final counter value: 9900.000000
100 100 8.644800

final counter value: 10000.000000
100 100 9.683000

final counter value: 99962.000000
100 1000 115.854600
```

Ceci est dû aux accès en concurrence. Deux threads ou plus peuvent essayer de modifier en même temps la variable. Seules les modifications de l'un d'entre eux sont alors réellement sauvegardées.

### b) Mesure de temps d’exécution

On exécute la mesure du temps d'exécution pour différents nombres de tâche et différents nombres de boucles:

![Graphe d'exécution](images/2b.png)

Sur un OS temps réel, on constate que le nombre de tâche reflète le nombre de coeurs: 
Tant que le nombre de tâches est en dessous du nombre de coeur, le temps d'exécution n'augmente quasiment pas. En revanche, quand on dépasse le nombre de coeurs, on a un bond brusque.

### c) Exécution sur plusieurs tâches avec mutex

On exécute la fonction précédente d'abord sans, puis avec protection par le mutex.

`./qc 100000 10 3 1`

```
final counter value: 426251.000000
100000 10 2.116700

final counter value: 276000.000000
100000 10 2.333200

final counter value: 310632.000000
100000 10 1.762000
```

`./qc 100000 10 3 1`

```
final counter value: 1000000.000000
100000 10 3.836700

final counter value: 1000000.000000
100000 10 6.062500

final counter value: 1000000.000000
100000 10 4.057500
```

On remarque qu'utiliser les mutex permet d'éviter les accès en concurrence. Le résultat est alors stable (le `counter` a toujours la valeur attendue). 
Cependant l'execution prend plus de temps.

## TD3

### a) Classe Chrono

La class Chrono est implémentée principalement en utilisant les fonctions temporelles utilitaires définies au TD1 a).

On teste le chrono en exécutant `./td3/qa`:

```
0.009000 ms
2966.792600 ms
2966.914551 ms
```

### b) Classe Timer

La classe abstraite `Timer` utilise implémente la logique temporelle du timer à l'aide des fonctions Posix. Cependant, elle n'implémente pas la logique concernant l'action à réaliser lorsque le timer arrive à échéance. Pour l'implémenter, il faut créer une nouvelle classe héritant de `Timer` et implémentant la méthode virtuelle `callback`.
Cette méthode est appelée via une référence à l'objet lui-même dans la fonction `call_callback`. Cette référence est passée comme `sigev_value.sival_ptr` lors de la création du `Timer`. Elle est donc passée en argument de `call_callback`, qui est l'action `sa_sigaction` réalisée à l'échéance du Timer.

On implémente une classe `PeriodicTimer`, qui permet d'exécuter la `callback` périodiquement.

Enfin, on implémente un `CountDown` pour tester les deux classes précédentes. On lui demande de compter de 9 à 0.
On peut le tester avec `./td3/qb`:

```
9
8
7
6
5
4
3
2
1
0
```

### c) Calibration en temps d’une boucle

Dans cet exercice, on utilise les classes définies précédemment pour reproduire la calibration du modèle affine présenté au TD1 d).
La Calibration est effectuée à la création de l'object `Calibrator` à l'un objet `Looper`. Le `Calibrator` créé peut ensuite être utilisé
plusieurs objets `CpuLoop`.

On calibre en lançant `./td3/qc` et on obtient:
`expected time: 2000.000000 ms, got : 1989.029306 ms`


## TD4

### a) Classe Thread

On crée d'abord une classe `PosixThread` qui encapsule la logique des threads posix en utilisant les fonctions `pthread_*`, le constructeur d'un `PosixThread` prend notamment une fonction en paramètre qui sera exécutée. On crée ensuite une class `Thread` héritat de `PosixThread` pour suivre au mieux les principes de la programmation orientée objet. Cette classe comporte une méthode abstraite `run` qui doit être implémentée par une sous-classe et sera exécutée dans un thread posix.

Pour tester `Thread`, on crée une sous-classe `Incrementer` qui incrémente un compteur en paralèlle. On lance plusieurs `Incrementer` en même temps pour tester le comportement des threads. On peut tester ce code avec `./td4/qa`.

```
count value: 125673
```

Cependant on remarque que la valeur finale du compteur n'est pas la même à chaque lancé.

### b) Classes Mutex

La classe `Mutex` représente un `pthread_mutex_t`. Cependant nous choisissons de représenter les actions à effectuer sur ce mutex par des classes
imbriquées plutôt que par de simples méthodes. On crée donc une class `Mutex::Monitor` pour représenter les actions `wait` et `notify` et des classes `Mutex::Lock` et `Mutex::TryLock`, sous-classes de `Mutex::Monitor` pour représenter les actions de `lock` et `unlock`. Pour `lock` le mutex il faut ainsi créer un objet `Lock` ou `TryLock` qui vérouille le mutex jusqu'à l'appelle de son destructeur, typiquement à la fin du scope dans lequel il est créé. On peut aussi appeler les méthodes `wait`, `notify` et `notifyAll` sur ce lock. On peut le tester avec `./td4/qb`.

```
count value: 300000
```

Avec l'ajout d'un mutex, la valeur finale est toujours la même, et bien la valeur attendue.

### c) Classe Semaphore

La classe `Semaphore` est une "boîtes à jetons" à accès concurrent. Elle est implémentée à l'aide d'un compteur dont l'accès est protégé par un `Mutex`. La méthode `give` incrémente le compteur, la méthode `take` décrémente le compteur s'il est supérieur à `0`, Sinon on appelle `wait` sur le mutex. Quand `give` est appelée, `notify` permet de réveiller un éventuel thread mis en pause. On peut le tester avec `./td4/qc`.

```
final semaphore counter value: 24
```

### d) Classe Fifo

La classe template `Fifo` est une file générique à accès concurrent qui support les méthodes `push` et `pop`. Elle est implémentée à l'aide d'une clase de la bibliothèque standard du C++: `std::queue`. Son accès est protégé par un mutex. `push` ajouter un élément à la fin de la file. `pop` extrait à l'élément au début de la file ou utilise `wait` du mutex si la file est vide. `push` appelle également `notify` pour réveiller un éventuel thread mis en pause. On peut la tester avec `./td4/qd`.

```
final counter value: 30
```

## TD5

Comme indiqué en cours, nous ne traitons pas le TD5 dans ce rapport.

## TD6

Les classes `ActiveObject` et `Request` implémentent de manière générale le pattern d'objet actif.

`Request` est un object abstrait représentant une requête. Il propose une méthode pour attendre le résultat, à l'aide d'un sémaphore. La méthode `execute`, executant le calcul, est virtuelle. En effet, son implémentation est spécifique à chaque cas. Il faut penser à libérer le sémaphore avec `returnSema.give()` dans l'implémentation de cette méthode.

`ActiveObject` est un thread possédant une file de requêtes. Sa boucle principale consiste à extraite les requêtes de la file et les exécuter une par une.

Les classes `ActiveCalc` et `CrunchReq` héritent des classes précédentes pour implémenter le pattern objet actif dans le cas particulier du calculateur.

`Calculator` est la classe exécutant le calcul en lui-même. Pour simuler la charge du calcul, on fait dormir le thread en utilisant `Thread::sleep_ms(param)`, où `param` est la valeur passée au calculateur.

`ActiveCalc` prend en argument de constructeur une référence vers un `Calculator` afin de créer une nouvelle requête `CrunchReq` qu'il empile dans sa pile.

Enfin, la classe `Client` représente un client qui demande l'exécution d'un calcul auprès d'un `ActiveCalc`. Son constructeur prend le paramètre du calcul ainsi que la référence vers le `ActiveCalc` à solliciter.

Le fichier `main` met en oeuvre le calcul en asynchrone de requêtes demandées par 10 clients différents.

Pour tester l'ensemble, lancer la commande `./td6/active`:

```
Client 2 result 4
Client 4 result 8
Client 16 result 32
Client 8 result 16
Client 32 result 64
Client 128 result 256
Client 64 result 128
Client 256 result 512
Client 1024 result 2048
Client 512 result 1024
```