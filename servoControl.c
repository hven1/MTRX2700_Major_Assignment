#include <hidef.h>
#include "math.h"
#include "stdlib.h"
#include "string.h"

//Servo Control variables


//Initialise the PWM Signal for the Servo Control
void initServo(void){
	//Require 2 PWM signals
	
	//Concatenate channels 6&7 and 4&5
	PWMCTL = 0xC0;
	
	//Select CLK source
	PWMCLK = 0x00;
	
	//Left align
	PWMCAE = 0x00;
	
	//Choose polarity 1 for channels 7&5
	PWMPOL = 0xA0;
	
	//Choose prescaler of 16
	PWMPRCLK = 0x44;
	
	
	//Choose period od 20ms
	//(16 * 30000 * 41.667ns = 20ms)
	PWMPER67 = 30000;
	PWMPER45 = 30000;
	
	//**Choose start position??
	//Calibrate that goes in middle around 2250
	//PWM in middle
	PWMDTY67 = 2250;
	PWMDTY45 = 2250;	
	
	//Enable PWM channels
	PWME = 0xA0;
}

void servoON(){
	PWME = 0xA0;     /Enable the PWM
}

void servoOFF(){
	PWME = 0x00;     /Disable the PWM
}

//Function to set the azimuth angel of the servo
//Use PWM channels45
void setAzimuth(float angleAzi){
	
	if (angleAzi >=0 && angleAzi <= 90) {
		//(Angle/90*900)+2250=PWMDTY
		PWMDTY45 = 2250 + (angleAzi*10);
	}
	else if (angleAzi <0 && angleAzi >= -90) {
		PWMDTY45 = 2250 - (angleAzi*10);
	}
	else {
		//RETURN TO DEFAULT
		PWMDTY45 = 2250;
	}
		
	
}

void setElevation(angleElev){
	if (angleElev >=0 && angleElev <= 90) {
		//(angleElev/90*900)+2250=PWMDTY
		PWMDTY67 = 2250 + (angleElev*10);
	}
	else if (angleElev <0 && angleElev >= -90) {
		PWMDTY67 = 2250 - (angleElev*10);
	}
	else {
		//RETURN TO DEFAULT
		PWMDTY67 = 2250;
	}
}
