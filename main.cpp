//
// ELEC143 C1 2019 TEMPLATE CODE
//
#include "mbed.h"
#include "TextLCD.h" 

DigitalOut ledOnboardGreen(LED1,0);
DigitalOut ledOnboardBlue(LED2,0);
DigitalOut ledOnboardRed(LED3,0);
DigitalOut redLED(PE_10,0);
DigitalOut yellowLED(PE_12,0);
DigitalOut greenLED(PE_14,0);
DigitalOut whiteLED(PE_7, 0);

DigitalIn  blueButton(USER_BUTTON);
DigitalIn  sw1(PE_15);
DigitalIn  sw2(PE_0);
DigitalIn  sw3(PB_10);
DigitalIn  sw4(PB_11);


AnalogIn adc(A0);
AnalogOut dac(D13);

TextLCD lcd(D3, D2, D7, D6, D5, D4); // rs, e, d4-d7

//Declare function written in another source file (post.cpp in this case)
extern void POST();

//
// THIS IS ONLY TEMPLATE CODE USED TO DEMO AND TEST YOUR HARDWARE
// IT IS SUGGESTED YOU COPY THIS PROJECT FOLDER, RENAME
// AND DELETE ALL THE CODE IN MAIN
// REMEMBER TO CONNECT D13 TO THE OSCILLOSCOPE AND A0 TO THE LDR
// 
int main()
{
    //Test the hardware (uncomment to test hardware)
    POST();

    // *****************************************************************
    // Simple rapid polling loop
    // Press and release the BLUE user button to toggle the onboard LEDs
    // *****************************************************************
    
    //Keep track of state for the blue switch
    int blueSwitchState = 0;
    
    //The timer used for debouncing the blue switch
    Timer tmrBlueSwitch;

    // Set LEDs in initial state
    ledOnboardGreen = 1;
    ledOnboardBlue  = 0;
    ledOnboardRed   = 1;		
		
    while(true) {
			
			//READ ALL INPUTS (without blocking)
			int tmr = tmrBlueSwitch.read_ms();
			int switch1 = blueButton;
			
			//UPDATE STATE and OUTPUTS
			switch (blueSwitchState)
			{
				//**************************
				//Looking for a switch press
				//**************************
				case 0:
					if (switch1 == 1) {
						//Change state
						blueSwitchState = 1;
						
						//Update outputs
						ledOnboardGreen = !ledOnboardGreen;
						ledOnboardBlue  = !ledOnboardBlue;
						ledOnboardRed   = !ledOnboardRed;
						tmrBlueSwitch.reset();
						tmrBlueSwitch.start();						
					}
					break;

				//*******************************
				//Looking for 50ms to have passed
				//*******************************					
				case 1:
					if (tmr >= 50) {
						//Change state
						blueSwitchState = 2;
						
						//Update outputs
						tmrBlueSwitch.stop();
					}
					break;

				//****************************
				//Looking for a switch release
				//****************************					
				case 2:
					if (switch1 == 0) {
						//Change state
						blueSwitchState = 3;
						
						//Update outputs
						tmrBlueSwitch.reset();
						tmrBlueSwitch.start();						
					}
					break;

				//*******************************
				//Looking for 50ms to have passed
				//*******************************					
				case 3:
					if (tmr >= 50) {
						//Change state back to the start
						blueSwitchState = 0;
						
						//Update outputs
						tmrBlueSwitch.stop();
					}
					break;

				// **********************************
				// IF SOMETHING HAS GONE BADLY WRONG!
				// **********************************
				default:
					blueSwitchState = 0;
				
			} //End switch

		} //end while
		
} //end main
