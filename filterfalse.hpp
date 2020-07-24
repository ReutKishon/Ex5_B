#pragma once

namespace itertools
{
    template <typename FUNC, typename T>
    class filterfalse
    {
        const T &container;
        const FUNC &function;

    public:
        filterfalse(const FUNC &func, const T &con) : function(func), container(con) {}

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