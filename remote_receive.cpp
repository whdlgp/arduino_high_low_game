/*
 * remote_receive.cpp
 *
 *  Created on: 2017. 11. 18.
 *      Author: whdlg
 */

#include "remote_receive.h"
#include <IRremote.h>

int RECV_PIN = 12;   //IR receiver OUTPUT terminated at pin 12
IRrecv irrecv(RECV_PIN);   // Define IRrecv object to receive infrared signals
decode_results  results;   //Decoding results on decode_results constructed object results in

static uint32_t input_val = 0;

//remote controller command
uint32_t remote_val[11] =
{
        0xFF6897 //0
        , 0xFF30CF //1
        , 0xFF18E7 //2
        , 0xFF7A85 //3
        , 0xFF10EF //4
        , 0xFF38C7 //5
        , 0xFF5AA5 //6
        , 0xFF42BD //7
        , 0xFF4AB5 //8
        , 0xFF52AD //9
        , 0xFFA857 }; //confirm

void remote_setup()
{
    irrecv.enableIRIn(); // Start IR decoding
}

//check some value in list received
int remote_available()
{
    int retval = 0;
    if(irrecv.decode(&results))
    {
        for(uint8_t i = 0; i < (sizeof(remote_val) / sizeof(remote_val[0])); i++)
        {
            if (results.value == remote_val[i])
            {
                input_val = i;
                retval = 1;
            }
        }

        irrecv.resume();
    }

    return retval;
}

uint32_t remote_read()
{
    return input_val;
}
