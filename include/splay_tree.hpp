//
// Created by Nikita Subbotin on 18.04.19.
//

#ifndef STEPIK_SPLAY_TREE_HPP
#define STEPIK_SPLAY_TREE_HPP

#include <memory>
#include <ostream>

#include <cstdint>

class SplayTree
{
public:
    struct Node
    {
        int64_t m_value;
        int64_t m_sum;
        std::shared_ptr<Node> m_parent;
        std::shared_ptr<Node> m_left;
        std::shared_ptr<Node> m_right;

        Node(int64_t value, std::shared_ptr<Node> parent) : m_value(value), m_sum(value), m_parent(std::move(parent)) {}

        friend std::ostream & operator<<(std::ostream & os, const Node & node);
    };

    void Insert(int64_t value);

    void Remove(int64_t value);

    std::shared_ptr<SplayTree::Node> Find(int64_t value);

    int64_t Sum(int64_t a, int64_t b);

    friend std::ostream & operator<<(std::ostream & os, const SplayTree & tree);

protected:

    std::shared_ptr<Node> m_root;

    static std::shared_ptr<SplayTree::Node> Insert(std::shared_ptr<Node> node, int64_t value);

    static std::shared_ptr<Node> FindNearest(std::shared_ptr<Node> node, int64_t value);

    static std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> Split(std::shared_ptr<Node> root, int64_t value);

    static std::shared_ptr<Node> Merge(std::shared_ptr<Node> v1, std::shared_ptr<Node> v2);

    static std::shared_ptr<Node> Splay(std::shared_ptr<Node> x);

    static void Rotate(std::shared_ptr<Node> x, std::shared_ptr<Node> y);

    static void RotateCommon(std::shared_ptr<Node> x, const std::shared_ptr<Node> & B, std::shared_ptr<Node> y);
};

#endif //STEPIK_SPLAY_TREE_HPP
