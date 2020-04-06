#include "character.h"

// define array of bullet structs (size is number allowed on screen at once)
bullet ammo[PLAY_NUM_BULLET];
static void draw_bullet(bool is_player, int x, int y) {
    /*
	Draws a bullet starting from top or bottom depending on character type.
    */
    if(is_player) {
        // if player, start from bottom
        // draw a bullet at current x and y position
        tft.fillRoundRect(x, y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, BULLET_COLOR_P);
        // draw black rectangle at old location
        tft.fillRoundRect(x, y + BULLET_HEIGHT, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, TFT_BLACK);
    }
    else {
        // if alien, start at top
        // draw bullet at current x and y pos 
        tft.fillRoundRect(x, y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, BULLET_COLOR_B);
        // draw black circle at old location
        tft.fillRoundRect(x, y - BULLET_HEIGHT, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, TFT_BLACK);
    }


}
void drawSpaceship(player_alien* player, int16_t x_pos, int16_t y_pos, int16_t scale) {
	/*
	Draws the spaceships at player and bot locations
	*/
	if(player->is_active) {
		int16_t color1, color2, color3, color4, color5, color6, color7;
		int16_t anchorX = player->x;
		int16_t anchorY = player->y;
		// change colour of ship based on character type
		if (player->is_player) {
			tft.fillCircle(x_pos, y_pos, size*scale, TFT_BLACK);
			color1 = COLOR_1_PLAYER;
			color2 = COLOR_2_PLAYER;
			color3 = COLOR_3_PLAYER;
			color4 = COLOR_4_PLAYER;
			color5 = COLOR_5_PLAYER;
			color6 = COLOR_6_PLAYER;
			color7 = COLOR_7_PLAYER;
		} 
		else {
			tft.fillCircle(x_pos, y_pos, (size+1)*scale, TFT_BLACK);
			scale *= -1;
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

}

// void draw_bot(int x, int y, int x_pos, int y_pos) {
//     tft.fillCircle(x_pos, y_pos, bot_size, TFT_BLACK);
//     tft.fillCircle(x, y, bot_size, BOT_COLOR);
// }

// void draw_player(int x, int y, int x_pos, int y_pos) {
//     tft.fillCircle(x_pos, y_pos, player_size, TFT_BLACK);
//     tft.fillCircle(x, y, player_size, PLAYER_COLOR);
// }

void fire_bullet(player_alien *player) {
	/*
	Fire bullet from player or bot
	*/
	int x = player->x;
	int y = player->y;
	bool is_player = player->is_player;
    for(int i = 0; i < PLAY_NUM_BULLET; i++) {
		// allows us to have multiple bullets going at once
        if(!ammo[i].active) {
            ammo[i].active = true;
            ammo[i].player = is_player;
            ammo[i].x = x;
            if(is_player) ammo[i].y = y - 2 * BULLET_HEIGHT;
            else ammo[i].y = y + 2 * BULLET_HEIGHT;
            
            break;
        }
    }
}


void drawExplosion(int x, int y, int radius, uint16_t colorBull){
    tft.drawCircle(x,y , radius, colorBull);
    tft.fillCircle(x,y , radius, colorBull);
    tft.drawCircle(x,y , radius, TFT_BLACK);
    tft.fillCircle(x,y , radius, TFT_BLACK);
}

void bullet_update(player_alien *bot, player_alien *player) {
    for(int i = 0; i < PLAY_NUM_BULLET; i++) {
        if(ammo[i].active) {
            draw_bullet(ammo[i].player, ammo[i].x, ammo[i].y);
            if(ammo[i].y < 50 + 2*BULLET_HEIGHT || ammo[i].y > HEIGHT - 50 - 2*BULLET_HEIGHT) {
                tft.fillRoundRect(ammo[i].x, ammo[i].y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, TFT_BLACK);
                ammo[i].active = false;
            }
            else {
                if(ammo[i].player) {
                    ammo[i].y -= BULLET_HEIGHT;
                    tft.setTextColor(TFT_RED);
                    if((((bot->x)+15) >= ammo[i].x) & (((bot->x)-15) <= ammo[i].x)  & (((bot->y)+15) >= ammo[i].y) & (((bot->y)-15) <= ammo[i].y) ){
                        ammo[i].active=0;
                        drawExplosion(bot->x,bot->y , 40, TFT_CYAN); // put radius as 40 so dont have to delete bullets 
                        bot->lives = (bot->lives)-1;
                        if((bot -> lives) == 0){ // do something when the bot dies.
							bot -> is_active = false;
							bot -> x = 0;
							bot -> y = 0;
							// erase old score
							tft.setTextColor(TFT_WHITE, TFT_BLACK);
							tft.fillRect(200, 30, WIDTH - 200, 15, TFT_BLACK);
							// update score
							player -> score += 100;
			            	tft.setCursor(200, 30);
            				tft.print(player->score);
                        }
                	}
                }
                else {
                    ammo[i].y += BULLET_HEIGHT;
                    if((((player->x)+15) >= ammo[i].x) & (((player->x)-15) <= ammo[i].x)  & (((player->y)+15) >= ammo[i].y) & (((player->y)-15) <= ammo[i].y) ){
                        ammo[i].active=0;
                        drawExplosion(player->x,player->y , 29, TFT_GREEN); // put radius samller than bot cause the floor gets removed at 40
                        player->lives = (player->lives)-1;
						// erase heart at bottom of screen
						tft.fillRect(10+(player->lives)*30, HEIGHT-20, 18, 18, TFT_BLACK);
                        if((player -> lives) == 0){ // do something when the player dies.
                            drawExplosion(player->x,player->y , 29, TFT_RED); // make sure game over
							// player -> is_active = false;
							// exit out of game, display score and display option to return to main screen
                        }
                	}
            	}
       		}
    	}
	}
}