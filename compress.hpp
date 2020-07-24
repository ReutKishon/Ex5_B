#pragma once
#include <iostream>


namespace itertools{
    template <class T1 , class T2>
    class compress{
        const T1& container1;
        const T2& container2;
    public:
        compress(const T1& c1 , const T2& c2) : container1(c1) , container2(c2){}

        class iterator{
            decltype(container1.begin()) iter1;
            decltype(container2.begin()) iter2;
            const compress& comp;
        public:

            iterator(decltype(container1.begin()) it1 , decltype(container2.begin()) it2 , const compress& c)
                    : iter1(it1) ,comp(c){
                if(iter2!=c.container2.end()) iter2=it2;
                while(iter2!=comp.container2.end() && *iter2==false) {
                    iter1++;
                    iter2++;
                }
            }

            iterator& operator++(){
                ++iter1;
                ++iter2;
                while(iter2!=comp.container2.end() && !(*iter2)) {
                    iter1++;
                    iter2++;
                }
                return *this;
            }

            const iterator operator++(int){
                iterator temp = *this;
                ++*this;
                return temp;
            }

            bool operator==(const iterator& it) const{
                return iter1==it.iter1;
            }

            bool operator!=(const iterator& it) const{
                return iter1!=it.iter1;
            }

            auto operator*(){
                return *iter1;
            }

        };

        iterator begin() const{
            return iterator(container1.begin(),container2.begin(),*this);
        }

        iterator end() const {
            return iterator(container1.end(),container2.end(),*this);
        };


    };
}