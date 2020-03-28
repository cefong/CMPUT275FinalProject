#include "main.h"

void sig();
void setup() {
  init();
  Serial.begin(115200);
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(21), sig, FALLING);
  
}
int main() {
  setup();
  return 0;
}