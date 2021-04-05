#include "Stepper.h"
#include "smc4.h"
#include <iostream>

void initMotor(MOTOR_PAR& motorConfig)
{
    motorConfig.startPosi=0;
    motorConfig.motorType=TYPE_STEP_MOTOR;
    motorConfig.encFlag=NO_ENCODER;
    motorConfig.motorDir=1;
    motorConfig.stepOfTurn=1000;
    motorConfig.encRatio=4.0;
    motorConfig.stepRes=0.001f;
    motorConfig.jogSpeed=1;
    motorConfig.accRate=100;
    motorConfig.exPulseFlag=NO_EX_PULSE;
}

void halt()
{
    HALT(xAxis);
    HALT(yAxis);
    HALT(zAxis);
    HALT(tAxis);
}


void main()
{
    MOTOR_PAR motorConfig[4];
    for (int i = 0; i < 4; ++i)
    {
        initMotor(motorConfig[i]);
    }

    halt(); // Halt all axis;
    FillDataStruct(motorConfig);    // fill motor configuration

    STEP0();    // move to home;

    // setup speed
    SPEED(xAxis,motorConfig[xAxis].jogSpeed);
    SPEED(yAxis,motorConfig[yAxis].jogSpeed);
    SPEED(zAxis,motorConfig[zAxis].jogSpeed);
    SPEED(tAxis,motorConfig[tAxis].jogSpeed);

    double pos = GETPOSITION(yAxis);
    std::cout << "Current Position: yAxis\t" << pos << std::endl;
    double delta = pos * 0.05;
    // relative move
    MOVE(yAxis, pos - delta);
    // get motor status
    bool isMoving = STATUS(yAxis) == 1 ? true : false;
    std::cout << "Moving Status\t" << isMoving << std::endl;
    halt();
}