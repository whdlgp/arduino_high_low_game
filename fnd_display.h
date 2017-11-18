#ifndef FND_DISPLAY_H_
#define FND_DISPLAY_H_

#include "Arduino.h"

enum disp_type_t
{
    DISP_NUM,
    DISP_RESULT,
};

void display_setup();
void display_set_val(uint8_t type, uint16_t val);
void display_process(uint32_t period_ms);

#endif /* FND_DISPLAY_H_ */
