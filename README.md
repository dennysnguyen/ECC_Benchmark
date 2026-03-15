# Nexys A7 ECC Benchmarking (MicroBlaze)

This project benchmarks the performance of Elliptic Curve Cryptography (ECC) on a 32-bit MicroBlaze soft-core processor implemented on a Nexys A7 (Xilinx Artix-7) FPGA. 

The implementation uses the **micro-ecc** library to perform Key Generation and Signing operations across different NIST prime curves.

## Hardware Configuration
* **FPGA:** Nexys A7 (XC7A100T)
* **Processor:** MicroBlaze (32-bit)
* **Clock Frequency:** 100 MHz
* **Timer:** AXI Timer (used for cycle-accurate benchmarking)
* **Optimization Level:** `-O0` (Standard Debug)

## Benchmark Results
The following results were measured in clock cycles and converted to real-time execution based on the 100 MHz system clock.

| Curve | Key Size | KeyGen (Cycles) | Time (Seconds) |
| :--- | :--- | :--- | :--- |
| **secp160r1** | 160-bit | 60,126,993 | ~0.60s |
| **secp192r1** | 192-bit | 94,129,093 | ~0.94s |
| **secp256r1** | 256-bit | 234,176,863 | ~2.34s |

## Library Reference
This project utilizes the **micro-ecc** library, a small and efficient ECDH and ECDSA implementation for 8-bit, 16-bit, and 32-bit processors.

* **Original Library:** [kmackay/micro-ecc](https://github.com/kmackay/micro-ecc)

## Files in this Repository
* `src/main.c`: The benchmarking logic, including a dummy RNG for testing.
* `system_top_wrapper.xsa`: The hardware platform specification exported from Vivado.
* `lscript.ld`: Linker script defining the MicroBlaze memory map.