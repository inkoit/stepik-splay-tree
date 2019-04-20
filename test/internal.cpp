
//
// Created by Nikita Subbotin on 20.04.19.
//

#include <splay_tree.hpp>

#include <gtest/gtest.h>

namespace
{

class SplayTreeInternal : public SplayTree, public ::testing::Test
{
protected:
    std::shared_ptr<Node> x;
    std::shared_ptr<Node> p;
    std::shared_ptr<Node> g;
    std::shared_ptr<Node> A;
    std::shared_ptr<Node> B;
    std::shared_ptr<Node> C;
    std::shared_ptr<Node> D;

    std::string expected;

    void InitZigZigFull()
    {
        g = m_root = std::make_shared<Node>(6, nullptr);
        g->m_sum = 28;

        D = std::make_shared<Node>(7, g);
        g->m_right = D;

        p = std::make_shared<Node>(4, g);
        g->m_left = p;
        p->m_sum = 15;

        x = std::make_shared<Node>(2, p);
        p->m_left = x;
        x->m_sum = 6;

        A = std::make_shared<Node>(1, x);
        x->m_left = A;

        B = std::make_shared<Node>(3, x);
        x->m_right = B;

        C = std::make_shared<Node>(5, p);
        p->m_right = C;

        expected = "(((1, 1) <- 2, 6 -> (3, 3)) <- 4, 15 -> (5, 5)) <- 6, 28 -> (7, 7)";
    }

    void InitZigZagRightFull()
    {
        g = m_root = std::make_shared<Node>(6, nullptr);
        g->m_sum = 28;

        p = std::make_shared<Node>(2, g);
        g->m_left = p;
        p->m_sum = 15;

        A = std::make_shared<Node>(1, x);
        p->m_left = A;

        x = std::make_shared<Node>(4, p);
        p->m_right = x;
        x->m_sum = 12;

        B = std::make_shared<Node>(3, x);
        x->m_left = B;

        C = std::make_shared<Node>(5, p);
        x->m_right = C;

        D = std::make_shared<Node>(7, g);
        g->m_right = D;

        expected = "((1, 1) <- 2, 15 -> ((3, 3) <- 4, 12 -> (5, 5))) <- 6, 28 -> (7, 7)";
    }

    void InitZigZagLeftFull()
    {
        g = m_root = std::make_shared<Node>(2, nullptr);
        g->m_sum = 28;

        A = std::make_shared<Node>(1, x);
        g->m_left = A;

        p = std::make_shared<Node>(6, g);
        g->m_right = p;
        p->m_sum = 25;

        x = std::make_shared<Node>(4, p);
        p->m_left = x;
        x->m_sum = 12;

        B = std::make_shared<Node>(3, x);
        x->m_left = B;

        C = std::make_shared<Node>(5, p);
        x->m_right = C;

        D = std::make_shared<Node>(7, g);
        p->m_right = D;

        expected = "(1, 1) <- 2, 28 -> (((3, 3) <- 4, 12 -> (5, 5)) <- 6, 25 -> (7, 7))";
    }
};

TEST_F(SplayTreeInternal, RotateFull)
{
    InitZigZigFull();

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ(expected, ss.str());
    }

    Rotate(x, p);
    m_root->m_left = x;

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ("((1, 1) <- 2, 15 -> ((3, 3) <- 4, 12 -> (5, 5))) <- 6, 28 -> (7, 7)", ss.str());
    }

    Rotate(p, x);
    m_root->m_left = p;

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ(expected, ss.str());
    }
}

TEST_F(SplayTreeInternal, Zig)
{
    p = m_root = std::make_shared<Node>(4, nullptr);
    p->m_sum = 6;

    x = std::make_shared<Node>(2, p);
    p->m_left = x;

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ("(2, 2) <- 4, 6", ss.str());
    }

    m_root = Splay(x);

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ("2, 6 -> (4, 4)", ss.str());
    }

    m_root = Splay(p);

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ("(2, 2) <- 4, 6", ss.str());
    }
}

TEST_F(SplayTreeInternal, ZigZig)
{
    InitZigZigFull();

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ(expected, ss.str());
    }

    m_root = Splay(x);

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ("(1, 1) <- 2, 28 -> ((3, 3) <- 4, 25 -> ((5, 5) <- 6, 18 -> (7, 7)))", ss.str());
    }

    m_root = Splay(g);

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ(expected, ss.str());
    }
}

TEST_F(SplayTreeInternal, ZigZagRight)
{
    InitZigZagRightFull();

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ(expected, ss.str());
    }

    m_root = Splay(x);

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ("((1, 1) <- 2, 6 -> (3, 3)) <- 4, 28 -> ((5, 5) <- 6, 18 -> (7, 7))", ss.str());
    }
}

TEST_F(SplayTreeInternal, ZigZagLeft)
{
    InitZigZagLeftFull();

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ(expected, ss.str());
    }

    m_root = Splay(x);

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ("((1, 1) <- 2, 6 -> (3, 3)) <- 4, 28 -> ((5, 5) <- 6, 18 -> (7, 7))", ss.str());
    }
}

TEST_F(SplayTreeInternal, Merge)
{
    p = m_root = std::make_shared<Node>(2, nullptr);
    p->m_sum = 6;

    A = std::make_shared<Node>(1, p);
    p->m_left = A;

    B = std::make_shared<Node>(3, p);
    p->m_right = B;

    g = std::make_shared<Node>(6, nullptr);
    g->m_sum = 18;

    C = std::make_shared<Node>(5, g);
    g->m_left = C;

    D = std::make_shared<Node>(7, g);
    g->m_right = D;

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ("(1, 1) <- 2, 6 -> (3, 3)", ss.str());
    }
    {
        std::ostringstream ss;
        ss << *g;
        EXPECT_EQ("(5, 5) <- 6, 18 -> (7, 7)", ss.str());
    }

    m_root = Merge(p, g);

    {
        std::ostringstream ss;
        ss << *static_cast<SplayTree *>(this);
        EXPECT_EQ("((1, 1) <- 2, 3) <- 3, 24 -> ((5, 5) <- 6, 18 -> (7, 7))", ss.str());
    }
}

}