/**
 *  @file    main.c
 *  @authors Harrison Parkes
 *  @date    10th of November 2022
 *  @brief   Pong main loop
*/

#include "../drivers/avr/system.h"
#include "../drivers/navswitch.h"
#include "../common/position.h"
#include "../drivers/button.h"
#include "../drivers/led.h"
#include "../utils/pacer.h"
#include <stdint.h>
#include <stdbool.h>

#define DISPLAY_FREQUENCY 300

//typedef enum game_state_e {
//    Playing,
//    Lost,
//} Game_State_t;
//Game_State_t currentState = Placing_Ships;

bool is_playing = true;

int main (void)
{
    led_init();
    button_init();
    system_init();
    pacer_init(DISPLAY_FREQUENCY); // Initialize pacer to 300Hz so display columns update at 60Hz

    Pos_t ball_pos = {.row = 0, .col = 2};

    while (1)
    {
        navswitch_update(); // Get new readings from navswitch
        button_update(); // Get new readings from button

        if (is_playing) {
            // ball can bounce and paddle can move.
        } else {
            // game is lost
        }

//        miniGL_update(); // Refresh the matrix display
        pacer_wait(); // Wait for next pacer tick
    }
}