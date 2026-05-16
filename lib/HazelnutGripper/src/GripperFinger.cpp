//
// Created by Romain Pouvreau on 14/04/2026.
//
#include "GripperFinger.h"
#include <Wire.h>

namespace HazelnutGripper
{
    GripperFinger::GripperFinger(TwoWire* wire, uint8_t address)
    {
        this->_wire = wire;
        this->_addr = address;
    }

    void GripperFinger::enableStatusLed(bool enable)
    {
        _write8(REG_YELLOW_LED, enable ? 0x01 : 0x00);
    }

    void GripperFinger::enableActionLed(bool enable)
    {
        _write8(REG_BLUE_LED, enable ? 0x01 : 0x00);
    }

    void GripperFinger::setAngle(uint8_t servoIndex, uint8_t degrees)
    {
        uint8_t reg = (servoIndex == 1) ? REG_SERVO_1_POS : REG_SERVO_2_POS;
        _write8(reg, degrees);
    }

    void GripperFinger::open() { _write8(REG_MOTOR_TARGET, 0x01); }
    void GripperFinger::close() { _write8(REG_MOTOR_TARGET, 0x02); }
    void GripperFinger::stop() { _write8(REG_MOTOR_TARGET, 0x00); }

    bool GripperFinger::isMoving()
    {
        return (_read8(REG_MOTOR_STATUS) & 0x10); // Bit 4
    }

    bool GripperFinger::isTargetReached()
    {
        return (_read8(REG_MOTOR_STATUS) & 0x08); // Bit 3
    }

    bool GripperFinger::isFaulty()
    {
        return (_read8(REG_COLOR_STATUS)); // Bit 7
    }

    void GripperFinger::setSensingMode(OperationMode mode)
    {
        _write8(REG_COLOR_MODE, static_cast<uint8_t>(mode));
    }

    bool GripperFinger::hasNewColorData()
    {
        return (_read8(REG_COLOR_STATUS) & 0x20); // Bit 5
    }

    ColorData GripperFinger::getColor()
    {
        ColorData data{};
        data.clear = _read16(REG_COLOR_C_HIGH);
        data.red = _read16(REG_COLOR_R_HIGH);
        data.green = _read16(REG_COLOR_G_HIGH);
        data.blue = _read16(REG_COLOR_B_HIGH);
        return data;
    }

    void GripperFinger::_write8(uint8_t cmd, uint8_t value)
    {
        this->_wire->beginTransmission(_addr);
        this->_wire->write(cmd);
        this->_wire->write(value);
        this->_wire->endTransmission();
    }

    uint8_t GripperFinger::_read8(uint8_t cmd)
    {
        this->_wire->beginTransmission(_addr);
        this->_wire->write(cmd);
        this->_wire->write(0);
        this->_wire->endTransmission(false); // Restart condition

        this->_wire->requestFrom(_addr, (uint8_t)1);
        if (_wire->available())
        {
            return _wire->read();
        }
        return 0;
    }

    uint16_t GripperFinger::_read16(uint8_t cmd)
    {
        uint16_t data;
        data = this->_read8(cmd) << 8;
        data |= this->_read8(cmd + 1);

        return data;
    }
}
