#include "fnd_display.h"
#include "remote_receive.h"

void setup()
{
    //remote controller setup
    remote_setup();

    //first display is '0'
    display_setup();
}

void loop()
{
    if(remote_available())
    {
        display_set_val(DISP_NUM, remote_read());
    }
    display_process(6);
}
