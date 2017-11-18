#include "game_user_input.h"

static uint8_t user_input_raw[3] = {0,};

void user_input_init()
{
    user_input_raw[0] = 0;
    user_input_raw[1] = 0;
    user_input_raw[2] = 0;
}

//return value
//0 means no input
//1 means input received but not confirmed
//2 means input confirmed
int user_input_state(uint16_t* user_input)
{
    int retval = NO_INPUT;

    if(remote_available())
    {
        uint8_t tmp = remote_read();

        if((tmp <= REMOTE_9) && (tmp >= REMOTE_0))
        {
            user_input_raw[0] = user_input_raw[1];
            user_input_raw[1] = user_input_raw[2];
            user_input_raw[2] = tmp;

            *user_input = user_input_raw[0] * 100
                          +user_input_raw[1] * 10
                          +user_input_raw[2];

            retval = NOT_CONFIRMED;
        }
        else if(tmp == REMOTE_CONFIRM)
        {
            retval = CONFIRMED;
        }
    }

    return retval;
}


