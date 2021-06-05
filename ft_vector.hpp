#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include "ft_utils.hpp"
#include <iostream>
#include <string>
#include <cstddef>
#include <limits>

#include <cmath>
namespace ft{

template < class T, class Alloc = ft::allocator<T> >
class vector
{
    public:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer	pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    private:
    value_type  *value;
    size_type size_var;
    size_type capacity_var;
    allocator_type allocator;

    public:
    class Iterator
    {
        protected:
            value_type          *iter;
        public:
			typedef size_t		size_type;
			typedef ptrdiff_t	difference_type;
			typedef T*			pointer;
			typedef T&			reference;
			typedef T			value_type;
			typedef const T&	const_reference;
			typedef const T*	const_pointer;
        Iterator():iter(NULL){}
        Iterator(const Iterator &iter):iter(iter.iter){}
        Iterator &operator=(const Iterator &iter){this->iter = iter.iter;
        return *this;}
        Iterator(value_type *elem):iter(elem){}
        ~Iterator(){}
        bool operator ==(const Iterator &right) const
        {
            return (iter == right.iter);
        }
        bool operator !=(const Iterator &right) const
        {
            return (iter != right.iter);
        }
        T& operator * ()
        {
            return (*iter);
        }
		T* operator -> ()
        {
            return (iter);
        }
		Iterator& operator ++ ()
        {
            this->iter++;
            return (*this);
        }
        Iterator& operator -- ()
        {
            this->iter--;
            return (*this);
        }
		Iterator operator ++ (int)
        {
            Iterator new_iter = *this;
            this->iter++;
            return (new_iter);

        }
			Iterator operator -- (int)
        {
            Iterator new_iter = *this;
            this->iter--;
            return (new_iter);

        }
		Iterator operator + (difference_type n)
        {
            Iterator new_iter = *this;
            new_iter.iter = this->iter + n;
            return (new_iter);
        }
		Iterator operator - (difference_type n)
        {
            Iterator new_iter = *this;
            new_iter.iter = this->iter - n;
            return (new_iter);
        }
		difference_type operator - (Iterator it)
        {
            return (this->iter - it.iter);
        }
		void operator += (difference_type n)
        {
            this->iter = this->iter + n;
        }
		void operator -= (difference_type n)
        {
            this->iter = this->iter - n;
        }
		T& operator [] (difference_type n)
        {
            return (*(this->iter + n));
        }
		bool operator < (const Iterator& it) const
        {
            return (this->iter < it.iter);
        }
		bool operator <= (const Iterator& it) const
        {
            return (this->iter <= it.iter);
        }
		bool operator > (const Iterator& it) const
        {
            return (this->iter > it.iter);
        }
		bool operator >= (const Iterator& it) const
        {
            return (this->iter >= it.iter);
        }
    };

// class Iterator 
// 		{
// 			public:
// 			typedef size_t		size_type;
// 			typedef ptrdiff_t	difference_type;
// 			typedef T*			pointer;
// 			typedef T&			reference;
// 			typedef T			value_type;
// 			typedef const T&	const_reference;
// 			typedef const T*	const_pointer;

// 			Iterator()
// 			{
// 				t = NULL;
// 			};

// 			Iterator(const Iterator& it)
// 			{
// 				t = it.t;
// 			};

// 			void operator = (const Iterator& it)
// 			{
// 				t = it.t;
// 			};

// 			Iterator(T* t): t(t)
// 			{}

// 			~Iterator() {};

// 			bool operator == (const Iterator& it) const
// 			{
// 				return (it.t == t);
// 			};

// 			bool operator != (const Iterator& it) const
// 			{
// 				return (it.t != t);
// 			};

// 			T& operator * ()
// 			{
// 				return (*t);
// 			};

// 			T* operator -> ()
// 			{
// 				return (t);
// 			};

// 			Iterator& operator ++ ()
// 			{
// 				t = t + 1;
// 				return (*this);
// 			};

// 			Iterator& operator -- ()
// 			{
// 				t = t - 1;
// 				return (*this);
// 			};

// 			Iterator operator ++ (int)
// 			{
// 				Iterator b = *this;

// 				t = t + 1;
// 				return (b);
// 			};

// 			Iterator operator -- (int)
// 			{
// 				Iterator b = *this;

// 				t = t - 1;
// 				return (b);
// 			};

// 			Iterator operator + (difference_type n)
// 			{
// 				Iterator b;

// 				b.t = t + n;
// 				return (b);
// 			};

// 			Iterator operator - (difference_type n)
// 			{
// 				Iterator b;

// 				b.t = t - n;
// 				return (b);
// 			};

// 			difference_type operator - (Iterator it)
// 			{
// 				return (t - it.t);
// 			};

// 			void operator += (difference_type n)
// 			{
// 				t += n;
// 			};

// 			void operator -= (difference_type n)
// 			{
// 				t -= n;
// 			};

// 			T& operator [] (difference_type n)
// 			{
// 				return (*(t + n));
// 			};

// 			bool operator < (const Iterator& it) const
// 			{
// 				return (t < it.t);
// 			};

// 			bool operator <= (const Iterator& it) const
// 			{
// 				return (t <= it.t);
// 			};

// 			bool operator > (const Iterator& it) const
// 			{
// 				return (t > it.t);
// 			};

// 			bool operator >= (const Iterator& it) const
// 			{
// 				return (t >= it.t);
// 			};

// 			protected:
// 			T			*t;
// 		};

		class Const_Iterator: public Iterator
		{
			public:
			Const_Iterator(): Iterator()
			{
			}

			Const_Iterator(const Const_Iterator& i): Iterator(i)
			{}

			Const_Iterator(const Iterator& i): Iterator(i)
			{}

			void operator = (const Const_Iterator& i)
			{
				Iterator::_t = i.t;
			}

			virtual ~Const_Iterator() {};

			Const_Iterator(T* t): Iterator(t)
			{}

			const T& operator [] (difference_type n)
			{
				return (*(Iterator::iter + n));
			};

			const T& operator * ()
			{
				return (*(Iterator::iter));
			};

			const T* operator -> ()
			{
				return (Iterator::iter);
			};


		};

		class Const_Reverse_Iterator: public Reverse_Iterator<Iterator>
		{
			public:
			Const_Reverse_Iterator() {};
			Const_Reverse_Iterator(const Iterator& i): Reverse_Iterator<Iterator>(i)
			{};
			Const_Reverse_Iterator(const Const_Reverse_Iterator& i): Reverse_Iterator<Iterator>(i)
			{};
			Const_Reverse_Iterator(const Reverse_Iterator<Iterator>& i): Reverse_Iterator<Iterator>(i)
			{};
			void operator = (const Reverse_Iterator<Iterator>& i)
			{
				Reverse_Iterator<Iterator>::current = i.current;
			}

			const_reference operator * () const
			{
				const_iterator a = Reverse_Iterator<Iterator>::current;
				return (*a);
			};

			const_reference operator [] (difference_type n) const
			{
				iterator a(Reverse_Iterator<Iterator>::current);
				const_iterator b(a - n);
				return (*b);
			};

			const_pointer operator -> () const
			{
				const_iterator a = Reverse_Iterator<Iterator>::current;
				return (Reverse_Iterator<Iterator>::current::t);
			};
		};

		typedef Iterator	iterator;
		typedef Reverse_Iterator<iterator> reverse_iterator;
		typedef Const_Iterator const_iterator;
		typedef Const_Reverse_Iterator const_reverse_iterator;

    explicit vector (const allocator_type& alloc = allocator_type()):value(NULL),size_var(0),capacity_var(0),allocator(alloc)
    {
    }
    explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()):size_var(n),capacity_var(n),allocator(alloc)
    {
        value = allocator.allocate(size_var);
        for (size_type i = 0; i < size_var; i++)
        {
            allocator.construct(&value[i],val);
        }

    }
    template <class InputIterator>
    vector (InputIterator first, InputIterator last,
    const allocator_type& alloc = allocator_type())
    {
        allocator = alloc;
        InputIterator input = first;
        size_type size_input = 0;
        while (input != last)
        {
            input++;
            size_input++;
        }
        if (size_input == 0)
        {
            size_var = 0;
            capacity_var = 0;
            value = NULL;
            return;
        }
        size_var = size_input;
        capacity_var = size_input;
        value = allocator.allocate(size_var);
        for (size_type i = 0; i < size_var; i++)
        {
            allocator.construct(&value[i],*first);
            first++;
        }
    }
    vector (const vector& x)
    {
        capacity_var = x.capacity_var;
        size_var = x.size_var;
        allocator = x.allocator;
        value = allocator.allocate(capacity_var);
        for(size_type i = 0;i < size_var;i++)
        {
            allocator.construct(&value[i],x.value[i]);
        }
    }
    ~vector()
    {
        if (capacity_var == 0)
            return;
        for (size_type i = 0; i < capacity_var; i++)
        {
            allocator.destroy(&value[i]);
        }
        allocator.deallocate(value,capacity_var); 
    }
    void operator = (const vector& x)
    {
        allocator = x.allocator;
        if (capacity_var > 0)
        {
            for (size_type i = 0; i < capacity_var; i++)
                allocator.destroy(&value[i]);
            allocator.deallocate(value,capacity_var);  
            value = NULL;  
        }
        capacity_var = x.capacity_var;
        size_var = x.size_var;
        value = allocator.allocate(capacity_var);
        for(size_type i = 0;i < size_var;i++)
        {
            allocator.construct(&value[i],x.value[i]);
        }
    }
    iterator begin()
    {
        iterator it(&value[0]);
        return it;
    }
    const_iterator begin() const
    {
        iterator tmp(&value[0]);
        const_iterator it(tmp);
        return it;
    }
    iterator end()
    {
        iterator it(&value[size_var]);
        return it;
    }
    const_iterator end() const
    {
        iterator tmp(&value[size_var]);
        const_iterator it(tmp);
        return it;
    }
    reverse_iterator rbegin()
    {
        iterator tmp(end()-1);
        reverse_iterator it(tmp);
        return it;
    }
    const_reverse_iterator rbegin() const
    {
        iterator tmp(end()-1);
        const_reverse_iterator it(tmp);
        return it;
    }
    reverse_iterator rend()
    {
        iterator tmp(begin()-1);
        reverse_iterator it(tmp);
        return it;
    }
    const_reverse_iterator rend() const
    {
        iterator tmp(begin()-1);
        const_reverse_iterator it(tmp);
        return it;
    }
    size_type size() const
    {
        return this->size_var;
    }
    size_type max_size() const
    {
        return (std::numeric_limits<size_type>::max()/sizeof(value_type));
    }
    void resize (size_type n, value_type val = value_type())
    {
        if (n > max_size())
            throw(std::length_error("very big lenght you want"));
        if (n < size_var)
        {
            size_var = n;
            return;
        }
        if (n <= capacity_var)
        {
            for (size_type i = size_var; i < capacity_var;i++)
                value[i] = val;
            size_var = n;
        }
        else
        {
        value_type *new_vector;
        new_vector = allocator.allocate(n);
        for (size_type i = 0; i < size_var; i++)
        {
            allocator.construct(&new_vector[i],value[i]);
        }
        for (size_type i = size_var; i < n; i++)
        {
            allocator.construct(&new_vector[i],val);
        }
        if (capacity_var > 0)
        {
            for (size_type i = 0; i < capacity_var; i++)
                allocator.destroy(&value[i]);
            allocator.deallocate(value,capacity_var);  
            value = NULL;  
        }
        size_var = n;
        capacity_var = n;
        value = new_vector;
        }
    }
    size_type capacity() const
    {
        return this->capacity_var;
    }
    bool empty() const
    {
        return (this->size_var == 0);
    }
    void reserve (size_type n)
    {
        if (n > max_size())
            throw(std::length_error("very big lenght you want"));
        if (n <= capacity_var)
            return;
        value_type *new_vector;
        new_vector = allocator.allocate(n);
        for (size_type i = 0; i < size_var; i++)
        {
            allocator.construct(&new_vector[i],value[i]);
        }
        if (capacity_var > 0)
        {
            for (size_type i = 0; i < capacity_var; i++)
                allocator.destroy(&value[i]);
            allocator.deallocate(value,capacity_var);  
            value = NULL;  
        }
        capacity_var = n;
        value = new_vector;
    }
    reference operator[] (size_type n)
    {
        return (value[n]);
    }
    const_reference operator[] (size_type n) const
    {
        return (value[n]);
    }
      reference at (size_type n)
      {
        if (n >= size_var || n < 0)
            throw (std::out_of_range("out of range"));
        return (value[n]);
      }
const_reference at (size_type n) const
{
    if (n >= size_var || n < 0)
        throw (std::out_of_range("out of range"));
    return (value[n]);
}
      reference front()
      {
        if (this->empty())
			throw(std::out_of_range("Vector is empty, mission impossible"));
        return (value[0]);
      }
const_reference front() const
{
        if (this->empty())
			throw(std::out_of_range("Vector is empty, mission impossible"));
        return (value[0]); 
}
      reference back()
{
            if (this->empty())
			throw(std::out_of_range("Vector is empty, mission impossible"));
        return (value[size_var - 1]);
}
const_reference back() const
{
    if (this->empty())
		throw(std::out_of_range("Vector is empty, mission impossible"));
    return (value[size_var - 1]); 
}	
allocator_type get_allocator() const
{
    return this->allocator;
}
template <class InputIterator>
  void assign (InputIterator first, InputIterator last)
  {
        InputIterator input = first;
        size_type size_input = 0;
        while (input != last)
        {
            input++;
            size_input++;
        }
        if (size_input == 0)
        {
            size_var = 0;
            capacity_var = 0;
            value = NULL;
            return;
        }
        if (size_input <= capacity_var)
        {
        for (size_type i = 0; i<size_input;i++)
        {
            value[i] = *first;
            first++;
        }
        size_var = size_input;
        }
        else
        {
            clear();
        while (first != last)
        {
            push_back(*first);
            first++;
        }
        }
  }
void assign (size_type n, const value_type& val)
{
    if (n <= capacity_var)
    {
        for (size_type i = 0; i<n;i++)
            value[i] = val;
        size_var = n;
    }
    else
    {
        this->clear();
        for (size_type i = 0; i < n; i++)
            push_back(val);
    }
}
void push_back (const value_type& val)
{
    size_type tmp_capacity;
    value_type *tmp_value;
    if (size_var < capacity_var)
    {
        allocator.construct(&value[size_var],val);
        size_var++;
        return;
    }

    if (size_var > 0)
        tmp_capacity = size_var * 2;
    else
        tmp_capacity = 1;
    
    tmp_value = allocator.allocate(tmp_capacity);
    for (size_type i = 0; i < size_var; i++)
        allocator.construct(&tmp_value[i],value[i]);
    allocator.construct(&tmp_value[size_var],val);
    if (capacity_var > 0)
    {
    for (size_type i = 0; i < size_var; i++)
        allocator.destroy(&value[i]);
    allocator.deallocate(value, capacity_var);
    }
    capacity_var = tmp_capacity;
    value = tmp_value;
    size_var++;
}
void pop_back()
{
    if (!empty())
        this->size_var--;
}

iterator insert (iterator position, const value_type& val)
{
 size_type diff = 0;
    iterator it = this->begin();
    while (it != position)
    {
        diff++;
        it++;
    }
    if (size_var + 1 > capacity_var)
        this->reserve(size_var+1);
    for (size_type i = size_var; i >= diff;i--)
    {
        allocator.construct(&value[i+1],value[i]);
  //      value[i+1] = value[i];
    }
    size_var++;
    allocator.construct(&value[diff],val);
  //  value[diff] = val;
    return (position);
}
    void insert (iterator position, size_type n, const value_type& val)
{
 size_type diff = 0;
    iterator it = this->begin();
    while (it != position)
    {
        diff++;
        it++;
    }
    if (size_var + n > capacity_var)
        this->reserve(size_var+n);
    for (size_type i = 0; i < n;i++)
    {
        for (size_type j = size_var; j >= diff;j--)
        {
             allocator.construct(&value[j+1],value[j]);
        }
            size_var++;
        allocator.construct(&value[diff],val);
        diff++;
    }
  //  return (position);   
}
template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last)
{
    size_type diff = 0;
    size_type input_diff = 0;
    iterator it = this->begin();
    InputIterator input_it = first;
    while (it != position)
    {
        diff++;
        it++;
    }
    while (input_it != last)
    {
        input_diff++;
        input_it++;
    }
    if (size_var + input_diff > capacity_var)
        this->reserve(size_var+input_diff);
    for (size_type i = 0; i < input_diff;i++)
    {
        for (size_type j = size_var; j >= diff;j--)
        {
             allocator.construct(&value[j+1],value[j]);
        }
        size_var++;
        allocator.construct(&value[diff],*first);
        diff++;
        first++;
    } 
}
iterator erase (iterator position)
{
    size_type diff = 0;
    iterator it = this->begin();
    while (it != position)
    {
        diff++;
        it++;
    }
    for (size_type i = diff; i < size_var - 1;i++)
    {
        value[i] = value[i+1];
    }
    size_var--;
    if (diff == size_var)
        return (end());
    else   
        return (position);
}
iterator erase (iterator first, iterator last)
{
    difference_type diff = first - begin();
    difference_type length = last - first;
    if (length <= 0)
        return (first);
    for (size_type i = diff; last != end(); i++, last++)
        value[i] = *last;
    size_var = size_var - length;
    return first;
}
void swap (vector& x)
{
    size_type tmp_size;
    size_type tmp_capacity;
    value_type *tmp_val;

    tmp_size = this->size_var;
    this->size_var = x.size_var;
    x.size_var = tmp_size;

    tmp_val = this->value;
    this->value = x.value;
    x.value = tmp_val;
    
    tmp_capacity = this->capacity_var;
    this->capacity_var = x.capacity_var;
    x.capacity_var = tmp_capacity;
}
void clear()
{
    this->size_var = 0;
}
};

template <class T, class Alloc>
  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
  {
      x.swap(y);
  }
template <class T, class Alloc>
  bool operator == (const vector<T,Alloc>& x, const vector<T,Alloc>& y)
{
    if (x.size() == y.size())
    {
        for (typename vector<T,Alloc>::size_type i = 0; i < x.size(); i++)
            if (x[i] != y[i])
                return(false);
        return(true);
    }
    return(false);
}
template <class T, class Alloc>
  bool operator!= (const vector<T,Alloc>& x, const vector<T,Alloc>& y)
  {
      return(!(x == y));
  }
template <class T, class Alloc>
  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
  {
      typename vector<T,Alloc>::const_iterator start1 = lhs.begin();
      typename vector<T,Alloc>::const_iterator start2 = rhs.begin();
      typename vector<T,Alloc>::const_iterator end1 = lhs.end();
      typename vector<T,Alloc>::const_iterator end2 = rhs.end();

      while (start1 != end1)
      {
          if (start2 == end2 || start2 < start1)
            return(false);
            else if (start1 < start2)
                return(true);
            start2++;
            start1++;
      }
      return (start2 != end2);
  }
template <class T, class Alloc>
  bool operator<= (const vector<T,Alloc>& x, const vector<T,Alloc>& y)
{
    return (!(y<x));
}
template <class T, class Alloc>
  bool operator>  (const vector<T,Alloc>& x, const vector<T,Alloc>& y)
  {
      return (y<x);
  }
template <class T, class Alloc>
  bool operator>= (const vector<T,Alloc>& x, const vector<T,Alloc>& y)
{
    return (!(x < y));
}

}

#endif