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
#define Depart_B 0
#define R1D_B 1
#define R2L_B 2
#define R3L_B 3
#define R2P_B 4
#define R1P_B 5
#define R0D_B 6
#define R3D_B 7
#define R0P_B 8
#define R0L_B 9

//position geogebra de la team jaune
inline Position positions_jaune[] = {
   Position(2696.948387545501f, 1648.0496055811986f,-PI/2), //Depart_J_jaune
   Position(44.0f, 40.0f,PI), //R1L_J_jaune
   Position(109.91151713267399f, 43.852527975099996f,3 * PI / 2), //R2L_J_jaune
   Position(114.7951679161948f, 53.52824981187007f,PI/2), //R3L_J_jaune
   Position(40.0f, 40.0f,PI), //R1P_J_jaune
   Position(109.91151713267399f, 39.852527975099996f,3*PI/2), //R2P_J_jaune
   Position(114.7951679161948f, 57.528249811870076f,PI/2), //R3P_J_jaune
   Position(9.88404375784381f, 55.74783708591414f,PI/2), //R1D_J_jaune
   Position(55.9756444679994f, 103.08366002410847f,7 * PI / 4), //R0D_J_jaune
   Position(95.0f, 35.0f,5 * PI / 4), //R2D_J_jaune
   Position(125.407903173633f, 120.35880269343f, PI / 2), //R3D_J_jaune
   Position(39.978448130320004f, 119.86717541175099f,PI), //R0P_J_jaune
   Position(43.978448130320004f, 119.86717541175099f,PI), //R0L_J_jaune
};

//position geogebra de la team bleu
inline Position positions_bleu[] = {
   Position(2696.948387545501f + 150, 1648.0496055811986f,-PI/2), //R2D_{B}_bleu
   Position(2899.7100722722753f, 560.1534813867162f,0+3.14), //R1D_{B}_bleu
   Position(1899.6643874376957f, 439.28988429000924f,0+3.14), //R2L_{B}_bleu
   Position(1850.6431432355473f, 535.9536387208536f,0+3.14), //R3L_{B}_bleu
   Position(1850.5667353069764f, 575.9535657436428f,0+3.14), //R2P_{B}_bleu
   Position(2598.8518741981375f, 402.1001233775338f,0+3.14), //R1P_{B}_bleu
   Position(2437.8906980353604f, 1032.6304062258816f,0+3.14), //R0D_{B}_bleu
   Position(1743.2393882553897f, 1204.0552239802414f,0+3.14), //R3D_{B}_bleu
   Position(2597.541771143235f, 1200.7708320575468f,0), //R0P_{B}_bleu
   Position(2557.541844120446f, 1200.6944241289762f,0), //R0L_{B}_bleu
};

inline Position* positions_match;//ce pointeur vaut soit positions_bleus soit positions_bleu en fonction de la couleur.
#endif //TEAM2026_GEOGEBRA_H_CERTIF
