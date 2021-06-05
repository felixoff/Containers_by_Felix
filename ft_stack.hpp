#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include "ft_utils.hpp"
#include <deque>
#include "ft_list.hpp"
#include <iostream>
#include <string>
#include <cstddef>
#include <limits>
namespace ft{
    
template <class T, class Container= std::deque <T> >
class stack
{
    public:
        typedef typename Container::value_type value_type;
        typedef Container container_type;
        typedef typename Container::size_type size_type;
        explicit stack(const container_type& right = container_type())
        {
            this->c = right;
        }
        stack(stack const &other):c(other.c)
        {
      //      *this = other;
        }
        stack &operator=(stack const &other)
        {
            this->c = other.c;
            return (*this);
        }
        ~stack()
        {
        }
        bool empty() const
        {
            return (this->c.size() == 0);
        }
        size_type size() const
        {
            return (this->c.size());
        }
        value_type &top()
        {
            return (this->c.back());
        }
        const value_type &top() const
        {
            return (this->c.back());
        }
        void push(const value_type& val)
        {
            return (this->c.push_back(val));
        }
        void pop()
        {
            return (this->c.pop_back());
        }
    private:
        container_type c;
        template <class value_type, class container_type>
        friend bool operator!=(const stack<value_type, container_type>&lev, const stack<value_type,container_type> &prav);
        template <class value_type, class container_type>
        friend bool operator==(const stack<value_type, container_type>&lev, const stack<value_type,container_type> &prav);
        template <class value_type, class container_type>
        friend bool operator>(const stack<value_type, container_type>&lev, const stack<value_type,container_type> &prav);
        template <class value_type, class container_type>
        friend bool operator>=(const stack<value_type, container_type>&lev, const stack<value_type,container_type> &prav);
        template <class value_type, class container_type>
        friend bool operator<=(const stack<value_type, container_type>&lev, const stack<value_type,container_type> &prav);
        template <class value_type, class container_type>
        friend bool operator<(const stack<value_type, container_type>&lev, const stack<value_type,container_type> &prav);
};

template <class value_type, class container_type>
bool operator!=(const stack<value_type, container_type>&lev, const stack<value_type,container_type> &prav)
{
    return (lev.c!=prav.c);
}

template <class T, class Container>
bool operator==(const stack<T, Container>&lev, const stack<T,Container> &prav)
{
    return (lev.c==prav.c);
}

template <class T, class Container>
bool operator>=(const stack<T, Container>&lev, const stack<T,Container> &prav)
{
    return (lev.c>=prav.c);
}

template <class T, class Container>
bool operator>(const stack<T, Container>&lev, const stack<T,Container> &prav)
{
    return (lev.c>prav.c);
}

template <class T, class Container>
bool operator<(const stack<T, Container>&lev, const stack<T,Container> &prav)
{
    return (lev.c<prav.c);
}

template <class T, class Container>
bool operator<=(const stack<T, Container>&lev, const stack<T,Container> &prav)
{
    return (lev.c<=prav.c);
}

};

#endif