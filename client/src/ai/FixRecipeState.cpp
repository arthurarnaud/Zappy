#include "zappy_ai_stdafx.hpp"

namespace ai
{
  FixRecipeState::FixRecipeState(
      std::map<BasicState, std::unique_ptr<IState>> &states, PlayerInfo &player)
      : AState(states, player)
  {
  }

  FixRecipeState::~FixRecipeState()
  {
  }

  void FixRecipeState::readState(std::queue<std::string> &readQueue)
  {
    nope::log::Log(Debug) << "FixRecipe[READ]State";
    m_states[BasicState::LOOK]->readState(readQueue);
    Value ret = m_states[BasicState::LOOK]->getResponse();
    std::array<std::int32_t, 6> cmpTable = m_player.diff(m_player.getRecipe(), static_cast<LookState *>(m_states[BasicState::LOOK])->getCurStones());
    std::int32_t count = 0;
    for (std::size_t i = 0; i < 6; ++i)
    {
      if (cmpTable[i] > 0)
      {
        m_states[BasicState::TAKE]->readState(readQueue);
      }
      else if (cmpTable[i] < 0)
      {
        m_states[BasicState::SET]->readState(readQueue);
      }
      else
      {
        ++count;
      }
      if (count == 6)
      {
        m_curValue = Value::YES;
      }
    }
  }

  void FixRecipeState::writeState(std::queue<std::string> &writeQueue)
  {
    nope::log::Log(Debug) << "FixRecipe[WRITE]State";
    m_states[BasicState::LOOK]->reset(Value::NO);
    m_states[BasicState::LOOK]->writeState(writeQueue);
    m_canWrite = false;
  }

  void FixRecipeState::reset(Value value)
  {
    nope::log::Log(Debug) << "FixRecipeState reset";
    m_curValue = Value::LOOP;
    m_retValue = value;
    m_canWrite = true;
  }

  Value FixRecipeState::getResponse() const
  {
    return (m_curValue);
  }
}
