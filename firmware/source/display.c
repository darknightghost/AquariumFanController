#include <clock.h>
#include <hd_math.h>

#include <display.h>

// Ports.
#define GPIO_DISPLAY_DC1 P0_3
#define GPIO_DISPLAY_DC2 P0_2
#define GPIO_DISPLAY_DC3 P0_1
#define GPIO_DISPLAY_DC4 P0_0

#define GPIO_MODE1_DISPLAY0 P0M1
#define GPIO_MODE0_DISPLAY0 P0M0
#define GPIO_MODE_MASK_DISPLAY0                                          \
    ((uint8_t)((uint8_t)(1 << 3) | (uint8_t)(1 << 2) | (uint8_t)(1 << 1) \
               | (uint8_t)(1 << 0)))

#define GPIO_DISPLAY_DC5 P2_7
#define GPIO_DISPLAY_DC6 P2_5
#define GPIO_DISPLAY_DC7 P2_4
#define GPIO_DISPLAY_DC8 P2_6

#define GPIO_MODE1_DISPLAY1 P2M1
#define GPIO_MODE0_DISPLAY1 P2M0
#define GPIO_MODE_MASK_DISPLAY1                                          \
    ((uint8_t)((uint8_t)(1 << 7) | (uint8_t)(1 << 5) | (uint8_t)(1 << 4) \
               | (uint8_t)(1 << 6)))

#define GPIO_DISPLAY_DA1 P1_1
#define GPIO_DISPLAY_DA2 P1_0
#define GPIO_DISPLAY_DA3 P1_4

#define GPIO_MODE1_DISPLAY_SELECT P1M1
#define GPIO_MODE0_DISPLAY_SELECT P1M0
#define GPIO_MODE_MASK_DISPLAY_SELECT \
    ((uint8_t)((uint8_t)(1 << 1) | (uint8_t)(1 << 0) | (uint8_t)(1 << 4)))

#define GPIO_DISPLAY_DIG1 GPIO_DISPLAY_DA1
#define GPIO_DISPLAY_DIG2 GPIO_DISPLAY_DA2
#define GPIO_DISPLAY_DIG3 GPIO_DISPLAY_DA3

#define GPIO_DISPLAY_A  GPIO_DISPLAY_DC7
#define GPIO_DISPLAY_B  GPIO_DISPLAY_DC8
#define GPIO_DISPLAY_C  GPIO_DISPLAY_DC4
#define GPIO_DISPLAY_D  GPIO_DISPLAY_DC2
#define GPIO_DISPLAY_E  GPIO_DISPLAY_DC1
#define GPIO_DISPLAY_F  GPIO_DISPLAY_DC6
#define GPIO_DISPLAY_G  GPIO_DISPLAY_DC5
#define GPIO_DISPLAY_DP GPIO_DISPLAY_DC3

// Seegment code.
#define BIT_C  0
#define BIT_DP 1
#define BIT_D  2
#define BIT_E  3

#define BIT_A 4
#define BIT_F 5
#define BIT_B 6
#define BIT_G 7

#define segmentCode(__bit) ((uint8_t)(1 << (__bit)))

/**
 * @brief   Segment data.
 */
union SegmentData {
    uint8_t value;
    struct {
        uint8_t p0Bits : 4; ///< P0 bits.
                            ///< Bit 0 :    C
                            ///< Bit 1 :    DP
                            ///< Bit 2 :    D
                            ///< Bit 3 :    E
        uint8_t p2Bits : 4; ///< P2 bits.
                            ///< Bit 4 :    A
                            ///< Bit 5 :    F
                            ///< Bit 6 :    B
                            ///< Bit 7 :    G
    } bits;
};

/**
 * @brief   Segment code.
 */
enum SegmentCode {
    SEG_NONE = 0x00, ///< None.
    SEG_0    = segmentCode(BIT_A) | segmentCode(BIT_B) | segmentCode(BIT_C)
            | segmentCode(BIT_D) | segmentCode(BIT_E)
            | segmentCode(BIT_F),                    ///< '0'.
    SEG_1 = segmentCode(BIT_B) | segmentCode(BIT_C), ///< '1'.
    SEG_2 = segmentCode(BIT_A) | segmentCode(BIT_B) | segmentCode(BIT_G)
            | segmentCode(BIT_E) | segmentCode(BIT_D), ///< '2'.
    SEG_3 = segmentCode(BIT_A) | segmentCode(BIT_B) | segmentCode(BIT_G)
            | segmentCode(BIT_C) | segmentCode(BIT_D), ///< '3'.
    SEG_4 = segmentCode(BIT_F) | segmentCode(BIT_G) | segmentCode(BIT_B)
            | segmentCode(BIT_C), ///< '4'.
    SEG_5 = segmentCode(BIT_A) | segmentCode(BIT_F) | segmentCode(BIT_G)
            | segmentCode(BIT_C) | segmentCode(BIT_D), ///< '5'.
    SEG_6 = segmentCode(BIT_A) | segmentCode(BIT_F) | segmentCode(BIT_G)
            | segmentCode(BIT_C) | segmentCode(BIT_D)
            | segmentCode(BIT_E), ///< '6'.
    SEG_7
    = segmentCode(BIT_A) | segmentCode(BIT_B) | segmentCode(BIT_C), ///< '7'.
    SEG_8 = segmentCode(BIT_A) | segmentCode(BIT_B) | segmentCode(BIT_C)
            | segmentCode(BIT_D) | segmentCode(BIT_E) | segmentCode(BIT_F)
            | segmentCode(BIT_G), ///< '8'.
    SEG_9 = segmentCode(BIT_A) | segmentCode(BIT_B) | segmentCode(BIT_C)
            | segmentCode(BIT_D) | segmentCode(BIT_F)
            | segmentCode(BIT_G), ///< '9'.
    SEG_E = segmentCode(BIT_A) | segmentCode(BIT_D) | segmentCode(BIT_E)
            | segmentCode(BIT_F) | segmentCode(BIT_G), ///< 'E'.
    SEG_R = segmentCode(BIT_A) | segmentCode(BIT_B) | segmentCode(BIT_C)
            | segmentCode(BIT_E) | segmentCode(BIT_F)
            | segmentCode(BIT_G),   ///< 'R'.
    SEG_MINUS = segmentCode(BIT_G), ///< '-'.
    SEG_POINT = segmentCode(BIT_DP) ///< '.'.
};

// Clock.
#define REFRESH_FREQ   60
#define CLOCK_INTERVAL ((uint16_t)(1000000L / (REFRESH_FREQ * 3) / 100))

#define l_clockInitValue (65536 - (IRC_FEQ / 1000000) * CLOCK_INTERVAL)

/// Data of each segment.
static __idata union SegmentData l_segmentData[3];

/**
 * @brief       Initialize display.
 */
void initDisplay(void)
{
    // Set initial value.
    GPIO_DISPLAY_DA1 = 1;
    GPIO_DISPLAY_DA2 = 1;
    GPIO_DISPLAY_DA3 = 1;

    GPIO_DISPLAY_DC1 = 0;
    GPIO_DISPLAY_DC2 = 0;
    GPIO_DISPLAY_DC3 = 0;
    GPIO_DISPLAY_DC4 = 0;
    GPIO_DISPLAY_DC5 = 0;
    GPIO_DISPLAY_DC6 = 0;
    GPIO_DISPLAY_DC7 = 0;
    GPIO_DISPLAY_DC8 = 0;

    l_segmentData[0].value = SEG_NONE;
    l_segmentData[1].value = SEG_NONE;
    l_segmentData[2].value = SEG_NONE;

    // Set GPIO mode.
    P_SW2 |= 0x80;
    GPIO_MODE1_DISPLAY0 &= ~GPIO_MODE_MASK_DISPLAY0;
    GPIO_MODE0_DISPLAY0 &= ~GPIO_MODE_MASK_DISPLAY0;

    GPIO_MODE1_DISPLAY1 &= ~GPIO_MODE_MASK_DISPLAY1;
    GPIO_MODE0_DISPLAY1 &= ~GPIO_MODE_MASK_DISPLAY1;

    GPIO_MODE1_DISPLAY_SELECT &= ~GPIO_MODE_MASK_DISPLAY_SELECT;
    GPIO_MODE0_DISPLAY_SELECT &= ~GPIO_MODE_MASK_DISPLAY_SELECT;
    P_SW2 &= ~(uint8_t)0x80;

    // Initialize clock.
    // Set T4 to 1T mode.
    T4T3M |= 0x20;

    // Load initialize value.
    T4L = l_clockInitValue & 0xFF;
    T4H = (l_clockInitValue >> 8) & 0xFF;

    // Enable timer4 interrupt.
    IE2 |= (1 << 6);
}

/**
 * @brief       Start display.
 */
void startDisplay(void)
{
    // Start timer.
    T4T3M |= 0x80;
}

/**
 * @brief       Task to test display.
 */
void testDisplayTask(void)
{
    static __xdata uint32_t oldCount     = 0;
    static __xdata uint8_t  status       = 255;
    __xdata uint32_t        currentCount = getSystemClock() / (500L * 1000);
    if (currentCount != oldCount) {
        // Lock.
        __sbit oldEA = EA;
        EA           = 0;

        GPIO_DISPLAY_DA1 = 1;
        GPIO_DISPLAY_DA2 = 1;
        GPIO_DISPLAY_DA3 = 1;

        // Move segment data.
        l_segmentData[0].value = l_segmentData[1].value;
        l_segmentData[1].value = l_segmentData[2].value;

        // Set data.
        switch (status) {
            case 0: {
                l_segmentData[2].value = SEG_1;
            } break;
            case 1: {
                l_segmentData[2].value = SEG_2;
            } break;
            case 2: {
                l_segmentData[2].value = SEG_3;
            } break;
            case 3: {
                l_segmentData[2].value = SEG_4;
            } break;
            case 4: {
                l_segmentData[2].value = SEG_5;
            } break;
            case 5: {
                l_segmentData[2].value = SEG_6;
            } break;
            case 6: {
                l_segmentData[2].value = SEG_7;
            } break;
            case 7: {
                l_segmentData[2].value = SEG_8;
            } break;
            case 8: {
                l_segmentData[2].value = SEG_9;
            } break;
            case 9: {
                l_segmentData[2].value = SEG_E;
            } break;
            case 10: {
                l_segmentData[2].value = SEG_R;
            } break;
            case 11: {
                l_segmentData[2].value = SEG_MINUS;
            } break;
            case 12: {
                l_segmentData[2].value = SEG_POINT;
            } break;
            case 13: {
                l_segmentData[2].value = SEG_NONE;
            } break;
            case 14: {
                l_segmentData[2].value = SEG_0;
            } break;
            default:
                l_segmentData[0].value = SEG_NONE;
                l_segmentData[1].value = SEG_0;
                l_segmentData[2].value = SEG_1;
                status                 = 0;
        }

        // Unlock.
        EA = oldEA;

        status += 1;
        oldCount = currentCount;
    }
}

/**
 * @brief       Parse number to segment code.
 *
 * @param[in[   num     Number to parse.
 */
inline uint32_t toSegmentCode(uint8_t num)
{
#define __MAKE_CASE(num) \
    case num:            \
        return SEG_##num;

    switch (num) {
        __MAKE_CASE(0);
        __MAKE_CASE(1);
        __MAKE_CASE(2);
        __MAKE_CASE(3);
        __MAKE_CASE(4);
        __MAKE_CASE(5);
        __MAKE_CASE(6);
        __MAKE_CASE(7);
        __MAKE_CASE(8);
        __MAKE_CASE(9);
        default:
            return SEG_NONE;
    }

#undef __MAKE_CASE
}

/**
 * @brief       Set display temperature.
 */
void setDisplayTemperature(float temperature)
{
    __xdata uint8_t data[3];

    if (temperature >= 10.0 && temperature < 100.0) {
        __xdata uint16_t t10 = (uint16_t)(temperature * 10);

        __xdata uint16_t unit10;
        __xdata uint16_t r10;
        divModU16U16(t10, 100, &unit10, &r10);

        __xdata uint16_t unit1;
        __xdata uint16_t unit0_1;
        divModU16U16(r10, 10, &unit1, &unit0_1);

        data[0] = toSegmentCode(unit10);
        data[1] = toSegmentCode(unit1) | SEG_POINT;
        data[2] = toSegmentCode(unit0_1);

    } else if (temperature >= 0.0 && temperature < 10.0) {
        __xdata uint16_t t100 = (uint16_t)(temperature * 100);

        __xdata uint16_t unit1;
        __xdata uint16_t r1;
        divModU16U16(t100, 100, &unit1, &r1);

        __xdata uint16_t unit0_1;
        __xdata uint16_t unit0_0_1;
        divModU16U16(r1, 10, &unit0_1, &unit0_0_1);

        data[0] = toSegmentCode(unit1) | SEG_POINT;
        data[1] = toSegmentCode(unit0_1);
        data[2] = toSegmentCode(unit0_0_1);
    } else if (temperature >= -10.0 && temperature < 0.0) {
        __xdata uint16_t t10 = (uint16_t)(-temperature * 10);

        __xdata uint16_t unit1;
        __xdata uint16_t unit0_1;
        divModU16U16(t10, 10, &unit1, &unit0_1);

        data[0] = SEG_MINUS;
        data[1] = toSegmentCode(unit1) | SEG_POINT;
        data[2] = toSegmentCode(unit0_1);

    } else if (temperature > -100.0 && temperature < -10.0) {
        __xdata uint16_t t1 = (uint16_t)(-temperature);

        __xdata uint16_t unit10;
        __xdata uint16_t unit1;
        divModU16U16(t1, 10, &unit10, &unit1);

        data[0] = SEG_MINUS;
        data[1] = toSegmentCode(unit10);
        data[2] = toSegmentCode(unit1);
    } else {
        setDisplayError();
        return;
    }

    // Set value.
    __sbit oldEA = EA;
    EA           = 0;

    GPIO_DISPLAY_DA1 = 1;
    GPIO_DISPLAY_DA2 = 1;
    GPIO_DISPLAY_DA3 = 1;

    l_segmentData[0].value = data[0];
    l_segmentData[1].value = data[1];
    l_segmentData[2].value = data[2];
    EA                     = oldEA;
}

/**
 * @brief       Set display error.
 */
void setDisplayError(void)
{
    __sbit oldEA = EA;
    EA           = 0;

    GPIO_DISPLAY_DA1 = 1;
    GPIO_DISPLAY_DA2 = 1;
    GPIO_DISPLAY_DA3 = 1;

    l_segmentData[0].value = SEG_E;
    l_segmentData[1].value = SEG_R;
    l_segmentData[2].value = SEG_R;
    EA                     = oldEA;
}

/**
 * @brief       Timer4 ISR.
 */
void displayTimer4ISR(void) __interrupt(INT_TIMER4)
{
    EA = 0;
    if (GPIO_DISPLAY_DA1 == 0) {
        // Segment 1.
        GPIO_DISPLAY_DA1 = 1;
        P0               = (P0 & 0xF0) | (l_segmentData[1].value & 0x0F);
        P2               = (P2 & 0x0F) | (l_segmentData[1].value & 0xF0);
        GPIO_DISPLAY_DA2 = 0;

    } else if (GPIO_DISPLAY_DA2 == 0) {
        // Segment 2.
        GPIO_DISPLAY_DA2 = 1;
        P0               = (P0 & 0xF0) | (l_segmentData[2].value & 0x0F);
        P2               = (P2 & 0x0F) | (l_segmentData[2].value & 0xF0);
        GPIO_DISPLAY_DA3 = 0;

    } else {
        // Segment 0.
        // Segment 2.
        GPIO_DISPLAY_DA3 = 1;
        P0               = (P0 & 0xF0) | (l_segmentData[0].value & 0x0F);
        P2               = (P2 & 0x0F) | (l_segmentData[0].value & 0xF0);
        GPIO_DISPLAY_DA1 = 0;
    }

    EA = 1;
}
