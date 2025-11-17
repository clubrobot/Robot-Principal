#ifndef __WB_CONST_H__
#define __WB_CONST_H__

#include <Wheeledbase.h>

//Really traveled distance > thought traveled distance -> decrease codewheels radius
//Really rotated angle > thought rotated angle         -> increase axle track
//Turn right when thinking moving forward              -> increase left codewheel radius
//Turn left when thinking moving forward               -> increase right codewheel radius


inline WBConstants wb_consts = {
    .LEFTWHEEL_RADIUS = 23.8125,
    .LEFTWHEEL_CONSTANT = 0.209380534,
    .LEFTWHEEL_MAXPWM = 1.0,
    .RIGHTWHEEL_RADIUS = 23.8125,
    .RIGHTWHEEL_CONSTANT = 0.209380534,
    .RIGHTWHEEL_MAXPWM = 1.0,
    .LEFTCODEWHEEL_COUNTSPERREV = -(10000/2), //TODO: Fix/source problem this /2
    .RIGHTCODEWHEEL_COUNTSPERREV = (10000/2),
    .LEFTCODEWHEEL_RADIUS = 22.78,
    .RIGHTCODEWHEEL_RADIUS = 22.767,

    .ODOMETRY_AXLETRACK = 209.7622878807068,
    .ODOMETRY_SLIPPAGE = 0,

    .VELOCITYCONTROL_AXLETRACK = 125.0,//201.5
    .VELOCITYCONTROL_MAXLINACC = 500,
    .VELOCITYCONTROL_MAXLINDEC = 1000,
    .VELOCITYCONTROL_MAXANGACC = 3.14/2,
    .VELOCITYCONTROL_MAXANGDEC = 6.28,
    .VELOCITYCONTROL_SPINSHUTDOWN = false,

    /*---- LINEAR VELOCITIES PID  ----*/
    .LINVELPID_KP = 1.85,
    .LINVELPID_KI = 35.0,
    .LINVELPID_KD = 0.0,

    .LINVELPID_MINOUTPUT = -1000,
    .LINVELPID_MAXOUTPUT = 1000,

    /*---- ANGULAR VELOCITIES PID ----*/
    .ANGVELPID_KP = 3,
    .ANGVELPID_KI = 15.0,
    .ANGVELPID_KD = 0.0,

    .ANGVELPID_MINOUTPUT = -18.0278/2,
    .ANGVELPID_MAXOUTPUT = 18.0278/2,

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
    .LEFT_MOTOR_EN = PB13,
    .LEFT_MOTOR_PWM = PE11,
    .LEFT_MOTOR_DIR = PF4,
    .RIGHT_MOTOR_EN = PB15,
    .RIGHT_MOTOR_PWM = PE9,
    .RIGHT_MOTOR_DIR = PF5,
    .DRIVER_RESET = PA15,
    .DRIVER_FAULT = PB12,
};

#endif // __WB_CONST_H__
