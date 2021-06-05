#ifndef FT_LIST_HPP
#define FT_LIST_HPP

#include "ft_utils.hpp"
#include <iostream>
#include <exception>
#include <string>

#include <cstddef>
#include <limits>
namespace ft{

template < class T, class Alloc = ft::allocator<T> >
class list
{
public:
typedef T value_type;
typedef Alloc allocator_type;
typedef typename allocator_type::reference	reference;
typedef typename	allocator_type::const_reference	const_reference;
typedef typename	allocator_type::pointer	pointer;
typedef typename	allocator_type::const_pointer	const_pointer;		
typedef ptrdiff_t difference_type;
typedef size_t size_type;

class Node
{
    public:
    Node *prev;
    Node *next;
    T value;
    Node():prev(NULL),next(NULL){}
    ~Node(){}
    Node(const Node &node):prev(node.prev),next(node.next),value(node.value){}
    Node &operator=(const Node &node)
    {
        this->prev = node.prev;
        this->next = node.next;
        this->value = node.value;
    }
    Node(Node *prev,Node *next, const T&value = T()):prev(prev),next(next),value(value){}
};

class Iterator
{
    protected:
        Node *node; 
    public:
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef T* pointer;
    typedef T& reference;
    typedef T value_type;
    typedef const T* const_pointer;
    typedef const T& const_reference;
    Iterator():node(NULL){}
    Iterator(Node *node):node(node){}
    Iterator &operator=(const Iterator &other)
    {
        this->node = other.node;
        return (*this);
    }
    Iterator(const Iterator &other):node(other.node){}
    ~Iterator(){}
    bool operator ==(const Iterator &right) const
    {
        return node == right.node;
    }
    bool operator !=(const Iterator &right) const
    {
        return node != right.node;
    }
    pointer operator ->()
    {
        return this->node->value;
    }
    reference operator *()
    {
        return node->value;
    }
    Iterator& operator ++()
    {
        this->node = this->node->next;
        return *this;
    }
    Iterator& operator --()
    {
        this->node = this->node->prev;
        return *this;
    }
    Iterator operator ++(int i)
    {
        (void)i;
        Iterator tmp = *this;
        this->node = this->node->next;
        return tmp;
    }
    Iterator operator --(int i)
    {
        (void)i;
        Iterator tmp = *this;
        this->node = this->node->prev;
        return tmp;
    }
};


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
				Iterator::node = i._node;
			}

			virtual ~Const_Iterator() {};

			Const_Iterator(T* t): Iterator(t)
			{}

			const T& operator * ()
			{
				return (Iterator::node->value);
			};


			const T* operator -> () const
			{
				return (Iterator::node);
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
			//	return (*_base);
			};

			const_pointer operator -> () const
			{
				const_iterator a = Reverse_Iterator<Iterator>::current;
				return (Reverse_Iterator<Iterator>::current::node);
			};
		};

		typedef Iterator iterator;
		typedef Reverse_Iterator<Iterator> reverse_iterator;
		typedef Const_Iterator const_iterator;
		typedef Const_Reverse_Iterator const_reverse_iterator;
// template<class U>
// class Const_Iterator: public Iter_for_list<U> 
// 		{
// 			public:
// 			Const_Iterator(): Iter_for_list<U> ()
// 			{
// 			}

// 			Const_Iterator(const Const_Iterator& i): Iter_for_list<U> (i)
// 			{}

// 			Const_Iterator(const Iter_for_list<U> & i): Iter_for_list<U> (i)
// 			{}

// 			void operator = (const Const_Iterator& i)
// 			{
// 				Iter_for_list<U> ::node = i.node;
// 			}

// 			virtual ~Const_Iterator() {};

// 			Const_Iterator(T* t): Iter_for_list<U> (t)
// 			{}

// 			const T& operator * ()
// 			{
// 				return (Iter_for_list<U> ::node->value);
// 			};


// 			const T* operator -> () const
// 			{
// 				return (Iter_for_list<U> ::node);
// 			};


// 		};
// template<class U>
// 		class Const_Reverse_Iterator: public Reverse_Iterator<Iter_for_list<U> >
// 		{
// 			public:
// 			Const_Reverse_Iterator() {};
// 			Const_Reverse_Iterator(const Iter_for_list<U> & i): Reverse_Iterator<Iter_for_list<U> >(i)
// 			{};
// 			Const_Reverse_Iterator(const Const_Reverse_Iterator& i): Reverse_Iterator<Iter_for_list<U> >(i)
// 			{};
// 			Const_Reverse_Iterator(const Reverse_Iterator<Iter_for_list<U> >& i): Reverse_Iterator<Iter_for_list<U> >(i)
// 			{};
// 			void operator = (const Reverse_Iterator<Iter_for_list<U> >& i)
// 			{
// 				Reverse_Iterator<Iter_for_list<U> >::current = i.current;
// 			}

// 			const_reference operator * () const
// 			{
// 				const_iterator a = Reverse_Iterator<Iter_for_list<U> >::current;
// 				return (*a);
// 			//	return (*_base);
// 			};

// 			const_pointer operator -> () const
// 			{
// 				const_iterator a = Reverse_Iterator<Iter_for_list<U> >::current;
// 				return (Reverse_Iterator<Iter_for_list<U> >::current::node);
// 			};
// 		};
// typedef Iter_for_list <value_type> iterator;
// typedef Const_Iterator<value_type> const_iterator;	
// typedef Reverse_Iterator<iterator> reverse_iterator;		
// typedef Const_Reverse_Iterator<value_type> const_reverse_iterator;

typedef typename Alloc::template rebind<Node>::other node_alloc_type;
private:
    Node *head;
    Node *tail;
    Node past_end;
    Node past_begin;
    size_type size_var;
    node_alloc_type allocator;
void set_head_tail()
{
    if (head)
        head->prev = &past_begin;
    if (tail)
        tail->next = &past_end;
    past_begin.next = head;
    past_end.prev = tail;
}

Node *allocate_node()
{
    Node *new_node = allocator.allocate(1);
    return (new_node);
}

Node *allocate_node(Node *next, Node *prev, const value_type &value= T())
{
    Node *tmp = allocate_node();
    Node new_node(next,prev,value);
    allocator.construct(tmp,new_node);
    return (tmp);
}

void push_list(list &list)
{
    if (list.empty())
        return;
    if (this->empty())
    {
        tail = list.tail;
        head = list.head;
    }
    else
    {
        tail->next = list.head;
        list.head->prev = tail;
        tail = list.tail;
    }
    size_var+=list.size_var;
    set_head_tail();
}

void push_node(Node *node, Node *next, Node *prev)
{
    if (prev)
        prev->next = node;
    else
        head = node;
    node->prev = prev;
    if (next)
        next->prev = node;
    else
        tail = node;
    node->next = next;
    size_var+=1;
    set_head_tail();
}

void delete_node(Node *node)
{
    pop_node(node);
    deallocate_node(node);
}
void pop_node(Node *node)
{
    if (node == &past_end || node == &past_begin)
        return;
    if (node->next)
    node->next->prev = node->prev;
    if (node->prev)
    node->prev->next = node->next;
    if (node == head)
        head = node->next;
    if (node == tail)
        tail = node->prev;     
    size_var-=1;
    set_head_tail();
}
void deallocate_node(Node *node)
{
   allocator.destroy(node);
   allocator.deallocate(node,1); 
}

Node *get_node(iterator it)
{
    iterator tmp = begin();
    Node *node = head;
    
    if (it == --begin())
        return (&past_begin);
    while (tmp != it)
    {
        node = node->next;
        tmp++;
    }
    return(node);
}

iterator insert_node(iterator pos, Node *node)
{
    Node *tmp = get_node(pos);
    if (tmp == head)
        head = node;
    if (tmp == &past_begin)
        head = node;
    if (tmp == &past_end)
        tail = node;
    node->next = tmp;
    node->prev = tmp->prev;
    tmp->prev->next = node;
    tmp->prev = node;
    size_var+=1;
    set_head_tail();
    return(iterator(node));
}

reference operator[](size_type pos)
{
    if (pos < 0 || pos >= size_var)
        throw (std::out_of_range("ERROR:out of range"));
    Node *tmp;
    tmp = head;
    for (size_type i = 0; i < pos; i++)
        tmp = tmp->next;
    return(tmp->value);
}

const reference operator[](size_type pos) const
{
    if (pos < 0 || pos >= size_var)
        throw (std::out_of_range("ERROR:out of range"));
    Node *tmp;
    tmp = head;
    for (size_type i = 0; i < pos; i++)
        tmp = tmp->next;
    return(tmp->value);
}

public:
explicit list (const allocator_type& alloc = node_alloc_type()):head(NULL),tail(NULL),size_var(0),allocator(alloc)	
{
    set_head_tail();
}
explicit list (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = node_alloc_type()):head(NULL),tail(NULL),size_var(0),allocator(alloc)
{
    set_head_tail();
    if (n <= 0)
        return;
    for (size_type i = 0; i < n; i++)
        push_back(val);
    set_head_tail();
        
}

template <class InputIterator>
  list (InputIterator first, InputIterator last,
         const allocator_type& alloc = node_alloc_type()):head(NULL),tail(NULL),size_var(0),allocator(alloc)
{
    if (first ==last)
        return;
    while(first != last)
        push_back(*(first++));
    set_head_tail();
}
list (const list& x):head(NULL),tail(NULL),size_var(0),allocator(node_alloc_type())
{
    for (size_type i = 0; i < x.size_var; i++)
        push_back(x[i]);
    set_head_tail();
}

list& operator= (const list& x)
{
    clear();
    for (size_type i = 0; i < x.size_var; i++)
        push_back(x[i]);
    set_head_tail();
    return(*this);    
}
~list(){clear();}

iterator begin()
{
    iterator it(head);
    return it;
}
const_iterator begin() const
{
    const_iterator it(head);
    return it;    
}

iterator end()
{
    iterator it(&past_end);
    return it;
}
const_iterator end() const
{
    const_iterator it(tail);
    if (tail)
        it++;
    return it;
}
reverse_iterator rbegin()
{
    reverse_iterator it(tail);
    return it;
}
const_reverse_iterator rbegin() const
{
    const_reverse_iterator it(tail);
    return it;
}
reverse_iterator rend()
{
    reverse_iterator it(&past_begin);
    return it;
}
const_reverse_iterator rend() const
{
    const_reverse_iterator it(&past_begin);
    return it;
}
bool empty() const
{
    return (size_var == 0);
}
size_type size() const
{
    return size_var;
}
size_type max_size() const
{
    return std::numeric_limits<size_type>::max() / sizeof(Node);
}
reference front()
{
    return (head->value);
}
const_reference front() const
{
    return (tail->head);
}
reference back()
{
    return (tail->value);
}
const_reference back() const
{
    return (tail->value);
}

void clear()
{
    for (size_type i = 0; i < size_var; i++)
    {
        Node *tmp;
        tmp = head->next;
        deallocate_node(head);
        head = tmp;
    }
    head = NULL;
    tail = NULL;
    size_var = 0;
}
void resize (size_type n, value_type val = value_type())
{
    if (n > size_var)
        while (size_var < n)
            push_back(val);
    else if (n < size_var)
        while (size_var > n)
            pop_back();
}

void swap (list& x)
{
    Node *tmp_node;
    tmp_node = head;
    head = x.head;
    x.head = tmp_node;

    tmp_node = tail;
    tail = x.tail;
    x.tail = tmp_node;

    size_type tmp_size;
    tmp_size = size_var;
    size_var = x.size_var;
    x.size_var = tmp_size;

    set_head_tail();
    x.set_head_tail();
}

iterator erase (iterator position)
{
    iterator tmp_iter = begin();
    Node *tmp_node;
    size_type i;
    i = 0;
    tmp_node = head;
    while (tmp_iter != position)
    {
        tmp_iter++;
        tmp_node = tmp_node->next;
        i++;
    }
    delete_node(tmp_node);
    if (i >= size_var)
        return (end());
    tmp_node = head;
    while (i > 0)
    {
        tmp_node = tmp_node->next;
        i--;
    }
    return(iterator(tmp_node));
    return(position);
}
iterator erase (iterator first, iterator last)
{
    while (first != last)
        first = erase(first);
    return(first);
}

iterator insert (iterator position, const value_type& val)
{
    iterator tmp_iter;
    Node *tmp_node;

    tmp_iter = begin();
    tmp_node = head;
    while(tmp_iter != position)
    {
        tmp_iter++;
        tmp_node = tmp_node->next;
    }
    Node *new_node = allocate_node(NULL,NULL,val);
    return(insert_node(position,new_node));
}

    void insert (iterator position, size_type n, const value_type& val)
    {
        for (size_type i = 0;i < n;i++)
            insert(position,val);
    }

template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last)
{
    if (first >=last)
        return;
    while(first != last)
    {
        insert(position,*first);
        first++;
    }
}

void pop_back()
{
    delete_node(tail);
}

void push_back (const value_type& val)
{
    if (size_var == 0)
    {
    Node *tmp_node = allocate_node(NULL,NULL,val);
    push_node(tmp_node,NULL,NULL);
    return;
    }
    else 
    {
    Node *tmp_node = allocate_node(NULL,tail,val);
    push_node(tmp_node,NULL,tail);
    }
}

void pop_front()
{
    delete_node(head);
}
void push_front (const value_type& val)
{
if (size_var == 0)
{
    Node *tmp_node = allocate_node(NULL,NULL,val);
    push_node(tmp_node,NULL,NULL);
    return;
}
else 
{
    Node *tmp_node = allocate_node(head,NULL,val);
    push_node(tmp_node,head,NULL);
}
}

template <class InputIterator>
  void assign (InputIterator first, InputIterator last)
  {
      clear();
      list<value_type> new_list(first,last);
      *this = new_list;
  }
void assign (size_type n, const value_type& val)
{
      clear();
      list<value_type> new_list(n,val);
      *this = new_list;
}

void reverse()
{
    value_type tmp;
    
    for (size_type i = 0, j = size_var -1;i < j; i++,j--)
    {
        tmp = (*this)[i];
        (*this)[i] = (*this)[j];
        (*this)[j] = tmp;
    }
}

void remove (const value_type& val)
{
    Node *curr;
    Node *next;

    curr = head;
    while (curr != &past_end)
    {
        next = curr->next;
        if (curr->value == val)
            delete_node(curr);
        curr = next;
    }
}

template <class Predicate>
  void remove_if (Predicate pred)
  {
    Node *curr;
    Node *next;

    curr = head;
    while (curr != &past_end)
    {
        next = curr->next;
        if (pred(curr->value) == true)
            delete_node(curr);
        curr = next;
    }
  }

void unique()
{
    Node *curr = head;
    Node *tmp = head->next;

    if (size_var <= 1)
        return;

    while (curr->next != &past_end)
    {
        if (curr->value == curr->next->value)
        {
            tmp = curr->next->next;
            delete_node(curr->next);
            curr->next = tmp;
        }
        else
            curr = curr->next;
    }
}
template <class BinaryPredicate>
  void unique (BinaryPredicate binary_pred)
{
    (void)binary_pred;
    Node *curr = head;
    Node *tmp = head->next;

    if (size_var <= 1)
        return;

    while (curr->next != &past_end)
    {
        if (binary_pred(curr->value,curr->next->value) == true)
        {
            tmp = curr->next->next;
            delete_node(curr->next);
            curr->next = tmp;
        }
        else
            curr = curr->next;
    }
}

  void sort()
  {
    value_type tmp;
    for (size_type i =  size_var-1; i >= 1;i--)
    {
        for (size_type j = 0 ;j < i - 1; j++)
        {
            if ((*this)[j] > (*this)[j+1])
            {
            tmp = (*this)[j];
            (*this)[j] = (*this)[j+1];
            (*this)[j+1] = tmp;
            }
        }
    }
  }

template <class Compare>
  void sort (Compare comp)
  {
    (void)comp;
    value_type tmp;
    for (size_type i =  size_var-1; i >= 1;i--)
    {
        for (size_type j = 0 ;j < i - 1; j++)
        {
            if (comp((*this)[j+1],(*this)[j]))
            {
            tmp = (*this)[j];
            (*this)[j] = (*this)[j+1];
            (*this)[j+1] = tmp;
            }
        }
    }
}

  void merge (list& x)
  {
 if (this == &x)
        return;
 if (size_var == 0)
 {
    head = x.head;
    tail = x.tail;
    size_var+=x.size_var;
    set_head_tail();
    x.size_var = 0;
    return;
 }
    iterator first1 = begin();
    iterator last1 = end();
    iterator first2 = x.begin();
    iterator last2 = x.end();
    while (first1 != last1 && first2 != last2)
    {
        if (*first2 >= *first1)
            first1++;
        else 
        {
            splice(first1,x,first2);
            first2 = x.begin();
        }
    }
    if (first2 != last2)
    {
        splice(end(),x);
    }
    x.size_var = 0;
  }
template <class Compare>
  void merge (list& x, Compare comp)
  {
 if (this == &x)
        return;
 if (size_var == 0)
 {
    head = x.head;
    tail = x.tail;
    size_var+=x.size();
    set_head_tail();
    x.size_var = 0;
    return;
 }
    iterator first1 = begin();
    iterator last1 = end();
    iterator first2 = x.begin();
    iterator last2 = x.end();
    while (first1 != last1 && first2 != last2)
    {
        if (!comp(*first2,*first1))
            first1++;
        else 
        {
            splice(first1,x,first2);
            first2 = x.begin();
        }
    }
    if (first2 != last2)
    {
        splice(end(),x);
    }
    x.size_var = 0;
  }

void splice (iterator position, list& x)
{
    if (x.empty())
        return;
    Node *tmp_node = get_node(position);
    
    if (tmp_node == &past_end)
    {
        push_list(x);
        // tail->next = x.head;
		// x.head->prev = tail;
		// tail = x.tail;
		// size_var += x.size();
    }
    else if (tmp_node == &past_begin)
    {
        head->prev = x.tail;
        x.tail->next = head;
        head = x.head;
        size_var+=x.size();
    }
    else
    {
        tmp_node->prev->next = x.head;
        x.head->prev = tmp_node->prev;
        x.tail->next =tmp_node;
        tmp_node->prev = x.tail;
        size_var+=x.size();
    }
    set_head_tail();
    x.size_var = 0;
}

void splice (iterator position, list& x, iterator i)
{
    if (x.empty())
        return;
    Node *new_node = x.get_node(i);
    x.pop_node(new_node);
    insert_node(position, new_node);

    // if (x.empty())
    //     return;
    // Node *new_node = x.get_node(i);
	// Node *tmp_node = get_node(position);
    // x.pop_node(new_node);
	// if (tmp_node == &past_end)
	// 	{
	// 		new_node->prev = tail;
	// 		tail->next = new_node;
	// 		tail = new_node;
	// 		size_var++;
	// 	}
	// 	else if (tmp_node == &past_begin)
	// 	{
	// 		new_node->next = head;
	// 		head->prev = new_node;
	// 		head = new_node;
	// 		size_var++;
	// 	}
	// 	else
	// 	{
	// 		tmp_node->prev->next = new_node;
	// 		new_node->prev = tmp_node->prev;
	// 		new_node->next = tmp_node;
	// 		tmp_node->prev = new_node;
	// 		size_var++;
	// 	}
	// 	if (tmp_node == head)
	// 		head = new_node;
	// 	set_head_tail();
}

void splice (iterator position, list& x, iterator first, iterator last)
{
    iterator tmp_iter;

    while (first != last)
    {
        tmp_iter = first;
        first++;
        splice(position,x,tmp_iter);
    }
}
};

template <class T, class Allocator>
  bool operator == (const list<T,Allocator>& lhs, const list<T,Allocator>& rhs)
  {
    typename ft::list<T,Allocator>::const_iterator begin1 = lhs.begin();
    typename ft::list<T,Allocator>::const_iterator end1 = lhs.end();
    typename ft::list<T,Allocator>::const_iterator begin2 = rhs.begin();
    if (lhs.size() == rhs.size())
    {
        for(;begin1 != end1; begin1++,begin2++)
            if (*begin1 != *begin2)
                return false;
        return true;
    }
    return(false);
  }
template <class T, class Allocator>
  bool operator != (const list<T,Allocator>& lhs, const list<T,Allocator>& rhs)
  {
      return !(lhs==rhs);
  }
template <class T, class Allocator>
  bool operator <  (const list<T,Allocator>& lhs, const list<T,Allocator>& rhs)
  {
  typename ft::list<T,Allocator>::const_iterator begin1 = lhs.begin();
    typename ft::list<T,Allocator>::const_iterator end1 = lhs.end();
    typename ft::list<T,Allocator>::const_iterator begin2 = rhs.begin();
    typename ft::list<T,Allocator>::const_iterator end2 = rhs.end();

        while (begin1 != end1)
        {
            if (begin2 == end2 || *begin2 < *begin1)
                return false;
            else if (*begin2 > *begin1)
                return true;
            begin1++;
            begin2++;
        }
        return begin2 != end2;
  }
template <class T, class Allocator>
  bool operator <= (const list<T,Allocator>& lhs, const list<T,Allocator>& rhs)
  {
      return (!(rhs < lhs));
  }
template <class T, class Allocator>
  bool operator >  (const list<T,Allocator>& lhs, const list<T,Allocator>& rhs)
  {
      return (rhs < lhs);
  }
template <class T, class Allocator>
  bool operator >= (const list<T,Allocator>& lhs, const list<T,Allocator>& rhs)
  {
      return !(lhs < rhs);
  }
  
  template <class T, class Allocator>
  void swap (list<T,Allocator>& x, list<T,Allocator>& y)
  {
      x.swap(y);
  }

};

#endif