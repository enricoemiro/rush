#include "Room.hh"

namespace Rush
{

Room::Room(RoomType type, RoomRole role) : m_Type(type), m_Role(role) {}

bool Room::IsCorridor() const
{
    return m_Type == RoomType::CORRIDOR;
}

bool Room::IsLanding() const
{
    return m_Type == RoomType::LANDING;
}

bool Room::IsDrop() const
{
    return m_Type == RoomType::DROP;
}

bool Room::IsOpen() const
{
    return m_Type == RoomType::OPEN;
}

bool Room::IsNormal() const
{
    return m_Role == RoomRole::NORMAL;
}

bool Room::IsSpawn() const
{
    return m_Role == RoomRole::SPAWN;
}

bool Room::IsExit() const
{
    return m_Role == RoomRole::EXIT;
}

} // namespace Rush
