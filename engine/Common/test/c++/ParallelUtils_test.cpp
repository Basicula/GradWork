#include <gtest/gtest.h>
#include <chrono>

#include <ParallelUtils.h>

TEST(ParallelFillTest, ParallelFillCommonTest)
  {
  std::vector<int> data;
  const int default_value = 123;
  const std::size_t size = 100;
  Parallel::ParallelFill(data, default_value, size);

  EXPECT_EQ(data.size(), size);
  for (const auto& elem : data)
    EXPECT_EQ(elem, default_value);
  }

TEST(ParallelFillTest, ParallelFillVSCommonFill)
  {
  const std::size_t iterations = 1;
  const std::size_t size = 1000000;
  const int default_value = 123;

  std::vector<int> common, parallel;

  using FillFunctionWrapper = std::function<void()>;

  auto fill_function = [&iterations](const FillFunctionWrapper& i_func)
    {
    const auto start = std::chrono::system_clock::now();
    for (auto i = 0u; i < iterations; ++i)
      i_func();
    const auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    };

  auto parallel_time =
    fill_function([&]()
      {
      Parallel::ParallelFill(parallel, default_value, size);
      });

  auto common_time =
    fill_function([&]()
      {
      common.resize(size);
      for (auto i = 0u; i < size; ++i)
        common[i] = default_value;
      });

  EXPECT_TRUE(common_time > parallel_time);
  }
