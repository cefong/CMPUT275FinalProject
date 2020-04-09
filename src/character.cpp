/*
Names: Claire Martin (1571140), Celine Fong, Minh Dang, Zi Xue Lim
CMPUT 275, Winter 2020

Final Project: A Variation on 'Galaga'
character.cpp: Character/graphics control
*/

#include "character.h"

// define array of bullet structs (size is number allowed on screen at once)
bullet ammo[PLAY_NUM_BULLET];

static void draw_bullet(bool is_player, int x, int y) {
    /*
	Draws a bullet starting from top or bottom depending on character type.

	PARAMETERS:
		is_player: True if the character shooting is a player, false if it is an alien
		x: current x position of bullet
		y: current y position of bullet
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
        // draw black rectangle at old location
        tft.fillRoundRect(x, y - BULLET_HEIGHT, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, TFT_BLACK);
    }


}


void drawHeart(int16_t anchorX, int16_t anchorY, int16_t scale, int16_t color = TFT_RED) {
	/*
	Draws a bullet starting from top or bottom depending on character type.

	PARAMETERS:
		anchorX: Anchor x position for bitmap (top left)
		anchorY: Anchor y position for bitmap (top left)
		scale: Chosen scale of bitmap (able to make large or smaller)
		color: Chosen colour of character (default red for aliens)
    */
    // anchor point in upper left corner
    tft.drawRect(anchorX, anchorY+2*scale, scale, 3*scale, color);
    tft.drawRect(anchorX+1*scale, anchorY+1*scale, scale, 5*scale, color);
    tft.drawRect(anchorX+2*scale, anchorY+1*scale, scale, 6*scale, color);
    tft.drawRect(anchorX+3*scale, anchorY+2*scale, scale, 6*scale, color);
    tft.drawRect(anchorX+4*scale, anchorY+3*scale, scale, 6*scale, color);
    tft.drawRect(anchorX+8*scale, anchorY+2*scale, scale, 3*scale, color);
    tft.drawRect(anchorX+7*scale, anchorY+1*scale, scale, 5*scale, color);
    tft.drawRect(anchorX+6*scale, anchorY+1*scale, scale, 6*scale, color);
    tft.drawRect(anchorX+5*scale, anchorY+2*scale, scale, 6*scale, color);   
}


void drawSpaceship(player_alien* ship, int16_t scale) {
	/*
	Draws the spaceships at player and bot locations

	PARAMETERS:
		ship: The character to be drawn (can be either player or alien)
		scale: Size of character
	*/

	if(ship->is_active) {
		int16_t color1, color2, color3, color4, color5, color6, color7;
		int16_t anchorX = ship->x;
		int16_t anchorY = ship->y;
		// change colour of ship based on character type
		if (ship->is_player) {
			// if player, use player colours
			tft.fillCircle(ship->x_temp, ship->y_temp, size*scale, TFT_BLACK);
			color1 = COLOR_1_PLAYER;
			color2 = COLOR_2_PLAYER;
			color3 = COLOR_3_PLAYER;
			color4 = COLOR_4_PLAYER;
			color5 = COLOR_5_PLAYER;
			color6 = COLOR_6_PLAYER;
			color7 = COLOR_7_PLAYER;
		} 
		else {
			// if alien, use alien colours
			tft.fillCircle(ship->x_temp, ship->y_temp, (size+1)*scale, TFT_BLACK);
			scale *= -1;
			color1 = COLOR_1_ENEMY;
			color2 = COLOR_2_ENEMY;
			color3 = COLOR_3_ENEMY;
			color4 = COLOR_4_ENEMY;
			color5 = COLOR_5_ENEMY;
			color6 = COLOR_6_ENEMY;
			color7 = COLOR_7_ENEMY;
		}
		// update x and y position
		ship->x_temp = ship->x;
		ship->y_temp = ship->y;
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


void fire_bullet(player_alien *ship) {
	/*
	Fire bullet from player or bot.

	PARAMETERS:
		ship: The character that is currently firing
	*/

	// define x and y starting positions of bullet
	int x = ship->x;
	int y = ship->y;
	// determine if bullet should come from bottom or top (alien or player)
	bool is_player = ship->is_player;
    for(int i = 0; i < PLAY_NUM_BULLET; i++) {
		// allows us to have multiple bullets going at once
        if(!ammo[i].active) {
            ammo[i].active = true;
            ammo[i].player = is_player;
            ammo[i].x = x;
			// if player, move up the screen (subtract from y position)
            if(is_player) ammo[i].y = y - 2 * BULLET_HEIGHT;
			// if alien, move down the screen
            else ammo[i].y = y + 2 * BULLET_HEIGHT;            
            break;
        }
    }
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


void bullet_update(player_alien *bot, player_alien *player, uint32_t high_score) {
	/*
	Updates bullet positions for bots and players.

	PARAMETERS:
		bot: The alien in play
		player: The player
    */

    // iterate through each bullet
    for(int i = 0; i < PLAY_NUM_BULLET; i++) {
        if(ammo[i].active) {
			// draw active bullets
            draw_bullet(ammo[i].player, ammo[i].x, ammo[i].y);
            if(ammo[i].y < 50 + 2*BULLET_HEIGHT || ammo[i].y > HEIGHT - 50 - 2*BULLET_HEIGHT) {
				// if bullet hits edge of screen, deactivate and remove it
				tft.fillRoundRect(ammo[i].x, ammo[i].y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, TFT_BLACK);
                ammo[i].active = false;
            }
            else {
                if(ammo[i].player) {
					// if bullet was fired from player
                    ammo[i].y -= BULLET_HEIGHT;
                    tft.setTextColor(TFT_RED);
                    if((((bot->x)+15) >= ammo[i].x) && (((bot->x)-15) <= ammo[i].x)  && (((bot->y)+15) >= ammo[i].y) && (((bot->y)-15) <= ammo[i].y) && bot->is_active ){
                        ammo[i].active=0;
                        drawExplosion(bot->x,bot->y , 3); // put radius as 40 so dont have to delete bullets
						tft.fillCircle(bot->x, bot->y, 40, TFT_BLACK); 
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
							if(player->score > high_score) {
								tft.setCursor(10, 30);
								tft.print(player->score);
							}
                        }
                	}
                }
                else {
                    ammo[i].y += BULLET_HEIGHT;
                    if((((player->x)+15) >= ammo[i].x) && (((player->x)-15) <= ammo[i].x)  && (((player->y)+15) >= ammo[i].y) && (((player->y)-15) <= ammo[i].y) && player->is_active ){
                        ammo[i].active=0;
                        drawExplosion(player->x,player->y , 3); // put radius samller than bot cause the floor gets removed at 40
						tft.fillCircle(player->x, player->y, 30, TFT_BLACK);
                        player->lives = (player->lives)-1;
						// erase heart at bottom of screen
						tft.fillRect(10+(player->lives)*30, HEIGHT-20, 18, 18, TFT_BLACK);
                        if((player -> lives) == 0){ // do something when the player dies.
							drawExplosion(player->x,player->y , 3);
							tft.fillCircle(player->x, player->y, 30, TFT_BLACK);
							player -> is_active = false;
							// exit out of game, display score and display option to return to main screen
                        }
                	}
            	}
       		}
    	}
	}
} 
/*
void bullet_update(player_alien *bot, player_alien *player) {
	int player_ammo = PLAYER_BULLETS;
	int enemy_ammo = ENEMY_BULLETS;
    for(int i = 0; i < PLAY_NUM_BULLET; i++) {
        if(ammo[i].active) {
            draw_bullet(ammo[i].player, ammo[i].x, ammo[i].y);
            if(ammo[i].y < 50 + 2*BULLET_HEIGHT || ammo[i].y > HEIGHT - 50 - 2*BULLET_HEIGHT) {
                tft.fillRoundRect(ammo[i].x, ammo[i].y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, TFT_BLACK);
                ammo[i].active = false;
            }
            else {
                if(ammo[i].player) {
					// if bullet was fired from player
                    ammo[i].y -= BULLET_HEIGHT;
                    tft.setTextColor(TFT_RED);
                    if((((bot->x)+15) >= ammo[i].x) && (((bot->x)-15) <= ammo[i].x)  && (((bot->y)+15) >= ammo[i].y) && (((bot->y)-15) <= ammo[i].y) && bot->is_active ){
                        ammo[i].active=0;
                        drawExplosion(bot->x,bot->y , 3); // put radius as 40 so dont have to delete bullets
						tft.fillCircle(bot->x, bot->y, 40, TFT_BLACK); 
                        bot->lives = (bot->lives)-1;
                        if((bot -> lives) == 0){
							// if bot is dead
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
							if(player->score > high_score) {
								tft.setCursor(10, 30);
            					tft.print(player->score);
							}
                        }
                	}
                }
                else {
					// if bullet was fired by alien
                    ammo[i].y += BULLET_HEIGHT;
                    if((((player->x)+15) >= ammo[i].x) && (((player->x)-15) <= ammo[i].x)  && (((player->y)+15) >= ammo[i].y) && (((player->y)-15) <= ammo[i].y) && player->is_active ){
                        ammo[i].active=0;
                        drawExplosion(player->x,player->y , 3); // put radius samller than bot cause the floor gets removed at 40
						tft.fillCircle(player->x, player->y, 30, TFT_BLACK);
                        player->lives = (player->lives)-1;
						// erase heart at bottom of screen
						tft.fillRect(10+(player->lives)*30, HEIGHT-20, 18, 18, TFT_BLACK);
                        if((player -> lives) == 0){ // do something when the player dies.
							drawExplosion(player->x,player->y , 3);
							tft.fillCircle(player->x, player->y, 30, TFT_BLACK);
							player -> is_active = false;
							// exit out of game, display score and display option to return to main screen
                        }
                	}
            	}
       		}
    	}
	}
}
*/