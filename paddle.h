/**
 *  @file    paddle.h
 *  @authors Harrison Parkes
 *  @date    10th of November 2022
 *  @brief   paddle related functionality
*/

#ifndef HARRY_PARKES_UCFK4_PADDLE_H
#define HARRY_PARKES_UCFK4_PADDLE_H

#include <stdbool.h>
#include "../common/Position.h"

extern void paddle_control();
extern bool paddle_collision(const Pos_t * const pos);
extern int8_t paddle_velocity();

#endif //HARRY_PARKES_UCFK4_PADDLE_H
