#ifndef __WB_CONST_H__
#define __WB_CONST_H__

#include <Wheeledbase.h>

//Really traveled distance > thought traveled distance -> decrease codewheels radius
//Really rotated angle > thought rotated angle         -> increase axle track
//Turn right when thinking moving forward              -> increase left codewheel radius
//Turn left when thinking moving forward               -> increase right codewheel radius


inline WBConstants wb_consts = {
    .LEFTWHEEL_RADIUS = 23.8125,
    .LEFTWHEEL_CONSTANT = 0.209380534*2,
    .LEFTWHEEL_MAXPWM = 1.0,
    .RIGHTWHEEL_RADIUS = 23.8125,
    .RIGHTWHEEL_CONSTANT = 0.209380534*2,
    .RIGHTWHEEL_MAXPWM = 1.0,
    .LEFTCODEWHEEL_COUNTSPERREV = (10000/2),
    .RIGHTCODEWHEEL_COUNTSPERREV = (10000/2),
    .LEFTCODEWHEEL_RADIUS = 22.78,
    .RIGHTCODEWHEEL_RADIUS = 22.767,

    .ODOMETRY_AXLETRACK = 209.7622878807068,
    .ODOMETRY_SLIPPAGE = 0,

    .VELOCITYCONTROL_AXLETRACK = 125.0,//201.5
    .VELOCITYCONTROL_MAXLINACC = 250,
    .VELOCITYCONTROL_MAXLINDEC = 250,
    .VELOCITYCONTROL_MAXANGACC = PI/3,
    .VELOCITYCONTROL_MAXANGDEC = PI/3,
    .VELOCITYCONTROL_SPINSHUTDOWN = false,

    /*---- LINEAR VELOCITIES PID  ----*/

    .LINVELPID_KP = 1.3,
    .LINVELPID_KI = 2.3,
    .LINVELPID_KD = 0,

    /*
    .LINVELPID_KP = 1.4,
    .LINVELPID_KI = 3.2,
    .LINVELPID_KD = 0,*/

    .LINVELPID_MINOUTPUT = -300,
    .LINVELPID_MAXOUTPUT = 300,

    /*---- ANGULAR VELOCITIES PID ----*/
    .ANGVELPID_KP = 3, //.5 3  0.8,
    .ANGVELPID_KI = 3,//.1 1.5   0.5,
    .ANGVELPID_KD = 0,

    .ANGVELPID_MINOUTPUT = -2*PI/3,
    .ANGVELPID_MAXOUTPUT = 2*PI/3,

    /*---- POSITION PID ----*/
    .POSITIONCONTROL_LINVELKP = 2.2,
    .POSITIONCONTROL_ANGVELKP = 2.5,

    .POSITIONCONTROL_LINVELMAX = 700,
    .POSITIONCONTROL_ANGVELMAX = 10,
    .POSITIONCONTROL_LINPOSTHRESHOLD = 6,
    .POSITIONCONTROL_ANGPOSTHRESHOLD = 0.10000000149011612,
    .PUREPURSUIT_LOOKAHEAD = 235.0,
    .PUREPURSUIT_LOOKAHEADBIS = 200.0,

    // Timesteps
    .ODOMETRY_TIMESTEP = 20e-3,
    .PID_CONTROLLERS_TIMESTEP = 20e-3,
    .POSITIONCONTROL_TIMESTEP = 20e-3,

    // DC motors driver
    .LEFT_MOTOR_EN = PD1,
    .LEFT_MOTOR_PWM = PC7,
    .LEFT_MOTOR_DIR = PD3,
    .RIGHT_MOTOR_EN = PD0,
    .RIGHT_MOTOR_PWM = PC6,
    .RIGHT_MOTOR_DIR = PD2,
    .DRIVER_RESET = PC11,
    .DRIVER_FAULT = PC12,
};

#endif // __WB_CONST_H__
