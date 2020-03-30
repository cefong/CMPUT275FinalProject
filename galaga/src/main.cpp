#include "main.h"

static THD_WORKING_AREA(waPlayer, 128);
static THD_FUNCTION(Player, arg) {
  (void)arg;
  player();
}

static THD_WORKING_AREA(waBot, 128);
static THD_FUNCTION(Bot, arg) {
  (void)arg;
  bot();
}

static THD_WORKING_AREA(waEngine, 4096);
static THD_FUNCTION(Engine, arg) {
  (void)arg;
  uint16_t ID = tft.readID();
  if(ID == 0xD3D3) ID = 0x9481;
  tft.begin(ID);
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  while(1) {
    engine();
  }
}
void interruptHandler() { 
  // set a flag to signal Engine Thread
  CH_IRQ_PROLOGUE();
  chSysLockFromISR();
  chEvtSignalI(player_thread, 1);
  chEvtSignalI(engine_thread, 1);
  chSysUnlockFromISR();
  CH_IRQ_EPILOGUE();
}

void chSetup() {
  player_thread = chThdCreateStatic(waPlayer, sizeof(waPlayer), NORMALPRIO, Player, NULL);
  engine_thread = chThdCreateStatic(waEngine, sizeof(waEngine), NORMALPRIO + 1, Engine, NULL);
  bot_thread    = chThdCreateStatic(waBot, sizeof(waBot), NORMALPRIO, Bot, NULL);
}
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once
  pinMode(BUTT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTT), interruptHandler, FALLING);
  pinMode(13, OUTPUT);
  chBegin(chSetup);
  while(1){
    chThdSleep(100);
  }
}
void loop(){}