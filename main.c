/**
 *  @file    main.c
 *  @authors Harrison Parkes
 *  @date    10th of November 2022
 *  @brief   Pong main loop
*/

#include "../drivers/avr/system.h"
#include "../drivers/navswitch.h"
#include "../drivers/display.h"
#include "../common/position.h"
#include "../drivers/button.h"
#include "../drivers/led.h"
#include "../utils/pacer.h"
#include "paddle.h"
#include "ball.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define DISPLAY_FREQUENCY 300

//typedef enum game_state_e {
//    Playing,
//    Lost,
//} Game_State_t;
//Game_State_t currentState = Placing_Ships;

bool is_playing = true;

bool display[7][5];
void update_display(void);

int main (void)
{
    led_init();
    button_init();
    system_init();
    pacer_init(DISPLAY_FREQUENCY); // Initialize pacer to 300Hz so display columns update at 60Hz
    led_set(LED1, 0);

    while (1)
    {
        memset(display, 0, 35);

        navswitch_update(); // Get new readings from navswitch
        button_update(); // Get new readings from button

        if (is_playing) {
            // ball can bounce and paddle can move.
            led_set(LED1, 1);
            paddle_control();
            ball_update();
        } else {
            // game is lost
        }

        update_display();
//        miniGL_update(); // Refresh the matrix display
        pacer_wait(); // Wait for next pacer tick
    }
}

void update_display(void)
{
    for (uint8_t row = 0; row < 7; row++) {
        for (uint8_t col = 0; col < 5; col++) {
            display_pixel_set(col, row, display[row][col]);
        }
    }
    display_update();
}