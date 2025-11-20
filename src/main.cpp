#include <Arduino.h>
#include <list>
#include <STM32FreeRTOS.h>
#include <Wheeledbase.h>

#include <My_Clock.h>
#include <PrintfSupport.h>
#include <variables_globales.h>
#include <Logger.h>
#include <Musique.h>
#include <Teleplot.h>
#include <team2025/TacheBanderole.h>

#include "ihm/ihm.h"
#include "wheeledbase/wb_thread.h"
#include "sensors/SensorsThread.h"
#include "decisions/Automate.h"
#include "include/SensorArray.h"
#include "yeux/yeuxThread.h"

#include "team2025/ListeActionneurs.h"

#define DEBUG 1
#define TEST_NO_FREERTOS false //Ignore le FreeRTOS et se comporte comme un arduino classique

TIM_HandleTypeDef htim16;
TIM_HandleTypeDef htim17;

TaskHandle_t hl_wb = nullptr;
TaskHandle_t hl_sens = nullptr;
TaskHandle_t  hl_robot = nullptr;


//timer initialisation
static void MX_TIM16_Init()
{

    htim16.Instance = TIM16;
    htim16.Init.Prescaler = 550 - 1;
    htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim16.Init.Period = 65535;
    htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim16.Init.RepetitionCounter = 0;
    htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
    {
        Error_Handler();
    }
}

static void MX_TIM17_Init()
{
    htim17.Instance = TIM17;
    htim17.Init.Prescaler = 550 - 1;
    htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim17.Init.Period = 65535;
    htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim17.Init.RepetitionCounter = 0;
    htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
    {
        Error_Handler();
    }
}

//ISR
void wbTimer16IRSHandler(){
    BaseType_t taskWoken = pdFALSE;
    //prvClearInterruptSource(); is in doc but doesn't exists here ? maybe should clear timer directly

    // send notification to the weeeledbase
    vTaskNotifyGiveFromISR(hl_wb,&taskWoken);

    // triggers the scheduler
    portYIELD_FROM_ISR(taskWoken);
}

Logger main_logs = Logger("MAIN");
using namespace ihm;
void procedure_demarrage(){
    main_logs.log(INFO_LEVEL, "Mise à zero des actionneurs\n");
    //TODO

    main_logs.log(INFO_LEVEL, "Sélectionez une équipe\n");
    led_jaune(HIGH);
    led_bleu(HIGH);
    while (true){
        if (etat_jaune()){
            main_logs.log(GOOD_LEVEL,"Equipe Jaune !\n");
            yeuxThread::yeux.println("Smerci Aisprid  *75$robo jaune 54");
            led_bleu(LOW);
            my_team = TEAM_JAUNE;
            break;
        }
        if (etat_bleu()){
            main_logs.log(GOOD_LEVEL,"Equipe Bleu!\n");
            led_jaune(LOW);
            my_team=TEAM_BLEU;yeuxThread::yeux.println("Smerci Aisprid  *75$robo bleu 54");
            break;
        }
    }

    main_logs.log(INFO_LEVEL,"Veuillez mettre le robot en place et appuyer sur vert; rouge pour mettre la banderole!\n");

    unsigned int prev_vert = millis();
    unsigned int prev_rouge = millis();
    bool last_state_rouge=etat_rouge();

    while (!etat_vert()){
        unsigned int curr_time = millis();
        if (curr_time-prev_vert > 500){
            prev_vert = curr_time;
            led_vert();
        }
        if(curr_time-prev_rouge>100){
            prev_rouge = curr_time;
            led_rouge();
        }
        bool state_rouge = etat_rouge();
        if (state_rouge!=last_state_rouge){
            printf("ENTRE\n");
            if(state_rouge){
                listeActionneur::mise_banderole();
            }else{
                listeActionneur::haut_banderole();
            }
        }
        last_state_rouge=state_rouge;
    }
    led_vert(LOW);
    Automate::init(my_team);
    main_logs.log(WARNING_LEVEL,"Le robot est armé!\n");

    //Detect tirette
    while(etat_tirette()==1){}
    main_logs.log(WARNING_LEVEL,"tirette mise (dans le trou de Boris) !\n");
    while (etat_tirette()==0){}
    main_logs.log(WARNING_LEVEL,"tirette enlevée (du trou de Boris) !\n");
    yeuxThread::yeux.println("Smerci Aisprid  *75$robo arme 54");

}


/**
TODO:
Valeurs servo limites  OK
Régler PID/Accel => Logger OK
Procédure démarrage Preque OK
Tache empiler
Tache banderole OK
check reset if vl53 are flshed !!!!!!!!!!!!!!
*/


//Setup de base


void setup(){
    if (HAL_Init()!= HAL_OK){
        Error_Handler();
    }

    DWT_Init(); //Très important
    MX_TIM16_Init();
    MX_TIM17_Init();

#if DEBUG
    PrintfSupport::begin(PRINTF_BAUD);
    main_logs.log(WARNING_LEVEL, "Debug enabled at %d baud\n", PRINTF_BAUD);
    //main_logs.log(INFO_LEVEL, "Printing WheeledBase Params\n");
    //Wheeledbase::PRINT_PARAMS();
#endif
    //Musique myBeeper = Musique(PA6, 10);
    //myBeeper.playSheetMusic(cantina);
    match_started= false;
    yeuxThread::yeux_setup();
    SensorsThread::Init();
    yeuxThread::yeux.println("$A3*100$SENSORS OK");
    listeActionneur::Init();
    yeuxThread::yeux.println("SA3*100$ACTIO OK");
    wb_setup();
    yeuxThread::yeux.println("SA3*100$WB OK");
    ServosPCA9685::Init();
    yeuxThread::yeux.println("Smerci Aisprid  *75$score 54");
    match_started= false;
    main_logs.log(GOOD_LEVEL,"Wheeledbase & Actionneurs & Sensors & IHM initied\n");
    //procedure_demarrage();
    //listeActionneur::ascenseur.setEndlessMode(true);

#if TEST_NO_FREERTOS
    main_logs.log(WARNING_LEVEL,"Not using FreeRTOS\n");
    return;
#endif
    main_logs.log(GOOD_LEVEL,"Using FreeRTOS\n");
    //Setup FreeRTOS

    //TaskHandle_t  hl_wb = nullptr;

    BaseType_t ret_wb = xTaskCreate(
                wb_loop,       /* Function that implements the task. */
                "Wheeledbase loop",          /* Text name for the task. */
                10000,      /* Stack size in words, not bytes. */
                nullptr,    /* Parameter passed into the task. */
                5,//Prio max
                &hl_wb );      /* Used to pass out the created task's handle. */

    if(ret_wb!=pdPASS) {Error_Handler()}

    //TaskHandle_t  hl_sens = nullptr;
    BaseType_t ret_sens= xTaskCreate(
                 SensorsThread::Thread,       /* Function that implements the task. */
                "Sensors loop",          /* Text name for thedi task. */
                 10000,      /* Stack size in words, not bytes. */
                nullptr,    /* Parameter passed into the task. */
                 5,//Prio nulle à chier
                 &hl_sens );      /* Used to pass out the created task's handle. */

     if(ret_sens!=pdPASS) {Error_Handler()}

    //TaskHandle_t  hl_robot = nullptr;

    BaseType_t ret_robot = xTaskCreate(
                Automate::play_match,       /* Function that implements the task. */
                "Robot loop",          /* Text name for the task. */
                10000,      /* Stack size in words, not bytes. */
                (void *) procedure_demarrage,    /* Parameter passed into the task. */
                5,//Prio un peu mieux
                &hl_robot );      /* Used to pass out the created task's handle. */

    if(ret_robot!=pdPASS) {Error_Handler()}

    TaskHandle_t  hl_yeux= nullptr;

    // BaseType_t ret_yeux = xTaskCreate(
    //         yeuxThread::yeux_loop,       /* Function that implements the task. */
    //         "UwU",          /* Text name for the task. */
    //         10000,      /* Stack size in words, not bytes. */
    //         NULL,    /* Parameter passed into the task. */
    //         5,//Prio un peu mieux
    //         &hl_yeux );      /* Used to pass out the created task's handle. */
    //
    // if(ret_yeux!=pdPASS) {Error_Handler()}

    main_logs.log(GOOD_LEVEL,"Starting tasks\n");
    vTaskStartScheduler();//On commence FreeRTOS
    //On devrait pas être là; Uh oh
    main_logs.log(ERROR_LEVEL,"FreeRTOS crashed\n");
    Error_Handler();
}
float i=0;
void loop(){
    return;
    i=i+0.01;
    teleplot.add_variable_float_2decimal("sin", sin(i));
    if (i>=2*PI) i=0;
    //printf("Pince Droite %f\tPince Gauche %f\t Banderole %f\t\n", listeActionneur::pince_droite.readPosition(), listeActionneur::pince_gauche.readPosition(), listeActionneur::banderole.readPosition());
}

