#ifndef UTILITY_H
#define UTILITY_H

namespace sodark::utility
{

template<std::integral T>
[[nodiscard]] static constexpr auto to_array(T value) noexcept -> std::array<uint8_t, sizeof(T)>
{
    static_assert(std::has_unique_object_representations_v<T>, "T may not have padding bits");
    auto value_array = std::bit_cast<std::array<std::uint8_t, sizeof(T)>>(value);
    if constexpr (std::endian::native == std::endian::little) {
        std::ranges::reverse(value_array);
    }
    return value_array;
}

[[nodiscard]] static constexpr uint32_t to_int(std::array<uint8_t, 4> value_array) noexcept
{
    if constexpr (std::endian::native == std::endian::little) {
        std::ranges::reverse(value_array);
    }
    return std::bit_cast<uint32_t>(value_array);
}

[[nodiscard]] static constexpr uint64_t to_llong(std::array<uint8_t, 8> value_array) noexcept
{
    if constexpr (std::endian::native == std::endian::little) {
        std::ranges::reverse(value_array);
    }
    return std::bit_cast<uint64_t>(value_array);
}

} // namespace sodark::utility

#endif // UTILITY_H
