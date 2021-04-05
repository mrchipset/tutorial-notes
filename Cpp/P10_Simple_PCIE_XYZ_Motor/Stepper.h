/* stepper.h -- function prototypes for calls to stepper motor control
 *
 * The actual functions are provided by Physical Acoustics Corp.
 * Distance units are inches or centimeter.  Status is OK (= 0) or error (!= 0).
 *
 * Move( Axis, Distance) -- move Distance along Axis, return status.
 * GetPosition( Axis ) --  return position along Axis.
 * SetPosition( Axis, Position ) -- set current position of Axis to Position,
 *     return status.
 * Speed( Axis, Rate ) -- set scan speed of Axis to Rate, return status.
 * SetLimit( Axis, Minimum, Maximum ) -- set position limits of Axis to 
 *     Minimum and Maximum, return status.
 * Halt() -- stop all movement, return status.
 * Status( Axis ) -- return the status of Axis; 0 = halted, 1 = moving,
 *     2 = at minimum limit, 3 = at maximum limit.
 * Step0() -- initialize stepper motor controller board, return status.
 * mess3() -- warnning message for scanner not ready. It is not used in an ordinary
 *     Cscan Imaging system.
 *************************************************************************************
 */
#ifndef STEPPER_H
#define STEPPER_H
#define TOTAL_AXES 4
#define xAxis 0
#define yAxis 1
#define zAxis 2
#define tAxis 3

//int MOVE(unsigned int axis, double distance );
//double  GETPOSITION(unsigned int  axis );
//int  SETPOSITION(unsigned int axis, double position );
//int  SPEED(unsigned int axis, double rate );
//int  STATUS(unsigned int axis );
//short STEP0();

//int checkFinish(int axis, short *, short *);
//void HALT(MOTOR_PAR *, int axis );

#define TYPE_STEP_MOTOR 0
#define TYPE_HAND_SCAN 1
#define EX_CONTINUE_MOTOR 2

#define PULSES_FOR_SPEED_MAX 12500   // the maximum speed the card can handle


// function to call from motor driver functions to get parameters
//extern void motorIniSetup(double *, double *, unsigned short *, short *, short *, short); 

#endif