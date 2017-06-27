#ifndef AI_HPP_
#define AI_HPP_

#include <iostream>
#include <map>
#include <queue>
#include <array>
#include "TCPSocket.hpp"

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

#define NB_FOOD_MIN (5)
#define NB_FOOD_NORMAL (7)

namespace ai
{
  enum class Value : std::int8_t
  {
    YES,
    NO,
    COME,
    GO_AWAY,
    SEARCH,
    WAINTING,
    READY,
    END_INCANT,
    NB_VALUE,
  };

  enum class State : std::int8_t
  {
    NO_CHANGE = -1,
    DEAD,
    STARVING,
    RECEIVE_MSG,
    MISSING_STONE,
    MISSING_PLAYER,
    SET_RECIPE,
    INCANT,
    FOOD_ON_CASE,
    COLLECT_FOOD,
    FIND_FOOD,
    MOVE_TO_FOOD,
    LEVEL,
    MOVE_TO_TEAMMATE,
    ARRIVED,
    FIX_RECIPE,
    STONE_ON_CASE,
    COLLECT_STONE,
    FIND_STONE,
    MOVE_TO_STONE,
    TROLL,
    NB_STATE,
  };

  class AI
  {
  public:
    explicit AI(std::string ip, std::uint16_t port);
    AI(AI const &) = delete;
    AI(AI const &&) = delete;
    ~AI();

    AI &operator=(AI const &) = delete;
    AI &operator=(AI const &&) = delete;

  private:
    std::int32_t checkActivity(fd_set &readfds, fd_set &writefds);
    std::int32_t treatIncomingData();
    std::int32_t treatOutcomingData();
    std::int32_t loop();

    void initAction();
    void send(std::string const &msg);
    void move(std::pair<std::int32_t, std::int32_t> coord);
    std::int32_t look(std::string const &object);
    std::pair<std::int32_t, std::int32_t> const
        direction(std::int32_t caseNumber);
    std::array<std::int32_t, 6> const diff(std::array<std::int32_t, 6> old,
                                           std::array<std::int32_t, 6> newTab);

    Value starving(Value value = Value::YES);
    Value receiveMsg(Value value = Value::YES);
    Value missingStone(Value value = Value::YES);
    Value missingPlayer(Value value = Value::YES);
    Value setRecipe(Value value = Value::YES);
    Value incant(Value value = Value::YES);
    Value foodOnCase(Value value = Value::YES);
    Value collectFood(Value value = Value::YES);
    Value findFood(Value value = Value::YES);
    Value moveToFood(Value value = Value::YES);
    Value checkLevel(Value value = Value::YES);
    Value moveToTeammate(Value value = Value::YES);
    Value arrived(Value value = Value::YES);
    Value fixRecipe(Value value = Value::YES);
    Value stoneOnCase(Value value = Value::YES);
    Value collectStone(Value value = Value::YES);
    Value findStone(Value value = Value::YES);
    Value moveToStone(Value value = Value::YES);
    Value troll(Value value = Value::YES);

    std::map<State, Value (AI::*)(Value)> m_actionForState;
    std::int32_t m_foodUnit;
    std::array<char, 512> m_lastUnknownMsg;
    network::TCPSocket m_sock;
    std::queue<std::string> m_cmdToSend;
    std::queue<std::string> m_cmdToRecv;
    State m_curState;
    Value m_curValue;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !AI_HPP_
