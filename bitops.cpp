#include <cstdint>

const int BITS_SHIFT_8 = 8;
const int BITS_SHIFT_16 = 16;
const int BITS_SHIFT_32 = 32;
const int COUNT_BITS = 64;
const uint64_t MASK_1_BIT = 0x5555555555555555;
const uint64_t INV_MASK_1_BIT = 0xAAAAAAAAAAAAAAAA;
const uint64_t MASK_2_BITS = 0x3333333333333333;
const uint64_t INV_MASK_2_BITS = 0xCCCCCCCCCCCCCCCC;
const uint64_t MASK_4_BITS = 0x0F0F0F0F0F0F0F0F;
const uint64_t INV_MASK_4_BITS = 0xF0F0F0F0F0F0F0F0;
const uint64_t MASK_8_BITS = 0x00FF00FF00FF00FF;
const uint64_t INV_MASK_8_BITS = 0xFF00FF00FF00FF00;
const uint64_t MASK_16_BITS = 0x0000FFFF0000FFFF;
const uint64_t INV_MASK_16_BITS = 0xFFFF0000FFFF0000;
const uint64_t MASK_32_BITS = 0x00000000FFFFFFFF;
const uint64_t INV_MASK_32_BITS = 0xFFFFFFFF00000000;

uint64_t SwapBytes(uint64_t value) {
    value = ((value & MASK_8_BITS) << BITS_SHIFT_8) | ((value & INV_MASK_8_BITS) >> BITS_SHIFT_8);
    value = ((value & MASK_16_BITS) << BITS_SHIFT_16) | ((value & INV_MASK_16_BITS) >> BITS_SHIFT_16);
    value = ((value & MASK_32_BITS) << BITS_SHIFT_32) | ((value & INV_MASK_32_BITS) >> BITS_SHIFT_32);
    return value;
}

uint64_t ReverseBits(uint64_t value) {
    value = ((value & MASK_1_BIT) << 1) | ((value & INV_MASK_1_BIT) >> 1);
    value = ((value & MASK_2_BITS) << 2) | ((value & INV_MASK_2_BITS) >> 2);
    value = ((value & MASK_4_BITS) << 4) | ((value & INV_MASK_4_BITS) >> 4);
    value = ((value & MASK_8_BITS) << BITS_SHIFT_8) | ((value & INV_MASK_8_BITS) >> BITS_SHIFT_8);
    value = ((value & MASK_16_BITS) << BITS_SHIFT_16) | ((value & INV_MASK_16_BITS) >> BITS_SHIFT_16);
    value = ((value & MASK_32_BITS) << BITS_SHIFT_32) | ((value & INV_MASK_32_BITS) >> BITS_SHIFT_32);
    return value;
}

uint64_t ReverseBitsInBytes(uint64_t value) {
    value = ((value & MASK_1_BIT) << 1) | ((value & INV_MASK_1_BIT) >> 1);
    value = ((value & MASK_2_BITS) << 2) | ((value & INV_MASK_2_BITS) >> 2);
    value = ((value & MASK_4_BITS) << 4) | ((value & INV_MASK_4_BITS) >> 4);
    return value;
}

uint64_t SetBits(uint64_t value, uint64_t offset, uint64_t count, uint64_t bits) {
    uint64_t mask = ((static_cast<uint64_t>(1) << count) - 1) << offset;
    return ((value & ~mask) | (bits << offset));
}

uint64_t ExtractBits(uint64_t value, uint64_t offset, uint64_t count) {
    uint64_t mask = ((static_cast<uint64_t>(1) << count) - 1) << offset;
    return (value & mask) >> offset;
}

uint32_t CountSetBits(uint64_t value) {
    value = (value & MASK_1_BIT) + ((value & INV_MASK_1_BIT) >> 1);
    value = (value & MASK_2_BITS) + ((value & INV_MASK_2_BITS) >> 2);
    value = (value & MASK_4_BITS) + ((value & INV_MASK_4_BITS) >> 4);
    value = (value & MASK_8_BITS) + ((value & INV_MASK_8_BITS) >> BITS_SHIFT_8);
    value = (value & MASK_16_BITS) + ((value & INV_MASK_16_BITS) >> BITS_SHIFT_16);
    value = (value & MASK_32_BITS) + ((value & INV_MASK_32_BITS) >> BITS_SHIFT_32);
    return value;
}

uint32_t CountTrailingZeros(uint64_t value) {
    if (value == 0) {
        return COUNT_BITS;
    }
    uint32_t count = 0;
    if (value % (static_cast<uint64_t>(1) << BITS_SHIFT_32) == 0) {
        count += BITS_SHIFT_32;
        value = value >> BITS_SHIFT_32;
    }
    if (value % (static_cast<uint64_t>(1) << BITS_SHIFT_16) == 0) {
        count += BITS_SHIFT_16;
        value = value >> BITS_SHIFT_16;
    }
    if (value % (static_cast<uint64_t>(1) << BITS_SHIFT_8) == 0) {
        count += BITS_SHIFT_8;
        value = value >> BITS_SHIFT_8;
    }
    if (value % (static_cast<uint64_t>(1) << 4) == 0) {
        count += 4;
        value = value >> 4;
    }
    if (value % (static_cast<uint64_t>(1) << 2) == 0) {
        count += 2;
        value = value >> 2;
    }
    if (value % (static_cast<uint64_t>(1) << 1) == 0) {
        count += 1;
    }
    return count;
}

uint32_t CountLeadingZeros(uint64_t value) {
    if (value == 0) {
        return COUNT_BITS;
    }
    uint32_t count = 0;
    if ((value >> BITS_SHIFT_32) == 0) {
        count += BITS_SHIFT_32;
        value = value << BITS_SHIFT_32;
    }
    if ((value >> (BITS_SHIFT_16 + BITS_SHIFT_32)) == 0) {
        count += BITS_SHIFT_16;
        value = value << (BITS_SHIFT_16 + BITS_SHIFT_32);
    }
    if ((value >> (BITS_SHIFT_8 + BITS_SHIFT_16 + BITS_SHIFT_32)) == 0) {
        count += BITS_SHIFT_8;
        value = value << BITS_SHIFT_8;
    }
    if ((value >> (4 + BITS_SHIFT_8 + BITS_SHIFT_16 + BITS_SHIFT_32)) == 0) {
        count += 4;
        value = value << 4;
    }
    if ((value >> (2 + 4 + BITS_SHIFT_8 + BITS_SHIFT_16 + BITS_SHIFT_32)) == 0) {
        count += 2;
        value = value << 2;
    }
    if ((value >> (1 + 2 + 4 + BITS_SHIFT_8 + BITS_SHIFT_16 + BITS_SHIFT_32)) == 0) {
        count += 1;
    }
    return count;
}

uint64_t RotateLeft(uint64_t value, uint32_t shift) {
    if ((shift % COUNT_BITS) == 0) {
        return value;
    }
    return (value << (shift % COUNT_BITS)) | (value >> (COUNT_BITS - (shift % COUNT_BITS)));
}

uint64_t RotateRight(uint64_t value, uint32_t shift) {
    if ((shift % COUNT_BITS) == 0) {
        return value;
    }
    return (value >> (shift % COUNT_BITS)) | (value << (COUNT_BITS - (shift % COUNT_BITS)));
}

bool IsPowerOfTwo(uint64_t value) {
    if (value != 0 && (value & value - 1) == 0) {
        return true;
    }
    return false;
}

uint64_t RoundUpToPowerOfTwo(uint64_t value) {
    if (value == 0) {
        return 1;
    }
    --value;
    for (int i = 1; i <= BITS_SHIFT_32; i *= 2) {
        value |= value >> i;
    }
    return ++value;
}

uint64_t AlignDown(uint64_t value, uint64_t alignment) {
    return (value & ~(alignment - 1));
}

uint64_t AlignUp(uint64_t value, uint64_t alignment) {
    return (value + alignment - 1) & ~(alignment - 1);
}
