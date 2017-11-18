#include "fnd_display.h"

//FND pin layout
enum
{
    DISP1 = 2,
    DISP2 = 3,
    DISP3 = 4,

    FND_A = 5,
    FND_B = 6,
    FND_C = 7,
    FND_D = 8,
    FND_E = 9,
    FND_F = 10,
    FND_G = 11,
};

// Font array index
enum
{
    FONT_0 = 0,
    FONT_1,
    FONT_2,
    FONT_3,
    FONT_4,
    FONT_5,
    FONT_6,
    FONT_7,
    FONT_8,
    FONT_9,

    FONT_H,
    FONT_L,
    FONT_I,
    FONT_O
};

//Font array
static uint8_t fnd_font[14][7] =
{
        1, 1, 1, 1, 1, 1, 0
        , 0, 1, 1, 0, 0, 0, 0
        , 1, 1, 0, 1, 1, 0, 1
        , 1, 1, 1, 1, 0, 0, 1
        , 0, 1, 1, 0, 0, 1, 1
        , 1, 0, 1, 1, 0, 1, 1
        , 1, 0, 1, 1, 1, 1, 1
        , 1, 1, 1, 0, 0, 1, 0
        , 1, 1, 1, 1, 1, 1, 1
        , 1, 1, 1, 1, 0, 1, 1
        , 0, 1, 1, 0, 1, 1, 1
        , 0, 0, 0, 1, 1, 1, 0
        , 0, 0, 0, 0, 1, 1, 0
        , 0, 0, 1, 1, 1, 0, 1 };

static uint8_t disp_type;
static uint16_t disp_val;

void display_setup()
{
    //FND SETUP
    for (int i = 0; i < 12; i++)
    {
        pinMode(i + 2, OUTPUT);
    }

    disp_type = DISP_NUM;
    disp_val = 0;
}

void digit3_disp_num(uint8_t num, uint8_t val)
{
    //select
    switch (num)
    {
    case 1:
        digitalWrite(DISP1, HIGH);
        digitalWrite(DISP2, LOW);
        digitalWrite(DISP3, LOW);
        break;
    case 2:
        digitalWrite(DISP1, LOW);
        digitalWrite(DISP2, HIGH);
        digitalWrite(DISP3, LOW);
        break;
    case 3:
        digitalWrite(DISP1, LOW);
        digitalWrite(DISP2, LOW);
        digitalWrite(DISP3, HIGH);
        break;
    default:
        digitalWrite(DISP1, LOW);
        digitalWrite(DISP2, LOW);
        digitalWrite(DISP3, LOW);
        break;
    }

    //write value
    for (int i = 0; i < 7; i++)
    {
        digitalWrite(FND_A + i, !fnd_font[val][i]);
    }
}

void display_number(uint16_t num)
{
    static uint8_t state = 0;

    uint16_t hundreds = num / 100;
    uint16_t tens = (num % 100) / 10;
    uint16_t ones = num % 10;

    switch(state)
    {
    case 0:
        if(hundreds == 0)
        {
            //4 means 'no display'
            digit3_disp_num(4, 0);
        }
        else
        {
            digit3_disp_num(1, hundreds);
        }
        state = 1;
        break;
    case 1:
        if(tens == 0)
        {
            //4 means 'no display'
            digit3_disp_num(4, 0);
        }
        else
        {
            digit3_disp_num(2, tens);
        }
        state = 2;
        break;
    case 2:
        digit3_disp_num(3, ones);
        state = 0;
        break;
    default:
        break;
    }
}

void display_high_low(bool val)
{
    static uint8_t state = 0;

    switch (val)
    {
    case HIGH:
        if(state == 0)
        {
            digitalWrite(DISP1, HIGH);
            digitalWrite(DISP2, LOW);
            digitalWrite(DISP3, LOW);

            //write value
            for(int i = 0; i < 7; i++)
            {
                digitalWrite(FND_A + i, !fnd_font[FONT_H][i]);
            }
            state = 1;
        }
        else
        {
            digitalWrite(DISP1, LOW);
            digitalWrite(DISP2, HIGH);
            digitalWrite(DISP3, LOW);

            //write value
            for(int i = 0; i < 7; i++)
            {
                digitalWrite(FND_A + i, !fnd_font[FONT_I][i]);
            }
            state = 0;
        }
        break;

    case LOW:
        if(state == 0)
        {
            digitalWrite(DISP1, HIGH);
            digitalWrite(DISP2, LOW);
            digitalWrite(DISP3, LOW);

            //write value
            for(int i = 0; i < 7; i++)
            {
                digitalWrite(FND_A + i, !fnd_font[FONT_L][i]);
            }
            state = 1;
        }
        else
        {
            digitalWrite(DISP1, LOW);
            digitalWrite(DISP2, HIGH);
            digitalWrite(DISP3, LOW);

            //write value
            for(int i = 0; i < 7; i++)
            {
                digitalWrite(FND_A + i, !fnd_font[FONT_O][i]);
            }
            state = 0;
        }
        break;
    default:
        break;
    }
}


//usage example
//display_set_val(DISP_NUM, 123)
//display_set_val(DISP_RESULT, HIGH)
//display_set_val(DISP_RESULT, LOW)
void display_set_val(uint8_t type, uint16_t val)
{
    disp_type = type;
    disp_val = val;
}

void display_process(uint32_t period_ms)
{
    static uint32_t pre_time = 0;
    uint32_t time = millis();

    if((time - pre_time) > period_ms)
    {
        switch(disp_type)
        {
        case DISP_NUM:
            //display_number
            display_number(disp_val);
            break;

        case DISP_RESULT:
            //display result
            display_high_low(disp_val);
            break;

        default:
            break;
        }

        pre_time = time;
    }
}
