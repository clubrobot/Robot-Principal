Copyright (C) 2026 Club Robot INSA Rennes This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, version 3. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details. You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 

# Introduction

Dans ce dépôt, vous trouverez le code source du robot du Club Robot INSA Rennes. Il est à noter que ce code est principalement destiné
à un usage interne et n'est pas forcément adapté à vos usages, mais vous pouvez l'utiliser à vos risques et périls.

Nous utilisons pour le robot un microcontrôleur STM32 ainsi que FreeRTOS avec une couche de compatibilité pour les fonctions Arduino.
Afin d'uploader le code sur le microcontrôleur, nous utilisons platformio, qui est un outil de compilation et d'upload multi-plateforme. 
Il est donc nécessaire de l'installer pour pouvoir compiler le code du robot.

# Compilation

[Installez platformio sur votre machine locale](https://docs.platformio.org/en/latest/core/installation/index.html) si ce n'est pas déjà fait.
Ensuite, vous pouvez utiliser la commande suivante pour compiler le code du robot :

```bash
platformio run
#ou
make build-upload
```

Vous pouvez consulter le fichier `Makefile` pour une liste (non-exhaustive) de ce que vous pouvez faire avec platformio. Ce fichier contient
également des alias de commande pour faciliter l'utilisation de platformio.

# Fonctionnement du code

Le point d'entrée du code est situé dans le fichier `src/main.cpp`. Là, vous trouverez les fonctions nécessaires pour initialiser le robot,
puis passer le contrôle à FreeRTOS. Une fois lancé, FreeRTOS va exécuter les différentes tâches du robot en parallèle :
* **WheeledBase loop** Cette tâche est responsable de tout ce qui touche à la base roulante du robot, c'est-à-dire gestion de l'asservissement, des moteurs, des encodeurs, etc.
* **Sensors loop** Cette tâche est responsable de la lecture des capteurs d'obstacles du robot.
* **Robot Loop** Cette tâche est responsable de la logique du robot, elle va passer des instructions à la base roulante et aux divers autres actionneurs.

Il existe une dernière tâche, le killer (`src/cerveau/killer.cpp`), qui est responsable de l'arrêt du robot à la fin du temps imparti pour le match.
Cette tâche est lancée par un timer FreeRTOS une fois que le match se fini.
