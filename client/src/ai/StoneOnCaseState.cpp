#include "zappy_ai_stdafx.hpp"

namespace ai
{
  StoneOnCaseState::StoneOnCaseState() : AState()
  {
  }

  StoneOnCaseState::~StoneOnCaseState()
  {
  }

  void StoneOnCaseState::readState(std::queue<std::string> &readQueue)
  {
  }

  void StoneOnCaseState::writeState(std::queue<std::string> &writeQueue)
  {
  }

  void StoneOnCaseState::reset(Value value)
  {
  }

  Value StoneOnCaseState::getResponse() const
  {
    return (m_curValue);
  }
}