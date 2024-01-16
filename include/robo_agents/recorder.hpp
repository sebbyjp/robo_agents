// Copyright (c) 2023 Sebastian Peralta
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once
#include <vector>
#include <functional>
#include <memory>


namespace robo
{
/**
 * @brief Responsible for generating actions from observations. Stores the history of actions.
 *
 * @tparam ActT
 * @tparam ObsT
 * @tparam SupervisionT: Can be a reward, label, or other supervision signal.
 */
template<typename ActT, typename ObsT, typename SupervisionT>
class Recorder
{
public:


  Recorder() = default;

  void record(const ObsT& observation, const ActT& action, const std::string& output_dir, const SupervisionT* supervision = nullptr) {

  }
};

}  // namespace robo
