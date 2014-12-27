//----------------------------------------------------------------------------
//    프로그램명 	: BiRover Motor
//
//    만든이     	: Cho Han Cheol 
//
//    날  짜     : 
//    
//    최종 수정  	: 
//
//    MPU_Type	: 
//
//    파일명     	: BiRover_Motor.cpp
//----------------------------------------------------------------------------



#include <avr/interrupt.h>
#include <Arduino.h> 

#include "Rover_Motor.h"




#define LEFT_PIN_DIR_0			7
#define LEFT_PIN_DIR_1			8
#define LEFT_PIN_PWM_R			5
#define LEFT_PIN_PWM_F			9


#define RIGHT_PIN_DIR_0			21
#define RIGHT_PIN_DIR_1			20
#define RIGHT_PIN_PWM_R			6
#define RIGHT_PIN_PWM_F			10


#define MOTOR_FW				0
#define MOTOR_BW				1
#define MOTOR_STOP				2






/*---------------------------------------------------------------------------
     TITLE   : Rover_Motor
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
Rover_Motor::Rover_Motor()
{
	Pwm_Left  = 0;
	Pwm_Right = 0;
}





/*---------------------------------------------------------------------------
     TITLE   : setup
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Rover_Motor::setup()
{
	//-- I/O 초기화  
	//
	pinMode( LEFT_PIN_DIR_0, OUTPUT );
	pinMode( LEFT_PIN_DIR_1, OUTPUT );
	pinMode( LEFT_PIN_PWM_R, OUTPUT );
	pinMode( LEFT_PIN_PWM_F, OUTPUT );

	pinMode( RIGHT_PIN_DIR_0, OUTPUT );
	pinMode( RIGHT_PIN_DIR_1, OUTPUT );
	pinMode( RIGHT_PIN_PWM_R, OUTPUT );
	pinMode( RIGHT_PIN_PWM_F, OUTPUT );

	Set_DirLeftOut ( MOTOR_STOP );
	Set_DirRightOut( MOTOR_STOP );

	Set_PwmLeftOut ( 0 );
	Set_PwmRightOut( 0 );
}





/*---------------------------------------------------------------------------
     TITLE   : Set_PwmLeftOut
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Rover_Motor::Set_Pwm( int16_t PwmLeft, int16_t PwmRight )
{
	if( PwmLeft >  255 ) PwmLeft =  255;
	if( PwmLeft < -255 ) PwmLeft = -255;

	if( PwmRight >  255 ) PwmRight =  255;
	if( PwmRight < -255 ) PwmRight = -255;


	if( PwmLeft == 0 )
	{
		Set_DirLeftOut ( MOTOR_STOP );
		Set_PwmLeftOut ( 0 );		
	}
	else
	if( PwmLeft > 0 )	
	{
		Set_DirLeftOut ( MOTOR_FW );
		Set_PwmLeftOut ( PwmLeft );		
	}
	else
	{
		Set_DirLeftOut ( MOTOR_BW );
		Set_PwmLeftOut ( -PwmLeft );		
	}


	if( PwmRight == 0 )
	{
		Set_DirRightOut ( MOTOR_STOP );
		Set_PwmRightOut ( 0 );		
	}
	else
	if( PwmRight > 0 )	
	{
		Set_DirRightOut ( MOTOR_FW );
		Set_PwmRightOut ( PwmRight );		
	}
	else
	{
		Set_DirRightOut ( MOTOR_BW );
		Set_PwmRightOut ( -PwmRight );		
	}
}





/*---------------------------------------------------------------------------
     TITLE   : Set_PwmLeftOut
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Rover_Motor::Set_PwmLeftOut( uint16_t PwmData  )
{
	if( PwmData > 255 ) PwmData = 255;

	Pwm_Left = PwmData;

	analogWrite( LEFT_PIN_PWM_R, PwmData );
	analogWrite( LEFT_PIN_PWM_F, PwmData );
}





/*---------------------------------------------------------------------------
     TITLE   : Set_PwmRighttOut
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Rover_Motor::Set_PwmRightOut( uint16_t PwmData  )
{
	if( PwmData > 255 ) PwmData = 255;

	Pwm_Right = PwmData;

	analogWrite( RIGHT_PIN_PWM_R, PwmData );
	analogWrite( RIGHT_PIN_PWM_F, PwmData );
}





/*---------------------------------------------------------------------------
     TITLE   : Set_DirLeftOut
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Rover_Motor::Set_DirLeftOut( uint8_t DirData  )
{
	switch( DirData )
	{
		case MOTOR_FW:
			digitalWrite( LEFT_PIN_DIR_0, HIGH );
			digitalWrite( LEFT_PIN_DIR_1, LOW );		
			break;

		case MOTOR_BW:
			digitalWrite( LEFT_PIN_DIR_0, LOW );
			digitalWrite( LEFT_PIN_DIR_1, HIGH );		
			break;

		case MOTOR_STOP:
			digitalWrite( LEFT_PIN_DIR_0, LOW );
			digitalWrite( LEFT_PIN_DIR_1, LOW );		
			break;

		default:
			digitalWrite( LEFT_PIN_DIR_0, LOW );
			digitalWrite( LEFT_PIN_DIR_1, LOW );		
			break;
	}
}





/*---------------------------------------------------------------------------
     TITLE   : Set_DirRightOut
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Rover_Motor::Set_DirRightOut( uint8_t DirData  )
{
	switch( DirData )
	{
		case MOTOR_FW:
			digitalWrite( RIGHT_PIN_DIR_0, HIGH );
			digitalWrite( RIGHT_PIN_DIR_1, LOW );		
			break;

		case MOTOR_BW:
			digitalWrite( RIGHT_PIN_DIR_0, LOW );
			digitalWrite( RIGHT_PIN_DIR_1, HIGH );		
			break;

		case MOTOR_STOP:
			digitalWrite( RIGHT_PIN_DIR_0, LOW );
			digitalWrite( RIGHT_PIN_DIR_1, LOW );		
			break;

		default:
			digitalWrite( RIGHT_PIN_DIR_0, LOW );
			digitalWrite( RIGHT_PIN_DIR_1, LOW );		
			break;
	}
}


