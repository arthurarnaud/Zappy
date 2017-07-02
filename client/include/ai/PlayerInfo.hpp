#ifndef PLAYERINFO_HPP_
#define PLAYERINFO_HPP_

#include <iostream>
#include <queue>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

namespace ai
{
  class PlayerInfo
  {
  public:
    PlayerInfo(std::queue<std::string> &queue);
    PlayerInfo(PlayerInfo const &);
    PlayerInfo(PlayerInfo &&);
    ~PlayerInfo();

    PlayerInfo &operator=(PlayerInfo const &);
    PlayerInfo &operator=(PlayerInfo &&);

    std::int32_t getLevel() const;
    void         setLevel(std::int32_t);
    std::array<std::int32_t, 6> const getRecipe() const;
    std::int32_t getNbPlayer() const;
    std::array<std::int32_t, 6> const
        diff(std::array<std::int32_t, 6> const old,
             std::array<std::int32_t, 6> const newTab) const;
    std::array<std::int32_t, 6> const
        missingStone(std::array<std::int32_t, 6> const inventory) const;

    std::int32_t getTargetID() const;
    void setTargetID(std::int32_t);

    std::int32_t getPlayerID() const;
    std::queue<std::string> &getMSG();

    std::int32_t getDirection() const;
    void setDirection(std::int32_t dir);

    std::string getStoneName(std::int32_t i) const;

  private:
    std::int32_t m_level;
    std::queue<std::string> &m_cmdMSG;
    std::int32_t m_targetID;
    std::int32_t m_playerID;
    std::int32_t m_direction;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !PLAYERINFO_HPP_
