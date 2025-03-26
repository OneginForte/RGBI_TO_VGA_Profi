#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "build/pio_programs.pio.h"
#include "pico/multicore.h"
#include "sys/reent.h"
#include <cstdlib>
#include <cstring>
#include "tusb.h"
#include "RP2040USB.h"
#include "Serial.h"

extern void setup1() __attribute__((weak));
extern void loop1() __attribute__((weak));
extern void setup();
extern void loop();

void process_menu(char &inbyte);

namespace arduino {
extern void serialEventRun();
extern void serialEvent1Run();
extern void serialEvent2Run();
};

//#define USE_TINYUSB 1

void save_set();
//--------------------------------------------------------------------+
// Device
//--------------------------------------------------------------------+

void yield()
{
#ifdef USE_TINYUSB
        TinyUSB_Device_Task();
        TinyUSB_Device_FlushCDC();
#endif
}


extern void __loop() {
#ifdef USE_TINYUSB
    yield();
#endif

    if (arduino::serialEventRun) {
        arduino::serialEventRun();
    }
#if 0
    if (arduino::serialEvent1Run) {
        arduino::serialEvent1Run();
    }
    if (arduino::serialEvent2Run) {
        arduino::serialEvent2Run();
    }
#endif
}
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

extern SerialUSB Serial;

int main()
{
    stdio_init_all();
    // Allocate impure_ptr (newlib temps) if there is a 2nd core running
    // Let rest of core know if we're using FreeRTOS
    bool __isFreeRTOS = false;
    if (!__isFreeRTOS && (setup1 || loop1)) {
        _impure_ptr1 = (struct _reent*)calloc(1, sizeof(struct _reent));
        _REENT_INIT_PTR(_impure_ptr1);
    }
#ifndef NO_USB
#ifdef USE_TINYUSB
    TinyUSB_Device_Init(0);

#else
    __USBStart();

#ifndef DISABLE_USB_SERIAL

    if (!__isFreeRTOS) {
        // Enable serial port for reset/upload always
        Serial.begin(115200);
    }
#endif
#endif
#endif
    multicore_launch_core1(main1);
    setup();
    while (true) {
        loop();
        __loop();
    }
}
