//
// Created by awing on 10/05/2026.
//

#include "Automate.h"

#include "FreeRTOS.h"
#include "Wheeledbase.h"
#include "FreeRTOS/Source/include/task.h"
#include "ihm/ihm.h"

void procedure_demarrage(){

    cerveau::automate::Team team;
    cerveau::automate::automateLogger.log(INFO_LEVEL,"Le robot est armé!\n");

    //Detect tirette
    pinMode(PD11,OUTPUT);

    digitalWrite(PD11,1);
#if LCD_OUTPUT
    ihm::ihmLogger.log(SCREEN_LEVEL, "Team ?");
#endif
    while (!ihm::etat_bleu() && !ihm::etat_jaune()) {}
    if (ihm::etat_bleu()) {
        digitalWrite(PD11, 0);
        cerveau::automate::automateLogger.log(INFO_LEVEL,"Equipe bleue détectée\n");
        team = cerveau::automate::BLEU;
        ihm::ihmLogger.sameLine(" Bleu");
    } else {
        digitalWrite(PD11, 0);
        cerveau::automate::automateLogger.log(INFO_LEVEL,"Equipe jaune détectée\n");
        team = cerveau::automate::JAUNE;
        ihm::ihmLogger.sameLine(" Jaune");
    }
    cerveau::automate::init(team);
    while(ihm::etat_tirette()==1){}
    while (ihm::etat_tirette()==0){}
    ihm::ihmLogger.log(SCREEN_LEVEL, "Lets go !");
}

void cerveau::automate::init(const Team team) {
    if (team == BLEU) {
        strategie::start = strategie::blueStart;
        strategie::generateBlueStrat();
    } else {
        strategie::start = strategie::yellowStart;
        strategie::generateYellowStrat();
    }
    Wheeledbase::SET_POSITION(&strategie::start);
}

void cerveau::automate::play_match(void *pvParameters) {
    procedure_demarrage();   velocityControl.enable();


    while (true) {}
    Wheeledbase::GOTO_DELTA(810, 0, true);
    Wheeledbase::GOTO_DELTA(-810, 0, true);

    /*

    HazelnutGripper::Gripper::closeAll();

    HazelnutGripper::Gripper::setRotationAll(0);

    while (!HazelnutGripper::Gripper::getFinger(0).isTargetReached())
    {
        printf("%d %d %d %d\n",HazelnutGripper::Gripper::getFinger(0).isTargetReached(), HazelnutGripper::Gripper::getFinger(1).isTargetReached(), HazelnutGripper::Gripper::getFinger(2).isTargetReached(), HazelnutGripper::Gripper::getFinger(3).isTargetReached());
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    Wheeledbase::GOTO_DELTA(400, 0, true);
    HazelnutGripper::Elevator::setAngle(10);
    while (abs(HazelnutGripper::Elevator::getAngle() - 10) > 3)
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    printf("Reading colors\n");
    vTaskDelay(pdMS_TO_TICKS(2000));

    printf("Reading color ends\n");
    HazelnutGripper::Elevator::setAngle(20);
    HazelnutGripper::Gripper::openAll();
    Wheeledbase::GOTO_DELTA(50, 0, true);

    printf("Waiting for fingers\n");
    while (!HazelnutGripper::Gripper::getFinger(0).isTargetReached() || abs(HazelnutGripper::Elevator::getAngle() - 20) > 3)
    {
        printf("%d %d %d %d\n",HazelnutGripper::Gripper::getFinger(0).isTargetReached(), HazelnutGripper::Gripper::getFinger(1).isTargetReached(), HazelnutGripper::Gripper::getFinger(2).isTargetReached(), HazelnutGripper::Gripper::getFinger(3).isTargetReached());
        vTaskDelay(pdMS_TO_TICKS(1));
    }


    printf("New angle\n");
    HazelnutGripper::Elevator::setAngle(0);
    while (abs(HazelnutGripper::Elevator::getAngle()) > 3)
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
    HazelnutGripper::Elevator::setAngle(60);

    while (abs(HazelnutGripper::Elevator::getAngle() - 60) > 3)
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

    HazelnutGripper::Elevator::setAngle(0);
    while (abs(HazelnutGripper::Elevator::getAngle() - 0) > 3)
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

    HazelnutGripper::Elevator::setAngle(60);

    while (abs(HazelnutGripper::Elevator::getAngle() - 53) > 3)
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    HazelnutGripper::Gripper::closeAll();*/
    vTaskDelete(nullptr);
}
