//new data structure for ultrawin
// FILE: newDef.h

#ifndef NEWDEF_H 
#define NEWDEF_H 




typedef struct {
	float 	startPosi;
	short   motorType;
	short   encFlag;
	short   motorDir;
	unsigned long    stepOfTurn;
	float 	encRatio;
	float 	stepRes;
	float   jogSpeed;
	short   accRate;
	short   exPulseFlag;
}MOTOR_PAR;

#define WITH_ENCODER 1
#define NO_ENCODER 0

#define WITH_EX_PULSE 1
#define NO_EX_PULSE   0



#endif // for ifndef NEWDEF_H
