#pragma once
#include <vector>
#include <thread>

namespace Parallel
  {
  template<class T>
  void Fill(std::vector<T>& o_to_fill, const T& i_default_value)
    {

    }

  template<class IndexType, class Function>
  void ParallelFor(
    IndexType i_start,
    IndexType i_end,
    const Function& i_function)
    {
    const auto num_of_workers_hint = std::thread::hardware_concurrency();
    const auto num_of_workers = 
      (num_of_workers_hint == 0u ? 8u : num_of_workers_hint);
    IndexType num_of_tasks = i_end - i_start + 1;
    IndexType bucket_size = num_of_tasks / num_of_workers;
    IndexType rest_work = num_of_tasks - bucket_size * num_of_workers;

    auto worker_task = [&i_function](IndexType i_start, IndexType i_end)
      {
      for (auto i = i_start; i < i_end; ++i)
        i_function(i);
      };

    std::vector<std::thread> workers;
    workers.reserve(num_of_workers);
    }
  }