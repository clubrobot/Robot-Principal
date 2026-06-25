# Comment contribuer ?
## Vous faites partie du Club
Si vous faites partie du Club Robot INSA Rennes, vous pouvez contribuer au code du robot ainsi :
* clonez le dépôt sur votre machine locale, si vous ne l'avez pas déjà fait, sinon faites un `git pull`
* créez une branche pour votre fonctionnalité le cas échéant celle-ci doit contenir le numéro de l'issue correspondante 
(ex: `#1234-fabrication-de-crêpes`)
* faites un `git push` pour créer la branche sur le dépôt distant
* faites une pull request en brouillon sur le dépôt distant pour montrer que vous travaillez sur le sujet
* faites vos modifications en réalisant des commits concis avec des messages clairs, n'hésitez pas à faire des messages 
multi-lignes si nécessaire [1]
* poussez vos modifications sur le dépôt distant
* une fois que vous avez terminé, mettez la pull request prête pour relecture et demandez au resp' informatique de la relire via l'outil intégré à github

[1] vous pouvez faire un commentaire multi ligne ainsi :
```bash
git commit -m "description courte
- changement 1
- changement 2"
```
## Vous ne faites pas partie du Club
Créez d'abord un fork du dépôt, puis faites comme si vous faisiez partie du Club, mais en poussant vos modifications sur votre fork et en faisant une pull request vers le dépôt principal.

# Style de code

Le code suit librement les [conventions de code de LLVM](https://llvm.org/docs/CodingStandards.html). Voici les points sur lesquels nous insistons particulièrement :
* Les noms de variables et de fonctions sont en `camelCase` (ex: `maFonction()`, `maVariable`)
* Les noms de namespace, classes et de structures sont en `PascalCase` (ex: `MaClasse`, `MaStructure`)
* Les noms de types sont en `PascalCase`, prefixé de `t_` (ex: `t_MaStructure`, `t_MaClasse`)
* Les noms de fichiers sont ceux du namespace, de la classe ou de la structure qu'ils contiennent, en `PascalCase` (ex: `MaClasse.cpp`, `MaStructure.h`)
* Si le fichier ne contient pas de classe ou de structure, il est en `snake_case` (ex: `mes_fonctions.cpp`)
* Les noms de variables, fonctions, classes, structures et types doivent être explicites et en anglais.
* La documentation embarquée doit être en français. Les commentaires peuvent être en anglais ou en français.
* Si vous utilisez un `TODO:`, `FIXME:` ou `BUG:` dans un commentaire, il doit être suivi de la date à laquelle vous l'avez écrit.

Par ailleurs, le nom des commits doit être en français et explicite. Si vous travaillez sur une issue, vous pouvez mettre le numéro de l'issue dans le message du commit.