#include "main.h"

static THD_WORKING_AREA(waPlayer, 1024);
static THD_FUNCTION(Player, arg) {
  //TODO
}

static THD_WORKING_AREA(waBot, 1024);
static THD_FUNCTION(Bot, arg) {
  //TODO
}

static THD_WORKING_AREA(waEngine, 2048);
static THD_FUNCTION(Engine, arg) {
  //TODO
}
void interrupt() { 
  digitalWrite(13, 1);
}
void setup() {
  init();
  Serial.begin(115200);
  // put your setup code here, to run once
  attachInterrupt(digitalPinToInterrupt(21), interrupt, FALLING);
  pinMode(13, OUTPUT);
  uint16_t ID = tft.readID();
  if(ID == 0xD3D3) ID = 0x9481;
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
}
int main() {
  setup();
  chThdCreateStatic(waPlayer, sizeof(waPlayer), NORMALPRIO + 1, Player, NULL);
  chThdCreateStatic(waEngine, sizeof(waEngine), NORMALPRIO, Engine, NULL);
  chThdCreateStatic(waBot, sizeof(waEngine), NORMALPRIO + 1, Bot, NULL);
  while(1);
  return 0;
}