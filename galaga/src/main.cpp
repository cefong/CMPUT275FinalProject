#include "main.h"


void sig() { 
  digitalWrite(13, 1);
}
void setup() {
  init();
  Serial.begin(115200);
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(21), sig, FALLING);
  pinMode(13, OUTPUT);
}
int main() {
  setup();
  return 0;
}