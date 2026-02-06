#include <Arduino.h>
#include <Logger.h>

#include "Codewheel.h"
#include "ihm/ihm.h"


Logger main_logs = Logger("MAIN"); //Cf /lib, fonction pratique => normalise le format des logs
using namespace ihm; //Simplifie l'ecriture des fonctions ihm (without préfixe)

float CountTicksCodeurs(){
    return (float)(Codewheel::getCounter() - m_startCounter);
}    
    
float getAngleLeftWheel(){
    return (float) 360*CountTicksCodeurs()/m_countsPerRev;
}

void loop(){
    while (true){
        if (etat_jaune()){
            main_logs.log(INFO_LEVEL, "Veuillez position le robot, puis appyer sur jaune. Il va avancer d'environ 50cm\n");
            main_logs.log(GOOD_LEVEL,"Départ\n");
            
            //Il avance d'environ 50cm, jsp comment faire
            
            main_logs.log(GOOD_LEVEL,"Veuillez rentrer exactement la distance parcourue (en cm):\n");
            if(Serial.available()>0){
                float distanceLeftWheel = Serial.parseFloat();
                Serial.println(distanceLeftWheel);
            }
            //Fonction similaire à getTravelDistance definie dans codewhelle et utilisé dans odométrie
            //Mais je ne comprends pas "depuis le dernier Codewheel::reset ou Codewheel::restart", donc je l'ai réecrite
            NewWheelRadius = distanceLeftWheel/getAngleLeftWheel();
            
            leftWheel.setWheelRadius(NewWheelRadius);
            break;
        }
    }
        
    
        /*if (etat_bleu()){
            write_default_params();
            break;
        }

void write_default_params() {
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