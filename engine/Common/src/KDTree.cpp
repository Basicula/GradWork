#include <KDTree.h>

void KDTree::_Build()
  {
  }

KDNode::Axis KDTree::_DetectSplitingAxis(const BoundingBox& i_current_bbox) const
  {
  const double x = i_current_bbox.DeltaX();
  const double y = i_current_bbox.DeltaY();
  const double z = i_current_bbox.DeltaZ();
  if (x > y && x > z)
    return KDNode::Axis::X;
  else if (y > z)
    return KDNode::Axis::Y;
  else
    return KDNode::Axis::Z;
  }