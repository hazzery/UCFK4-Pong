/**
 *  @file    paddle.h
 *  @authors Harrison Parkes
 *  @date    10th of November 2022
 *  @brief   paddle related functionality
*/

#include <stdbool.h>
#include "../drivers/navswitch.h"
#include "../common/Position.h"
#include "../common/config.h"
#include "paddle.h"

static Pos_t paddle_position = {.row = GRID_HEIGHT - 1, .col = 4};
static int8_t previous_position = 4;

void paddle_control()
{
    previous_position = paddle_position.col;

    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        if (paddle_position.col < GRID_WIDTH) {
            paddle_position.col += 1;
        }
    } else if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        if (paddle_position.col > 0) {
            paddle_position.col -= 1;
        }
    }
}

bool paddle_collision(const Pos_t* const pos)
{
    if (pos->col == paddle_position.col || pos->col == paddle_position.col + 1) {
        return true;
    } else {
        return false;
    }
}

int8_t paddle_velocity()
{
    return paddle_position.col - previous_position;
}