#include <stdbool.h>

#include <clock.h>

#include <key.h>

#define GPIO_KEY_UP   P3_6
#define GPIO_KEY_DOWN P3_5
#define GPIO_KEY_SET  P3_4

#define DEBOUNCE_DELAY   10000L
#define REPEATE_DELAY    500000L
#define REPEATE_INTERVAL 200000L

/**
 * @brief   Key status.
 */
enum KeyStatus {
    Released,   ///< The key is released.
    Debouncing, ///< Debouncing.
    Pressed,    ///< The key is pressed.
    Repeating,  ///< The input of the key is repeating.
};

/**
 * @brief   Key infomation.
 */
struct KeyInfo {
    enum KeyStatus status;         ///< Key status.
    uint32_t       beginTimestamp; ///< Status begin timestamp.
};

/// Key `UP` infomation.
static __xdata struct KeyInfo l_keyUpInfo;

/// Key `DOWN` infomation.
static __xdata struct KeyInfo l_keyDownInfo;

/// Key `SET` infomation.
static __xdata struct KeyInfo l_keySetInfo;

/**
 * @brief       Initialize key.
 */
void initKey(void)
{
    // Initialize ports.
    P3_6 = 1;
    P3_5 = 1;
    P3_4 = 1;

    // Initialize status.
    l_keyUpInfo.status   = Released;
    l_keyDownInfo.status = Released;
    l_keySetInfo.status  = Released;
}

#define GET_KEY_STATUS_IMPL(__keyInfo)                                  \
    switch ((__keyInfo).status) {                                       \
        case Released:                                                  \
        case Debouncing:                                                \
            return -1;                                                  \
        case Pressed: {                                                 \
            return 0;                                                   \
        }                                                               \
        case Repeating: {                                               \
            __xdata uint32_t currentTime = getSystemClock();            \
            return (int16_t)((currentTime - (__keyInfo).beginTimestamp) \
                             / REPEATE_INTERVAL);                       \
        }                                                               \
        default:                                                        \
            (__keyInfo).status = Released;                              \
            return -1;                                                  \
    }

/**
 * @brief       Get key `UP` status.
 */
int16_t getKeyUpStatus(void)
{
    GET_KEY_STATUS_IMPL(l_keyUpInfo);
}

/**
 * @brief       Get key `DOWN` status.
 */
int16_t getKeyDownStatus(void)
{
    GET_KEY_STATUS_IMPL(l_keyDownInfo);
}

/**
 * @brief       Get key `SET` status.
 */
int16_t getKeySetStatus(void)
{
    GET_KEY_STATUS_IMPL(l_keySetInfo);
}

#undef GET_KEY_STATUS_IMPL

/**
 * @brief       Key task.
 */
void keyTask(void)
{
    __xdata uint32_t currentTime = getSystemClock();
#define KEY_TASK_INPL(__keyInfo, __port)                           \
    {                                                              \
        if ((__port)) {                                            \
            (__keyInfo).status = Released;                         \
        } else {                                                   \
            switch ((__keyInfo).status) {                          \
                case Released: {                                   \
                    (__keyInfo).status         = Debouncing;       \
                    (__keyInfo).beginTimestamp = currentTime;      \
                } break;                                           \
                case Debouncing: {                                 \
                    if (currentTime - (__keyInfo).beginTimestamp   \
                        >= DEBOUNCE_DELAY) {                       \
                        (__keyInfo).status         = Pressed;      \
                        (__keyInfo).beginTimestamp = currentTime;  \
                    }                                              \
                } break;                                           \
                case Pressed: {                                    \
                    if (currentTime - (__keyInfo).beginTimestamp   \
                        >= REPEATE_DELAY) {                        \
                        (__keyInfo).status         = Repeating;    \
                        (__keyInfo).beginTimestamp = currentTime;  \
                    }                                              \
                } break;                                           \
                case Repeating: {                                  \
                } break;                                           \
                default:                                           \
                    (__keyInfo).status         = Debouncing;       \
                    (__keyInfo).beginTimestamp = getSystemClock(); \
            }                                                      \
        }                                                          \
    }

    KEY_TASK_INPL(l_keyUpInfo, GPIO_KEY_UP);
    KEY_TASK_INPL(l_keyDownInfo, GPIO_KEY_DOWN);
    KEY_TASK_INPL(l_keySetInfo, GPIO_KEY_SET);

#undef KEY_TASK_INPL
}
