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
 * @brief This class is responsible for generating actions from the current state.
 *
 * @tparam T
 */
template<typename ActT, typename StateT>
class Actor
{
public:
  typedef  std::function<std::shared_ptr<std::vector<ActT>>(std::shared_ptr<StateT>)> ActFunctor;
/**
 * @brief Construct a new Actor object
 *
 * @param act_func Function that generates a list of actions from an observation.
 * @param buffer_size
 */

  Actor(
    ActFunctor act_func,
    size_t buffer_size = 10);

  /**
     * @brief Generates an action from the current state. Stores the action in its replay buffer.
     *
     * @param state
     * @return std::vector<ActT>
     */
  std::shared_ptr<std::vector<ActT>> act(std::shared_ptr<StateT> state);

  /**
   * @brief Get the replay buffer object
   *
   * @return robo::ReplayBuffer<std::vector<ActT>>
   */
  ReplayBuffer<std::vector<ActT>> & history() {return replay_;}

private:
  ActFunctor act_func_;
  ReplayBuffer<std::vector<ActT>> replay_;   // Stores action lists in chronological order.
};

// Implementation.
template<typename ActT, typename StateT>
Actor<ActT, StateT>::Actor(
  ActFunctor act_func,
  size_t buffer_size)
: act_func_(act_func), replay_(buffer_size)
{
}

template<typename ActT, typename StateT>
std::shared_ptr<std::vector<ActT>> Actor<ActT, StateT>::act(std::shared_ptr<StateT> state)
{
  std::shared_ptr<std::vector<ActT>> actions = act_func_(state);
  replay_.add(actions);
  return actions;
}

}  // namespace robo
