#pragma once
#include <algorithm>
#include <vector>
#include <thread>

namespace Parallel
  {
  template<class T>
  void ParallelFill(
    std::vector<T>& o_to_fill, 
    const T& i_default_value, 
    std::size_t i_size);

  template<class IndexType, class Function>
  void ParallelFor(
    IndexType i_start,
    IndexType i_end,
    const Function& i_function);
  }

#include <ParallelUtils_impl.h>