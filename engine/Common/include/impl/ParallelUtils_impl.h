namespace Parallel
  {
  template<class T>
  void ParallelFill(std::vector<T>& o_to_fill, const T& i_default_value, std::size_t i_size)
    {
    if (i_size == 0)
      return;
    o_to_fill.resize(i_size);
    ParallelFor(static_cast<std::size_t>(0), i_size,
      [&o_to_fill, &i_default_value](std::size_t i_index)
      {
      o_to_fill[i_index] = i_default_value;
      });
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
    const IndexType num_of_tasks = i_end - i_start + 1;
    auto bucket_size = static_cast<IndexType>(
      std::round(num_of_tasks / static_cast<double>(num_of_workers)));
    bucket_size = std::max(bucket_size, IndexType(1));

    auto worker_task = [&i_function](IndexType i_start, IndexType i_end)
      {
      for (auto i = i_start; i < i_end; ++i)
        i_function(i);
      };

    std::vector<std::thread> workers;
    workers.reserve(num_of_workers);
    IndexType i1 = i_start;
    IndexType i2 = std::min(i_start + bucket_size, i_end);
    for (auto i = 0u; i + 1 < num_of_workers && i1 < i_end; ++i)
      {
      workers.emplace_back(worker_task, i1, i2);
      i1 = i2;
      i2 = std::min(i1 + bucket_size, i_end);
      }
    if (i1 < i_end)
      workers.emplace_back(worker_task, i1, i_end);
    for (auto& worker : workers)
      if (worker.joinable())
        worker.join();
    }
  }