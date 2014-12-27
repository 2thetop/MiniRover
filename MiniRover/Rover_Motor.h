//----------------------------------------------------------------------------
//    프로그램명 	: Rover Motor
//
//    만든이     	: Cho Han Cheol 
//
//    날  짜     : 
//    
//    최종 수정  	: 
//
//    MPU_Type	: 
//
//    파일명     	: Rover_Motor.h
//----------------------------------------------------------------------------
#ifndef _ROVER_MOTOR_H_
#define _ROVER_MOTOR_H_

#include <inttypes.h>




class Rover_Motor
{
public:
	Rover_Motor();


	void setup( void );

	void Set_Pwm( int16_t PwmLeft, int16_t PwmRight );



private:
	int16_t  Pwm_Left;
	int16_t  Pwm_Right;

	void Set_PwmLeftOut( uint16_t PwmData  );
	void Set_PwmRightOut( uint16_t PwmData  );

	void Set_DirLeftOut( uint8_t DirData  );
	void Set_DirRightOut( uint8_t DirData  );

};


#endif
