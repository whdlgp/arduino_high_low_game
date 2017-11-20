#include "fnd_display.h"
#include "remote_receive.h"
#include "game_user_input.h"

enum
{
    MAKE_RANDOM,
    RECEIVE_USER_INPUT,
    HIGH_OR_LOW,
};

void setup()
{
    //remote controller setup
    remote_setup();

    //first display is '0'
    display_setup();

    //setup random seed to analog input pin 0
    randomSeed(analogRead(0));
}

void loop()
{
    static uint16_t user_input = 0;
    static uint16_t random_val = 0;

    int user_confirmed = 0;

    static uint8_t game_status = 0;
    static uint8_t game_count = 0;
    switch(game_status)
    {
    case MAKE_RANDOM: //make random value 0~100
        random_val = random(100);
        game_status = RECEIVE_USER_INPUT;
        break;

    case RECEIVE_USER_INPUT: //receive user input and wait until confirm
        user_confirmed = user_input_state(&user_input);
        if(user_confirmed == NOT_CONFIRMED)
        {
            //user send some input but not confirm
            //just display user command
            display_set_val(DISP_NUM, user_input);
        }
        else if(user_confirmed == CONFIRMED)
        {
            game_count++;
            //user confirmed input. let's go next step
            game_status = HIGH_OR_LOW;
        }
        break;

    case HIGH_OR_LOW: //compare user input and random value
        //if game player input matched or can't matched until count 10, display random value
        if((user_input == random_val) || (game_count > 9))
        {
            // random value and user command matched, start again
            game_count = 0;
            display_set_val(DISP_NUM, random_val);
            game_status = MAKE_RANDOM;
        }
        else if(user_input > random_val)
        {
            display_set_val(DISP_RESULT, HIGH);
            game_status = RECEIVE_USER_INPUT;
        }
        else if(user_input < random_val)
        {
            display_set_val(DISP_RESULT, LOW);
            game_status = RECEIVE_USER_INPUT;
        }

        user_input_init();
        break;
    }

    //display must be process with fast period
    //run asynchronously
    display_process(6);
}
