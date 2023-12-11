// Copyright (c) 2023 Sebastian Peralta
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Copyright (c) 2023 Sebastian Peralta
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once
#include <queue>
#include <memory>
#include <chrono>
#include <shared_mutex>

namespace robo
{
enum  class Status
{
  OK = 0,
  MISS_TOO_LATE = 1,   // The requested id is too old to be in the buffer.
  MISS_TOO_EARLY = 2,   // The requested id is too new to be in the buffer.
  NOT_ENOUGH_DATA = 3,   // The buffer does not have enough data to satisfy the request.
};

/**
 * @brief Container for thread-safe storing of objects.
 *  Useful for storing and reading data with temporal ordering.
 *  Shared read access is allowed, but write access is exclusive.
 *
 * @tparam T
 */
template<typename T>
class ReplayBuffer
{
public:
  struct Entry
  {
    std::shared_ptr<T> value;
    int id;
    std::chrono::milliseconds timestamp;
  };
  /**
   * @brief Construct a new Replay Buffer object
   *
   * @param max_size Maximum number of entries to store.
   */
  ReplayBuffer(const size_t max_size);

  const Status  get(const int id, Entry & entry_out) const;

  const Status get_last(const int N, std::vector<Entry> & entries_out) const;

  /**
   * @brief   Adds a new entry to the buffer.
   *
   * @param value
   * @return int The id of the new entry.
   */
  int add(
    const std::shared_ptr<T> & value);

private:
  const int id_from_idx(size_t idx) const {return idx + num_pops_;}
  const size_t idx_from_id(int id) const {return id - num_pops_;}
  const size_t max_size_;
  int num_pops_ = 0;
  mutable std::shared_mutex mutex_;
  // Stores objects in chronological order.
  std::deque<Entry> buffer_;
};


// Implementation.
template<typename T>
ReplayBuffer<T>::ReplayBuffer(size_t max_size)
: max_size_(max_size) {}

template<typename T>
const Status ReplayBuffer<T>::get(const int id, Entry & entry_out) const
{
  std::shared_lock lock(mutex_);
  if (id < num_pops_) {
    return Status::MISS_TOO_LATE;
  }
  if (idx_from_id(id) >= buffer_.size()) {
    return Status::MISS_TOO_EARLY;
  }
  entry_out = buffer_[idx_from_id(id)];
  return Status::OK;
}

template<typename T>
const Status ReplayBuffer<T>::get_last(const int N, std::vector<Entry> & entries_out) const
{
  if (N > buffer_.size()) {
    return Status::NOT_ENOUGH_DATA;
  }
  entries_out = std::vector<Entry>(buffer_.end() - N, buffer_.end());
  return Status::OK;
}


template<typename T>
int ReplayBuffer<T>::add(
  const std::shared_ptr<T> & value)
{
  std::unique_lock lock(mutex_);
  if (buffer_.size() >= max_size_) {
    buffer_.pop_front();
    num_pops_++;
  }
  buffer_.push_back(
    Entry{value,
      static_cast<int>(buffer_.size()) - 1,
      std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch())}
  );
  return buffer_.size() - 1;
}
} // namespace robo
