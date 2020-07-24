#pragma once

namespace itertools
{
    template <typename FUNCTOR, typename CONT>
    class filterfalse
    {
        const CONT &container;
        const FUNCTOR &function;

    public:
        filterfalse(const FUNCTOR &func, const CONT &con) : function(func), container(con) {}

        class iterator
        {
            decltype(container.begin()) iter; // return iterator of container (begin)
            const filterfalse &filter;

        public:
            iterator(decltype(container.begin()) it, const filterfalse &f) : iter(it), filter(f)
            {
                while (iter != filter.container.end() && filter.function(*iter))
                    iter++;
            }

            iterator &operator=(const iterator &temp_iter)
            {
                if (this != &temp_iter)
                {
                    this->iter = temp_iter.iter;
                    this->filter = temp_iter.filter;
                }
                return *this;
            }

            iterator &operator++()
            {
                ++iter;
                while (iter != filter.container.end() && filter.function(*iter))
                    ++iter;
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
                return iter == it.iter;
            }

            bool operator!=(const iterator &it) const
            {
                return iter != it.iter;
            }

            auto operator*()
            {
                return *iter;
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