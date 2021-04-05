#include "newdef.h"
/*_declspec(dllimport)*/
extern "C"
{
_declspec(dllimport)int MOVE(unsigned int axis, double distance );
_declspec(dllimport)double  GETPOSITION(unsigned int  axis );
_declspec(dllimport)int  SETPOSITION(unsigned int axis, double position );
_declspec(dllimport)int  SPEED(unsigned int axis, double rate );
_declspec(dllimport)int  STATUS(unsigned int axis );
_declspec(dllimport)short STEP0();
_declspec(dllimport)void SetDriverData(int axis,float startPosi,short motorType,short  encFlag,short  motorDir, float encRatio,float stepRes,float jogSpeed,short  accRate,	short exPulseFlag,unsigned long stepOfTurn);
_declspec(dllimport)int checkFinish(int , short *, short *);
_declspec(dllimport)void HALT(int axis );
_declspec(dllimport)void FillDataStruct(MOTOR_PAR * pData);
}