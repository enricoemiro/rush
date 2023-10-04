#pragma once

namespace Rush
{

enum class RoomType : uint8_t
{
    CORRIDOR, ///< Has exists to the left and right.
    LANDING,  ///< Has exists up, left, and right.
    DROP,     ///< Has exists left, right, and down.
    OPEN,     ///< Has exists in all directions.
};

} // namespace Rush
