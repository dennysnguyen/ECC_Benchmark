#include <stdio.h>
#include "xparameters.h"
#include "xtmrctr.h"
#include "uECC.h"
#include "xil_printf.h"

typedef unsigned long u32;

XTmrCtr Timer;

// Dummy Random Number Generator
int dummy_rng(uint8_t *dest, unsigned size) {
    for (unsigned i = 0; i < size; ++i) {
        dest[i] = i; 
    }
    return 1; 
}

int main() {
    // 1. Initialize AXI Timer
    XTmrCtr_Initialize(&Timer, XPAR_XTMRCTR_0_BASEADDR);
    XTmrCtr_SetOptions(&Timer, 0, XTC_AUTO_RELOAD_OPTION);
    
    // Arrays sized for the largest curve (256-bit)
    uint8_t public_key[64];
    uint8_t private_key[32];
    u32 start, end;

    uECC_set_rng(&dummy_rng);

    xil_printf("\r\n=== Nexys A7 ECC KeyGen Benchmark ===\r\n");

    // --- Benchmark 1: 160-bit Curve ---
    XTmrCtr_Start(&Timer, 0);
    start = XTmrCtr_GetValue(&Timer, 0);
    uECC_make_key(public_key, private_key, uECC_secp160r1());
    end = XTmrCtr_GetValue(&Timer, 0);
    xil_printf("160-bit (secp160r1): %lu cycles\r\n", end - start);

    // --- Benchmark 2: 192-bit Curve ---
    start = XTmrCtr_GetValue(&Timer, 0);
    uECC_make_key(public_key, private_key, uECC_secp192r1());
    end = XTmrCtr_GetValue(&Timer, 0);
    xil_printf("192-bit (secp192r1): %lu cycles\r\n", end - start);

    // --- Benchmark 3: 256-bit Curve ---
    start = XTmrCtr_GetValue(&Timer, 0);
    uECC_make_key(public_key, private_key, uECC_secp256r1());
    end = XTmrCtr_GetValue(&Timer, 0);
    xil_printf("256-bit (secp256r1): %lu cycles\r\n", end - start);

    xil_printf("Done!\r\n");
    return 0;
}