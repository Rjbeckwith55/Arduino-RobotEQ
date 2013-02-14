// Copyright (C) 2013 Andy Kipp <kipp.andrew@gmail.com> 
// 
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
// 
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef ROBOTEQ_H
#define ROBOTEQ_H

#include <HardwareSerial.h>

#define ROBOTEQ_DEFAULT_TIMEOUT     1000 
#define ROBOTEQ_BUFFER_SIZE         64

#define ROBOTEQ_QUERY_CHAR          0x05
#define ROBOTEQ_ACK_CHAR            0x06

#define ROBOTEQ_OK                  0
#define ROBOTEQ_TIMEOUT             -1 
#define ROBOTEQ_ERROR               -2
#define ROBOTEQ_BAD_COMMAND         -3
#define ROBOTEQ_BAD_RESPONSE        -4
#define ROBOTEQ_BUFFER_OVER         -5

#define ROBOTEQ_FAULT_OVERHEAT      0x01
#define ROBOTEQ_FAULT_OVERVOLTAGE   0x02
#define ROBOTEQ_FAULT_UNDERVOLTAGE  0x04
#define ROBOTEQ_FAULT_SHORT         0x08
#define ROBOTEQ_FAULT_ESTOP         0x10
#define ROBOTEQ_FAULT_SCRIPT        0x20
#define ROBOTEQ_FAULT_MOSFET        0x40
#define ROBOTEQ_FAULT_CONFIG        0x80

#define ROBOTEQ_STATUS_SERIAL       0x01
#define ROBOTEQ_STATUS_PULSE        0x02
#define ROBOTEQ_STATUS_ANALOG       0x04
#define ROBOTEQ_STATUS_POWER_OFF    0x08
#define ROBOTEQ_STATUS_STALL        0x10
#define ROBOTEQ_STATUS_LIMIT        0x20
#define ROBOTEQ_SCRIPT_RUN          0x80

class RobotEQ {
    // Constructors
    public:
        RobotEQ(Stream *serial);

    // Destructors
    public:
        ~RobotEQ(void);

    // Public Methods
    public:
        int isConnected(void);

        /*
         * send motor power command (!G)
         *
         * @param ch channel
         * @param p power level (-1000, 1000)
         *
         * @return ROBOTEQ_OK if successful 
         */
        int commandMotorPower(uint8_t ch, int16_t p);

        /*
         * send emergency stop command (!EX) 
         * note: you have to reset the controller after this sending command
         *
         * @return ROBOTEQ_OK if successful 
         */
        int commandEmergencyStop(void);

        /*
         * query controller firmware
         * 
         * @param
         * @param
         *
         * @return
         */ 
        int queryFirmware(char *buf, size_t bufSize);

        /*
         * query motor amps
         * 
         * @param ch channel
         * 
         * @return motor amps * 10
         */
        int queryMotorAmps(uint8_t ch);
        
        int queryMotorPower(uint8_t ch);

        /*
         * query battery amps
         * 
         * @return battery amps * 10
         */
        int queryBatteryAmps(void);
        
        /*
         * query battery amps
         * 
         * @param ch channel
         * 
         * @return battery amps * 10
         */
        int queryBatteryAmps(uint8_t ch);
       
        /*
         * query battery voltage
         * 
         * @return battery voltage * 10
         */ 
        int queryBatteryVoltage(void);

        int queryFaultFlag(void);
        
        int queryStatusFlag(void);
        
        
        uint16_t getTimeout(void);
        
        void setTimeout(uint16_t timeout);


    // Private Methods
    private:

        int sendQuery(const char *query, uint8_t *buf, size_t bufSize);
        int sendQuery(const char *query, size_t querySize, uint8_t *buf, size_t bufSize);
        
        int sendCommand(const char *command);
        int sendCommand(const char *command, size_t commandSize);
        
        int readResponse(uint8_t *buf, size_t bufSize);

    // Private Data
    private:
        uint16_t    m_Timeout;
        Stream      *m_Serial; 
};

#endif

