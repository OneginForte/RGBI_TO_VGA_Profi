#ifndef PIO_PROGRAMS_H
#define PIO_PROGRAMS_H

#include "hardware/pio.h"
#include "build/pio_programs.pio.h"
static const uint16_t nop_opcode = 0xa042;
static const uint16_t set_opcode = 0xe020;
#if 0
extern const uint16_t nop_opcode;

extern const struct pio_program pio_capture_0;
extern uint16_t pio_capture_0_instructions[];

extern const uint16_t set_opcode;

extern const struct pio_program pio_capture_0;
extern const struct pio_program pio_capture_1;
extern const struct pio_program pio_program2_CAP;

extern uint16_t pio_capture_0_instructions[];
extern uint16_t pio_capture_1_instructions[];
extern uint16_t pio_program2_instructions[];

extern const struct pio_program pio_program_vga;
extern uint16_t pio_program_vga_instructions[];

extern const struct pio_program pio_program_dvi;
extern uint16_t pio_program_dvi_instructions[];
#endif
#endif