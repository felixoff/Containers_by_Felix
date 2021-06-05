#ifndef FT_QUEUE_HPP
#define FT_QUEUE_HPP

#include "ft_list.hpp"
#include <iostream>
#include <string>
#include <cstddef>
#include <limits>
namespace ft{

template <class Type, class Container = std::deque <Type> >
class queue
{
    public:
        typedef typename Container::value_type value_type;
        typedef Container container_type;
        typedef typename Container::size_type size_type;
        explicit queue(const container_type& right = container_type()):c(right)
        {
     //       this->c = right;
        }
        queue(queue const &other):c(other.c)
        {
      //      *this = other;
        }
        queue &operator=(queue const &other)
        {
            this->c = other.c;
            return (*this);
        }
        ~queue()
        {
        }
        void push(const value_type& val)
        {
            return (this->c.push_back(val));
        }
        void pop()
        {
            return (this->c.pop_front());
        }
        bool empty() const
        {
            return (this->c.size() == 0);
        }
        size_type size() const
        {
            return (this->c.size());
        }
        value_type &back()
        {
            return (this->c.back());
        }
        value_type &front()
        {
            return (this->c.front());
        }
        const value_type &front() const
        {
            return (this->c.front());
        }
        const value_type &back() const
        {
            return (this->c.back());
        }
    private:
        container_type c;
        template <class value_type, class container_type>
        friend bool operator!=(const queue<value_type, container_type>&lev, const queue<value_type,container_type> &prav);
        template <class value_type, class container_type>
        friend bool operator==(const queue<value_type, container_type>&lev, const queue<value_type,container_type> &prav);
        template <class value_type, class container_type>
        friend bool operator>(const queue<value_type, container_type>&lev, const queue<value_type,container_type> &prav);
        template <class value_type, class container_type>
        friend bool operator>=(const queue<value_type, container_type>&lev, const queue<value_type,container_type> &prav);
        template <class value_type, class container_type>
        friend bool operator<=(const queue<value_type, container_type>&lev, const queue<value_type,container_type> &prav);
        template <class value_type, class container_type>
        friend bool operator<(const queue<value_type, container_type>&lev, const queue<value_type,container_type> &prav);
};

template <class value_type, class container_type>
bool operator!=(const queue<value_type, container_type>&lev, const queue<value_type,container_type> &prav)
{
    return (lev.c!=prav.c);
}

template <class T, class Container>
bool operator==(const queue<T, Container>&lev, const queue<T,Container> &prav)
{
    return (lev.c==prav.c);
}

template <class T, class Container>
bool operator>=(const queue<T, Container>&lev, const queue<T,Container> &prav)
{
    return (lev.c>=prav.c);
}

template <class T, class Container>
bool operator>(const queue<T, Container>&lev, const queue<T,Container> &prav)
{
    return (lev.c>prav.c);
}

template <class T, class Container>
bool operator<(const queue<T, Container>&lev, const queue<T,Container> &prav)
{
    return (lev.c<prav.c);
}

template <class T, class Container>
bool operator<=(const queue<T, Container>&lev, const queue<T,Container> &prav)
{
    return (lev.c<=prav.c);
}

};

#endif