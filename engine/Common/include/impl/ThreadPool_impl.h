#include <algorithm>

using namespace Parallel;

ThreadPool* ThreadPool::m_instance = nullptr;
std::size_t ThreadPool::m_in_progress_cnt = 0;
const std::size_t ThreadPool::m_max_workers = 16;

ThreadPool::ThreadPool()
  : m_stop(false)
  {
  const auto num_of_workers_hint = std::thread::hardware_concurrency();
  const auto num_of_workers = (num_of_workers_hint == 0u ? 8u : num_of_workers_hint);
  for (std::size_t i = 0; i < num_of_workers; ++i)
    _AddWorker();
  }

template<class IndexType, class Function>
void ThreadPool::ParallelFor(
  IndexType i_start,
  IndexType i_end,
  const Function& i_function)
  {
  const std::size_t num_of_tasks = static_cast<std::size_t>(i_end - i_start + 1);
  // we don't want to use all workers 
  // if we have more than 4 workers
  // often 4 is quite enough for this task
  const auto num_of_workers = 
    std::min(m_workers.size(), static_cast<std::size_t>(4));
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

inline ThreadPool::~ThreadPool()
  {
  if (true)
    {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_stop = true;
    }
  m_wait_condition.notify_all();
  for(auto& worker : m_workers)
    worker.join();
  }

inline ThreadPool* ThreadPool::GetInstance()
  {
  if(!m_instance)
    m_instance = new ThreadPool();
  return m_instance;
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

inline void Parallel::ThreadPool::_AddWorker()
  {
  m_workers.emplace_back(
    [this]()
    {
    while (true)
      {
      ThreadTask task;

      // critical section waiting for task
      if (true)
        {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_wait_condition.wait(
          lock,
          [this]()
          {
          return m_stop || !m_tasks.empty();
          });
        if (m_stop && m_tasks.empty())
          return;
        task = std::move(m_tasks.front());
        m_tasks.pop();
        }
      // execute task
      ++m_in_progress_cnt;
      task();
      --m_in_progress_cnt;
      }
    });
  }