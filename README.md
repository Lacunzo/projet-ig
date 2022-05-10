# projet-ig
Projet de création d'un Rogue-like

**Lucas Cosson** - **Joseph Debray** - **Kamelia Louani**

## Compilation

Pour compiler le projet il suffit d'ouvrir la solution visual studio et d'exécuter le programme.

## Informations techniques

Nous avons structuré le code en différentes classes :
- Personnage: correspond à la réalisation du personnage
- Map: correspond à la carte
- Leaf: correspond à une sous division de la carte
- Room: correspond à la pièce dans la sous division

Les autres classes servent pour les transformations géométriques.

Nous avons décidé ensemble que la génération du donjon se ferait aléatoirement. Nous avons pour cela utilisé l'algorithme BSP Trees.

Pour le personnage, il est composé de 10 parties : 2 bras en 2 parties, 2 jambes en 2 parties, un corps, une cou et une tête.
Tous ces éléments dépendent d'une taille, pour pouvoir redimentionner le personnage facilement, et d'un angle pour permettre l'animation ensuite.
Le personnage possède aussi des fonctions pour changer de position (avancer selon la direction) et pour changer sa direction.
Pour l'animation du personnage, deux fonctions définissent la position du personnage selon son état : 
une fonction "idle" quand le personnage est inactif,
une fonction lorsque le personnage se déplace.

Pour les caméras, celle du point de vu du personnge se place au coordonée de celui-ci au niveau de la tête, et s'oriente selon la direction qu'il regarde.
Pour la caméra vue d'en haut, elle se place aussi au coordonée du personnage, au dessus et regarde vers le bas, elle s'oriente de la même façon.


## Contrôles

Pour déplacer le personnage, il faut utiliser les touches directionnelles, haut et bas pour avancer et reculer, droite et gauche pour changer son orientation.