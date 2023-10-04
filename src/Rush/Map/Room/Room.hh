#pragma once

#include "RoomRole.hh"
#include "RoomType.hh"

namespace Rush
{

class Room
{
  public:
    Room(RoomType type = RoomType::CORRIDOR, RoomRole role = RoomRole::NORMAL);

    bool IsCorridor() const;
    bool IsLanding() const;
    bool IsDrop() const;
    bool IsOpen() const;

    bool IsNormal() const;
    bool IsSpawn() const;
    bool IsExit() const;

  private:
    RoomType m_Type;
    RoomRole m_Role;
};

} // namespace Rush
