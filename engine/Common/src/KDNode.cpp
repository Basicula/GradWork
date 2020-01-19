#include <KDNode.h>
#include <Intersection.h>

KDNode::KDNode()
  {
  _Reset();
  }

KDNode::KDNode(const Objects & i_objects)
  {
  _Build(i_objects);
  }

bool KDNode::IntersectWithRay(IntersectionRecord & io_intersection, const Ray & i_ray) const
  {
  if (m_type == NodeType::EMPTY)
    return false;

  if (m_type == NodeType::LEAF)
    {
    bool intersected = false;
    for (const auto& object : m_objects)
      intersected |= object->IntersectWithRay(io_intersection, i_ray);
    return intersected;
    }

  if (RayIntersectBox(i_ray, m_bounding_box))
    {
    const bool left = m_left->IntersectWithRay(io_intersection, i_ray);
    const bool right = m_right->IntersectWithRay(io_intersection, i_ray);
    return (left || right);
    }

  return false;
  }

KDNode::Axis KDNode::_DetectSplitingAxis(const BoundingBox& i_current_bbox)
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

void KDNode::_Build(const Objects& i_objects)
  {
  _Reset();
  if (i_objects.empty())
    return;

  m_bounding_box = BoundingBox();
  for (const auto& object : i_objects)
    m_bounding_box.Merge(object->GetBoundingBox());

  m_objects = i_objects;
  m_type = NodeType::LEAF;
  m_left.reset(new KDNode());
  m_right.reset(new KDNode());

  if (i_objects.size() == 1)
    return;

  auto axis = _DetectSplitingAxis(m_bounding_box);
  const auto& bbox_center = m_bounding_box.Center();
  Objects left, right;
  for (const auto& object : m_objects)
    if(object->GetBoundingBox().Center()[axis] < bbox_center[axis])
      left.push_back(object);
    else 
      right.push_back(object);

  if (m_objects.size() == left.size() 
    || m_objects.size() == right.size())
    return;

  m_type = NodeType::INTERNAL;
  m_left->_Build(left);
  m_right->_Build(right);
  }

void KDNode::_Reset()
  {
  m_type = NodeType::EMPTY;
  m_bounding_box = BoundingBox();
  m_objects.clear();
  m_left.release();
  m_right.release();
  }

void KDNode::Clear()
  {
  if (m_type == NodeType::EMPTY)
    return;
  if(m_left)
    m_left->Clear();
  if(m_right)
    m_right->Clear();
  _Reset();
  }