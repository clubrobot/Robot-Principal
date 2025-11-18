#include <Arduino.h>
#include "wb_thread.h"

//Declare all modules
DCMotorsDriver driver;
DCMotor leftWheel;
DCMotor rightWheel;

TIM_HandleTypeDef htim23;//Right
TIM_HandleTypeDef htim24;//Left

Codewheel leftCodewheel(&htim23);
Codewheel rightCodewheel(&htim24);

Odometry odometry;

VelocityController velocityControl;
#if ENABLE_VELOCITYCONTROLLER_LOGS
VelocityControllerLogs controllerLogs;
#endif // ENABLE_VELOCITYCONTROLLER_LOGS

PID linVelPID;
PID angVelPID;

PositionController::PositionController positionControl;

PurePursuit purePursuit;
TurnOnTheSpot turnOnTheSpot;

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

    PositionController::setVelLimits(&positionControl, wb_consts.POSITIONCONTROL_LINVELMAX, wb_consts.POSITIONCONTROL_ANGVELMAX);
    PositionController::setPosThresholds(&positionControl, wb_consts.POSITIONCONTROL_LINPOSTHRESHOLD, wb_consts.POSITIONCONTROL_ANGPOSTHRESHOLD);
    purePursuit.setLookAhead(wb_consts.PUREPURSUIT_LOOKAHEAD);
    purePursuit.setLookAheadBis(wb_consts.PUREPURSUIT_LOOKAHEADBIS);
}


void codewheels_setup(){
    //--------TIM23
    TIM_Encoder_InitTypeDef sConfig23 = {0};
    TIM_MasterConfigTypeDef sMasterConfig23 = {0};
    GPIO_InitTypeDef GPIO_InitStruct23 = {0};
    __HAL_RCC_TIM23_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    /**TIM23 GPIO Configuration
    PF6     ------> TIM23_CH1
    PF7     ------> TIM23_CH2
    */
    GPIO_InitStruct23.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct23.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct23.Pull = GPIO_NOPULL;
    GPIO_InitStruct23.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct23.Alternate = GPIO_AF13_TIM23;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct23);

    htim23.Instance = TIM23;
    htim23.Init.Prescaler = 0;
    htim23.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim23.Init.Period = 4294967295;
    htim23.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim23.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    sConfig23.EncoderMode = TIM_ENCODERMODE_TI1;
    sConfig23.IC1Polarity = TIM_ICPOLARITY_RISING;
    sConfig23.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig23.IC1Prescaler = TIM_ICPSC_DIV1;
    sConfig23.IC1Filter = 0;
    sConfig23.IC2Polarity = TIM_ICPOLARITY_RISING;
    sConfig23.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig23.IC2Prescaler = TIM_ICPSC_DIV1;
    sConfig23.IC2Filter = 0;

    if (HAL_TIM_Encoder_Init(&htim23, &sConfig23) != HAL_OK){
        Error_Handler();//Not good
    }
    sMasterConfig23.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig23.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim23, &sMasterConfig23) != HAL_OK){
        Error_Handler();//Not good
    }

    HAL_TIM_Encoder_Start_IT(&htim23, TIM_CHANNEL_ALL);

    //--------TIM24
    TIM_Encoder_InitTypeDef sConfig24 = {0};
    TIM_MasterConfigTypeDef sMasterConfig24 = {0};
    GPIO_InitTypeDef GPIO_InitStruct24 = {0};
    __HAL_RCC_TIM24_CLK_ENABLE();
    //__HAL_RCC_GPIOF_CLK_ENABLE(); Already enabled
    /**TIM24 GPIO Configuration
    PF11     ------> TIM24_CH1
    PF12     ------> TIM24_CH2
    */
    GPIO_InitStruct24.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct24.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct24.Pull = GPIO_NOPULL;
    GPIO_InitStruct24.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct24.Alternate = GPIO_AF14_TIM24;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct24);

    htim24.Instance = TIM24;
    htim24.Init.Prescaler = 0;
    htim24.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim24.Init.Period = 4294967295;
    htim24.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim24.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    sConfig24.EncoderMode = TIM_ENCODERMODE_TI1;
    sConfig24.IC1Polarity = TIM_ICPOLARITY_RISING;
    sConfig24.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig24.IC1Prescaler = TIM_ICPSC_DIV1;
    sConfig24.IC1Filter = 0;
    sConfig24.IC2Polarity = TIM_ICPOLARITY_RISING;
    sConfig24.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig24.IC2Prescaler = TIM_ICPSC_DIV1;
    sConfig24.IC2Filter = 0;

    if (HAL_TIM_Encoder_Init(&htim24, &sConfig24) != HAL_OK){
        Error_Handler();//Not good
    }
    sMasterConfig24.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig24.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim24, &sMasterConfig24) != HAL_OK){
        Error_Handler();//Not good
    }

    HAL_TIM_Encoder_Start_IT(&htim24, TIM_CHANNEL_ALL);

    rightCodewheel.m_htim = &htim23;
    rightCodewheel.m_tim = TIM23;
    leftCodewheel.m_htim = &htim24;
    leftCodewheel.m_tim = TIM24;
}

// Setup
void wb_setup(){
    //TODO once
    write_default_params();
    // DC motors wheels
    driver.attach(wb_consts.DRIVER_RESET, wb_consts.DRIVER_FAULT);
    driver.reset();

    leftWheel.attach(wb_consts.LEFT_MOTOR_EN, wb_consts.LEFT_MOTOR_PWM, wb_consts.LEFT_MOTOR_DIR);
    rightWheel.attach(wb_consts.RIGHT_MOTOR_EN, wb_consts.RIGHT_MOTOR_PWM, wb_consts.RIGHT_MOTOR_DIR);

    // Codewheels
    codewheels_setup();

    leftCodewheel.reset();
    rightCodewheel.reset();

    // Odometry
    odometry.setCodewheels(leftCodewheel, rightCodewheel);
    odometry.setTimestep(wb_consts.ODOMETRY_TIMESTEP);
    odometry.enable();

    // Engineering control
    velocityControl.setWheels(leftWheel, rightWheel);
    velocityControl.setPID(linVelPID, angVelPID);
    velocityControl.disable();

    // const float maxLinVel = min(leftWheel.getMaxVelocity(), rightWheel.getMaxVelocity());
    //const float maxAngVel = min(leftWheel.getMaxVelocity(), rightWheel.getMaxVelocity()) * 2 / VELOCITYCONTROL_AXLETRACK_VALUE;

    //linVelPID.setOutputLimits(-maxLinVel, maxLinVel);
    //angVelPID.setOutputLimits(-maxAngVel, maxAngVel);

#if ENABLE_VELOCITYCONTROLLER_LOGS
    controllerLogs.setController(velocityControl);
    controllerLogs.setTimestep(VELOCITYCONTROLLER_LOGS_TIMESTEP);
    controllerLogs.enable();
#endif // VELOCITYENABLE_CONTROLLER_LOGS

    // Position control
    positionControl.m_timestep = wb_consts.POSITIONCONTROL_TIMESTEP;
    PositionController::disable(&positionControl);

    //purePursuit.load(PUREPURSUIT_ADDRESS);
}

void wb_loop(void *pvParameters){
for(;;) {
    // Update odometry
    if (odometry.update()){
        PositionController::setPosInput(&positionControl, *odometry.getPosition());
        velocityControl.setInputs(odometry.getLinVel(), odometry.getAngVel());
    }
    // Compute trajectory
    if (positionControl.update())
    {
        float linVelSetpoint = PositionController::getLinVelSetpoint(&positionControl);
        float angVelSetpoint = PositionController::getAngVelSetpoint(&positionControl);
        velocityControl.setSetpoints(linVelSetpoint, angVelSetpoint);
    }
        // Integrate engineering control
#if ENABLE_VELOCITYCONTROLLER_LOGS
        if (velocityControl.update())
            controllerLogs.update();
#else
        velocityControl.update();
#endif // ENABLE_VELOCITYCONTROLLER_LOGS
}
}
