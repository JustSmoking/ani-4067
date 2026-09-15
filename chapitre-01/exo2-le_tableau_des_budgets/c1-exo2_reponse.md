# Liens de référence

Lien qui nous a servi de référence et qui nous a permis d'approfondir la notion de "Motion to photon" :

- https://unity.com/fr/glossary/motion-to-photon-latency
- https://link.springer.com/article/10.3758/s13428-022-01983-5#data-availability
- https://vrarwiki.com/wiki/Motion-to-photon_latency ==> pour les mesures !

---

## Estimation des temps par étape

| Étape | Estimation du temps |
| :--- | :--- |
| Mesure du(des capteurs) capteur | 1-2ms |
| Transmission et Traitement des données | 1-4ms |
| Traitement de l'app | Introuvable(limite max définie 5 à 10ms) |
| Compositeur | 1-2ms |
| Rafraîchissement de l'écran | 1–16,7 ms (balayage à 60 Hz) + 1–8 ms |