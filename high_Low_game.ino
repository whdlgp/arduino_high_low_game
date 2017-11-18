#include "fnd_display.h"

//remote controller command index
enum
{
    REMOTE_CONFIRM = 0,
    REMOTE_0,
    REMOTE_1,
    REMOTE_2,
    REMOTE_3,
    REMOTE_4,
    REMOTE_5,
    REMOTE_6,
    REMOTE_7,
    REMOTE_8,
    REMOTE_9,
};
//remote controller command
uint32_t remote_val[11] =
{
        0xFFA857 //confirm
        , 0xFF6897 //0
        , 0xFF30CF //1
        , 0xFF18E7 //2
        , 0xFF7A85 //3
        , 0xFF10EF //4
        , 0xFF38C7 //5
        , 0xFF5AA5 //6
        , 0xFF42BD //7
        , 0xFF4AB5 //8
        , 0xFF52AD }; //9

void setup()
{
    //first display is '0'
    display_setup();
}

void loop()
{
    display_process(6);
}
