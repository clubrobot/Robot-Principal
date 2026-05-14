#ifndef TEAM2026_GEOGEBRA_H_CERTIF
#define TEAM2026_GEOGEBRA_H_CERTIF
#include "Odometry.h" 
#define Depart_J 0
#define R1L_J 1
#define R2L_J 2
#define R3L_J 3
#define R1P_J 4
#define R2P_J 5
#define R3P_J 6
#define R1D_J 7
#define R0D_J 8
#define R2D_J 9
#define R3D_J 10
#define R0P_J 11
#define R0L_J 12
#define R2D_B 13
#define R1D_B 14
#define R2L_B 15
#define R3L_B 16
#define R2P_B 17
#define R1P_B 18
#define R0D_B 19
#define R3D_B 20
#define R0P_B 21
#define R0L_B 22

//position geogebra de la team jaune
struct Position positions_jaune[] = {
   Position(30.0f, 164.60000000000002f,3 * PI/2), //Depart_J_jaune
   Position(44.0f, 40.0f,PI), //R1L_J_jaune
   Position(109.91151713267399f, 43.852527975099996f,3 * PI / 2), //R2L_J_jaune
   Position(114.7951679161948f, 53.52824981187007f,PI/2), //R3L_J_jaune
   Position(40.0f, 40.0f,PI), //R1P_J_jaune
   Position(109.91151713267399f, 39.852527975099996f,3*PI/2), //R2P_J_jaune
   Position(114.7951679161948f, 57.528249811870076f,PI/2), //R3P_J_jaune
   Position(9.88404375784381f, 55.74783708591414f,PI/2), //R1D_J_jaune
   Position(55.9756444679994f, 103.08366002410847f,7), //R0D_J_jaune
   Position(95.0f, 35.0f,0), //R2D_J_jaune
   Position(125.407903173633f, 120.35880269343f,0), //R3D_J_jaune
   Position(39.978448130320004f, 119.86717541175099f,0), //R0P_J_jaune
   Position(43.978448130320004f, 119.86717541175099f,0), //R0L_J_jaune
};

//position geogebra de la team bleu
struct Position positions_bleu[] = {
   Position(204.8948387545501f, 35.104960558119856f,0+3.14), //R2D_B_bleu
   Position(289.9710072272275f, 56.01534813867162f,0+3.14), //R1D_B_bleu
   Position(189.96643874376957f, 43.928988429000924f,0+3.14), //R2L_B_bleu
   Position(185.06431432355473f, 53.595363872085365f,0+3.14), //R3L_B_bleu
   Position(185.05667353069765f, 57.595356574364274f,0+3.14), //R2P_B_bleu
   Position(259.88518741981375f, 40.210012337753376f,0+3.14), //R1P_B_bleu
   Position(243.78906980353605f, 103.26304062258815f,0+3.14), //R0D_B_bleu
   Position(174.32393882553896f, 120.40552239802415f,0+3.14), //R3D_B_bleu
   Position(259.7541771143235f, 120.07708320575469f,0+3.14), //R0P_B_bleu
   Position(255.7541844120446f, 120.0694424128976f,0+3.14), //R0L_B_bleu
};

struct Position* positions_match;//ce pointeur vaut soit positions_bleus soit positions_bleu en fonction de la couleur.
#endif //TEAM2026_GEOGEBRA_H_CERTIF
