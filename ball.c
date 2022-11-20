/**
 *  @file    ball.c
 *  @authors Harrison Parkes
 *  @date    10th of November 2022
 *  @brief   ball physics for pong
*/

#include "../common/Position.h"
#include "../common/vector.h"
#include "../common/config.h"
#include "paddle.h"
#include "ball.h"

static vector_t ball_velocity = {.x = 1, .y = -1};
static Pos_t ball_position = {.row = 0, .col = 1};

extern bool display[7][5];
extern bool is_playing;

void ball_update(void)
{
    ball_position.col += ball_velocity.x;
    ball_position.row += ball_velocity.y;

    if (ball_position.col > GRID_WIDTH - 1) {
        ball_position.col = GRID_WIDTH -1;
    }
    if (ball_position.row > GRID_HEIGHT - 1) {
        ball_position.row = GRID_HEIGHT -1;
    }

    if (ball_position.row == GRID_HEIGHT - 1) {
        if (paddle_collision(&ball_position)) {
            ball_velocity.y *= -1;
            ball_velocity.x += paddle_velocity();
        } else {
            is_playing = false;
        }
    } else if (ball_position.row == 0) {
        ball_velocity.y *= -1;
    }

    if (ball_position.col == GRID_WIDTH - 1 || ball_position.col == 0) {
        ball_velocity.x *= -1;
    }

    display[ball_position.row][ball_position.col] = 1;
}
