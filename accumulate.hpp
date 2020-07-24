
#pragma once
#include <vector>
#include <iterator>

using namespace std;

typedef struct
{
    template <typename T>
    auto operator()(const T &x, const T &y) const
    {
        return x + y;
    }

} add;

namespace itertools
{

    template <typename CONT, typename OP = add> // OP = operator
    class accumulate
    {
        const CONT &container;
        const OP &function;

    public:
        accumulate(const CONT &con, const OP &op = add()) : container(con), function(op) {}

        class iterator
        {
            decltype(container.begin()) iter;                              // e.g if container is vector then the type is vector::iterator
            typename std::decay<decltype(*(container.begin()))>::type sum; // return type of elements in the given container
            const accumulate &acc;

        public:
            iterator(decltype(container.begin()) curr, const accumulate &acc) : iter(curr), acc(acc)
            {
                if (curr != acc.container.end())
                    sum = *curr;
            }

            iterator &operator++()
            { //++iter
                ++iter;
                if (iter == acc.container.end())
                    return *this;
                sum = acc.function(sum, *iter);
                return *this;
            }

            const iterator operator++(int)
            { //iter++
                iterator temp = *this;
                sum = acc.function(sum, *(iter));
                iter++;
                return temp;
            }

            bool operator==(const iterator &it) const
            {
                return iter == it.iter;
            }

            bool operator!=(const iterator &it) const
            {
                return !(iter == it.iter);
            }

            auto operator*()
            {
                return sum;
            }

            iterator &operator=(const iterator &temp_iter)
            {
                if (this != &temp_iter)
                {
                    this->iter = temp_iter.iter;
                    this->acc = temp_iter.acc;
                    this->sum = temp_iter.sum;
                }
                return *this;
            }
        };

        iterator begin() const
        {
            return iterator(container.begin(), *this);
        }
        iterator end() const
        {
            return iterator(container.end(), *this);
        }
    };

} // namespace itertools
