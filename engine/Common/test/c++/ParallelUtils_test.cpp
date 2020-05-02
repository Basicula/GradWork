#include <gtest/gtest.h>
#include <chrono>

#include <ParallelUtils.h>
#include "Utils.h"

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

  auto parallel_time =
    function_wrapper_for_time([&]()
      {
      Parallel::ParallelFill(parallel, default_value, size);
      },
      iterations);

  auto common_time =
    function_wrapper_for_time([&]()
      {
      common.resize(size);
      for (auto i = 0u; i < size; ++i)
        common[i] = default_value;
      },
      iterations);

  EXPECT_TRUE(common_time > parallel_time);
  }