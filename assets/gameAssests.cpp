#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

// set color constants
#define COLOR_1_PLAYER 0xF800
#define COLOR_2_PLAYER 0xF401
#define COLOR_3_PLAYER 0xFF20
#define COLOR_4_PLAYER 0x0000
#define COLOR_5_PLAYER 0xD6FC
#define COLOR_6_PLAYER 0x6EDD
#define COLOR_7_PLAYER 0xADB7

#define COLOR_1_ENEMY 0xF800
#define COLOR_2_ENEMY 0xF401
#define COLOR_3_ENEMY 0xFF20
#define COLOR_4_ENEMY 0x0000
#define COLOR_5_ENEMY 0xE9A6
#define COLOR_6_ENEMY 0xF3A0
#define COLOR_7_ENEMY 0xF260

#define COLOR_1_EXPLOSION 0xF800
#define COLOR_2_EXPLOSION 0xF401
#define COLOR_3_EXPLOSION 0xFF20
#define COLOR_4_EXPLOSION 0xFFFF

#define SPACE_COLOR 0x32B2

// width/height of the display when rotated horizontally
#define TFT_WIDTH  480
#define TFT_HEIGHT 320

MCUFRIEND_kbv tft;

void setup() {
	init();

	// do not actually need to change the pinmode of the digital TouchScreen
	// pins, the function to get a touchscreen reading will set and change them

	Serial.begin(9600);

	uint16_t ID = tft.readID();
	tft.begin(ID);

	tft.fillScreen(SPACE_COLOR);
	tft.setRotation(1);

}

void drawSpaceship(int16_t anchorX, int16_t anchorY, int16_t scale, char characterSelect) {
	int16_t color1, color2, color3, color4, color5, color6, color7;
	if (characterSelect == 'P') {
		color1 = COLOR_1_PLAYER;
		color2 = COLOR_2_PLAYER;
		color3 = COLOR_3_PLAYER;
		color4 = COLOR_4_PLAYER;
		color5 = COLOR_5_PLAYER;
		color6 = COLOR_6_PLAYER;
		color7 = COLOR_7_PLAYER;
	} else if (characterSelect == 'E') {
		color1 = COLOR_1_ENEMY;
		color2 = COLOR_2_ENEMY;
		color3 = COLOR_3_ENEMY;
		color4 = COLOR_4_ENEMY;
		color5 = COLOR_5_ENEMY;
		color6 = COLOR_6_ENEMY;
		color7 = COLOR_7_ENEMY;
	}

	// code for color 1
	tft.fillRect(anchorX, anchorY-4*scale, scale, scale, color1);
	tft.fillRect(anchorX, anchorY+6*scale, scale, scale, color1);
	tft.fillRect(anchorX-1*scale, anchorY+5*scale, scale, scale, color1);
	tft.fillRect(anchorX+1*scale, anchorY+5*scale, scale, scale, color1);
	tft.fillRect(anchorX+3*scale, anchorY+4*scale, scale, scale, color1);
	tft.fillRect(anchorX-3*scale, anchorY+4*scale, scale, scale, color1);

	// code for color 2
	tft.fillRect(anchorX, anchorY+5*scale, scale, scale, color2);
	tft.fillRect(anchorX+1*scale, anchorY+4*scale, scale, scale, color2);
	tft.fillRect(anchorX-1*scale, anchorY+4*scale, scale, scale, color2);

	// code for color 3
	tft.fillRect(anchorX-3*scale, anchorY+5*scale, scale, scale, color3);
	tft.fillRect(anchorX+3*scale, anchorY+5*scale, scale, scale, color3);
	tft.fillRect(anchorX, anchorY+4*scale, scale, scale, color3);

	// code for color 4
	tft.fillRect(anchorX-6*scale, anchorY-3*scale, scale, 3*scale, color4);
	tft.fillRect(anchorX-5*scale, anchorY, scale, 2*scale, color4);
	tft.fillRect(anchorX-5*scale, anchorY-4*scale, scale, scale, color4);
	tft.fillRect(anchorX-4*scale, anchorY+2*scale, scale, scale, color4);
	tft.fillRect(anchorX-4*scale, anchorY-5*scale, scale, scale, color4);
	tft.fillRect(anchorX-3*scale, anchorY+3*scale, scale, scale, color4);
	tft.fillRect(anchorX-3*scale, anchorY-6*scale, scale, 4*scale, color4);
	tft.fillRect(anchorX-2*scale, anchorY+2*scale, scale, scale, color4);
	tft.fillRect(anchorX-2*scale, anchorY-2*scale, scale, scale, color4);
	tft.fillRect(anchorX-scale, anchorY+2*scale, scale, 2*scale, color4);
	tft.fillRect(anchorX-scale, anchorY-scale, scale, scale, color4);
	tft.fillRect(anchorX, anchorY+3*scale, scale, scale, color4);
	tft.fillRect(anchorX, anchorY-3*scale, scale, 2*scale, color4);
	tft.fillRect(anchorX+6*scale, anchorY-3*scale, scale, 3*scale, color4);
	tft.fillRect(anchorX+5*scale, anchorY, scale, 2*scale, color4);
	tft.fillRect(anchorX+5*scale, anchorY-4*scale, scale, scale, color4);
	tft.fillRect(anchorX+4*scale, anchorY+2*scale, scale, scale, color4);
	tft.fillRect(anchorX+4*scale, anchorY-5*scale, scale, scale, color4);
	tft.fillRect(anchorX+3*scale, anchorY+3*scale, scale, scale, color4);
	tft.fillRect(anchorX+3*scale, anchorY-6*scale, scale, 4*scale, color4);
	tft.fillRect(anchorX+2*scale, anchorY+2*scale, scale, scale, color4);
	tft.fillRect(anchorX+2*scale, anchorY-2*scale, scale, scale, color4);
	tft.fillRect(anchorX+scale, anchorY+2*scale, scale, 2*scale, color4);
	tft.fillRect(anchorX+scale, anchorY-scale, scale, scale, color4);

	// code for color 5
	tft.fillRect(anchorX-5*scale, anchorY-3*scale, scale, 3*scale, color5);
	tft.fillRect(anchorX-4*scale, anchorY, scale, 2*scale, color5);
	tft.fillRect(anchorX-4*scale, anchorY-4*scale, scale, 2*scale, color5);
	tft.fillRect(anchorX-3*scale, anchorY-2*scale, scale, 5*scale, color5);
	tft.fillRect(anchorX-2*scale, anchorY-scale, scale, 2*scale, color5);
	tft.fillRect(anchorX+5*scale, anchorY-3*scale, scale, 3*scale, color5);
	tft.fillRect(anchorX+4*scale, anchorY, scale, 2*scale, color5);
	tft.fillRect(anchorX+4*scale, anchorY-4*scale, scale, 2*scale, color5);
	tft.fillRect(anchorX+3*scale, anchorY-2*scale, scale, 5*scale, color5);
	tft.fillRect(anchorX+2*scale, anchorY-scale, scale, 2*scale, color5);

	// code for color 6
	tft.fillRect(anchorX-4*scale, anchorY-2*scale, scale, 2*scale, color6);
	tft.fillRect(anchorX-2*scale, anchorY+scale, scale, scale, color6);
	tft.fillRect(anchorX+4*scale, anchorY-2*scale, scale, 2*scale, color6);
	tft.fillRect(anchorX+2*scale, anchorY+scale, scale, scale, color6);	

	// code for color 7
	tft.fillRect(anchorX-scale, anchorY, scale, 2*scale, color7);
	tft.fillRect(anchorX, anchorY-scale, scale, 4*scale, color7);
	tft.fillRect(anchorX+scale, anchorY, scale, 2*scale, color7);
}

void drawExplosion(int16_t anchorX, int16_t anchorY, int16_t scale) {
	// set colors
	int16_t color1 = COLOR_1_EXPLOSION;
	int16_t color2 = COLOR_2_EXPLOSION;
	int16_t color3 = COLOR_3_EXPLOSION;
	int16_t color4 = COLOR_4_EXPLOSION;

	// upper left corner
	tft.drawRect(anchorX-6*scale, anchorY-1*scale, scale, scale, color1);
	tft.drawRect(anchorX-5*scale, anchorY-1*scale, scale, scale, color2);
	tft.drawRect(anchorX-5*scale, anchorY-2*scale, scale, scale, color1);
	tft.drawRect(anchorX-4*scale, anchorY-1*scale, scale, scale, color1);
	tft.drawRect(anchorX-4*scale, anchorY-2*scale, scale, scale, color2);
	tft.drawRect(anchorX-4*scale, anchorY-3*scale, scale, scale, color1);
	tft.drawRect(anchorX-3*scale, anchorY-1*scale, scale, scale, color2);
	tft.drawRect(anchorX-3*scale, anchorY-2*scale, scale, scale, color3);
	tft.drawRect(anchorX-3*scale, anchorY-3*scale, scale, scale, color2);
	tft.drawRect(anchorX-3*scale, anchorY-4*scale, scale, scale, color1);
	tft.drawRect(anchorX-2*scale, anchorY-1*scale, scale, scale, color3);
	tft.drawRect(anchorX-2*scale, anchorY-2*scale, scale, scale, color3);
	tft.drawRect(anchorX-2*scale, anchorY-3*scale, scale, scale, color3);
	tft.drawRect(anchorX-2*scale, anchorY-4*scale, scale, scale, color2);
	tft.drawRect(anchorX-2*scale, anchorY-5*scale, scale, scale, color1);
	tft.drawRect(anchorX-1*scale, anchorY-1*scale, scale, scale, color4);
	tft.drawRect(anchorX-1*scale, anchorY-2*scale, scale, scale, color3);
	tft.drawRect(anchorX-1*scale, anchorY-3*scale, scale, scale, color2);
	tft.drawRect(anchorX-1*scale, anchorY-4*scale, scale, scale, color1);
	tft.drawRect(anchorX-1*scale, anchorY-5*scale, scale, scale, color2);
	tft.drawRect(anchorX-1*scale, anchorY-6*scale, scale, scale, color1);
	tft.drawRect(anchorX-6*scale, anchorY-5*scale, scale, scale, color1);
	tft.drawRect(anchorX-2*scale, anchorY-6*scale, scale, scale, color2);

	// upper right corner
	tft.drawRect(anchorX+6*scale, anchorY-1*scale, scale, scale, color1);
	tft.drawRect(anchorX+5*scale, anchorY-1*scale, scale, scale, color2);
	tft.drawRect(anchorX+5*scale, anchorY-2*scale, scale, scale, color1);
	tft.drawRect(anchorX+4*scale, anchorY-1*scale, scale, scale, color1);
	tft.drawRect(anchorX+4*scale, anchorY-2*scale, scale, scale, color2);
	tft.drawRect(anchorX+4*scale, anchorY-3*scale, scale, scale, color1);
	tft.drawRect(anchorX+3*scale, anchorY-1*scale, scale, scale, color2);
	tft.drawRect(anchorX+3*scale, anchorY-2*scale, scale, scale, color3);
	tft.drawRect(anchorX+3*scale, anchorY-3*scale, scale, scale, color2);
	tft.drawRect(anchorX+3*scale, anchorY-4*scale, scale, scale, color1);
	tft.drawRect(anchorX+2*scale, anchorY-1*scale, scale, scale, color3);
	tft.drawRect(anchorX+2*scale, anchorY-2*scale, scale, scale, color3);
	tft.drawRect(anchorX+2*scale, anchorY-3*scale, scale, scale, color3);
	tft.drawRect(anchorX+2*scale, anchorY-4*scale, scale, scale, color2);
	tft.drawRect(anchorX+2*scale, anchorY-5*scale, scale, scale, color1);
	tft.drawRect(anchorX+1*scale, anchorY-1*scale, scale, scale, color4);
	tft.drawRect(anchorX+1*scale, anchorY-2*scale, scale, scale, color3);
	tft.drawRect(anchorX+1*scale, anchorY-3*scale, scale, scale, color2);
	tft.drawRect(anchorX+1*scale, anchorY-4*scale, scale, scale, color1);
	tft.drawRect(anchorX+1*scale, anchorY-5*scale, scale, scale, color2);
	tft.drawRect(anchorX+1*scale, anchorY-6*scale, scale, scale, color1);
	tft.drawRect(anchorX+4*scale, anchorY-7*scale, scale, scale, color2);
	tft.drawRect(anchorX+6*scale, anchorY-6*scale, scale, scale, color1); 

	//  lower right corner
	tft.drawRect(anchorX+6*scale, anchorY+1*scale, scale, scale, color1);
	tft.drawRect(anchorX+5*scale, anchorY+1*scale, scale, scale, color2);
	tft.drawRect(anchorX+5*scale, anchorY+2*scale, scale, scale, color1);
	tft.drawRect(anchorX+4*scale, anchorY+1*scale, scale, scale, color1);
	tft.drawRect(anchorX+4*scale, anchorY+2*scale, scale, scale, color2);
	tft.drawRect(anchorX+4*scale, anchorY+3*scale, scale, scale, color1);
	tft.drawRect(anchorX+3*scale, anchorY+1*scale, scale, scale, color2);
	tft.drawRect(anchorX+3*scale, anchorY+2*scale, scale, scale, color3);
	tft.drawRect(anchorX+3*scale, anchorY+3*scale, scale, scale, color2);
	tft.drawRect(anchorX+3*scale, anchorY+4*scale, scale, scale, color1);
	tft.drawRect(anchorX+2*scale, anchorY+1*scale, scale, scale, color3);
	tft.drawRect(anchorX+2*scale, anchorY+2*scale, scale, scale, color3);
	tft.drawRect(anchorX+2*scale, anchorY+3*scale, scale, scale, color3);
	tft.drawRect(anchorX+2*scale, anchorY+4*scale, scale, scale, color2);
	tft.drawRect(anchorX+2*scale, anchorY+5*scale, scale, scale, color1);
	tft.drawRect(anchorX+1*scale, anchorY+1*scale, scale, scale, color4);
	tft.drawRect(anchorX+1*scale, anchorY+2*scale, scale, scale, color3);
	tft.drawRect(anchorX+1*scale, anchorY+3*scale, scale, scale, color2);
	tft.drawRect(anchorX+1*scale, anchorY+4*scale, scale, scale, color1);
	tft.drawRect(anchorX+1*scale, anchorY+5*scale, scale, scale, color2);
	tft.drawRect(anchorX+1*scale, anchorY+6*scale, scale, scale, color1);
	tft.drawRect(anchorX+4*scale, anchorY+7*scale, scale, scale, color3);
	tft.drawRect(anchorX+5*scale, anchorY+5*scale, scale, scale, color1); 

	//  lower left corner
	tft.drawRect(anchorX-6*scale, anchorY+1*scale, scale, scale, color1);
	tft.drawRect(anchorX-5*scale, anchorY+1*scale, scale, scale, color2);
	tft.drawRect(anchorX-5*scale, anchorY+2*scale, scale, scale, color1);
	tft.drawRect(anchorX-4*scale, anchorY+1*scale, scale, scale, color1);
	tft.drawRect(anchorX-4*scale, anchorY+2*scale, scale, scale, color2);
	tft.drawRect(anchorX-4*scale, anchorY+3*scale, scale, scale, color1);
	tft.drawRect(anchorX-3*scale, anchorY+1*scale, scale, scale, color2);
	tft.drawRect(anchorX-3*scale, anchorY+2*scale, scale, scale, color3);
	tft.drawRect(anchorX-3*scale, anchorY+3*scale, scale, scale, color2);
	tft.drawRect(anchorX-3*scale, anchorY+4*scale, scale, scale, color1);
	tft.drawRect(anchorX-2*scale, anchorY+1*scale, scale, scale, color3);
	tft.drawRect(anchorX-2*scale, anchorY+2*scale, scale, scale, color3);
	tft.drawRect(anchorX-2*scale, anchorY+3*scale, scale, scale, color3);
	tft.drawRect(anchorX-2*scale, anchorY+4*scale, scale, scale, color2);
	tft.drawRect(anchorX-2*scale, anchorY+5*scale, scale, scale, color1);
	tft.drawRect(anchorX-1*scale, anchorY+1*scale, scale, scale, color4);
	tft.drawRect(anchorX-1*scale, anchorY+2*scale, scale, scale, color3);
	tft.drawRect(anchorX-1*scale, anchorY+3*scale, scale, scale, color2);
	tft.drawRect(anchorX-1*scale, anchorY+4*scale, scale, scale, color1);
	tft.drawRect(anchorX-1*scale, anchorY+5*scale, scale, scale, color2);
	tft.drawRect(anchorX-1*scale, anchorY+6*scale, scale, scale, color1); 
	tft.drawRect(anchorX-6*scale, anchorY+5*scale, scale, scale, color2);
	tft.drawRect(anchorX-2*scale, anchorY+6*scale, scale, scale, color3);

	// inner x axis
	tft.drawRect(anchorX-5*scale, anchorY, scale, scale, color1);
	tft.drawRect(anchorX-4*scale, anchorY, scale, scale, color2);
	tft.drawRect(anchorX-3*scale, anchorY, scale, scale, color3);
	tft.drawRect(anchorX-2*scale, anchorY, scale, scale, color4);
	tft.drawRect(anchorX-1*scale, anchorY, scale, scale, color4);
	tft.drawRect(anchorX, anchorY, scale, scale, color4);
	tft.drawRect(anchorX+5*scale, anchorY, scale, scale, color1);
	tft.drawRect(anchorX+4*scale, anchorY, scale, scale, color2);
	tft.drawRect(anchorX+3*scale, anchorY, scale, scale, color3);
	tft.drawRect(anchorX+2*scale, anchorY, scale, scale, color4);
	tft.drawRect(anchorX+1*scale, anchorY, scale, scale, color4);

	// inner y axis
	tft.drawRect(anchorX, anchorY-5*scale, scale, scale, color1);
	tft.drawRect(anchorX, anchorY-4*scale, scale, scale, color2);
	tft.drawRect(anchorX, anchorY-3*scale, scale, scale, color3);
	tft.drawRect(anchorX, anchorY-2*scale, scale, scale, color4);
	tft.drawRect(anchorX, anchorY-1*scale, scale, scale, color4);
	tft.drawRect(anchorX, anchorY+5*scale, scale, scale, color1);
	tft.drawRect(anchorX, anchorY+4*scale, scale, scale, color2);
	tft.drawRect(anchorX, anchorY+3*scale, scale, scale, color3);
	tft.drawRect(anchorX, anchorY+2*scale, scale, scale, color4);
	tft.drawRect(anchorX, anchorY+1*scale, scale, scale, color4);


}
int main() {
	setup();
	/*
	drawSpaceship(TFT_WIDTH/4, TFT_HEIGHT/2, 3, 'P');
	drawSpaceship(3*TFT_WIDTH/4, TFT_HEIGHT/2, -3, 'E');
	*/
	drawExplosion(TFT_WIDTH/4, TFT_HEIGHT/2, 3);
	Serial.end();

	return 0;
}