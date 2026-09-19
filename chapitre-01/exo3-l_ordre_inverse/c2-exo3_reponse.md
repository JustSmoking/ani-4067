# Rapport

Par rapport à la version précédente du code, nous avons placé les tests dans deux fonctions distinctes pour des raisons de lisibilité.

Nous avons également appliqué la translation puis la rotation, afin de tester cet ordre et de le comparer avec l'ordre normal des transformations.

## Valeurs testées pour les deux cas :

**Premier test :**
* Position de la Pose : (1, 1, 1)
* Quaternion de la Pose : (45, 2, 3, 4)
* Point à tester : (2, 2, 2)

**Deuxième test :**
* Position de la Pose : (0, 10, 0)
* Quaternion de la Pose : (0, 1, 0, 0)
* Point à tester : (0, 5, 0)

Ce programme est fourni à titre d'exemple ; de nombreuses optimisations restent à faire, notamment sur la gestion des cas limites, l'optimisation des opérations mathématiques, ou encore une meilleure surcharge des opérateurs (ces derniers ayant été implémentés de manière basique à des fins de test).

**Compilateur :** MSVC

---

## Résultats

**Premier test :**
* Pose normale : (2.89, 3.17, 2.92)
* Pose Translation d'abord : (2.83642, 3.25706, 2.889)
> *Observation : Valeurs très proches.*

**Deuxième test :**
* Pose normale : [ATTENTION : insère ici le bon résultat, ex: (0, 5, 0)]
* Pose Translation d'abord : (0, -15, 0)

### Cas de coïncidence parfaite des deux méthodes
*(Avec l'aide de Gemini, car nous n'avons pas pu déduire ce cas de figure par nous-mêmes).*

Pour que les deux fonctions coïncident, il faut appliquer la règle géométrique suivante : **la translation doit s'effectuer sur le même axe que la rotation**. En choisissant l'axe Z (la profondeur) :

* **Position de la Pose :** (0, 0, 10)
  *(une translation de 10 mètres purement sur l'axe Z).*
* **Quaternion (w, x, y, z) :** (1, 0, 0, 1)
  *(le code va le normaliser, ce qui correspondra à une rotation de 90° autour de l'axe Z).*
* **Point local :** (5, 5, 5)
  *(il est possible d'utiliser n'importe quelles coordonnées ici, le résultat restera identique).*

### Observation
[](1.png)