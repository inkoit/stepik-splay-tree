
//
// Created by Nikita Subbotin on 19.04.19.
//

#include <splay_tree.hpp>

#include <iostream>

class F
{
public:
    int64_t operator()(int64_t x) { return (x % m_p + m_sum) % m_p; }

    F & operator=(const int64_t & sum)
    {
        m_sum = sum;
        return *this;
    }

    friend std::ostream & operator<<(std::ostream & os, const F & f) { return os << f.m_sum; }

private:
    int64_t m_sum = 0;
    const int64_t m_p = 1000000001;
};

int main()
{
    std::ios::sync_with_stdio(false);

    SplayTree tree;
    F f;

    int n;
    std::cin >> n;
    while (n--)
    {
        char command;
        std::cin >> command;
        if (command == 's')
        {
            int64_t a, b;
            std::cin >> a >> b;
            a = f(a), b = f(b);
            std::cout << (f = tree.Sum(a, b + 1)) << '\n';
        }
        else
        {
            int64_t x;
            std::cin >> x;
            x = f(x);

            switch (command)
            {
                case '+':
                    tree.Insert(x);
                    break;
                case '-':
                    tree.Remove(x);
                    break;
                case '?':
                    std::cout << (tree.Find(x) ? "Found\n" : "Not found\n");
                    break;
            }
        }
    }
    return 0;
}