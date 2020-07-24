#pragma once

#include <iostream>
namespace itertools
{
    class myit
    {
        int index;

    public:
         myit(int i = 0) : index(i) {}
        int operator*() const { return index; }
        myit &operator++()
        {
            ++index;
            return *this;
        }
        myit operator++(int)
        {
            myit t = *this;
            index++;
            return t;
        }
        bool operator!=(const myit &other) const
        {
            return index != other.index;
        }
        bool operator==(const myit &other) const
        {
            return index == other.index;
        }
    };

    class range
    {
        int start;
        int finish;

    public:
        range(int s, int e) : start(s), finish(e) {}
        myit begin() const { return myit(start); }
        myit end() const { return myit(finish); }
    };
} // namespace itertools