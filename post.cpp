#include "mbed.h"
#include "TextLCD.h" 

extern DigitalOut ledOnboardGreen;
extern DigitalOut ledOnboardBlue;
extern DigitalOut ledOnboardRed;
extern DigitalOut redLED;
extern DigitalOut yellowLED;
extern DigitalOut greenLED;
extern DigitalOut whiteLED;
extern DigitalIn  blueButton;
extern DigitalIn  sw1;
extern DigitalIn  sw2;
extern DigitalIn  sw3;
extern DigitalIn  sw4;

extern AnalogIn adc;
extern AnalogOut dac;
extern TextLCD lcd;

//This is private to this file
static void waitForSwitch(DigitalIn& sw )
{
    while ( sw == 0 );
    wait_us(50000);  //50ms
    while ( sw == 1 );
    wait_us(50000);  //50ms
}

//Global function
void POST()
{
    // ********
    // TEST LEDS
    // ********
    lcd.cls(); lcd.locate(0,0);
    lcd.printf("Press BLUE x4");
    waitForSwitch(blueButton);
    whiteLED = 1;
    waitForSwitch(blueButton);
    redLED = 1;
    waitForSwitch(blueButton);
    yellowLED = 1;
    waitForSwitch(blueButton);
    greenLED = 1;


    // ********
    // TEST SW1
    // ********
    lcd.cls(); lcd.locate(0,0);
    lcd.puts("Press sw1 x4");
    waitForSwitch(sw1);
    whiteLED = !whiteLED;
    waitForSwitch(sw1);
    redLED = !redLED;
    waitForSwitch(sw1);
    yellowLED = !yellowLED;
    waitForSwitch(sw1);
    greenLED = !greenLED;    

    // ********
    // TEST SW2
    // ********
    lcd.locate(0,1);
    lcd.puts("Press sw2 x4");
	waitForSwitch(sw2);
    whiteLED = !whiteLED;
    waitForSwitch(sw2);
    redLED = !redLED;
    waitForSwitch(sw2);
    yellowLED = !yellowLED;
    waitForSwitch(sw2);
    greenLED = !greenLED;       
		
		
    // ********
    // TEST SW3
    // ********
	lcd.cls(); lcd.locate(0,0);
    lcd.puts("Press sw3 x4");
	waitForSwitch(sw3);
    whiteLED = !whiteLED;
    waitForSwitch(sw3);
    redLED = !redLED;
    waitForSwitch(sw3);
    yellowLED = !yellowLED;
    waitForSwitch(sw3);
    greenLED = !greenLED;    

    // ********
    // TEST SW4
    // ********
    lcd.locate(0,1);
    lcd.puts("Press sw4 x4");
	waitForSwitch(sw4);
    whiteLED = !whiteLED;
    waitForSwitch(sw4);
    redLED = !redLED;
    waitForSwitch(sw4);
    yellowLED = !yellowLED;
    waitForSwitch(sw4);
    greenLED = !greenLED;   
    
    //****************************************************
    //ADC and DAC Demo - CONNECT D13 to A0 to test the DAC
    //****************************************************
    float v=0.0f;
    lcd.cls(); lcd.locate(0,0);
    lcd.printf("ADC/LDR Check");		

    wait_us(3000000);
    v = 3.3f*adc;				//Read from ADC
    lcd.cls(); lcd.locate(0,0); lcd.printf("ADC: %4.2fV", v);

    wait_us(3000000);
    v = 3.3f*adc;
    lcd.cls(); lcd.locate(0,0); lcd.printf("ADC: %4.2fV", v);		
    
    wait_us(3000000);
    v = 3.3f*adc;
    lcd.cls(); lcd.locate(0,0); lcd.printf("ADC: %4.2fV", v);		

    // ************
    // ONBOARD LEDs
    // ************
    wait_us(3000000);
    lcd.cls(); 
    lcd.printf("Flashing onboard");
    lcd.locate(0,1);
    lcd.printf("LEDs");
    for (unsigned int n=0; n<10; n++) {
        ledOnboardGreen = 1;
        ledOnboardBlue  = 1;
        ledOnboardRed   = 1;	
        wait_us(100000);
        ledOnboardGreen = 0;
        ledOnboardBlue  = 0;
        ledOnboardRed   = 0;
        wait_us(100000);			
    }
    lcd.cls(); 
    lcd.printf("Done.");
    wait_us(1000000);
    lcd.cls(); 
}
