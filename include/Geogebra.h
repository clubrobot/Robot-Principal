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
#define R0T_J 13
#define R0bisT_J 14
#define R1T_J 15
#define R1bisT_J 16
#define R2D_B 0
#define R1L_B 1
#define R1D_B 2
#define R2P_B 3
#define R2L_B 4
#define R3L_B 5
#define R3P_B 6
#define R1P_B 7
#define R0D_B 8
#define R3D_B 9
#define R0P_B 10
#define R0L_B 11
#define Depart_B 12
#define R0T_B 13
#define R0bisT_B 14
#define R1T_B 15
#define R1bisT_B 16

//position geogebra de la team jaune
inline Position positions_jaune[] = {
   Position(30.0f, 164.60000000000002f,-PI/2), //Depart_{J}_jaune
   Position(44.0f, 40.0f,PI), //R1L_{J}_jaune
   Position(109.91151713267399f, 43.852527975099996f,-PI/2), //R2L_{J}_jaune
   Position(114.7951679161948f, 53.52824981187007f,PI/2), //R3L_{J}_jaune
   Position(40.0f, 40.0f,-PI/2), //R1P_{J}_jaune
   Position(109.91151713267399f, 39.852527975099996f,-PI/2), //R2P_{J}_jaune
   Position(114.7951679161948f, 57.528249811870076f,PI/2), //R3P_{J}_jaune
   Position(9.88404375784381f, 55.74783708591414f,PI/2), //R1D_{J}_jaune
   Position(55.9756444679994f, 103.08366002410847f,-PI/4), //R0D_{J}_jaune
   Position(95.0f, 35.0f,- 3 * PI / 4), //R2D_{J}_jaune
   Position(125.407903173633f, 120.35880269343f,PI / 2), //R3D_{J}_jaune
   Position(39.978448130320004f, 119.86717541175099f,PI), //R0P_{J}_jaune
   Position(43.978448130320004f, 119.86717541175099f,PI), //R0L_{J}_jaune
   Position(60.622858328237f, 134.74414154568f,- PI / 4), //R0T_{J}_jaune
   Position(40.167436202942f, 108.620349433857f, - PI / 2), //R0bisT_{J}_jaune
   Position(47.807413141305005f, 85.94686948774701f,- PI / 2), //R1T_J_jaune
   Position(14.782996698057001f, 43.557320023281f,3 * PI /4), //R1bisT_J_jaune
};

//position geogebra de la team bleu
inline Position positions_bleu[] = {
   Position(204.89483875455016f, 35.104960558119856f,- 3 * PI / 4), //R2D_{B}_bleu
   Position(255.88519471753486f, 40.20237154489629f,0), //R1L_{B}_bleu
   Position(289.9710072272276f, 56.01534813867162f,PI / 2), //R1D_{B}_bleu
   Position(189.9740795366267f, 39.928995726722015f,- PI /3), //R2P_{B}_bleu
   Position(189.96643874376963f, 43.928988429000924f,-PI/2), //R2L_{B}_bleu
   Position(185.06431432355475f, 53.595363872085365f,PI/2), //R3L_{B}_bleu
   Position(185.05667353069768f, 57.595356574364274f,PI/2), //R3P_{B}_bleu
   Position(259.8851874198138f, 40.210012337753376f,0), //R1P_{B}_bleu
   Position(243.78906980353605f, 103.26304062258815f,- 3 * PI / 4), //R0D_{B}_bleu
   Position(174.323938825539f, 120.40552239802415f,PI / 2), //R3D_{B}_bleu
   Position(259.7541771143235f, 120.07708320575469f,0), //R0P_{B}_bleu
   Position(255.75418441204462f, 120.0694424128976f,0), //R0L_{B}_bleu
   Position(269.64715847801295f, 164.82888699588403f,- PI / 2), //Depart_B_bleu
   Position(239.08138662655068f, 134.91458728220158f,- 3 * PI / 4), //R0T_B_bleu
   Position(259.5866730533963f, 108.82991674223165f,- PI / 2), //R0bisT_B_bleu
   Position(251.99002089454285f, 86.14188429200013f,PI / 4), //R1T_B_bleu
   Position(285.0953495287365f, 43.815495345628655f,0), //R1bisT_{B}_bleu
};

inline Position* positions_match;//ce pointeur vaut soit positions_bleus soit positions_bleu en fonction de la couleur.
#endif //TEAM2026_GEOGEBRA_H_CERTIF
