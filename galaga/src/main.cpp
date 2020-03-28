#include "main.h"

static THD_WORKING_AREA(waPlayer, 128);
static THD_FUNCTION(Player, arg) {
  player();
  //TODO
}

static THD_WORKING_AREA(waEngine, 4096);
static THD_FUNCTION(Engine, arg) {
  engine();
  //TODO
}
void interruptHandler() { 
}
void setup() {
  init();
  Serial.begin(115200);
  // put your setup code here, to run once
  attachInterrupt(digitalPinToInterrupt(21), interruptHandler, FALLING);
  pinMode(13, OUTPUT);
  uint16_t ID = tft.readID();
  if(ID == 0xD3D3) ID = 0x9481;
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
}
int main() {
  setup();
  player_thread = chThdCreateStatic(waPlayer, sizeof(waPlayer), NORMALPRIO, Player, NULL);
  engine_thread = chThdCreateStatic(waEngine, sizeof(waEngine), NORMALPRIO + 1, Engine, NULL);
  while(1);
  return 0;
}