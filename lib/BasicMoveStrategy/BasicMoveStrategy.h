//
// Created by awing on 21/11/25.
//

#ifndef TEAM2026_BASICMOVESTRATEGY_H
#define TEAM2026_BASICMOVESTRATEGY_H
#include "PositionController.h"
#include "PID.h"

class BasicMoveStrategy : public AbstractMoveStrategy {
    /**
     * @brief Stratégie de mouvement basique.
     *
     * Stratégie développée afin de déplacer le robot en ligne droite selon l'axe x pour régler le PID.
     */
public:
    virtual ~BasicMoveStrategy() = default;
    float theta_init = 0;
    PID ang_pid = {};
    PID lin_pid = {};
protected:
    void computeVelSetpoints(float timestep) override;
    bool getPositionReached() override;
};


#endif //TEAM2026_BASICMOVESTRATEGY_H
