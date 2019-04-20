# Сплей-дерево с поддержкой суммы

Stepik, курс ["Алгоритмы: теория и практика. Структуры данных"](https://stepik.org/1547), модуль 4, задача 4

## Задача

Реализуйте структуру данных для хранения множества целых чисел, поддерживающую запросы добавления, удаления, поиска, 
а также суммы на отрезке. На вход в данной задаче будет дана последовательность таких запросов. Чтобы гарантировать,
что ваша программа обрабатывает каждый запрос по мере поступления (то есть онлайн), каждый запрос будет зависеть от 
результата выполнения одного из предыдущих запросов. Если бы такой зависимости не было, задачу можно было бы решить 
оффлайн: сначала прочитать весь вход и сохранить все запросы в каком-нибудь виде, а потом прочитать вход ещё раз, 
параллельно отвечая на запросы.

### Формат входа. 

Изначально множество пусто. Первая строка содержит число запросов _n_. Каждая из _n_ следующих строк содержит запрос в 
одном из следующих четырёх форматов:

- `+ i`: добавить число _f(i)_ в множество (если оно уже есть, проигнорировать запрос);
- `- i`: удалить число f(i) из множества (если его нет, проигнорировать запрос);
- `? i`: проверить принадлежность числа f(i) множеству;
- `s l r`: посчитать сумму всех элементов множества, попадающих в отрезок _\[f(l),f(r)\]_.

Функция _f_ определяется следующим образом. Пусть _s_ — результат последнего запроса суммы на отрезке (если таких 
запросов ещё не было, то _s = 0_). Тогда

_f(x) = (x + s) mod 1 000 000 001_

### Формат выхода. 

Для каждого запроса типа `? i` выведите «Found» или «Not found».
 
Для каждого запроса суммы выведите сумму всех элементов множества, попадающих в отрезок _\[f(l),f(r)\]_.
 
Гарантируется, что во всех тестах f(l) ≤ f(r).

### Ограничения. 

_1 ≤ n ≤ 10 ^ 5 ; 0 ≤ i ≤ 10 ^ 9_ 

## Решение

Первая реализация была основана на `std::set` и попытке выполнить `std::accumulate` на промежутке 
`[lower_bound, upper_bound)`. 
Однако тесты падали из-за истечения лимита времени на прохождение: время работы такого алгоритма было линейным, а 
требовалось, вероятно, логарифмическое.

Было решено написать свою реализацию сплей-дерева с поддержкой суммы элементов поддерева в каждом узле. Определение 
суммы дерева с корнем в узле `x` следующее: 

`sum(x) = sum(x->left) + sum(x->right) + x->value`

Причины выбора сплей-дерева следующие:

- балансируются => в среднем все операции _log(n)_
- для нахождения суммы необходимо дважды выполнить _Split_ по дереву, взять значение суммы в корне получившегося дерева 
в середине и в обратном порядке выполнить _Merge_ => сложность _log(n)_ 
- просты в реализации

Из-за ограничений принимающей платформы необходимо было использовать C++11 и только STL

Класс реализован в виде разделяемой библиотеки, `cli.cpp` реализует управление классом в соответствии с заданием 
(команды, функции и т.п.) 
