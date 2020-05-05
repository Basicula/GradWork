#include <algorithm>
#include <math.h>
using namespace Parallel;

template<class IndexType, class Function>
void ThreadPool::ParallelFor(
  IndexType i_start,
  IndexType i_end,
  const Function& i_function)
  {
  const std::size_t num_of_tasks = static_cast<std::size_t>(i_end - i_start + 1);
  // we don't want to use all workers 
  // if we have more than 8 workers
  // often 8 is quite enough for this task
  const auto num_of_workers = 
    std::min(m_workers.size(), static_cast<std::size_t>(8));
  auto bucket_size = static_cast<std::size_t>(
    std::round(num_of_tasks / static_cast<double>(num_of_workers)));
  bucket_size = std::max(bucket_size, static_cast<std::size_t>(1));

  auto worker_task = [&i_function](IndexType i_start, IndexType i_end)
    {
    for (auto i = i_start; i < i_end; ++i)
      i_function(i);
    };

  std::vector<std::future<typename std::result_of<Function(IndexType)>::type>> results;
  IndexType i1 = i_start;
  IndexType i2 = std::min(i_start + bucket_size, i_end);
  for (auto i = 0u; i + 1 < num_of_workers && i1 < i_end; ++i)
    {
    results.push_back(Enqueue(worker_task, i1, i2));
    i1 = i2;
    i2 = std::min(i1 + bucket_size, i_end);
    }
  if (i1 < i_end)
    results.push_back(Enqueue(worker_task, i1, i_end));
  for (auto& reslult : results)
    reslult.get();
  }

template<class Function, class ...Args>
inline auto ThreadPool::Enqueue(Function&& i_function, Args&&... i_args) 
  -> std::future<typename std::result_of<Function(Args...)>::type>
  {
  using ResultType = typename std::result_of<Function(Args...)>::type;
  auto task = std::make_shared<std::packaged_task<ResultType()>>(
    std::bind(
      std::forward<Function>(i_function), 
      std::forward<Args>(i_args)...)
      );
  std::future<ResultType> result = task->get_future();
  if (true)
    {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_tasks.emplace([task](){(*task)();});
    }
  if (m_in_progress_cnt == m_workers.size() 
    && m_workers.size() < m_max_workers
    && m_tasks.size() > m_workers.size())
    _AddWorker();
  m_wait_condition.notify_one();
  return result;
  }