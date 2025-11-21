//
// Created by awing on 21/11/25.
//

#include "PositionController.h"

#ifndef TEAM2026_BASICMOVESTRATEGY_H
#define TEAM2026_BASICMOVESTRATEGY_H


class BasicMoveStrategy : public AbstractMoveStrategy {
    /**
     * @brief Stratégie de mouvement basique.
     *
     * Stratégie développée afin de déplacer le robot en ligne droite selon l'axe x pour régler le PID.
     */
public:
    int x_precision;
    int x_max_speed;
    int slowing_distance;
protected:
    void computeVelSetpoints(float timestep) override;
    bool getPositionReached() override;

};


#endif //TEAM2026_BASICMOVESTRATEGY_H
