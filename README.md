# Informatique Temps Réel (ITR)

Travaux dirigés pour le cours _Informatique temps Réel_.

## TD1

### d) Mesure du temps d’exécution d’une fonction

- Il faut déclarer pStop comme _virtual_
- On obtient les résultats suivants:

```
a: 3.53056e+08
b: 5.76607e+07
Estimated loop number: 3588223232
Real loop number: 3728146160
Model error: 3.75315%
```

Note: la calibration rate parfois, probablement à cause d'autres programmes tournant sur la machine. Il est donc possible qu'une nouvelle éxecution du programme donne une erreur de modèle de plus de 50%.

## TD2

### a) Exécution sur plusieurs tâches sans mutex

En executant la fonction plusieurs fois avec le même paramètre, on obtient parfois le mauvais résultat:

```
nLoops: 100
nTasks: 100
10000

nLoops: 100
nTasks: 100
9900

nLoops: 100
nTasks: 100
9800

nLoops: 100
nTasks: 100
10000
```

Ceci est dû aux accès en concurrence. Deux threads ou plus peuvent essayer de modifier en même temps la variable. Seules les modifications de l'un d'entre eux sont alors réellement sauvegardées.

### b) Mesure de temps d’exécution

![Graphe d'exécution](images/2b.png)
Sur un OS temps réel, on constate que le nombre de tâche reflète le nombre de coeurs: tant que le nombre de tâches est en dessous du nombre de coeur, le temps d'exécution n'augmente quasiment pas. En revanche, quand on dépasse le nombre de coeurs, on a un bond brusque.

### c) Exécution sur plusieurs tâches avec mutex

`100000 10 SCHED_RR`

```
Counter: 564111 - duration: 0.003
Counter: 623077 - duration: 0.003
Counter: 565825 - duration: 0.003
```

`100000 10 SCHED_RR protected`

```
Counter: 1e+06 - duration: 0.028
Counter: 1e+06 - duration: 0.034
Counter: 1e+06 - duration: 0.027
```

On remarque qu'utiliser les mutex permet d'éviter les accès en concurrence. Le résultat est alors stable (le `counter` a toujours la valeur attendue). Cependant l'execution prend plus de temps.

## TD4

### a) Classe Thread

```
Policy 0 - priority 0
Before start - start 0 - stop 0 - exec 0
After start - start 1.58498e+12 - stop 0 - exec -1.58498e+12
When finished - start 1.58498e+12 - stop 1.58498e+12 - exec 2791
Result 1e+09
```

### b) Classes Mutex

### c) Classe Semaphore

### d) Classe Fifo

## TD6

Les classes `ActiveObjects` et `Requests` implémentent de manière générale le pattern d'objet actif.

`Requête` est un object abstrait représentant une requête. Il propose une méthode pour attendre le résultat, à l'aide d'un sémaphore. La méthode `execute`, executant le calcul, est virtuelle. En effet, son implémentation est spécifique à chaque cas. Il faut penser à libérer le sémaphore avec `semaphore.give()` dans l'implémentation de cette méthode.

`ActiveObject` est un thread possédant une file de requêtes. Sa boucle principale consiste à extraite les requêtes de la file et les exécuter une par une.

Les classes `ActiveCalc` et `CrunchReq` héritent des classes précédentes pour implémenter le pattern objet actif dans le cas particulier du calculateur.

`Calculator` est la classe exécutant le calcul en lui-même. Pour simuler la charge du calcul, on fait dormir le thread en utilisant `Thread::sleep_ms(param)`, où `param` est la valeur passée au calculateur.

`ActiveCalc` prend en argument de constructeur une référence vers un `Calculator` afin de créer une nouvelle requête `CrunchReq` qu'il empile dans sa pile.

Enfin, la classe `Client` représente un client qui demande l'exécution d'un calcul auprès d'un `ActiveCalc`. Son constructeur prend le paramètre du calcul ainsi que la référence vers le `ActiveCalc` à solliciter.

Le fichier `main` met en oeuvre le calcul en asynchrone de requêtes demandées par 10 clients différents.
