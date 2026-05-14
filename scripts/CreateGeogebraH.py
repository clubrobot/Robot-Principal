from xml.etree.ElementTree import PI

from geogebra import Geogebra
import os
import re
#Exporte les points du fichier geogbra sous forme d'un .h.
#les points d'interet du geogbra doivent contenir un des trois mots-clés
#   Bleu: pour les points d'intérêt de l'équipe bleu
#   Jaune: pour les points d'intérêt de l'équipe jaune
#   All: pour les points d'intéret commun aux deux équipes.
#Pour chaque variable avec Bleu il en faut une autre avec Jaune à la place.

CHEMIN_POINT_H="D:/Technique/Code/CLUB_ROBOT/team2026_SAUV_V2/include/Geogebra.h"
CHEMIN_GEOGEBRA="D:/Technique/Code/CLUB_ROBOT/team2026_SAUV_V2/maps/StrategieRobotMap.ggb"

#on lit les angles pour pouvoir les sauvegarder et ne pas les ecraser
f = open(CHEMIN_POINT_H, "r")
thetas_bleu={}
thetas_jaune={}
lines=f.readlines()
pattern = r"Position\([^,]+,\s*[^,]+,\s*([^)]+)\),\s*//\s*(.+)_(jaune|bleu)"
for l in lines:
    match = re.search(pattern, l)
    if match:
        a = match.group(1).strip()   # angle (ex: 3*PI/2)
        b = match.group(2).strip()   # nom complet (ex: Depart_{J})
        color = match.group(3)       # jaune ou bleu

        print("match", a, b, color)

        if color == "jaune":
            # Sauvegarde directe de l'angle jaune
            thetas_jaune[b] = a

            # Génère automatiquement l'angle bleu correspondant
            nom_bleu = b.replace("_{J}", "_{B}")
            thetas_bleu[nom_bleu] = a 

f.close()

#charge le fichier geogebra
geo=Geogebra(CHEMIN_GEOGEBRA)

all=geo.getall("")

elements = geo.root.findall("./construction/element")

# Extraire les valeurs des attributs 'label'
element_names = [elem.get("label") for elem in elements if elem.get("label") is not None]
liste_jaune=[]
liste_bleu=[]
for e in element_names:
    if(e.__contains__("_{J}")):
        liste_jaune.append(e)
    elif(e.__contains__("_{B}")):
        liste_bleu.append(e)

noms=""
var_bleus=""
var_jaunes=""
id=0
error=0
for e_j in liste_jaune:
    name=e_j
    noms+="#define "+name+" "+str(id)+"\n"
    point=geo.get(e_j)
    theta = "TBD"
    if name in thetas_jaune:    
        theta = thetas_jaune[name]
    var_jaunes+="   Position("+str(point[0]*10)+"f, "+str(point[1]*10)+"f,"+theta+"), //"+name+"_jaune"+"\n"
    found=True

"""Sauvegarde pour les angles:
Position(30.0f, 177.5f, 3*PI/2), //Depart_{J}_jaune
Position(44.0f, 40.0f, PI), //R1L_{J}_jaune
Position(109.91151713267399f, 43.852527975099996f, 3*PI/2), //R2L_{J}_jaune
Position(114.7951679161948f, 53.52824981187007f, PI/2), //R3L_{J}_jaune
Position(40.0f, 40.0f, PI), //R1P_{J}_jaune
Position(109.91151713267399f, 39.852527975099996f, 3*PI/2), //R2P_{J}_jaune
Position(114.7951679161948f, 57.528249811870076f, PI/2), //R3P_{J}_jaune
Position(9.88404375784381f, 55.74783708591414f, PI/2), //R1D_{J}_jaune
Position(56.31281594435417f, 80.52948870796966f, 7*PI/4), //R0D_{J}_jaune
Position(94.22975170480235f, 9.16305455714684f, 5*PI/4), //R2D_{J}_jaune
Position(125.407903173633f, 120.35880269343f, PI/2), //R3D_{J}_jaune
Position(39.978448130320004f, 119.86717541175099f, PI), //R0P_{J}_jaune
Position(43.978448130320004f, 119.86717541175099f, PI), //R0L_{J}_jaune
"""

for e_b in liste_bleu:
    name=e_b
    noms+="#define "+name+" "+str(id)+"\n"
    point=geo.get(e_b)
    theta = "TBD"
    if name in thetas_bleu:
        theta = thetas_bleu[name]
    var_bleus+="   Position("+str(point[0]*10)+"f, "+str(point[1]*10)+"f,"+theta+"+"+str(3.14)+"), //"+name+"_bleu"+"\n"
    found=True

#on crée le fichier
f = open(CHEMIN_POINT_H, "w")
f.write("#ifndef TEAM2026_GEOGEBRA_H_CERTIF\n#define TEAM2026_GEOGEBRA_H_CERTIF\n#include \"Odometry.h\" \n")
f.write(noms)
f.write("\n")

f.write("//position geogebra de la team jaune\n")
f.write("struct Position positions_jaune[] = {\n")
f.write(var_jaunes)
f.write("};\n")
f.write("\n")
f.write("struct Position* positions_match;//ce pointeur vaut soit positions_jaunes soit positions_bleu en fonction de la couleur.\n")
f.write("#endif //TEAM2026_GEOGEBRA_H_CERTIF\n")

f.write("//position geogebra de la team bleu\n")
f.write("struct Position positions_bleu[] = {\n")
f.write(var_bleus)
f.write("};\n")
f.write("\n")
f.write("struct Position* positions_match;//ce pointeur vaut soit positions_bleus soit positions_bleu en fonction de la couleur.\n")
f.write("#endif //TEAM2026_GEOGEBRA_H_CERTIF\n")

f.close()

print("\n")
print("\n")
print(liste_bleu)
print(liste_jaune)

print("Création du fichier avec", error, "erreurs")
    