#include "main.h"

static THD_WORKING_AREA(waPlayer, 128);
static THD_FUNCTION(Player, arg) {
  (void)arg;
  player();
  //TODO
}

static THD_WORKING_AREA(waEngine, 4096);
static THD_FUNCTION(Engine, arg) {
  (void)arg;
  engine();
  //TODO
}
void interruptHandler() { 
  
  // set a flag to signal Engine Thread
  CH_IRQ_PROLOGUE();
  chSysLockFromISR();
  chEvtSignalI(engine_thread, 1);
  chSysUnlockFromISR();
  CH_IRQ_EPILOGUE();
}

void chSetup() {
  player_thread = chThdCreateStatic(waPlayer, sizeof(waPlayer), NORMALPRIO, Player, NULL);
  engine_thread = chThdCreateStatic(waEngine, sizeof(waEngine), NORMALPRIO + 1, Engine, NULL);
  while(1){
    chThdSleep(100);
  }
}
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once
  pinMode(BUTT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTT), interruptHandler, FALLING);
  pinMode(13, OUTPUT);
  uint16_t ID = tft.readID();
  if(ID == 0xD3D3) ID = 0x9481;
  tft.begin(ID);
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  chBegin(chSetup);
  while(1);
}
void loop(){}