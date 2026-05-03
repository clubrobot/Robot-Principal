//
// Created by bapti on 04/11/2024.
//

#include "Automate.h"
#include "My_Clock.h"
#include <chrono>
#include <FreeRTOS.h>
#include <FreeRTOSConfig_Default.h>
#include <Wheeledbase.h>
#include <FreeRTOS/Source/include/task.h>
#include <team2025/ListeActionneurs.h>

#include "variables_globales.h"
#include "sensors/SensorsThread.h"

#include "team2025/TacheEmpiler.h"
#include "team2025/TacheBanderole.h"


#include <Teleplot.h>
#include <team2025/Strategies.h>
#include <team2025/TacheTransport.h>
#include "yeux/yeuxThread.h"

#include "BasicMoveStrategy.h"
#include "Elevator.h"
#include "HazelnutGripper.h"

namespace Automate {
    Logger auto_logs = Logger("AUTOMATE");
    Tache** taches;//endroit de stockage des taches
    int color;//couleur de l'équipe
    int current_points;//current_points réalises pour l'instant
    int numberTaches;
}

void Automate::init(int team) {
    color=team;
    if(team==TEAM_JAUNE){
        auto_logs.log(WARNING_LEVEL, "Automate init avec Jaune\n");
    }else{
        auto_logs.log(WARNING_LEVEL, "Automate init avec Bleu\n");
    }
    //Load strat
    //Strategies::stratDeBase(team) ;
    Strategies::strat1(team) ;
    //Strategies::stratTestEmpilement(team);
    //Load taches
    Wheeledbase::SET_POSITION(Strategies::start);//&positions_match[start2]);
    numberTaches=Strategies::nb_taches;
    taches = Strategies::strat;
    current_points=0;
}

Position start = Position(1700,300,-1.57);
Position test = Position(1500,1250,-1.57);
Position test2 = Position(1300,300,-1.57);


void Automate::play_match(void *pvParameters){

    velocityControl.enable();

    HazelnutGripper::Gripper::setRotationAll(0);

    while (!HazelnutGripper::Gripper::getFinger(0).isTargetReached())
    {
        printf("%d %d %d %d\n",HazelnutGripper::Gripper::getFinger(0).isTargetReached(), HazelnutGripper::Gripper::getFinger(1).isTargetReached(), HazelnutGripper::Gripper::getFinger(2).isTargetReached(), HazelnutGripper::Gripper::getFinger(3).isTargetReached());
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    Wheeledbase::GOTO_DELTA(1300, 0, true);
    HazelnutGripper::Elevator::setAngle(126.562500);
    while (abs(HazelnutGripper::Elevator::getAngle() - 126.562500) > 3)
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    printf("Reading colors\n");
    vTaskDelay(pdMS_TO_TICKS(2000));

    printf("Reading color ends\n");
    HazelnutGripper::Elevator::setAngle(110);
    HazelnutGripper::Gripper::openAll();
    Wheeledbase::GOTO_DELTA(50, 0, true);

    printf("Waiting for fingers\n");
    while (!HazelnutGripper::Gripper::getFinger(0).isTargetReached() || abs(HazelnutGripper::Elevator::getAngle() - 110) > 3)
    {
        printf("%d %d %d %d\n",HazelnutGripper::Gripper::getFinger(0).isTargetReached(), HazelnutGripper::Gripper::getFinger(1).isTargetReached(), HazelnutGripper::Gripper::getFinger(2).isTargetReached(), HazelnutGripper::Gripper::getFinger(3).isTargetReached());
        vTaskDelay(pdMS_TO_TICKS(1));
    }


    printf("New angle\n");
    HazelnutGripper::Elevator::setAngle(132.187500);
    while (abs(HazelnutGripper::Elevator::getAngle() - 132.187500) > 3)
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
    HazelnutGripper::Gripper::closeAll();

    vTaskDelay(pdMS_TO_TICKS(1000));
    while (!HazelnutGripper::Gripper::getFinger(0).isTargetReached())
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    HazelnutGripper::Elevator::setAngle(61.875000);

    while (abs(HazelnutGripper::Elevator::getAngle() - 61.875000) > 3)
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    Wheeledbase::TURNTO_DELTA(PI/2);

    HazelnutGripper::Gripper::spreadFingers(180);

    vTaskDelay(pdMS_TO_TICKS(1000));

    HazelnutGripper::Gripper::getFinger(1).setAngle(1,180);
    HazelnutGripper::Gripper::getFinger(3).setAngle(1,180);


    vTaskDelay(pdMS_TO_TICKS(2000));


    HazelnutGripper::Gripper::spreadFingers(0);

    HazelnutGripper::Elevator::setAngle(132.187500);
    while (abs(HazelnutGripper::Elevator::getAngle() - 132.187500) > 3)
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
    HazelnutGripper::Gripper::openAll();

    while (!HazelnutGripper::Gripper::getFinger(0).isTargetReached())
    {
        printf("%d %d %d %d\n",HazelnutGripper::Gripper::getFinger(0).isTargetReached(), HazelnutGripper::Gripper::getFinger(1).isTargetReached(), HazelnutGripper::Gripper::getFinger(2).isTargetReached(), HazelnutGripper::Gripper::getFinger(3).isTargetReached());
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    HazelnutGripper::Elevator::setAngle(61.875000);

    while (abs(HazelnutGripper::Elevator::getAngle() - 61.875000) > 3)
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    HazelnutGripper::Gripper::closeAll();









    /*

    poly_delay(1000);
    Wheeledbase::TURNTO_DELTA(PI, true);

    poly_delay(1000);
    Wheeledbase::GOTO_DELTA(-1000, 0, true);

    poly_delay(1000);
    Wheeledbase::TURNTO_DELTA(PI/2, true);
    poly_delay(1000);
    Wheeledbase::GOTO_DELTA(0, -500, true);*/


   // Wheeledbase::GOTO_DELTA(300,true);

    //Wheeledbase::TURNTO_DELTA(PI,true);
    positionControl.enable();
    //Wheeledbase::SET_VELOCITIES(0,0);
    while(true)
    {


        //Wheeledbase::SET_OPENLOOP_VELOCITIES(100,100);


        //Wheeledbase::GOTO_DELTA(-300, 0, false);

        /*
        long t = millis() % 10000;


        if (t < 5000)
        {

            velocityControl.setSetpoints(100,0);
        }else
        {
            velocityControl.setSetpoints(-100,0);
        }
*/

        vTaskDelay(pdMS_TO_TICKS(1));



        //teleplot.add_variable_int("elapsed_ms",t);
    }



    /*
    printf("Premiere etape\n");
    Wheeledbase::GOTO_DELTA(300, 0, false);
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    printf("L'objectif GOTO_DELTA 1 a ete atteint, Automate est ok\n");

    printf("Deuxieme etape\n");
    Wheeledbase::TURNTO_DELTA(M_PI/2);
    printf("L'objectif TURNTO_DELTA 2 a ete atteint, Automate est ok\n");
    
    printf("Troisieme etape\n");
    Wheeledbase::GOTO_DELTA(-300, 0);
    printf("L'objectif GOTO_DELTA 3 a ete atteint, Automate est ok\n");
*/
    /*printf("Quatrieme etape\n");
    Wheeledbase::TURNTO_DELTA(M_PI/2);
    printf("L'objectif TURNTO_DELTA 4 a ete atteint, Automate est ok\n");

    printf("%f %f %f\n", Wheeledbase::GET_POSITION()->x, Wheeledbase::GET_POSITION()->y, Wheeledbase::GET_POSITION()->theta);

    printf("Cinquieme etape\n");
    Wheeledbase::GOTO_DELTA(-300, 0);
    printf("L'objectif GOTO_DELTA 5 a ete atteint, Automate est ok\n");

    printf("%f %f %f\n", Wheeledbase::GET_POSITION()->x, Wheeledbase::GET_POSITION()->y, Wheeledbase::GET_POSITION()->theta);

    printf("Sixieme etape\n");
    Wheeledbase::TURNTO_DELTA(M_PI);
    printf("L'objectif TURNTO_DELTA 6 a ete atteint, Automate est ok\n");

    printf("%f %f %f\n", Wheeledbase::GET_POSITION()->x, Wheeledbase::GET_POSITION()->y, Wheeledbase::GET_POSITION()->theta);*/

    for (;;){
    }
}
    /*auto *procedure_demarrage = (void (*)()) pvParameters;
    //cette fonction remplit le vecteur taches avec des tâches. Elles seront executée dans l'ordre ou elles ont été ajoutée.
    //Seulement la fonction execute  et get_necessary_time doivent être implémentée.
    //auto start_time = std::chrono::high_resolution_clock::now();
    procedure_demarrage();
    start_millis=millis();

    current_points=0;
    bool state=true;
    match_started=true;
    for (int tache_id = 0; tache_id < numberTaches; ++tache_id) {
        auto_logs.log(INFO_LEVEL, "Tache n.%d\n", tache_id);
        //execute les tâches dans l'ordre tant qu'on a assez de temps.
        //auto current = std::chrono::high_resolution_clock::now();
        //auto delta_t = std::chrono::duration<double, std::milli>(current-start_time).count();
        //auto_logs.log(INFO_LEVEL, "delta_t %f  et %f\n", delta_t, 100000-taches[tache_id]->get_necessary_time());
        //if(delta_t>100000-taches[tache_id]->get_necessary_time())break;//on est deja a la fin du match faut s'arrêter la
        //execute la tâche.
        state=taches[tache_id]->execute(state);
        if(state){
            current_points+=taches[tache_id]->get_max_score();
            char phrase[50];
            sprintf(phrase,"SMERCI AISPRID  *75$score 54");
            printf("%s\n",phrase);
            yeuxThread::yeux.println(phrase);
        }
    }
    Wheeledbase::SET_PARAMETER_VALUE(RIGHTWHEEL_MAXPWM_ID, 150);
    Wheeledbase::SET_PARAMETER_VALUE(LEFTWHEEL_MAXPWM_ID, 150);
    for (;;){}
}*/