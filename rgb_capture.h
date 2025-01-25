#ifndef RGB_CAPTURE_H
#define RGB_CAPTURE_H
#include "g_config.h"

#define SAMPL_F (12)
#define H_SYNC_PULSE (48 * SAMPL_F / 10)  //  4 µs @ 7.0 MHz pixel clock
#define V_SYNC_PULSE (40 * SAMPL_F) // 30 µs @ 7.0 MHz pixel clock

#define CAP_LINE_LENGTH 1024
#define CAP_DMA_BUF_CNT 30
#define CAP_DMA_BUF_SIZE (CAP_LINE_LENGTH * CAP_DMA_BUF_CNT)
#define CAP_DMA_LINE_BUF_SIZE 600 //V_BUF_W

extern uint32_t frame_count;

int16_t set_capture_shX(int16_t shX);
int16_t set_capture_shY(int16_t shY);
int8_t set_capture_delay(int8_t delay);
int16_t set_capture_len_VS(int16_t shY);
void set_video_sync_mode(bool video_sync_mode);
void check_settings(settings_t *settings);
void calculate_clkdiv(float frequency, uint16_t *div_int, uint8_t *div_frac);
void start_capture(settings_t *settings);
void stop_capture();

#endif