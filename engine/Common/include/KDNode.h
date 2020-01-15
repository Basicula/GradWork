#pragma once
#include <vector>
#include <memory>

#include <BoundingBox.h>

class KDNode
  {
  public:
    enum class Axis
      {
      X,
      Y,
      Z,
      };

  public:

  private:
    BoundingBox m_bounding_box;
    std::vector<int> m_object_indicies;
    std::unique_ptr<KDNode> m_left;
    std::unique_ptr<KDNode> m_right;
  };