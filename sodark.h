#ifndef SODARK_H
#define SODARK_H

#include "utility.h"

#include <array>
#include <cstdint>

namespace sodark::internal
{

constexpr std::array<uint32_t, 256> sbox_enc {
    0x9c, 0xf2, 0x14, 0xc1, 0x8e, 0xcb, 0xb2, 0x65, 0x97, 0x7a, 0x60, 0x17, 0x92, 0xf9, 0x78, 0x41,
    0x07, 0x4c, 0x67, 0x6d, 0x66, 0x4a, 0x30, 0x7d, 0x53, 0x9d, 0xb5, 0xbc, 0xc3, 0xca, 0xf1, 0x04,
    0x03, 0xec, 0xd0, 0x38, 0xb0, 0xed, 0xad, 0xc4, 0xdd, 0x56, 0x42, 0xbd, 0xa0, 0xde, 0x1b, 0x81,
    0x55, 0x44, 0x5a, 0xe4, 0x50, 0xdc, 0x43, 0x63, 0x09, 0x5c, 0x74, 0xcf, 0x0e, 0xab, 0x1d, 0x3d,
    0x6b, 0x02, 0x5d, 0x28, 0xe7, 0xc6, 0xee, 0xb4, 0xd9, 0x7c, 0x19, 0x3e, 0x5e, 0x6c, 0xd6, 0x6e,
    0x2a, 0x13, 0xa5, 0x08, 0xb9, 0x2d, 0xbb, 0xa2, 0xd4, 0x96, 0x39, 0xe0, 0xba, 0xd7, 0x82, 0x33,
    0x0d, 0x5f, 0x26, 0x16, 0xfe, 0x22, 0xaf, 0x00, 0x11, 0xc8, 0x9e, 0x88, 0x8b, 0xa1, 0x7b, 0x87,
    0x27, 0xe6, 0xc7, 0x94, 0xd1, 0x5b, 0x9b, 0xf0, 0x9f, 0xdb, 0xe1, 0x8d, 0xd2, 0x1f, 0x6a, 0x90,
    0xf4, 0x18, 0x91, 0x59, 0x01, 0xb1, 0xfc, 0x34, 0x3c, 0x37, 0x47, 0x29, 0xe2, 0x64, 0x69, 0x24,
    0x0a, 0x2f, 0x73, 0x71, 0xa9, 0x84, 0x8c, 0xa8, 0xa3, 0x3b, 0xe3, 0xe9, 0x58, 0x80, 0xa7, 0xd3,
    0xb7, 0xc2, 0x1c, 0x95, 0x1e, 0x4d, 0x4f, 0x4e, 0xfb, 0x76, 0xfd, 0x99, 0xc5, 0xc9, 0xe8, 0x2e,
    0x8a, 0xdf, 0xf5, 0x49, 0xf3, 0x6f, 0x8f, 0xe5, 0xeb, 0xf6, 0x25, 0xd5, 0x31, 0xc0, 0x57, 0x72,
    0xaa, 0x46, 0x68, 0x0b, 0x93, 0x89, 0x83, 0x70, 0xef, 0xa4, 0x85, 0xf8, 0x0f, 0xb3, 0xac, 0x10,
    0x62, 0xcc, 0x61, 0x40, 0xf7, 0xfa, 0x52, 0x7f, 0xff, 0x32, 0x45, 0x20, 0x79, 0xce, 0xea, 0xbe,
    0xcd, 0x15, 0x21, 0x23, 0xd8, 0xb6, 0x0c, 0x3f, 0x54, 0x1a, 0xbf, 0x98, 0x48, 0x3a, 0x75, 0x77,
    0x2b, 0xae, 0x36, 0xda, 0x7e, 0x86, 0x35, 0x51, 0x05, 0x12, 0xb8, 0xa6, 0x9a, 0x2c, 0x06, 0x4b};

[[nodiscard]] static consteval auto create_sodark_dec_sbox() noexcept -> std::array<uint32_t, 256>
{
    std::array<uint32_t, 256> sbox_dec {};
    for (uint16_t i = 0; i < 256; i++) {
        sbox_dec[sbox_enc[i]] = i;
    }
    return sbox_dec;
}

constexpr std::array<uint32_t, 256> sbox_dec = create_sodark_dec_sbox();

} // namespace sodark::internal

namespace sodark3
{

[[nodiscard]] static constexpr uint32_t encrypt(uint32_t rounds, uint32_t plain_text /*24 bits*/,
                                                uint64_t key /*56 bits*/,
                                                uint64_t seed /*64 bits*/) noexcept
{
    /******************************************************************************************
    A=I[1], B=I[2], C=I[3]
    r: 1...rounds
        A(r) = e[A(r-1) xor B(r-1) xor K[(3 * r - 3) % 7 + 1] xor S[(3 * r - 3) % 8]]
        C(r) = e[C(r-1) xor B(r-1) xor K[(3 * r - 2) % 7 + 1] xor S[(3 * r - 2) % 8]]
        B(r) = e[B(r-1) xor A(r) xor C(r) xor K[(3 * r - 1) % 7 + 1] xor S[(3 * r - 1) % 8]]
    O={0,A,B,C}
    ******************************************************************************************/

    auto ct = sodark::utility::to_array(plain_text);
    auto k  = sodark::utility::to_array(key);
    auto s  = sodark::utility::to_array(seed);

    for (uint8_t r = 1; r <= rounds; ++r) {
        const uint8_t rka = k[(3 * r - 3) % 7 + 1] ^ s[(3 * r - 3) % 8];
        const uint8_t rkc = k[(3 * r - 2) % 7 + 1] ^ s[(3 * r - 2) % 8];
        const uint8_t rkb = k[(3 * r - 1) % 7 + 1] ^ s[(3 * r - 1) % 8];

        ct[1] = sodark::internal::sbox_enc[ct[1] ^ ct[2] ^ rka];
        ct[3] = sodark::internal::sbox_enc[ct[3] ^ ct[2] ^ rkc];
        ct[2] = sodark::internal::sbox_enc[ct[2] ^ ct[1] ^ ct[3] ^ rkb];
    }
    return sodark::utility::to_int(ct);
}

[[nodiscard]] static constexpr uint32_t decrypt(uint8_t rounds, uint32_t cypher_text /*24 bits*/,
                                                uint64_t key /*56 bits*/,
                                                uint64_t seed /*64 bits*/) noexcept
{
    /******************************************************************************************
    A=I[1], B=I[2], C=I[3]
    r: rounds...1
        B(r) = d[B(r-1)] xor A(r-1) xor C(r-1) xor K[(3 * r - 1) % 7 + 1] xor S[(3 * r - 1) % 8]
        C(r) = d[C(r-1)] xor B(r) xor K[(3 * r - 2) % 7 + 1] xor S[(3 * r - 2) % 8]
        A(r) = d[A(r-1)] xor B(r) xor K[(3 * r - 3) % 7 + 1] xor S[(3 * r - 3) % 8]
    O={0,A,B,C}
    ******************************************************************************************/

    auto pt = sodark::utility::to_array(cypher_text);
    auto k  = sodark::utility::to_array(key);
    auto s  = sodark::utility::to_array(seed);

    for (uint8_t r = rounds; r >= 1; --r) {
        const uint8_t rka = k[(3 * r - 3) % 7 + 1] ^ s[(3 * r - 3) % 8];
        const uint8_t rkc = k[(3 * r - 2) % 7 + 1] ^ s[(3 * r - 2) % 8];
        const uint8_t rkb = k[(3 * r - 1) % 7 + 1] ^ s[(3 * r - 1) % 8];

        pt[2] = sodark::internal::sbox_dec[pt[2]] ^ pt[1] ^ pt[3] ^ rkb;
        pt[3] = sodark::internal::sbox_dec[pt[3]] ^ pt[2] ^ rkc;
        pt[1] = sodark::internal::sbox_dec[pt[1]] ^ pt[2] ^ rka;
    }
    return sodark::utility::to_int(pt);
}

} // namespace sodark3

namespace sodark6
{

[[nodiscard]] static constexpr uint64_t encrypt(uint32_t rounds, uint64_t plain_text /*48 bits*/,
                                                uint64_t key /*56 bits*/,
                                                uint64_t seed /*64 bits*/) noexcept
{
    /******************************************************************************************
    A=I[2], B=I[3], C=I[4], D=I[5], E=I[6], F=I[7]
    r: 1...rounds
        A(r) = e[A(r-1) xor B(r-1) xor F(r-1) xor K[(6 * r - 6) % 7 + 1] xor S[(6 * r - 6) % 8]]
        C(r) = e[C(r-1) xor B(r-1) xor D(r-1) xor K[(6 * r - 5) % 7 + 1] xor S[(6 * r - 5) % 8]]
        E(r) = e[E(r-1) xor D(r-1) xor F(r-1) xor K[(6 * r - 4) % 7 + 1] xor S[(6 * r - 4) % 8]]
        B(r) = e[B(r-1) xor A(r) xor C(r) xor K[(6 * r - 3) % 7 + 1] xor S[(6 * r - 3) % 8]]
        D(r) = e[D(r-1) xor C(r) xor E(r) xor K[(6 * r - 2) % 7 + 1] xor S[(6 * r - 2) % 8]]
        F(r) = e[F(r-1) xor A(r) xor E(r) xor K[(6 * r - 1) % 7 + 1] xor S[(6 * r - 1) % 8]]
    O={0,0,A,B,C,D,E,F}
    ******************************************************************************************/

    auto ct = sodark::utility::to_array(plain_text);
    auto k  = sodark::utility::to_array(key);
    auto s  = sodark::utility::to_array(seed);

    for (uint8_t r = 1; r <= rounds; ++r) {
        const uint8_t rka = k[(6 * r - 6) % 7 + 1] ^ s[(6 * r - 6) % 8];
        const uint8_t rkc = k[(6 * r - 5) % 7 + 1] ^ s[(6 * r - 5) % 8];
        const uint8_t rke = k[(6 * r - 4) % 7 + 1] ^ s[(6 * r - 4) % 8];
        const uint8_t rkb = k[(6 * r - 3) % 7 + 1] ^ s[(6 * r - 3) % 8];
        const uint8_t rkd = k[(6 * r - 2) % 7 + 1] ^ s[(6 * r - 2) % 8];
        const uint8_t rkf = k[(6 * r - 1) % 7 + 1] ^ s[(6 * r - 1) % 8];

        ct[2] = sodark::internal::sbox_enc[ct[2] ^ ct[3] ^ ct[7] ^ rka];
        ct[4] = sodark::internal::sbox_enc[ct[4] ^ ct[3] ^ ct[5] ^ rkc];
        ct[6] = sodark::internal::sbox_enc[ct[6] ^ ct[5] ^ ct[7] ^ rke];
        ct[3] = sodark::internal::sbox_enc[ct[3] ^ ct[2] ^ ct[4] ^ rkb];
        ct[5] = sodark::internal::sbox_enc[ct[5] ^ ct[4] ^ ct[6] ^ rkd];
        ct[7] = sodark::internal::sbox_enc[ct[7] ^ ct[2] ^ ct[6] ^ rkf];
    }
    return sodark::utility::to_llong(ct);
}

[[nodiscard]] static constexpr uint64_t decrypt(uint32_t rounds, uint64_t cypher_text /*48 bits*/,
                                                uint64_t key /*56 bits*/,
                                                uint64_t seed /*64 bits*/) noexcept
{
    /******************************************************************************************
    A=I[2], B=I[3], C=I[4], D=I[5], E=I[6], F=I[7]
    r: rounds...1
        B(r) = d[B(r-1)] xor A(r-1) xor C(r-1) xor K[(6 * r - 3) % 7 + 1] xor S[(6 * r - 3) % 8]
        D(r) = d[D(r-1)] xor C(r-1) xor E(r-1) xor K[(6 * r - 2) % 7 + 1] xor S[(6 * r - 2) % 8]
        F(r) = d[F(r-1)] xor A(r-1) xor E(r-1) xor K[(6 * r - 1) % 7 + 1] xor S[(6 * r - 1) % 8]
        E(r) = d[E(r-1)] xor D(r) xor F(r) xor K[(6 * r - 4) % 7 + 1] xor S[(6 * r - 4) % 8]
        C(r) = d[C(r-1)] xor B(r) xor D(r) xor K[(6 * r - 5) % 7 + 1] xor S[(6 * r - 5) % 8]
        A(r) = d[A(r-1)] xor B(r) xor F(r) xor K[(6 * r - 6) % 7 + 1] xor S[(6 * r - 6) % 8]
    O={0,0,A,B,C,D,E,F}
    ******************************************************************************************/

    auto pt = sodark::utility::to_array(cypher_text);
    auto k  = sodark::utility::to_array(key);
    auto s  = sodark::utility::to_array(seed);

    for (uint8_t r = rounds; r >= 1; --r) {
        const uint8_t rka = k[(6 * r - 6) % 7 + 1] ^ s[(6 * r - 6) % 8];
        const uint8_t rkc = k[(6 * r - 5) % 7 + 1] ^ s[(6 * r - 5) % 8];
        const uint8_t rke = k[(6 * r - 4) % 7 + 1] ^ s[(6 * r - 4) % 8];
        const uint8_t rkb = k[(6 * r - 3) % 7 + 1] ^ s[(6 * r - 3) % 8];
        const uint8_t rkd = k[(6 * r - 2) % 7 + 1] ^ s[(6 * r - 2) % 8];
        const uint8_t rkf = k[(6 * r - 1) % 7 + 1] ^ s[(6 * r - 1) % 8];

        pt[3] = sodark::internal::sbox_dec[pt[3]] ^ pt[2] ^ pt[4] ^ rkb;
        pt[5] = sodark::internal::sbox_dec[pt[5]] ^ pt[4] ^ pt[6] ^ rkd;
        pt[7] = sodark::internal::sbox_dec[pt[7]] ^ pt[2] ^ pt[6] ^ rkf;
        pt[6] = sodark::internal::sbox_dec[pt[6]] ^ pt[5] ^ pt[7] ^ rke;
        pt[4] = sodark::internal::sbox_dec[pt[4]] ^ pt[3] ^ pt[5] ^ rkc;
        pt[2] = sodark::internal::sbox_dec[pt[2]] ^ pt[3] ^ pt[7] ^ rka;
    }
    return sodark::utility::to_llong(pt);
}

} // namespace sodark6

#endif // SODARK_H
