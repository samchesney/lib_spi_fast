// Copyright (c) 2016, XMOS Ltd, All rights reserved
#include <xs1.h>
#include <platform.h>
#include <print.h>
#include "spi_fast.h"

spi_fast_ports spi_ports = {
    on tile[1]: XS1_PORT_1N,
    on tile[1]: XS1_PORT_1M,
    on tile[1]: XS1_PORT_1L,
    on tile[1]: XS1_PORT_4E,
    0, // CS on bit 0 of port 4E
    on tile[1]: XS1_CLKBLK_3,
    1, // 100/12
    1000,
    0
};

void test_spi_fast() {

    spi_fast_init(spi_ports);

#define BUF_LEN 16
    char buf[BUF_LEN];
    unsigned count = 0;

    while (1) {
        for (unsigned i=0; i  <BUF_LEN; i++) {
            buf[i] = count++;
        }
        spi_fast(BUF_LEN, buf, spi_ports);
        delay_milliseconds(10);
        printstr("sent\n");
    }
}

int main() {
    par {
        on tile[1]: test_spi_fast();
    }

    return 0;
}
