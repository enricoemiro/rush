#pragma once

namespace Rush
{

enum class RoomRole : uint8_t
{
    NORMAL = 0, ///< A normal room.
    SPAWN,      ///< A spawn room.
    EXIT,       ///< An exit room.
};

} // namespace Rush
