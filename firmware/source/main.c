#include <1-wire.h>
#include <clock.h>
#include <display.h>
#include <fan.h>
#include <platform.h>
#include <status_led.h>

#include <test.h>

/**
 * @brief       Main loop.
 */
void mainLoop(void)
{
    setStatusLED(true);
    while (1) {
    }
}

/**
 * @brief       Entery.
 *
 * @return      Not used.
 */
int main(void)
{
    initPlatform();

    if (needTest()) {
        testLoop();
    } else {
        mainLoop();
    }

    return 0;
}
