// Copyright (c) 2023 Sebastian Peralta
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once
#include <robo_ml/robo_ml.hpp>
#include <vector>
#include <functional>

namespace robo
{
/**
 * @brief Responsible for generating actions from states. Stores the history of actions.
 *
 * @tparam ActT
 * @tparam StateT
 */
template<typename ActT, typename StateT>
class Actor
{
public:
  typedef std::vector<ActT> ActionList;
  // Function that generates a list of actions from from some estimated state.
  typedef  std::function<ActionList(std::shared_ptr<StateT>)> ActFunctor;
/**
 * @brief Construct a new Actor object
 *
 * @param act_func Function that generates a list of actions.
 * @param buffer_size
 */

  Actor(ActFunctor act_func, size_t buffer_size = 10);

  /**
       * @brief Generates an action from the current state. Stores the action in its history_ buffer.
       *
       * @param state
       * @return std::vector<ActT>
       */
  ActionList act(std::shared_ptr<StateT> state);

  /**
   * @brief Get the history_ buffer object
   *
   * @return robo::ReplayBuffer<std::vector<ActT>>
   */
  ReplayBuffer<std::vector<ActT>> & history() {return history_;}

private:
  ActFunctor act_func_;
  ReplayBuffer<std::vector<ActT>> history_;   // Stores action lists in chronological order.
};

// Implementation.
template<typename ActT, typename StateT>
Actor<ActT, StateT>::Actor(
  ActFunctor act_func,
  size_t buffer_size)
: act_func_(act_func), history_(buffer_size)
{
}

template<typename ActT, typename StateT>
std::vector<ActT> Actor<ActT, StateT>::act(std::shared_ptr<StateT> state)
{
  ActionList actions = act_func_(state);
  history_.add(std::make_unique<ActionList>(actions));
  return actions;
}

}  // namespace robo
