#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/vreg.h"
//#include "hardware/pio.h"

#include "build/pio_programs.pio.h"
#include "pico/multicore.h"
#include "sys/reent.h"
#include <cstdlib>
#include <cstring>
#include "tusb.h"
#include "RP2040USB.h"
//#include "Serial.h"

extern void setup1() __attribute__((weak));
extern void loop1() __attribute__((weak));
extern void setup();
extern void loop();

//--------------------------------------------------------------------+
// Device
//--------------------------------------------------------------------+


static struct _reent *_impure_ptr1 = nullptr;

void main1() 
{
    //rp2040.fifo.registerCore();
    if (setup1) {
        setup1();
    }
    while (true) {
        if (loop1) {
            loop1();
        }
    }
}

int main()
{
    vreg_set_voltage(VREG_VOLTAGE_1_25);
    //set_sys_clock_khz(243000, true);
    // Allocate impure_ptr (newlib temps) if there is a 2nd core running
    // Let rest of core know if we're using FreeRTOS
    bool __isFreeRTOS = false;
    if (!__isFreeRTOS && (setup1 || loop1)) {
        _impure_ptr1 = (struct _reent*)calloc(1, sizeof(struct _reent));
        _REENT_INIT_PTR(_impure_ptr1);
    }
    __USBStart();
    multicore_launch_core1(main1);
    setup();
    while (true)
    {
        loop();
        tud_task();
        //__loop();
    }
}
