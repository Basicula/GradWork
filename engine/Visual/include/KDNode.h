#pragma once
#include <vector>
#include <memory>

#include <IRenderable.h>
#include <BoundingBox.h>

using Objects = std::vector<IRenderableSPtr>;

class KDNode
  {
  public:
    enum Axis
      {
      X = 0,
      Y = 1,
      Z,
      };

    enum class NodeType
      {
      INTERNAL,
      LEAF,
      EMPTY
      };

  public:
    KDNode();
    KDNode(const Objects& i_objects);

    bool IntersectWithRay(
      IntersectionRecord& io_intersection, 
      const Ray& i_ray) const;

    void Clear();

  private:
    void _Build(const Objects& i_objects);
    void _Reset();

    static KDNode::Axis _DetectSplitingAxis(const BoundingBox& i_current_bbox);

  private:
    NodeType m_type;
    BoundingBox m_bounding_box;
    Objects m_objects;
    std::unique_ptr<KDNode> m_left;
    std::unique_ptr<KDNode> m_right;
  };