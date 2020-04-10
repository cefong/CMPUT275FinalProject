/*
Names: Claire Martin (1571140), Celine Fong, Minh Dang, Zi Xue Lim
CMPUT 275, Winter 2020

Final Project: A Variation on 'Galaga'
main.cpp: Contains setup functions for threads
*/

#include "main.h"

// define player thread working area
static THD_WORKING_AREA(waPlayer, 128);
// define player thread
static THD_FUNCTION(Player, arg) {
	(void)arg;
	player();
}

// define bot thread working area
static THD_WORKING_AREA(waBot, 1024);
// define bot thread
static THD_FUNCTION(Bot, arg) {
	(void)arg;
	bot();
}

// define engine thread working area
static THD_WORKING_AREA(waEngine, 1024);
// define engine thread
static THD_FUNCTION(Engine, arg) {
	(void)arg;
	uint16_t ID = tft.readID();
	if(ID == 0xD3D3) ID = 0x9481;
	// initialize screen
	tft.begin(ID);
	tft.setRotation(0);
	tft.fillScreen(TFT_BLACK);
	// run engine
	while(1) {
    	engine();
	}
}


void interruptHandler() { 
	/*
	Set a flag to signal Engine Thread
	*/
	CH_IRQ_PROLOGUE();
	chSysLockFromISR();
	chEvtSignalI(engine_thread, 1);
	chSysUnlockFromISR();
	CH_IRQ_EPILOGUE();
}


void chSetup() {
	/*
	Setup threads
	*/
	player_thread  = chThdCreateStatic(waPlayer, sizeof(waPlayer), NORMALPRIO, Player, NULL);
	engine_thread  = chThdCreateStatic(waEngine, sizeof(waEngine), NORMALPRIO + 1, Engine, NULL);
	bot_thread     = chThdCreateStatic(waBot, sizeof(waBot), NORMALPRIO, Bot, NULL);
}


void setup() {
	/*
	Setup for main program
	*/

	// setting up interrupt pin 21
	pinMode(BUTT, INPUT_PULLUP);
	attachInterrupt(BUTT_ISR, interruptHandler, FALLING);

	chBegin(chSetup);
	while(1){
		chThdSleep(100);
  	}
}

// Arduino loop function
void loop(){}