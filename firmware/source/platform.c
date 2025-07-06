#include <clock.h>

#include <platform.h>

/**
 * @brief       Initialize platform.
 */
void initPlatform(void)
{
    RST_CFG = 0x50;

    // Disable interrpution.
    EA = 0;

    // Disable all I/O ports.
    // P0M0 = 0;
    // P0M1 = 0xFF;
    // P1M0 = 0;
    // P1M1 = 0xFF;
    // P2M0 = 0;
    // P2M1 = 0xFF;
    // P3M0 = 0;
    // P3M1 = 0xFF;
    // P4M0 = 0;
    // P4M1 = 0xFF;
    // P5M0 = 0;
    // P5M1 = 0xFF;
    // P6M0 = 0;
    // P6M1 = 0xFF;
    // P7M0 = 0;
    // P7M1 = 0xFF;

    // Initialize modules.
    initClock();

    // Enable interrpution.
    EA = 1;

    // Start modules.
    startClock();
}
