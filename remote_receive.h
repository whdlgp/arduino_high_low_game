/*
 * remote_receive.h
 *
 *  Created on: 2017. 11. 18.
 *      Author: whdlg
 */

#ifndef REMOTE_RECEIVE_H_
#define REMOTE_RECEIVE_H_

#include "Arduino.h"

//remote controller command index
enum
{
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
    REMOTE_CONFIRM,
};

void remote_setup();
int remote_available();
uint32_t remote_read();

#endif /* REMOTE_RECEIVE_H_ */
