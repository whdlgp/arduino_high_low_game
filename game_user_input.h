#ifndef GAME_USER_INPUT_H_
#define GAME_USER_INPUT_H_

#include "remote_receive.h"

enum
{
    NO_INPUT,
    NOT_CONFIRMED,
    CONFIRMED,
};

void user_input_init();
int user_input_state(uint16_t* user_input);

#endif /* GAME_USER_INPUT_H_ */
