#pragma once
#include <iostream>

namespace itertools
{
    template <typename T1, typename T2>
    class compress
    {
        const T1 &container1;
        const T2 &bool_container;

    public:
        compress(const T1 &c1, const T2 &c2) : container1(c1), bool_container(c2) {}

        class iterator
        {
            decltype(container1.begin()) iter1;
            decltype(bool_container.begin()) iter2;
            const compress &comp;

        public:
            iterator(decltype(container1.begin()) it1, decltype(bool_container.begin()) it2, const compress &c)
                : iter1(it1), iter2(it2), comp(c)
            {

                while (iter2 != comp.container2.end() && *iter2 == false)
                {
                    iter1++;
                    iter2++;
                }
            }

            iterator &operator++()
            {
                ++iter1;
                ++iter2;
                while (iter2 != comp.container2.end() && *iter2 == false))
                    {
                        iter1++;
                        iter2++;
                    }
                return *this;
            }

            const iterator operator++(int)
            {
                iterator temp = *this;
                ++*this;
                return temp;
            }

            bool operator==(const iterator &it) const
            {
                return iter1 == it.iter1;
            }

            bool operator!=(const iterator &it) const
            {
                return iter1 != it.iter1;
            }

            auto operator*()
            {
                return *iter1;
            }

            iterator &operator=(const iterator &temp_iter)
            {
                if (this != &temp_iter)
                {
                    this->iter1 = temp_iter.iter1;
                    this->iter2 = temp_iter.iter2;
                    this->comp = temp_iter.comp;
                }
                return *this;
            }
        };

        iterator begin() const
        {
            return iterator(container1.begin(), bool_container.begin(), *this);
        }

        iterator end() const
        {
            return iterator(container1.end(), bool_container.end(), *this);
        };
    };
} // namespace itertools