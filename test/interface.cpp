
//
// Created by Nikita Subbotin on 20.04.19.
//

#include <splay_tree.hpp>

#include <gtest/gtest.h>

namespace
{

class SplayTreeInterface : public ::testing::Test
{
public:
    SplayTreeInterface()
    {
        for (auto x : {1, 3, 5, 7, 2, 6, 4})
        {
            m_tree.Insert(x);
        }
    }

    void CheckState(const std::string & state) const
    {
        std::ostringstream ss;
        ss << m_tree;
        EXPECT_EQ(state, ss.str());
    }

    SplayTree m_tree;
    std::string m_init_state = "((1, 1) <- 2, 6 -> (3, 3)) <- 4, 28 -> ((5, 5) <- 6, 18 -> (7, 7))";
};

TEST_F(SplayTreeInterface, Insert)
{
    CheckState(m_init_state);
}

TEST_F(SplayTreeInterface, Remove)
{
    m_tree.Remove(0);
    m_tree.Remove(3);

    std::ostringstream ss;
    ss << m_tree;
    EXPECT_EQ("(1, 1) <- 2, 25 -> (4, 22 -> ((5, 5) <- 6, 18 -> (7, 7)))", ss.str());
}

TEST_F(SplayTreeInterface, Find)
{
    EXPECT_NE(nullptr, m_tree.Find(4));
    CheckState(m_init_state);

    EXPECT_NE(nullptr, m_tree.Find(5));
    CheckState("(((1, 1) <- 2, 6 -> (3, 3)) <- 4, 10) <- 5, 28 -> (6, 13 -> (7, 7))");

    EXPECT_EQ(nullptr, m_tree.Find(0));
    CheckState("1, 28 -> ((2, 9 -> ((3, 3) <- 4, 7)) <- 5, 27 -> (6, 13 -> (7, 7)))");
}

TEST_F(SplayTreeInterface, Sum)
{
    m_tree.Insert(-4);
    m_tree.Insert(10);

    EXPECT_EQ(28, m_tree.Sum(1, 7 + 1)) << m_tree;
    EXPECT_EQ(0, m_tree.Sum(0, 1)) << m_tree;
    EXPECT_EQ(-4, m_tree.Sum(-6, -2)) << m_tree;
    EXPECT_EQ(10, m_tree.Sum(8, 15)) << m_tree;
}

}