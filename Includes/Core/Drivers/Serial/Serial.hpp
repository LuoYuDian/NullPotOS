/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Serial.hpp

    Description:
        This header file is the serial driver of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.21
 */

#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <Types.hpp>

#define SERIAL_PORT 0x3f8

int InitSerial(void);

int SerialReceived(void);

char ReadSerial(void);

int IsTransmitEmpty(void);

void WriteSerial(char A);

#endif // SERIAL_HPP