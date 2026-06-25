//
// Created by boris on 28/10/2024.
//
/**
 * @file Wheeledbase.h
 * @ingroup wheeledbase
 * @ingroup lib
 * @brief Fonctions de convénience pour faire les déplacements facilement
 */
#ifndef WHEELEDBASE_H
#define WHEELEDBASE_H

#include "WheelMotor.h"
#include "Codewheel.h"
#include "Odometry.h"
#include "PID.h"
#include "VelocityController.h"
#include "PositionController.h"
#include "PurePursuit.h"
#include "TurnOnTheSpot.h"
#include "mathutils.h"
#include <math.h>

#include "DRV8844.h"
#include "Logger.h"

// Parameters identifiers
/**
 * @defgroup wb_global_define Des identifiants
 * @ingroup wheeledbase
 * @ingroup globals
 * @brief Les valeurs des identifiants des constantes
 * @{
 */
//TODO: (2026-06-25) Changer ce système de con
#define LEFTWHEEL_RADIUS_ID             0x10
#define LEFTWHEEL_CONSTANT_ID           0x11
#define LEFTWHEEL_MAXPWM_ID             0x12
#define RIGHTWHEEL_RADIUS_ID            0x20
#define RIGHTWHEEL_CONSTANT_ID          0x21
#define RIGHTWHEEL_MAXPWM_ID            0x22
#define LEFTCODEWHEEL_RADIUS_ID         0x40
#define LEFTCODEWHEEL_COUNTSPERREV_ID   0x41
#define RIGHTCODEWHEEL_RADIUS_ID        0x50
#define RIGHTCODEWHEEL_COUNTSPERREV_ID  0x51
#define ODOMETRY_AXLETRACK_ID           0x60
#define ODOMETRY_SLIPPAGE_ID            0x61
#define VELOCITYCONTROL_AXLETRACK_ID    0x80
#define VELOCITYCONTROL_MAXLINACC_ID    0x81
#define VELOCITYCONTROL_MAXLINDEC_ID    0x82
#define VELOCITYCONTROL_MAXANGACC_ID    0x83
#define VELOCITYCONTROL_MAXANGDEC_ID    0x84
#define VELOCITYCONTROL_SPINSHUTDOWN_ID 0x85
#define LINVELPID_KP_ID                 0xA0
#define LINVELPID_KI_ID                 0xA1
#define LINVELPID_KD_ID                 0xA2
#define LINVELPID_MINOUTPUT_ID          0xA3
#define LINVELPID_MAXOUTPUT_ID          0xA4
#define ANGVELPID_KP_ID                 0xB0
#define ANGVELPID_KI_ID                 0xB1
#define ANGVELPID_KD_ID                 0xB2
#define ANGVELPID_MINOUTPUT_ID          0xB3
#define ANGVELPID_MAXOUTPUT_ID          0xB4
#define POSITIONCONTROL_LINVELKP_ID     0xD0
#define POSITIONCONTROL_ANGVELKP_ID     0xD1
#define POSITIONCONTROL_LINVELMAX_ID    0xD2
#define POSITIONCONTROL_ANGVELMAX_ID    0xD3
#define POSITIONCONTROL_LINPOSTHRESHOLD_ID  0xD4
#define POSITIONCONTROL_ANGPOSTHRESHOLD_ID  0xD5
#define PUREPURSUIT_LOOKAHED_ID         0xE0
#define PUREPURSUIT_LOOKAHEADBIS_ID     0xE2
///@}
/**
 * @defgroup wb_slowdown_define Paramètres de ralentissement du robot
 * @ingroup wheeledbase
 * @ingroup globals
 * @brief Les paramètres de ralentissement du robot à la fin de goto
 * @{
 */
#define SLOWDOWN_FACTOR                 0.5
#define SLOWDOWN_DISTANCE               0
#define ALIGN_DISTANCE                  130
///@}

struct WBConstants
{
    const float LEFTWHEEL_RADIUS;
    const float LEFTWHEEL_CONSTANT;
    const float LEFTWHEEL_MAXPWM;
    const float RIGHTWHEEL_RADIUS;
    const float RIGHTWHEEL_CONSTANT;
    const float RIGHTWHEEL_MAXPWM;
    const long LEFTCODEWHEEL_COUNTSPERREV;
    const long RIGHTCODEWHEEL_COUNTSPERREV;
    const float LEFTCODEWHEEL_RADIUS;
    const float RIGHTCODEWHEEL_RADIUS;

    const float ODOMETRY_AXLETRACK;
    const float ODOMETRY_SLIPPAGE;

    const float VELOCITYCONTROL_AXLETRACK;
    const float VELOCITYCONTROL_MAXLINACC;
    const float VELOCITYCONTROL_MAXLINDEC;
    const float VELOCITYCONTROL_MAXANGACC;
    const float VELOCITYCONTROL_MAXANGDEC;
    const bool VELOCITYCONTROL_SPINSHUTDOWN;

    /*---- LINEAR VELOCITIES PID  ----*/
    const float LINVELPID_KP;
    const float LINVELPID_KI;
    const float LINVELPID_KD;

    const float LINVELPID_MINOUTPUT;
    const float LINVELPID_MAXOUTPUT;

    /*---- ANGULAR VELOCITIES PID ----*/
    const float ANGVELPID_KP;
    const float ANGVELPID_KI;
    const float ANGVELPID_KD;

    const float ANGVELPID_MINOUTPUT;
    const float ANGVELPID_MAXOUTPUT;

    /*---- POSITION PID ----*/
    const float POSITIONCONTROL_LINVELKP;
    const float POSITIONCONTROL_ANGVELKP;

    const float POSITIONCONTROL_LINVELMAX;
    const float POSITIONCONTROL_ANGVELMAX;
    const float POSITIONCONTROL_LINPOSTHRESHOLD;
    const float POSITIONCONTROL_ANGPOSTHRESHOLD;
    const float PUREPURSUIT_LOOKAHEAD;
    const float PUREPURSUIT_LOOKAHEADBIS;

    // Timesteps
    const float ODOMETRY_TIMESTEP;
    const float PID_CONTROLLERS_TIMESTEP;
    const float POSITIONCONTROL_TIMESTEP;

    // DC motors driver
    const int LEFT_MOTOR_EN;
    const int LEFT_MOTOR_PWM;
    const int LEFT_MOTOR_DIR;
    const int RIGHT_MOTOR_EN;
    const int RIGHT_MOTOR_PWM;
    const int RIGHT_MOTOR_DIR;
    const int DRIVER_RESET;
    const int DRIVER_FAULT;
};

// Global variables
extern DRV8844 driver;
extern WheelMotor leftWheel;
extern WheelMotor rightWheel;

extern Codewheel leftCodewheel;
extern Codewheel rightCodewheel;

extern Odometry odometry;

extern VelocityController velocityControl;

extern PID linVelPID;
extern PID angVelPID;

extern PositionController positionControl;

extern PurePursuit   purePursuit;
extern TurnOnTheSpot turnOnTheSpot;

/**
 * @ingroup libs
 * @ingroup globals
 * @ingroup wheeledbase
 * @brief Le logger pour la base roulante
 */
inline Logger wb_logger = Logger("WHEELEDBASE");

/**
 * @namespace Wheeledbase
 * @ingroup wheeledbase
 * @ingroup libs
 * @brief Fonctions de convénience pour faire les déplacements facilement
 */
namespace  Wheeledbase {
    // Instructions prototypes
    void DISABLE();

    void GOTO_DELTA(float dx, float dy, bool bloquant=true); //bloquant: do we pass at the next step after ?

    void TURNTO_DELTA(float dtheta, bool bloquant=true);

    //void TENTATIVE_POUR_PLUSTARD();

    void SET_OPENLOOP_VELOCITIES(float leftWheelVel, float rightWheelVel);

    void GET_CODEWHEELS_COUNTERS(float *leftCodewheelCounter, float *rightCodewheelCounter);

    void SET_VELOCITIES(float linVelSetpoint, float angVelSetpoint);

    void RESET_PUREPURSUIT();

    void ADD_PUREPURSUIT_WAYPOINT(float x, float y);

    void START_PUREPURSUIT(int8_t direction, float finalAngle);

    void START_TURNONTHESPOT(bool dir, float theta);

    void START_TURNONTHESPOT_DIR(bool dir, float theta);

    void PUREPURSUIT(const Position** waypoints, uint16_t nb_waypoints, char dir, float finalAngle);

    void GOTO(Position* pos, bool alignFirst=true, int8_t dir=PurePursuit::NONE,bool bloquant=true);

    void GOTO_WAYPOINTS(bool alignFirst=true, int8_t dir=PurePursuit::NONE, int nb_waypoints=1, ...);

    void GOTO_WAYPOINTS_ARRAY(Position* positions[], bool alignFirst=true, int8_t dir=PurePursuit::NONE, int nb_waypoints=1);

    void GOTO_FUNCT(Position* pos, void* duringMovingFunct, void* approachFunct, bool alignFirst=true, int8_t dir=PurePursuit::NONE, float finalAngle=MAXFLOAT);

    uint8_t POSITION_REACHED();

    void GET_VELOCITIES_WANTED(float *linOutput, float *angOutput, bool spin=true);

    void SET_POSITION(Position* pos);

    const Position* GET_POSITION();

    void GET_VELOCITIES(float *linVel, float *angVel);

    void SET_PARAMETER_VALUE(byte paramID, float value);

    float GET_PARAMETER_VALUE(byte paramID);

    void PRINT_PARAMS();
};



#endif //WHEELEDBASE_H
