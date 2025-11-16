#ifndef __WB_CONST_H__
#define __WB_CONST_H__

//Really traveled distance > thought traveled distance -> decrease codewheels radius
//Really rotated angle > thought rotated angle         -> increase axle track
//Turn right when thinking moving forward              -> increase left codewheel radius
//Turn left when thinking moving forward               -> increase right codewheel radius

inline struct constants
{
    float LEFTWHEEL_RADIUS = 23.8125;
    float LEFTWHEEL_CONSTANT = 0.209380534;
    float LEFTWHEEL_MAXPWM = 1.0;
    float RIGHTWHEEL_RADIUS = 23.8125;
    float RIGHTWHEEL_CONSTANT = 0.209380534;
    float RIGHTWHEEL_MAXPWM = 1.0;
    long LEFTCODEWHEEL_COUNTSPERREV = -(10000/2); //TODO: Fix/source problem this /2
    long RIGHTCODEWHEEL_COUNTSPERREV = (10000/2);
    float LEFTCODEWHEEL_RADIUS = 22.78;
    float RIGHTCODEWHEEL_RADIUS = 22.767;

    float ODOMETRY_AXLETRACK = 209.7622878807068;
    float ODOMETRY_SPLIPPAGE = 0;

    float VELOCITYCONTROL_AXLETRACK = 125.0;//201.5
    float VELOCITYCONTROL_MAXLINACC = 500;
    float VELOCITYCONTROL_MAXLINDEC = 1000;
    float VELOCITYCONTROL_MAXANGACC = 3.14/2;
    float VELOCITYCONTROL_MAXANGDEC = 6.28;
    bool VELOCITYCONTROL_SPINSHUTDOWN = false;

    /*---- LINEAR VELOCITIES PID  ----*/
    float LINVELPID_KP = 1.85;
    float LINVELPID_KI = 35.0;
    float LINVELPID_KD = 0.0;

    float LINVELPID_MINOUTPUT = -1000;
    float LINVELPID_MAXOUTPUT = 1000;

    /*---- ANGULAR VELOCITIES PID ----*/
    float ANGVELPID_KP = 3;
    float ANGVELPID_KI = 15.0;
    float ANGVELPID_KD = 0.0;

    float ANGVELPID_MINOUTPUT = -18.0278/2;
    float ANGVELPID_MAXOUTPUT = 18.0278/2;

    /*---- POSITION PID ----*/
    float POSITIONCONTROL_LINVELKP = 2.2;
    float POSITIONCONTROL_ANGVELKP = 2.5;

    float POSITIONCONTROL_LINVELMAX = 700;
    float POSITIONCONTROL_ANGVELMAX = 10;
    float POSITIONCONTROL_LINPOSTHRESHOLD = 6;
    float POSITIONCONTROL_ANGPOSTHRESHOLD = 0.10000000149011612;
    float PUREPURSUIT_LOOKAHEAD = 235.0;
    float PUREPURSUIT_LOOKAHEADBIS = 200.0;

    // Timesteps
    float ODOMETRY_TIMESTEP = 20e-3;
    float PID_CONTROLLERS_TIMESTEP = 20e-3;
    float POSITIONCONTROL_TIMESTEP = 20e-3;

    // DC motors driver
    int LEFT_MOTOR_EN = PB13;
    int LEFT_MOTOR_PWM = PE11;
    int LEFT_MOTOR_DIR = PF4;
    int RIGHT_MOTOR_EN = PB15;
    int RIGHT_MOTOR_PWM = PE9;
    int RIGHT_MOTOR_DIR = PF5;
    int DRIVER_RESET = PA15;
    int DRIVER_FAULT = PB12;
} wb_consts;

#endif // __WB_CONST_H__
