//----------------------------------------------------------------------------
//    프로그램명	: BiRover 메인 
//
//    만든이		: 
//
//    날  짜		: 
//    
//    최종 수정	: 
//
//    MPU_Type	: 
//
//    파일명		: 
//----------------------------------------------------------------------------

#include "MSP_Cmd.h"
#include "Rover_Motor.h"



const char VersionStr[] = "141226";


uint8_t     Enable;
int16_t		Pwm_Left;
int16_t		Pwm_Right;


uint32_t	Time_Current;
uint32_t	Time_Previous[4];


MSP_CMD_OBJ    *pCmd;
MSP_RESP_OBJ   *pResp;


Rover_Motor		Motor;
MSP_Cmd         Msp;




void MSP_Cmd_Loop( void );



/*---------------------------------------------------------------------------
     TITLE   : setup
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void setup()
{
    Enable    = false;
	Pwm_Left  = 0;
	Pwm_Right = 0;

	Motor.setup();
    Msp.begin();

    Serial.begin(115200);

}




/*---------------------------------------------------------------------------
     TITLE   : loop
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void loop()
{
	int16_t error;

	Time_Current = millis();


    //-- MSP Loop
    //
    MSP_Cmd_Loop();

	
	if( ( Time_Current - Time_Previous[0] ) > 5 )
	{
        if( Enable == true )
        {
            Motor.Set_Pwm(  Pwm_Left, Pwm_Right );
        }
        else
        {
            Motor.Set_Pwm(  0, 0 );    
        }

		Time_Previous[0] = Time_Current;
	}
	
}





/*---------------------------------------------------------------------------
     TITLE   : MSP_Cmd_Loop
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void MSP_Cmd_MSP_SET_RAW_RC_TINY( void )
{
    int16_t Roll;
    int16_t Pitch;
    int16_t Yaw;
    int16_t Throthle;

    int16_t Pwm_L;
    int16_t Pwm_R;
    int16_t Speed;
    int16_t Dir;

    Roll     = 1000 + pCmd->Data[0] * 4;
    Pitch    = 1000 + pCmd->Data[1] * 4;
    Yaw      = 1000 + pCmd->Data[2] * 4;
    Throthle = 1000 + pCmd->Data[3] * 4;

    /*
    Serial.print("Receive : ");
    Serial.print(Roll);     Serial.print("\t"); 
    Serial.print(Pitch);    Serial.print("\t"); 
    Serial.print(Yaw);      Serial.print("\t"); 
    Serial.print(Throthle); Serial.print("\t"); 
    Serial.println(" ");
    */

    Speed = (Pitch - 1500) / 2;
    Dir   = (Roll  - 1500) / 2;

    Pwm_L = Speed + Dir;
    Pwm_R = Speed - Dir;


    Pwm_Left  = Pwm_L;
    Pwm_Right = Pwm_R;
}





/*---------------------------------------------------------------------------
     TITLE   : MSP_Cmd_Loop
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void MSP_Cmd_Loop( void )
{
    bool Ready_Cmd = false;


    Ready_Cmd = Msp.update();


    //-- 명령어 처리 
    //
    if( Ready_Cmd == true )
    {
        pCmd  = Msp.Get_CmdPtr();
        pResp = Msp.Get_RespPtr();
        
        switch( pCmd->Cmd )
        {
            case MSP_SET_RAW_RC_TINY:
                MSP_Cmd_MSP_SET_RAW_RC_TINY();
                break;

            case MSP_ARM:
                Enable = true;
                break;

            case MSP_DISARM:
                Enable    = false;
                Pwm_Left  = 0;
                Pwm_Right = 0;

                break;

            default:
                pResp->Cmd       = pCmd->Cmd;
                pResp->ErrorCode = 0x00;
                pResp->Length    = 0;
                Msp.SendResp( pResp );
                break;
        }
        
    }
}


