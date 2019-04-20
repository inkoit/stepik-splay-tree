
//
// Created by Nikita Subbotin on 18.04.19.
//

#include <splay_tree.hpp>

std::ostream & operator<<(std::ostream & os, const SplayTree & tree)
{
    return tree.m_root ? os << *tree.m_root : os;
}

std::ostream & operator<<(std::ostream & os, const SplayTree::Node & node)
{
    if (node.m_left)
    {
        os << "(" << *node.m_left << ") <- ";
    }
    os << node.m_value << ", " << node.m_sum;
    if (node.m_right)
    {
        os << " -> (" << *node.m_right << ")";
    }
    return os;
}

void SplayTree::Insert(int64_t value)
{
    if (m_root)
    {
        auto node = Insert(m_root, value);
        if (node)
        {
            m_root = Splay(node);
        }
    }
    else
    {
        m_root = std::make_shared<Node>(value, nullptr);
    }
}

void SplayTree::Remove(int64_t value)
{
    if (!m_root)
    {
        return;
    }

    // Функция может вернуть не тот элемент, который нужно, поэтому необходимо дополнительно проверить, что он
    // соответствует требуемому значению
    auto found = FindNearest(m_root, value);
    if (found->m_value == value && (m_root = Merge(found->m_left, found->m_right)))
    {
        m_root->m_parent = nullptr;
    }
}

bool SplayTree::Contains(int64_t x)
{
    if (!m_root)
    {
        return false;
    }

    m_root = FindNearest(m_root, x);
    return m_root->m_value == x;
}

int64_t SplayTree::Sum(int64_t a, int64_t b)
{
    // Делим дерево на три части: (-inf, a), [a, b), [b, +inf)
    std::shared_ptr<Node> left, mid, right;
    std::tie(left, mid) = Split(m_root, a);
    std::tie(mid, right) = Split(mid, b);

    // Запоминаем результат, если не null, и восстанавливаем всё в !!обратном порядке!!
    auto res = mid ? mid->m_sum : 0;
    m_root = Merge(left, Merge(mid, right));

    return res;
}

std::shared_ptr<SplayTree::Node> SplayTree::Insert(std::shared_ptr<SplayTree::Node> node, int64_t value)
{
    if (value == node->m_value)
    {
        return nullptr;
    }

    // Выбираем нужного ребенка и, если он существует, спускаемся дальше, иначе создаём ребенка
    auto & child = value < node->m_value ? node->m_left : node->m_right;
    auto inserted = child ? Insert(child, value) : (child = std::make_shared<Node>(value, node));
    node->m_sum += inserted ? value : 0; // Добавляем в сумму по пути обратно, если вставка прошла успешно
    return inserted;
}

std::shared_ptr<SplayTree::Node> SplayTree::FindNearest(std::shared_ptr<SplayTree::Node> node, int64_t value)
{
    if (value == node->m_value)
    {
        return Splay(node);
    }

    auto & child = value < node->m_value ? node->m_left : node->m_right;
    return child ? FindNearest(child, value) : Splay(node);
}

std::pair<std::shared_ptr<SplayTree::Node>, std::shared_ptr<SplayTree::Node>>
SplayTree::Split(std::shared_ptr<SplayTree::Node> root, int64_t value)
{
    if (!root)
    {
        return {nullptr, nullptr};
    }

    // (-inf, value) U [value, +inf)
    root = FindNearest(std::move(root), value);

    std::shared_ptr<Node> left, right, child;

    // root in (-inf, value) => root->right in [value, +inf)
    if (root->m_value < value)
    {
        child = (left = root, right = root->m_right);
        root->m_right = nullptr;
    }
        // root in [value, +inf) => root->left in (-inf, value)
    else
    {
        child = (right = root, left = root->m_left);
        root->m_left = nullptr;
    }

    if (child)
    {
        child->m_parent = nullptr;
        root->m_sum -= child->m_sum;
    }

    return {left, right};
}

std::shared_ptr<SplayTree::Node>
SplayTree::Merge(std::shared_ptr<SplayTree::Node> v1, std::shared_ptr<SplayTree::Node> v2)
{
    if (!v1)
    {
        return v2;
    }
    if (!v2)
    {
        return v1;
    }
    v1->m_parent = v2->m_parent = nullptr;

    // Поиск максимума в v1 (самый правый элемент)
    for (; v1->m_right; v1 = v1->m_right) {}

    Splay(v1);

    v1->m_right = v2;
    v1->m_sum += v2->m_sum;
    return v2->m_parent = v1;
}

std::shared_ptr<SplayTree::Node> SplayTree::Splay(std::shared_ptr<SplayTree::Node> x)
{
    // Выполняем цикл до тех пор, пока родителем не будет nullptr (пока x не root)
    for (auto p = x->m_parent; p; p = x->m_parent)
    {
        auto g = p->m_parent; // дед
        if (!g)
        {
            // zig
            Rotate(x, p);
        }
        else
        {
            auto r = g->m_parent; // прадед

            if ((x == p->m_left && p == g->m_left) || (x == p->m_right && p == g->m_right))
            {
                // zig-zig
                Rotate(p, g);
                Rotate(x, p);
            }
            else
            {
                // zig-zag
                Rotate(x, p);

                // ВАЖНО: после поворота выше рассматриваемое поддерево c корнем в g не находится в согласованном
                // состоянии, т.к. g по-прежнему считает p своим потомком
                (g->m_left == p ? g->m_left : g->m_right) = x;

                Rotate(x, g);
            }

            if (r)
            {
                (r->m_left == g ? r->m_left : r->m_right) = x;
            }
        }
    }

    return x;
}

void SplayTree::Rotate(std::shared_ptr<SplayTree::Node> x, std::shared_ptr<SplayTree::Node> y)
{
    // Здесь необходимо обращать внимание на то, что A, B, C могут быть nullptr, а также на изменение значения суммы у

    if (y->m_left == x)
    {
        /*
         *     p         p
         *     |         |
         *     y         x
         *    / \       / \
         *   x  C  =>  A  y
         *  / \          / \
         * A  B         B  C
         *
         */
        const auto & A = x->m_left;
        const auto & B = x->m_right;

        RotateCommon(x, B, y);

        y->m_left = B;
        x->m_right = y;
        y->m_sum -= (A ? A->m_sum : 0) + x->m_value;
    }
    else
    {
        /*
         *   p          p
         *   |          |
         *   y          x
         *  / \        / \
         * A  x  =>   y  C
         *   / \     / \
         *  B  C    A  B
         *
         */
        const auto & B = x->m_left;
        const auto & C = x->m_right;

        RotateCommon(x, B, y);

        y->m_right = B;
        x->m_left = y;
        y->m_sum -= (C ? C->m_sum : 0) + x->m_value;
    }
}

void SplayTree::RotateCommon(std::shared_ptr<SplayTree::Node> x, const std::shared_ptr<SplayTree::Node> & B,
                             std::shared_ptr<SplayTree::Node> y)
{
    x->m_parent = y->m_parent;
    y->m_parent = x;
    x->m_sum = y->m_sum;

    if (B)
    {
        B->m_parent = y;
    }
}
