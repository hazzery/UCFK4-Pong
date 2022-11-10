/**
 *  @file    paddle.h
 *  @authors Harrison Parkes
 *  @date    10th of November 2022
 *  @brief   paddle related functionality
*/

#include "../drivers/navswitch.h"
#include "../common/Position.h"
#include "../common/config.h"
#include "paddle.h"

static Pos_t paddle_position;

void paddle_control()
{
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
