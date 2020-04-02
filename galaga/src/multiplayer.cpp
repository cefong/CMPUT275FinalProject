#include "multiplayer.h"
extern thread_t *engine_thread;
const uint16_t buf_size = 256;

// setting up serial buffer
String buffer = "";
uint16_t buff_len = 0;
bool wait_timeout(uint8_t nbytes, long timeout) {
	unsigned long deadline = TIME_I2MS(chVTGetSystemTime()) + timeout;// wraparound  not a problem
	while (Serial.available() < nbytes && (timeout < 0 ||  millis() < deadline)){
		chThdSleepMilliseconds(1); // be nice , no busy  loop
	}
	return  Serial.available() >= nbytes;
}

static uint8_t process() {
  buffer = "";
  buff_len = 0;
  while(1) {
    if(wait_timeout(1, 500)) {
      char in_char = Serial.read();
      if(in_char == '\n' || in_char == '\r') {
        return 1;
      }
      else {
        if(buff_len < buf_size - 1) {
          buffer += in_char;
          buff_len++;
        }
      }
    }
    else {
      return 0;
    }
  }
  return 1;

}
void multiplayer() {
    player_stats player;
    while(1) {
        chMsgWait();
        msg_t sig = chMsgGet(engine_thread);
        chMsgRelease(engine_thread, sig);
        if(sig == 2) {
          if(wait_timeout(1, 500)) {
              char r = Serial.read();
              if(r == 'C') {
                  process();
                  String temp = buffer.substring(2,3);
                  player.is_fire = temp.toInt();
                  Serial.println(player.is_fire);
                  int j = 4;
                  while(buffer.substring(j, j+1) != " ") {
                      j++;
                  }
                  temp = buffer.substring(4, j);
                  player.x = temp.toInt();
                  temp = buffer.substring(j + 1, buff_len);
                  player.y = temp.toInt();
                  Serial.println("A"); 
              }
          }
          else {
              //Error Handler
          }
          chMsgSend(engine_thread, (msg_t)&player);
        }

            
    }

}