#include "zappy_ai_stdafx.hpp"

namespace ai
{

  static const std::array<std::pair<std::int32_t, std::array<std::int32_t, 6>>,
                          7>
      recipes = {{
          {1, {{1, 0, 0, 0, 0, 0}}},
          {2, {{1, 1, 1, 0, 0, 0}}},
          {2, {{2, 0, 1, 0, 2, 0}}},
          {4, {{1, 1, 2, 0, 1, 0}}},
          {4, {{1, 2, 1, 3, 0, 0}}},
          {6, {{1, 2, 3, 0, 1, 0}}},
          {6, {{2, 2, 2, 2, 2, 1}}},
      }};

  PlayerInfo::PlayerInfo() : m_level(1)
  {
  }

  PlayerInfo::PlayerInfo(PlayerInfo const &that) : m_level(that.m_level)
  {
  }

  PlayerInfo::PlayerInfo(PlayerInfo &&that) : m_level(std::move(that.m_level))
  {
  }

  PlayerInfo &PlayerInfo::operator=(PlayerInfo const &that)
  {
    if (this == &that)
      return (*this);
    m_level = that.m_level;
    return (*this);
  }

  PlayerInfo &PlayerInfo::operator=(PlayerInfo &&that)
  {
    if (this == &that)
      return (*this);
    m_level = std::move(that.m_level);
    return (*this);
  }
  PlayerInfo::~PlayerInfo()
  {
  }

  std::int32_t PlayerInfo::getLevel() const
  {
  }

  void PlayerInfo::setLevel(std::int32_t level)
  {
    m_level = level;
  }

  std::array<std::int32_t, 6> const PlayerInfo::getRecipe() const
  {
    return (recipes[m_level].second);
  }

  std::int32_t PlayerInfo::getNbPlayer() const
  {
    return (recipes[m_level].first);
  }

  std::array<std::int32_t, 6> const
      PlayerInfo::diff(std::array<std::int32_t, 6> const old,
                       std::array<std::int32_t, 6> const newTab) const
  {
    std::array<std::int32_t, 6> res{};
    for (std::size_t i = 0; i < 6; ++i)
      {
	res[i] = newTab[i] - old[i];
      }
    return (res);
  }

  std::array<std::int32_t, 6> const PlayerInfo::missingStone(
      std::array<std::int32_t, 6> const inventory) const
  {
    std::array<std::int32_t, 6> res{};
    for (std::size_t i = 0; i < 6; ++i)
      {
	std::int32_t tmp = recipes[m_level].second[i] - inventory[i];
	if (tmp < 0)
	  res[i] = 0;
	else
	  res[i] = tmp;
      }
    return (res);
  }
}