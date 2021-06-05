#ifndef FT_UTILS_HPP
#define FT_UTILS_HPP

#include <cstddef>
#include <limits>
#include <iostream>
#include <string>

namespace ft{

// template <class T>
// class allocator
// {
//     public:
//     typedef T value_type;
//     typedef const value_type *const_pointer;
//     typedef const value_type& const_reference;
//     typedef value_type *pointer;
//     typedef ptrdiff_t difference_type;
//     typedef value_type& reference;
//     typedef size_t size_type;
//     template <class U>
//     struct rebind { typedef allocator<U> other; };

//     pointer address(reference val) {return &val;}
//     allocator(){}
//     allocator(const allocator<value_type>& right){(void)right;}
// template <class U>
//     allocator(const allocator<U>& right){(void)right;}
//     const_pointer address(const_reference val) const {return &val;}
// pointer allocate(size_type count, allocator<value_type>::const_pointer hint = 0)
// {
//     (void)hint;
//         if (count == 0)
//         {
//         return nullptr;
//         }
//         if (count > static_cast<size_type>(-1) / sizeof(T))
//         {
//         throw std::bad_array_new_length();
//         }
//         void *p = operator new(sizeof(value_type)* count);
//         return(static_cast<pointer>(p));
     
//   //   return reinterpret_cast<pointer>(::operator new(count *sizeof(T)));
// }
//     void construct(pointer ptr, const value_type& val)
//     {
//         new(ptr) value_type(val);
//     }
//     void deallocate(pointer ptr, size_type count)
//     {
//         (void)count;
//         if (ptr)
//             delete ptr;
//     }
//     void destroy(pointer ptr){ptr->~value_type();}
//     size_type max_size() const
//     {
//         return std::numeric_limits<size_type>::max() / sizeof(value_type);
//     }
//     template <class U>
//     allocator<value_type>& operator=(const allocator<U>& right)
//     {
//         (void)right;
//         return *this;
//     }
//     template <class U>
//     bool operator ==(const allocator<U>&)
//     {
//         return true;
//     }
//     template <class U>
//         bool operator !=(const allocator<U>&)
//     {
//         return false;
//     }
// };

template <class T>
class allocator
{
    public:
    typedef T value_type;
    typedef const value_type *const_pointer;
    typedef const value_type& const_reference;
    typedef value_type *pointer;
    typedef ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef size_t size_type;
    template <class U>
    struct rebind { typedef allocator<U> other; };

    pointer address(reference val) {return &val;}
    allocator(){}
    allocator(const allocator<value_type>& right){(void)right;}
template <class U>
    allocator(const allocator<U>& right){(void)right;}
    const_pointer address(const_reference val) const {return &val;}

pointer allocate(size_type count, allocator<value_type>::const_pointer hint = 0)
{
    (void)hint;
        if (count == 0)
        {
        return nullptr;
        }
        if (count > static_cast<size_type>(-1) / sizeof(T))
        {
        throw std::bad_array_new_length();
        }
        void *p = operator new(sizeof(value_type)* count);
        return(static_cast<pointer>(p));
     
  //   return reinterpret_cast<pointer>(::operator new(count *sizeof(T)));
}
    void construct(pointer ptr, const value_type& val)
    {
        new(ptr) value_type(val);
    }
    void deallocate(pointer ptr, size_type count)
    {
        (void)count;
        if (ptr)
            delete ptr;
        // ::operator delete(ptr);
    }
    void destroy(pointer ptr){ptr->~value_type();}
    size_type max_size() const
    {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }
    template <class U>
    allocator<value_type>& operator=(const allocator<U>& right)
    {
        (void)right;
        return *this;
    }
    template <class U>
    bool operator ==(const allocator<U>&)
    {
        return true;
    }
    template <class U>
        bool operator !=(const allocator<U>&)
    {
        return false;
    }
};

template <class iterator>
class Reverse_Iterator
{
    protected:
        iterator current;
    public:
    	typedef Reverse_Iterator<iterator>		reverse_iterator;
		typedef typename iterator::size_type		size_type;
		typedef typename iterator::difference_type	difference_type;
		typedef typename iterator::pointer			pointer;
		typedef typename iterator::reference			reference;
		typedef typename iterator::value_type			value_type;
		typedef typename iterator::const_reference	const_reference;
		typedef typename iterator::const_pointer	const_pointer;
    Reverse_Iterator(){};
    template <class IterType>
    Reverse_Iterator(const Reverse_Iterator<IterType> &iter){this->current = iter.current;};
    void operator = (const reverse_iterator &iter){this->current = iter.current;};
    
    Reverse_Iterator(iterator elem):current(elem){};
    ~Reverse_Iterator(){};
    bool operator ==(const reverse_iterator &right) const
    {
        return (current == right.current);
    }
    bool operator !=(const reverse_iterator &right) const
    {
        return (current != right.current);
    }
    reference operator * ()
    {
        return (*current);
    }
	pointer operator -> ()
    {
        return (&(*current));
    }
	reverse_iterator& operator ++ ()
    {
        current--;
        return (*this);
    }
    reverse_iterator& operator -- ()
    {
        current++;
        return (*this);
    }
	reverse_iterator operator ++ (int)
    {
        reverse_iterator new_iter = *this;
        current--;
        return (new_iter);
    }
	reverse_iterator operator -- (int)
    {
        reverse_iterator new_iter = *this;
        current++;
        return (new_iter);
    }
	reverse_iterator operator + (difference_type n)
    {
        reverse_iterator new_iter = *this;
        new_iter.current = current - n;
        return (new_iter);
    }
	reverse_iterator operator - (difference_type n)
    {
        reverse_iterator new_iter = *this;
        new_iter.current = current + n;
        return (new_iter);
    }
	difference_type operator - (reverse_iterator it)
    {
        return (it.current - this->current);
    }
	void operator += (difference_type n)
    {
        current = current - n;
    }
	void operator -= (difference_type n)
    {
        current = current + n;
    }
	reference operator [] (difference_type n)
    {
        return (*(this->current + n));
            //return(this->iterator[n])
    }
	bool operator < (const reverse_iterator& it) const
    {
        return (this->current > it.current);
    }
	bool operator <= (const reverse_iterator& it) const
    {
        return (this->current >= it.current);
    }
	bool operator > (const reverse_iterator& it) const
    {
        return (this->current < it.current);
    }
	bool operator >= (const reverse_iterator& it) const
    {
        return (this->current <= it.current);
    }
};

}

#endif
