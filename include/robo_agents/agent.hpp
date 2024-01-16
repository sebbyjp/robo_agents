// Copyright (c) 2023 Sebastian Peralta
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once
#include "robo_agents/actor.hpp"
#include "robo_agents/observer.hpp"


namespace robo_agents
{

/**
 * @brief This class is responsible for recieving observations and generatoring
 * actions.
 *
 * @tparam ObsT
 * @tparam ActionT
 * @tparam SrcTs
 */
template<typename ObsT, typename ActionT, typename ... SrcTs>
class Agent
{
public:
  /**
   * @brief Construct a new Agent object
   *
   * @param options
   * @param src_topics Source topics to subscribe to and generate observations from.
   */
  Agent(const std::function<ObsT(const SrcTs&...)>& obs_from_srcs_func,
      const std::function<ActionT(const ObsT&)>& action_from_obs_func,
      const size_t buffer_size = 10)
  {
    observer_ = std::make_shared<Observer<ObsT, SrcTs...>>(options, obs_from_srcs_func,
      buffer_size);
    actor_ =
      std::make_shared<Actor<ActionT>>(
        action_from_obs_func,
        buffer_size);
  }


protected:
  std::shared_ptr<Observer<ObsT, SrcTs...>> observer_;
  std::shared_ptr<Actor<ActionT>> actor_;
};
}  // namespace robo_agents
