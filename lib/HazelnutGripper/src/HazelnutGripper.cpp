//
// Created by Romain Pouvreau on 14/04/2026.
//

#include "HazelnutGripper.h"

namespace HazelnutGripper
{


    GripperFinger Gripper::_fingers[4] = {
        GripperFinger(&GripperWire,0x24),
        GripperFinger(&GripperWire,0x25),
        GripperFinger(&GripperWire,0x26),
        GripperFinger(&GripperWire,0x27)
    };

    void Gripper::init(uint8_t addr1, uint8_t addr2, uint8_t addr3, uint8_t addr4)
    {
        _fingers[0] = GripperFinger(&GripperWire,addr1);
        _fingers[1] = GripperFinger(&GripperWire,addr2);
        _fingers[2] = GripperFinger(&GripperWire,addr3);
        _fingers[3] = GripperFinger(&GripperWire,addr4);

        GripperWire.begin();
        GripperWire.setClock(100000);
    }

    void Gripper::openAll()
    {
        for (GripperFinger & _finger : _fingers) {
            _finger.open();
        }
    }

    void Gripper::closeAll()
    {
        for (GripperFinger & _finger : _fingers) {
            _finger.close();
        }
    }

    void Gripper::setRotationAll(uint8_t degrees)
    {
        for (GripperFinger & _finger : _fingers) {
            _finger.setAngle(1, degrees);
        }
    }

    void Gripper::spreadFingers(uint8_t degrees)
    {
        _fingers[0].setAngle(2, degrees);
    }

    GripperFinger& Gripper::getFinger(uint8_t index)
    {
        if (index > 3) return _fingers[0];
        return _fingers[index];
    }

} // HazelnutGripper