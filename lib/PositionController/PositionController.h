#ifndef __POSITIONCONTROLLER_H__
#define __POSITIONCONTROLLER_H__

#include "PeriodicProcess.h"
#include "Odometry.h"
#include "My_Clock.h"


class AbstractMoveStrategy;

/**
 * @brief Espace de nom support des objets AbstractMoveStrategy.
 *
 * PositionController est le support des AbstractMoveStrategy. C'est à dire qu'il permet de charger ou supprimer une stratégie.
 * Quand PositionController execute une stratégie de mouvement, il va l'executé tous les time_steps pour y obtenir de nouvelles vitesses à suivre.
 * PositionConstroller va égalemenr renseigné la position du robot à AbstractMoveStrategy chargée.
 *
 * @return class PositionController : public PeriodicProcess { public:
 */
namespace PositionController{


/**
 * @brief Structure de PositionController.
 *
 * Structure contenant les variables de PositionController.
 */
    struct PositionController {
        // IO
        Position m_posInput;/*!< Position du robot.*/
        Position m_posSetpoint;/*!< Position à atteindre.*/

        float m_linVelSetpoint;/*!< Vitesse linéaire à atteindre*/
        float m_angVelSetpoint;/*!< Vitesse angulaire à atteindre*/

        // Engineering control tunings
        float m_linVelKp; /*!< Coefficient proportionnel de vitesse linéaire. */
        float m_angVelKp; /*!< Coefficient proportionnel de vitesse angulaire. */
        float m_linVelMax;/*!< Vitesse linéaire max.*/
        float m_angVelMax;/*!< Vitesse angulaire max.*/
        float m_linPosThreshold;/*!< Précision cartésienne. */
        float m_angPosThreshold;/*!< Précision angulaire.*/
        float m_timestep; /*!< Temps entre deux process.*/

        AbstractMoveStrategy* m_moveStrategy;/*!< Stratégie de mouvement utilisée.*/

        Clock* clock; /*!< Horloge pour le calcul du temps écoulé entre deux process.*/
        bool enabled; /*!< Etat du PositionController (activé/désactivé).*/
    };

    /**
     * @brief Active le PositionController.
     * Active le PositionController pour qu'il commence à exécuter la stratégie de mouvement chargée.
     * @param positionController Pointeur vers l'objet PositionController à activer.
     */
    void enable(PositionController* positionController){positionController->enabled = true; positionController->clock->restart();}
    /**
     * @brief Désactive le PositionController.
     * Désactive le PositionController pour qu'il arrête d'exécuter la stratégie de mouvement chargée.
     * @param positionController Pointeur vers l'objet PositionController à désactiver.
     */
    void disable(PositionController* positionController){positionController->enabled = false;}

    /**
     * @brief Charge les nouvelles positions du robot.
     * Charge les nouvelles positions du robot pour les donner à une potentiel AbstractMoveStrategy chargée.
     * @param positionController Pointeur vers l'objet PositionController à modifier.
     * @param posInput Nouvelle objet Position représentant la position du robot.
     */
    void setPosInput(PositionController* positionController, Position posInput){positionController->m_posInput = posInput;}
    /**
     * @brief Charge la position à atteindre.
     *
     * Charge la position à atteindre avec une AbstractMoveStrategy.
     * Cette variable est potentiellement utilisé par l'AbstractMoveStrategy.
     *
     * @param positionController Pointeur vers l'objet PositionController à modifier.
     * @param posSetpoint Position à atteindre
     */
    void setPosSetpoint(PositionController* positionController, Position posSetpoint){positionController->m_posSetpoint = posSetpoint;}

    /**
     * @brief Charge l'angle à atteindre.
     *
     * Change l'angle objectif de l'objet Position.
     * Remarque : les coordonnées objectif reste les mêmes.
     *
     * @param theta Nouvelle angle objectif.
     */
    void setThetaSetPoint(PositionController* positionController, float theta){positionController->m_posSetpoint.theta = theta;}
    /**
     * @brief Retourne la vitesse linéaire à atteindre.
     *
     * Cette méthode retourne la vitesse linéaire que l'AbstractMoveStrategy souhaite atteindre.
     *
     * @param positionController Pointeur vers l'objet PositionController à interroger.
     * @return Vitesse à atteindre en mm/s.
     */
    float getLinVelSetpoint(const PositionController* positionController){return positionController->m_linVelSetpoint;}
    /**
     * @brief Retourne la vitesse angulaire à atteindre.
     *
     * Cette méthode retourne la vitesse angulaire que l'AbstractMoveStrategy souhaite atteindre.
     *
     * @param positionController Pointeur vers l'objet PositionController à interroger.
     * @return Vitesse angulaire à atteindre en rad/s.
     */
    float getAngVelSetpoint(const PositionController* positionController){return positionController->m_angVelSetpoint;}
    /**
     * @brief Paramètre les coéfficients linéaire.
     *
     * Paramètre de nouvelles valeurs pour les coefficients linéaire de vitesse et vitesse de rotation.
     * Ces coefficients seront appliqués lors du calcul de vitesses à atteindre.
     *
     * @param positionController Pointeur vers l'objet PositionController à modifier.
     * @param linVelKp Coefficient proportionnel de vitesse linéaire.
     * @param angVelKp Coefficient proportionnel de vitesse angulaire.
     */
    void setVelTunings(PositionController* positionController, float linVelKp, float angVelKp) {
        positionController->m_linVelKp = linVelKp;
        positionController->m_angVelKp = angVelKp;
    }
    /**
     * @brief Paramètre les vitesses max.
     *
     * Paramètre des vitesses maximals qui dois être appliquer à l'AbstractMoveStrategy.
     *
     * @param positionController Pointeur vers l'objet PositionController à modifier.
     * @param linVelMax Vitesse linéaire max.
     * @param angVelMax Vitesse angulaire max.
     */
    void setVelLimits(PositionController* positionController, float linVelMax, float angVelMax){
        positionController->m_linVelMax = linVelMax;
        positionController->m_angVelMax = angVelMax;
    }
    /**
     * @brief Paramètre les précisions en position.
     *
     * Paramètre les valeurs de précision pour l'AbstractMoveStrategy. Si l'erreur de position est inférieur, l' AbstractMoveStrategy est arrêté.
     *
     * @param positionController Pointeur vers l'objet PositionController à modifier.
     * @param linPosThreshold Précision en coordonnés cartésiens (en mm).
     * @param angPosThreshold Précision d'angle (en rad).
     */
    void setPosThresholds(PositionController* positionController, float linPosThreshold, float angPosThreshold) {
        positionController->m_linPosThreshold = linPosThreshold;
        positionController->m_angPosThreshold = angPosThreshold;
    }
    /**
     * @brief Charge une stratégie de mouvement.
     *
     * Charge la stratégie de mouvement (AbstractMoveStrategy) passée en paramètre.
     * Elle sera active après l'activation de PositionController ( PositionController::enable).
     *
     * @param positionController Pointeur vers l'objet PositionController à modifier.
     * @param moveStrategy AbstractMoveStrategy à utiliser.
     */
    void setMoveStrategy(PositionController* positionController, AbstractMoveStrategy* moveStrategy);

    /**
     * @brief Indique si la position est atteinte.
     *
     * Permet de savoir si la position objectif est atteinte avec la précision souhaitée.
     *
     * @param positionController Pointeur vers l'objet PositionController à interroger.
     * @return true Position atteinte.
     * @return false Position non atteinte.
     */
    bool getPositionReached(const PositionController* positionController);

    /**
     * @brief Retourne le coef proportionnel de vitesse linéaire.
     * @param positionController Pointeur vers l'objet PositionController à interroger.
     * @return Coefficient proportionnel (sans unité).
     */
    float getLinVelKp(const PositionController* positionController){return positionController->m_linVelKp;}
    /**
     * @brief Retourne le coef proportionnel de vitesse angulaire.
     * @param positionController Pointeur vers l'objet PositionController à interroger.
     * @return Coefficient proportionnel (sans unité).
     */
    float getAngVelKp(const PositionController* positionController){return positionController->m_angVelKp;}
    /**
     * @brief Retourne la vitesse max linéaire.
     * @param positionController Pointeur vers l'objet PositionController à interroger.
     * @return Vitesse max en mm/s.
     */
    float getLinVelMax(const PositionController* positionController){return positionController->m_linVelMax;}
    /**
     * @brief Retourne la vitesse max angulaire.
     * @return Vitesse  angulaire max en rad/s.
     */
    float getAngVelMax(const PositionController* positionController){return positionController->m_angVelMax;}
    /**
     * @brief Retourne la précision cartésienne.
     *
     * @param positionController Pointeur vers l'objet PositionController à interroger.
     * @return Précision cartésienne en mm.
     */
    float getLinPosThreshold(const PositionController* positionController){return positionController->m_linPosThreshold;}
    /**
     * @brief Retourne la précision angulaire.
     *
     * @param positionController Pointeur vers l'objet PositionController à interroger.
     * @return Précision angulaire en rad.
     */
    float getAngPosThreshold(const PositionController* positionController){return positionController->m_angPosThreshold;}

    /**
     * @brief Exécute la stratégie de mouvement.
     *
     * Exécute la méthode computeVelSetpoints de l'AbstractMoveStrategy chargée.
     */
    void process(PositionController* positionController);
}

/**
 * @brief Interface de Stratégie de mouvement.
 * 
 * Interface à implémenter pour réaliser une classe de strategie de mouvement. 
 */
class AbstractMoveStrategy
{
public:
	/**
	 * @brief Calcul les nouvelles vitesses désirer.
	 * 
	 * Méthode à implémenter pour réaliser une AbstractMoveStrategy. Cette méthode calcul à partir de la position du robot des vitesses à suivre pour le robot.
	 * 
	 * @param timestep Temps depuis le dernier appel en secondes.
	 * 
	 */
	virtual void computeVelSetpoints(float timestep) = 0;
	/**
	 * @brief Indique si la position désirée est atteinte.
	 * 
	 * Calcul la distance entre la position du robot et la position désirée selon le mode de calcul de l'AbstractMoveStrategy.
	 * 
	 * @return true Si la position est atteinte.
	 * @return false Si la position n'est pas atteinte.
	 */
	virtual bool getPositionReached() = 0;
	/**
	 * @brief Retourne la position du robot.
	 * 
	 * Retourne la position du robot stocker dans le PositionController.
	 * 
	 * @return La position du robot sous la struct Position.
	 */
	const Position getPosInput()    const {return m_context->m_posInput;}
	/**
	 * @brief  Retourne la position à atteindre.
	 * @return Position à atteindre.
	 */
	const Position getPosSetpoint() const {return m_context->m_posSetpoint;}
	/**
	 * @brief Charge une nouvelle vitesse pour le robot.
	 * 
	 * @param linVelSetpoint Vitesse linéaire en mm/s.
	 * @param angVelSetpoint Vitesse angulaire en rad/s.
	 */
	void setVelSetpoints(float linVelSetpoint, float angVelSetpoint){m_context->m_linVelSetpoint = linVelSetpoint; m_context->m_angVelSetpoint = angVelSetpoint;}
	/**
	 * @brief Retourne le coef proportionnel de vitesse linéaire.
	 * @return Coefficient proportionnel (sans unité).
	 */
	float getLinVelKp() const {return m_context->m_linVelKp;}
	/**
	 * @brief Retourne le coef proportionnel de vitesse angulaire.
	 * 
	 * @return Coefficient proportionnel (sans unité).
	 */
	float getAngVelKp() const {return m_context->m_angVelKp;}
	/**
	 * @brief Retourne vitesse linéaire max.
	 * 
	 * @return Vitesse en mm/s.
	 */
	float getLinVelMax() const {return m_context->m_linVelMax;}
	/**
	 * @brief Retourne vitesse angulaire max.
	 * 
	 * @return Vitesse en rad/s.
	 */
	float getAngVelMax() const {return m_context->m_angVelMax;}
	/**
	 * @brief Retourne la précision cartésienne à atteindre.
	 * 
	 * 
	 * @return Précision en mm.
	 */
	float getLinPosThreshold() const {

        return m_context->m_linPosThreshold;}
	/**
	 * @brief Retourne la précision angulaire à atteindre.
	 * 
	 * 
	 * @return Précision en rad.
	 */
	float getAngPosThreshold() const {return m_context->m_angPosThreshold;}

	PositionController::PositionController* m_context;/*!< Pointeur du PositionControlleur associé.*/

};

#endif // __POSITIONCONTROLLER_H__
