#include "Stepper.h"
#include "smc4.h"
#include <iostream>
#include <Windows.h>

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
    
	float move=0.1f;
	if (motorConfig[yAxis].stepRes>move)
    {
		move=motorConfig[yAxis].stepRes;
    }

    double pos = GETPOSITION(yAxis);
    std::cout << "Current Position: yAxis\t" << pos << std::endl;
    // relative move
    MOVE(yAxis, move);
    // get motor status
    while(STATUS(yAxis) == 1)
    {
        Sleep(100);
    }
    bool isMoving = STATUS(yAxis) == 1 ? true : false;
    std::cout << "Moving Status\t" << isMoving << std::endl;
    pos = GETPOSITION(yAxis);
    std::cout << "Current Position: yAxis\t" << pos << std::endl;
    halt();
}