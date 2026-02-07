#include <Arduino.h>
#include <Logger.h>

#include "Codewheel.h"
#include "ihm/ihm.h"
#include "BasicMoveStrategy.h"

extern Codewheel leftCodewheel;
extern Codewheel leftWheel;
extern void addWaypoint(float x, float y);

float distanceLeftWheel;
float NewLeftWheelRadius;
float m_startCounter;

float CountTicksCodeurs(){
    return (float)(leftCodewheel.getCounter() - m_startCounter);
}    
    
float getAngleLeftWheel(){
    return (float) 360*CountTicksCodeurs()/leftCodewheel.getCountsPerRev();
}

void loop(){
    while (true){
        Serial.println("Veuillez appyer sur jaune ou bleu. Le robot va avancer d'environ 50cm\n");
        if (ihm::etat_jaune()){
            m_startCounter = leftCodewheel.getCounter();
            
            Serial.println("Départ\n");
            addWaypoint(50, 0);
            while (!BasicMoveStrategy::getPositionReached()){
                BasicMoveStrategy::computeVelSetpoints(); //Il y a un argument float timestep  ms j'ai pas bien capté
            } //It's way to simple, it may miss some lines of code there, the robot must move forward for 50cm, then we can get the distance parcourue and calculate the new radius of the wheel with the angle parcourue (from codewheel) and the distance parcourue (from user input)
            Serial.println("Arrivé\n");

            Serial.println("Veuillez rentrer exactement la distance parcourue (en cm):\n");
            if(Serial.available()>0){
                distanceLeftWheel = Serial.parseFloat();
                Serial.println(distanceLeftWheel);
            }

            NewLeftWheelRadius = distanceLeftWheel/getAngleLeftWheel(); //Calcul
            leftWheel.setWheelRadius(NewLeftWheelRadius);
            break;
        }
    }
        
    
        /*if (etat_bleu()){
            break();
        }

void setup() { //In all the case we start with an approximation of the constantes
//then we can pass with the bleu or activatre the calibration phase with the yellow button
    leftWheel.setWheelRadius(wb_consts.LEFTWHEEL_RADIUS);
    leftWheel.setConstant(wb_consts.LEFTWHEEL_CONSTANT);
    leftWheel.setMaxPWM(wb_consts.LEFTWHEEL_MAXPWM);
    
    rightWheel.setWheelRadius(wb_consts.RIGHTWHEEL_RADIUS);
    rightWheel.setConstant(wb_consts.RIGHTWHEEL_CONSTANT);
    rightWheel.setMaxPWM(wb_consts.RIGHTWHEEL_MAXPWM);

    leftCodewheel.setWheelRadius(wb_consts.LEFTCODEWHEEL_RADIUS);
    leftCodewheel.setCountsPerRev(wb_consts.LEFTCODEWHEEL_COUNTSPERREV);
    rightCodewheel.setWheelRadius(wb_consts.RIGHTCODEWHEEL_RADIUS);
    rightCodewheel.setCountsPerRev(wb_consts.RIGHTCODEWHEEL_COUNTSPERREV);

    odometry.setAxleTrack(wb_consts.ODOMETRY_AXLETRACK);
    odometry.setSlippage(wb_consts.ODOMETRY_SLIPPAGE);

    velocityControl.setAxleTrack(wb_consts.VELOCITYCONTROL_AXLETRACK);
    velocityControl.setMaxLinAcc(wb_consts.VELOCITYCONTROL_MAXLINACC);
    velocityControl.setMaxLinDec(wb_consts.VELOCITYCONTROL_MAXLINDEC);
    velocityControl.setMaxAngAcc(wb_consts.VELOCITYCONTROL_MAXANGACC);
    velocityControl.setMaxAngDec(wb_consts.VELOCITYCONTROL_MAXANGDEC);
    
    velocityControl.setSpinShutdown(wb_consts.VELOCITYCONTROL_SPINSHUTDOWN);
    linVelPID.setTunings(wb_consts.LINVELPID_KP, wb_consts.LINVELPID_KI, wb_consts.LINVELPID_KD);
    linVelPID.setOutputLimits(wb_consts.LINVELPID_MINOUTPUT, wb_consts.LINVELPID_MAXOUTPUT);

    angVelPID.setTunings(wb_consts.ANGVELPID_KP, wb_consts.ANGVELPID_KI, wb_consts.ANGVELPID_KD);
    angVelPID.setOutputLimits(wb_consts.ANGVELPID_MINOUTPUT, wb_consts.ANGVELPID_MAXOUTPUT);

    positionControl.setVelLimits(wb_consts.POSITIONCONTROL_LINVELMAX, wb_consts.POSITIONCONTROL_ANGVELMAX);
    positionControl.setPosThresholds(wb_consts.POSITIONCONTROL_LINPOSTHRESHOLD, wb_consts.POSITIONCONTROL_ANGPOSTHRESHOLD);
    purePursuit.setLookAhead(wb_consts.PUREPURSUIT_LOOKAHEAD);
    purePursuit.setLookAheadBis(wb_consts.PUREPURSUIT_LOOKAHEADBIS);
}*/