#pragma once
#include <IObject.h>
#include <KDNode.h>

class KDTree
  {
  public:

  private:
    void _Build();

    KDNode::Axis _DetectSplitingAxis(const BoundingBox& i_current_bbox) const;

  private:
    std::unique_ptr<KDNode> m_root;
    std::vector<std::unique_ptr<IObject>> m_objects;
  };