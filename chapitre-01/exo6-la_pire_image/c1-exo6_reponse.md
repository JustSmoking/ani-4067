# Analyse et mesure de performance

Pour effectuer cette mesure de performance, nous avons utilisé notre mini moteur de rendu écrit lorsque nous étions en GAP3 et nous l'avons ajusté pour prendre les différentes mesures notamment grace a l'intelligence artificielle(Gemini) qui nous a permis d'effectuer cette modification sur le code!

## -- Lien du depot github du moteur de rendu : https://github.com/JustSmoking/GAP3_Rendering_OpenGL_Prelude

Nous avons désactivé la synchronisation verticale avec glfwSwapInterval(0), car celui ci synchronise les images generées au refresh rate de l'écran ce qui biaise les performances car pour un écran de 60hz, la durée d'une image est de 16.66ms qui dépasse déja les 11ms

# Méthodologie

On capture le temps actuel avec la fonction glfwGetTime(), puis on calcule le DeltaTime qui correspond au temps qui a fallu au PC pour fabriquer l'image, on exclut volontairement le temps de la premiere image car il est quasiment toujours biaisé

# Résultat

Comme le montre l'image nous avons répété le processus 03 fois, les resultants sont flagrants(Voir l'image) :  

- En moyenne 998 images sur 1000 dépassent les 11ms 
- La durée de la plus longue image pour la premiere iteration est de 33.99ms

## Consequence : Le constat est la, le programme n'est pas du tout adapté pour un casque VR, pour un casque d'un refresh rate de 90hz, les images seront saccadées avec des phénomenes de saut d'image qui causeront des effets nefastes a l'utilisateur