#pragma once

#include <platform.h>

/**
 * @brief   Oprand uint16_t.
 */
union OperandU16 {
    uint16_t value; ///< Value.
    struct OperandU16Bytes {
        uint8_t b0;
        uint8_t b1;
    } bytes; ///< Bytes.
};

/**
 * @brief   Oprand uint32_t.
 */
union OperandU32 {
    uint16_t value; ///< Value.
    struct OperandU32Bytes {
        uint8_t b0;
        uint8_t b1;
        uint8_t b2;
        uint8_t b3;
    } bytes; ///< Bytes.
};

#define OP16(value) (*((union OperandU16 *)(&(value))))
#define OP32(value) (*((union OperandU32 *)(&(value))))

/**
 * @brief   u32/u16 & u32%u16.
 *
 * @param[in]   op1         Operand 1.
 * @param[in]   op2         Operand 2.
 * @param[out]  quotient    Quotient.
 * @param[out]  residue     Residue;
 */
inline void divModU32U16(uint16_t  op1,
                         uint16_t  op2,
                         uint16_t *quotient,
                         uint16_t *residue)
{
    uint8_t oldPSW2 = P_SW2;
    __sbit  oldEA   = EA;
    EA              = 0;

    P_SW2 |= 0x80;

    MD3 = OP32(op1).bytes.b3;
    MD2 = OP32(op1).bytes.b2;
    MD1 = OP32(op1).bytes.b1;
    MD0 = OP32(op1).bytes.b0;

    MD5 = OP16(op2).bytes.b1;
    MD4 = OP16(op2).bytes.b0;

    ARCON = 6 << 5;
    OPCON = 1;
    while ((OPCON & 1) != 0) {
    }

    __idata union OperandU16 retQuotient;
    retQuotient.bytes.b0 = MD0;
    retQuotient.bytes.b1 = MD1;

    __idata union OperandU16 retResidue;
    retResidue.bytes.b0 = MD4;
    retResidue.bytes.b1 = MD5;

    P_SW2 = oldPSW2;
    EA    = oldEA;

    *quotient = retQuotient.value;
    *residue  = retResidue.value;
}

/**
 * @brief   u32/u16.
 *
 * @param[in]   op1       Operand 1.
 * @param[in]   op2       Operand 2.
 *
 * @return      Result.
 */
inline uint16_t divU32U16(uint16_t op1, uint16_t op2)
{
    uint8_t oldPSW2 = P_SW2;
    __sbit  oldEA   = EA;
    EA              = 0;

    P_SW2 |= 0x80;

    MD3 = OP32(op1).bytes.b3;
    MD2 = OP32(op1).bytes.b2;
    MD1 = OP32(op1).bytes.b1;
    MD0 = OP32(op1).bytes.b0;

    MD5 = OP16(op2).bytes.b1;
    MD4 = OP16(op2).bytes.b0;

    ARCON = 6 << 5;
    OPCON = 1;
    while ((OPCON & 1) != 0) {
    }

    __idata union OperandU16 ret;
    ret.bytes.b0 = MD0;
    ret.bytes.b1 = MD1;

    P_SW2 = oldPSW2;
    EA    = oldEA;
    return ret.value;
}

/**
 * @brief   u32%u16.
 *
 * @param[in]   op1       Operand 1.
 * @param[in]   op2       Operand 2.
 *
 * @return      Result.
 */
inline uint16_t modU32U16(uint16_t op1, uint16_t op2)
{
    uint8_t oldPSW2 = P_SW2;
    __sbit  oldEA   = EA;
    EA              = 0;

    P_SW2 |= 0x80;

    MD3 = OP32(op1).bytes.b3;
    MD2 = OP32(op1).bytes.b2;
    MD1 = OP32(op1).bytes.b1;
    MD0 = OP32(op1).bytes.b0;

    MD5 = OP16(op2).bytes.b1;
    MD4 = OP16(op2).bytes.b0;

    ARCON = 6 << 5;
    OPCON = 1;
    while ((OPCON & 1) != 0) {
    }

    __idata union OperandU16 ret;
    ret.bytes.b0 = MD4;
    ret.bytes.b1 = MD5;

    P_SW2 = oldPSW2;
    EA    = oldEA;
    return ret.value;
}

/**
 * @brief   u16/u16 & u16%u16.
 *
 * @param[in]   op1         Operand 1.
 * @param[in]   op2         Operand 2.
 * @param[out]  quotient    Quotient.
 * @param[out]  residue     Residue;
 */
inline void divModU16U16(uint16_t  op1,
                         uint16_t  op2,
                         uint16_t *quotient,
                         uint16_t *residue)
{
    uint8_t oldPSW2 = P_SW2;
    __sbit  oldEA   = EA;
    EA              = 0;

    P_SW2 |= 0x80;

    MD1 = OP16(op1).bytes.b1;
    MD0 = OP16(op1).bytes.b0;

    MD5 = OP16(op2).bytes.b1;
    MD4 = OP16(op2).bytes.b0;

    ARCON = (uint8_t)(5 << 5);
    OPCON = 1;
    while ((OPCON & 1) != 0) {
    }

    __idata union OperandU16 retQuotient;
    retQuotient.bytes.b0 = MD0;
    retQuotient.bytes.b1 = MD1;

    __idata union OperandU16 retResidue;
    retResidue.bytes.b0 = MD4;
    retResidue.bytes.b1 = MD5;

    P_SW2 = oldPSW2;
    EA    = oldEA;

    *quotient = retQuotient.value;
    *residue  = retResidue.value;

    return;
}

/**
 * @brief   u16/u16.
 *
 * @param[in]   op1       Operand 1.
 * @param[in]   op2       Operand 2.
 *
 * @return      Result.
 */
inline uint16_t divU16U16(uint16_t op1, uint16_t op2)
{
    uint8_t oldPSW2 = P_SW2;
    __sbit  oldEA   = EA;
    EA              = 0;

    P_SW2 |= 0x80;

    MD1 = OP16(op1).bytes.b1;
    MD0 = OP16(op1).bytes.b0;

    MD5 = OP16(op2).bytes.b1;
    MD4 = OP16(op2).bytes.b0;

    ARCON = 5 << 5;
    OPCON = 1;
    while ((OPCON & 1) != 0) {
    }

    __idata union OperandU16 ret;
    ret.bytes.b0 = MD0;
    ret.bytes.b1 = MD1;

    P_SW2 = oldPSW2;
    EA    = oldEA;
    return ret.value;
}

/**
 * @brief   u16%u16.
 *
 * @param[in]   op1       Operand 1.
 * @param[in]   op2       Operand 2.
 *
 * @return      Result.
 */
inline uint16_t modU16U16(uint16_t op1, uint16_t op2)
{
    uint8_t oldPSW2 = P_SW2;
    __sbit  oldEA   = EA;
    EA              = 0;

    P_SW2 |= 0x80;

    MD1 = OP16(op1).bytes.b1;
    MD0 = OP16(op1).bytes.b0;

    MD5 = OP16(op2).bytes.b1;
    MD4 = OP16(op2).bytes.b0;

    ARCON = 5 << 5;
    OPCON = 1;
    while ((OPCON & 1) != 0) {
    }

    __idata union OperandU16 ret;
    ret.bytes.b0 = MD4;
    ret.bytes.b1 = MD5;

    P_SW2 = oldPSW2;
    EA    = oldEA;
    return ret.value;
}

/**
 * @brief   u16 * u16.
 *
 * @param[in]   op1       Operand 1.
 * @param[in]   op2       Operand 2.
 *
 * @return      Result.
 */
inline uint32_t mulU16U16(uint16_t op1, uint16_t op2)
{
    uint8_t oldPSW2 = P_SW2;
    __sbit  oldEA   = EA;
    EA              = 0;

    P_SW2 |= 0x80;

    MD1 = OP16(op1).bytes.b1;
    MD0 = OP16(op1).bytes.b0;

    MD5 = OP16(op2).bytes.b1;
    MD4 = OP16(op2).bytes.b0;

    ARCON = 4 << 5;
    OPCON = 1;
    while ((OPCON & 1) != 0) {
    }

    __idata union OperandU32 ret;
    ret.bytes.b0 = MD0;
    ret.bytes.b1 = MD1;
    ret.bytes.b2 = MD2;
    ret.bytes.b3 = MD3;

    P_SW2 = oldPSW2;
    EA    = oldEA;
    return ret.value;
}
