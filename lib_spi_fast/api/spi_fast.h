// Copyright (c) 2016, XMOS Ltd, All rights reserved
#ifndef SPI_FAST_H_
#define SPI_FAST_H_

#include <xs1.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
    out buffered port:32 clk;
    in buffered port:32 miso; // Data driven at double the SPI clock rate
    out buffered port:32 mosi; // Data driven at double the SPI clock rate
    out port cs;
    size_t cs_port_bit;
    clock cb;
    unsigned clock_divide;
    unsigned cs_to_data_delay_ns;
    unsigned cs_to_data_delay_ticks;
} spi_fast_ports;

typedef enum port_time_mode_t {
    SPI_CS_DRIVE_NOW,
    SPI_CS_DRIVE_AT_TIME,
    SPI_CS_GET_TIMESTAMP
} port_time_mode_t;

typedef enum spi_direction_t {
    SPI_READ,
    SPI_WRITE,
    SPI_READ_WRITE
} spi_direction_t;

void spi_fast_init(spi_fast_ports &p);

void spi_fast(unsigned num_bytes, char *buffer, spi_fast_ports &p, spi_direction_t direction);

void drive_cs_port_now(spi_fast_ports &p,
                       uint32_t p_ss_bit,
                       uint32_t bit_value);

void drive_cs_port_at_time(spi_fast_ports &p,
                           uint32_t p_ss_bit,
                           uint32_t bit_value,
                           unsigned *time);

void drive_cs_port_get_time(spi_fast_ports &p,
                            uint32_t p_ss_bit,
                            uint32_t bit_value,
                            unsigned *time);

#endif /* SPI_FAST_H_ */
