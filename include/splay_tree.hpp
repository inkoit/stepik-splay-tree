//
// Created by Nikita Subbotin on 18.04.19.
//

#ifndef STEPIK_SPLAY_TREE_HPP
#define STEPIK_SPLAY_TREE_HPP

#include <memory>
#include <ostream>

#include <cstdint>

/*!
 * \brief Класс сплей-дерева с поддержкой суммирования
 * \details Реализует требуемый интерфейс доступа к дереву. Хранит значения в int64_t во избежание переполнения в
 * соответствии с условиями задачи
 */
class SplayTree
{
public:

    /*!
     * \brief Производит вставку элемента в дерево.
     * \details При наличии элемента в дереве ничего не происходит
     * \param value Значение для вставки
     */
    void Insert(int64_t value);

    /*!
     * \brief Производит удаление элемента из дерева.
     * \details При отсутствии элемента в дереве ничего не происходит
     * \param value Значение для удаления
     */
    void Remove(int64_t value);

    /*!
     * \brief Производит проверку наличия элемента в дерево.
     * \param value Значение элемента
     * \return true -- если элемент присутствует, false -- если нет
     */
    bool Contains(int64_t value);

    /*!
     * \brief Производит вставку элемента в дерево.
     * \details При наличии элемента в дереве ничего не происходит
     * \param value Значение для вставки
     */
    int64_t Sum(int64_t a, int64_t b);

    /*!
     * \brief Выводит дерево в виде "[(left) <- ]value, sum[ -> (right)]", где left и right выводятся аналогичным
     * образом
     * \param os Поток вывода
     * \param tree Дерево
     * \return Модифицированный поток вывода
     */
    friend std::ostream & operator<<(std::ostream & os, const SplayTree & tree);

protected:

    // Основная логика происходит здесь

    // Узел дерева с дополнительным полем суммы
    struct Node
    {
        int64_t m_value;
        int64_t m_sum; // вот то самое поле суммы
        std::shared_ptr<Node> m_parent;
        std::shared_ptr<Node> m_left;
        std::shared_ptr<Node> m_right;

        Node(int64_t value, std::shared_ptr<Node> parent) : m_value(value), m_sum(value), m_parent(std::move(parent)) {}

    };

    // Единственное, что хранит класс -- это корень дерева
    std::shared_ptr<Node> m_root;

    // Отладочный вывод дерева
    friend std::ostream & operator<<(std::ostream & os, const SplayTree::Node & tree);

    // Функция вставки в дерево. WARNING: при node == nullptr упадёт. Не вызывает Splay
    static std::shared_ptr<SplayTree::Node> Insert(std::shared_ptr<Node> node, int64_t value);

    // Функция поиска похожего значения (на котором остановился поиск). WARNING: при node == nullptr упадёт.
    // Вызывает Splay
    static std::shared_ptr<Node> FindNearest(std::shared_ptr<Node> node, int64_t value);

    // Функция разделения дерева на два: (-inf, value) U [value, +inf). nullptr подавать можно.
    static std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> Split(std::shared_ptr<Node> root, int64_t value);

    // Функция слияния двух деревьев v1 < v2. nullptr-ы подавать можно
    static std::shared_ptr<Node> Merge(std::shared_ptr<Node> v1, std::shared_ptr<Node> v2);

    // Функция сплей. WARNING: при node == nullptr упадёт.
    static std::shared_ptr<Node> Splay(std::shared_ptr<Node> x);

    // Функция поворота вокруг ребра x-y, где x -- ребенок, а y -- родитель.
    // WARNING: не модифицирует узлы выше по уровню! Запись x в исходного потомка y должна производиться в
    // вызывающем коде!
    // WARNING: x и y не могут быть nullptr!
    static void Rotate(std::shared_ptr<Node> x, std::shared_ptr<Node> y);

private:

    // Вспомогательная функция для осуществления поворота вокруг ребра x-y
    static void RotateCommon(std::shared_ptr<Node> x, const std::shared_ptr<Node> & B, std::shared_ptr<Node> y);
};

#endif //STEPIK_SPLAY_TREE_HPP
