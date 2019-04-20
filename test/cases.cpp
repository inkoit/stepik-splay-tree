
//
// Created by Nikita Subbotin on 20.04.19.
//

#include <splay_tree.hpp>

#include <gtest/gtest.h>

namespace
{

class SplayTreeCases : public ::testing::Test
{
protected:
    SplayTree m_tree;
    int64_t m_sum = 0;
    const int64_t p = 1000000001;
};

TEST_F(SplayTreeCases, Case1)
{
    EXPECT_FALSE(m_tree.Find(1)) << m_tree;

    m_tree.Insert(1);
    EXPECT_TRUE(bool(m_tree.Find(1))) << m_tree;

    m_tree.Insert(2);
    EXPECT_EQ(3, m_tree.Sum(1, 2 + 1)) << m_tree;

    m_tree.Insert(2);
    EXPECT_TRUE(bool(m_tree.Find(2))) << m_tree;

    m_tree.Remove(2);
    EXPECT_FALSE(bool(m_tree.Find(2))) << m_tree;
    EXPECT_EQ(1, m_tree.Sum(1, 2 + 1)) << m_tree;

    m_tree.Remove(3);
    EXPECT_FALSE(bool(m_tree.Find(3))) << m_tree;

    m_tree.Remove(1);
    m_tree.Insert(10);
    EXPECT_EQ(10, m_tree.Sum(1, 10 + 1)) << m_tree;
}

TEST_F(SplayTreeCases, Case2)
{
    EXPECT_FALSE(m_tree.Find(0)) << m_tree;

    m_tree.Insert(0);
    EXPECT_TRUE(bool(m_tree.Find(0))) << m_tree;

    m_tree.Remove(0);
    EXPECT_FALSE(bool(m_tree.Find(0))) << m_tree;
}

TEST_F(SplayTreeCases, Case3)
{
    m_tree.Insert(491572259);
    EXPECT_TRUE(bool(m_tree.Find(491572259))) << m_tree;
    EXPECT_FALSE(bool(m_tree.Find(899375874))) << m_tree;
    m_sum = m_tree.Sum(310971296, 877523306);
    EXPECT_EQ(491572259, m_sum);
    m_tree.Insert((352411209 + m_sum) % p);
}

TEST_F(SplayTreeCases, Case4)
{
    m_tree.Insert(9);
    m_tree.Insert(0);
    m_tree.Insert(1);
    m_tree.Insert(5);
    m_tree.Insert(6);
    m_tree.Insert(2);
    m_tree.Insert(3);
    m_tree.Insert(4);
    m_tree.Insert(7);
    m_tree.Insert(8);
    m_tree.Remove(4);
    EXPECT_EQ(31, m_tree.Sum(2, 8 + 1));
}

TEST_F(SplayTreeCases, Case5)
{
    m_tree.Insert(9);
    m_tree.Insert(0);
    m_tree.Insert(1);
    m_tree.Insert(5);
    m_tree.Insert(6);
    m_tree.Insert(100500);
    EXPECT_TRUE(bool(m_tree.Find(100500)));
    m_tree.Insert(100501);
    EXPECT_TRUE(bool(m_tree.Find(100501)));
    m_tree.Remove(100500);
    m_tree.Insert(100599);
    EXPECT_FALSE(bool(m_tree.Find(100500)));
    m_tree.Insert(2);
    m_tree.Insert(3);
    m_tree.Insert(4);
    m_tree.Insert(7);
    m_tree.Insert(8);
    m_tree.Remove(4);
    EXPECT_EQ(31, m_tree.Sum(2, 8 + 1));
    EXPECT_EQ(0, m_tree.Sum(200000, 200001 + 1));
}

TEST_F(SplayTreeCases, Case6)
{
    m_tree.Insert(9);
    m_tree.Insert(0);
    m_tree.Insert(1);
    m_tree.Insert(5);
    m_tree.Insert(6);
    m_tree.Insert(100500);
    EXPECT_TRUE(bool(m_tree.Find(100500)));
    m_tree.Insert(100501);
    EXPECT_TRUE(bool(m_tree.Find(100501)));
    m_tree.Remove(100500);
    m_tree.Insert(100599);
    EXPECT_FALSE(bool(m_tree.Find(100500)));
    m_tree.Insert(2);
    m_tree.Insert(3);
    m_tree.Insert(4);
    m_tree.Insert(7);
    m_tree.Insert(8);
    m_tree.Remove(4);
    m_tree.Remove(1);
    m_tree.Remove(2);
    m_tree.Remove(0);
    EXPECT_EQ(29, m_tree.Sum(2, 8 + 1));
    EXPECT_EQ(0, m_tree.Sum(200000, 200001 + 1));
    EXPECT_EQ(0, m_tree.Sum(0, 2 + 1));
    m_tree.Remove(100599);
    EXPECT_EQ(100539, m_tree.Sum(0, 100501 + 1));
    EXPECT_EQ(0, m_tree.Sum(0, 0 + 1));
    EXPECT_EQ(0, m_tree.Sum(100599, 100599 + 1));
    m_tree.Insert(5);
    EXPECT_EQ(100501, m_tree.Sum(100501, 100501 + 1));
    m_tree.Insert(6);
    EXPECT_EQ(100501, m_tree.Sum(100500, 100501 + 1));
    m_tree.Insert(0);
    EXPECT_EQ(100501, m_tree.Sum(100500, 100502 + 1));
    m_tree.Insert(9);
    EXPECT_EQ(100501, m_tree.Sum(100501, 100502 + 1));
    m_tree.Insert(7);
    EXPECT_EQ(100539, m_tree.Sum(0, 1000000000 + 1));
}

TEST_F(SplayTreeCases, Case7)
{
    m_tree.Insert(7);
    m_tree.Insert(8);
    m_tree.Insert(9);
    m_tree.Insert(0);
    m_tree.Insert(5);
    m_tree.Insert(6);
    m_tree.Insert(1);
    m_tree.Insert(2);
    m_tree.Insert(3);
    m_tree.Insert(4);
    m_tree.Remove(0);
    m_tree.Remove(9);
    m_tree.Insert(7);
    m_tree.Insert(8);
    m_tree.Insert(9);
    m_tree.Insert(0);
    m_tree.Insert(5);
    m_tree.Insert(6);
    m_tree.Insert(1);
    m_tree.Insert(2);
    m_tree.Insert(3);
    m_tree.Insert(4);
    EXPECT_EQ(45, m_tree.Sum(0, 9 + 1));
}

TEST_F(SplayTreeCases, Case8)
{
    m_tree.Insert(1);
    m_tree.Insert(2);
    m_tree.Insert(0);
    m_tree.Insert(4);
    m_tree.Remove(1);
    m_tree.Remove(2);
    m_tree.Remove(1);
    m_tree.Remove(2);
    EXPECT_EQ(4, m_tree.Sum(0, 100 + 1));
    EXPECT_EQ(4, m_tree.Sum(1, 4 + 1));
    EXPECT_EQ(0, m_tree.Sum(1, 1 + 1));
    EXPECT_EQ(4, m_tree.Sum(4, 4 + 1));
    EXPECT_EQ(4, m_tree.Sum(3, 4 + 1));
    EXPECT_EQ(4, m_tree.Sum(4, 5 + 1));
    EXPECT_EQ(0, m_tree.Sum(0, 0 + 1));
}

}
