#ifndef __WB_CONST_H__
#define __WB_CONST_H__

//Really traveled distance > thought traveled distance -> decrease codewheels radius
//Really rotated angle > thought rotated angle         -> increase axle track
//Turn right when thinking moving forward              -> increase left codewheel radius
//Turn left when thinking moving forward               -> increase right codewheel radius

inline struct constants
{
    const float LEFTWHEEL_RADIUS = 23.8125;
    const float LEFTWHEEL_CONSTANT = 0.209380534;
    const float LEFTWHEEL_MAXPWM = 1.0;
    const float RIGHTWHEEL_RADIUS = 23.8125;
    const float RIGHTWHEEL_CONSTANT = 0.209380534;
    const float RIGHTWHEEL_MAXPWM = 1.0;
    const long LEFTCODEWHEEL_COUNTSPERREV = -(10000/2); //TODO: Fix/source problem this /2
    const long RIGHTCODEWHEEL_COUNTSPERREV = (10000/2);
    const float LEFTCODEWHEEL_RADIUS = 22.78;
    const float RIGHTCODEWHEEL_RADIUS = 22.767;

    const float ODOMETRY_AXLETRACK = 209.7622878807068;
    const float ODOMETRY_SPLIPPAGE = 0;

    const float VELOCITYCONTROL_AXLETRACK = 125.0;//201.5
    const float VELOCITYCONTROL_MAXLINACC = 500;
    const float VELOCITYCONTROL_MAXLINDEC = 1000;
    const float VELOCITYCONTROL_MAXANGACC = 3.14/2;
    const float VELOCITYCONTROL_MAXANGDEC = 6.28;
    const bool VELOCITYCONTROL_SPINSHUTDOWN = false;

    /*---- LINEAR VELOCITIES PID  ----*/
    const float LINVELPID_KP = 1.85;
    const float LINVELPID_KI = 35.0;
    const float LINVELPID_KD = 0.0;

    const float LINVELPID_MINOUTPUT = -1000;
    const float LINVELPID_MAXOUTPUT = 1000;

    /*---- ANGULAR VELOCITIES PID ----*/
    const float ANGVELPID_KP = 3;
    const float ANGVELPID_KI = 15.0;
    const float ANGVELPID_KD = 0.0;

    const float ANGVELPID_MINOUTPUT = -18.0278/2;
    const float ANGVELPID_MAXOUTPUT = 18.0278/2;

    /*---- POSITION PID ----*/
    const float POSITIONCONTROL_LINVELKP = 2.2;
    const float POSITIONCONTROL_ANGVELKP = 2.5;

    const float POSITIONCONTROL_LINVELMAX = 700;
    const float POSITIONCONTROL_ANGVELMAX = 10;
    const float POSITIONCONTROL_LINPOSTHRESHOLD = 6;
    const float POSITIONCONTROL_ANGPOSTHRESHOLD = 0.10000000149011612;
    const float PUREPURSUIT_LOOKAHEAD = 235.0;
    const float PUREPURSUIT_LOOKAHEADBIS = 200.0;

    // Timesteps
    const float ODOMETRY_TIMESTEP = 20e-3;
    const float PID_CONTROLLERS_TIMESTEP = 20e-3;
    const float POSITIONCONTROL_TIMESTEP = 20e-3;

    // DC motors driver
    const int LEFT_MOTOR_EN = PB13;
    const int LEFT_MOTOR_PWM = PE11;
    const int LEFT_MOTOR_DIR = PF4;
    const int RIGHT_MOTOR_EN = PB15;
    const int RIGHT_MOTOR_PWM = PE9;
    const int RIGHT_MOTOR_DIR = PF5;
    const int DRIVER_RESET = PA15;
    const int DRIVER_FAULT = PB12;
} wb_consts;

#endif // __WB_CONST_H__
