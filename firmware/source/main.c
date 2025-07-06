#include <clock.h>
#include <platform.h>
#include <status_led.h>
#include <test.h>

/**
 * @brief       Main loop.
 */
void mainLoop()
{
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

    // if (needTest()) {
    testLoop();
    //} else {
    // mainLoop();
    //}

    return 0;
}
