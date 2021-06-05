#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "ft_utils.hpp"
#include <iostream>
#include <string>
#include <cstddef>
#include <limits>
namespace ft{

template<typename Key, typename T>
	class pair
{
    public:
        Key first;
        T second;
        pair(){}
        pair(const pair &pair):first(pair.first),second(pair.second){}
        pair(Key k, T t):first(k),second(t){}
        pair &operator=(const pair &pair)
        {
            this->first = pair.first;
            this->second = pair.second;
            return *this;
        }
        ~pair() {}
};

	template<typename Key, typename T>
	pair<Key, T> make_pair(Key first, T t)
    {
        pair<Key,T> pair(first,t);
        return pair;
    };
    
	template<typename T>
	class less
    {
        public:
        bool operator()(const T& x, const T&y) const
        {
            return (x < y);
        }
    };

template<class Key, class T, class Compare = less<Key>,
	class Alloc = allocator<pair<const Key,T> > >
class assistant
{
private:
typedef Key key_type;
typedef T mapped_type;		
typedef pair<const key_type,mapped_type> value_type;		
typedef Compare key_compare;
typedef Alloc allocator_type;
typedef value_type& reference;
typedef const pair<const key_type,mapped_type>& const_reference;
typedef value_type* pointer;
typedef const value_type* const_pointer;
typedef ptrdiff_t difference_type;
typedef size_t size_type;

class Node
{
    public:
        value_type pair;
        Node *left;
        Node *right;
        Node *parent;
    public:
        Node():left(NULL),right(NULL),parent(NULL){};
        Node(const Node &node):pair(node.pair),left(node.left),right(node.right),parent(node.parent){}
        Node(value_type pair,Node *left, Node *right, Node *parent):pair(pair),left(left),right(right),parent(parent){};
        void operator =(const Node &node)
        {
            pair = node.pair;
            left = node.left;
            right = node.right;
            parent = node.parent;
        }
        ~Node(){}
};

typedef typename Alloc::template rebind<Node>::other node_allocator_type;
Node *root;
size_type size_var;
key_compare key_comp_var;
node_allocator_type allocator;
public:
class Iterator_for_map
{
    public:	
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
		typedef pair<const Key,T>*			pointer;
		typedef pair<const Key,T>&			reference;
		typedef pair<const Key,T> value_type;
		typedef const pair<const Key,T>&	const_reference;
		typedef const pair<const Key,T>*	const_pointer;
    protected:
        Node *root;
        Node *node;
    public:
    Iterator_for_map():root(NULL),node(NULL){}
    Iterator_for_map(const Iterator_for_map &iter):root(iter.root),node(iter.node){}
    Iterator_for_map &operator=(const Iterator_for_map &iter)
    {
        root = iter.root;
        node = iter.node;
        return *this;
    }
    Iterator_for_map(Node *node,Node *root):root(root),node(node){}
    ~Iterator_for_map(){}
    reference operator *()
    {
        return this->node->pair;
    }    
    pointer operator ->()
    {
        return &this->node->pair;
    }
    bool operator==(const Iterator_for_map &iter) const
    {
        return node == iter.node;
    }
    bool operator!=(const Iterator_for_map &iter) const
    {
        return node != iter.node;
    }
    Iterator_for_map &operator++() 
    {  
        if (node && node->right)
        {
            node = node->right;
            while (node->left)
                node = node->left;
        }
        else if (node)
        {
        while(node->parent && node->parent->left != node)
            node = node->parent;
        node = node->parent;
        }
        else 
        {
            node = root;
            while (node->left)
                node = node->left;
        }
        return (*this);
			}

    Iterator_for_map &operator--() 
    {  
        if (node && node->left)
        {
            node = node->left;
            while (node->right)
                node = node->right;
        }
        else if (node)
        {
        while(node->parent && node->parent->right != node)
            node = node->parent;
        node = node->parent;

        }
        else 
        {
            node = root;
            while (node->right)
                node = node->right;
        }
        return (*this);
    }
    Iterator_for_map operator++(int i) 
    {
        (void)i;
        Iterator_for_map tmp_iter = *this;
        operator++();
        return (tmp_iter);
    }
    Iterator_for_map operator--(int i) 
    {
        (void)i;
        Iterator_for_map tmp_iter = *this;
        operator--();
        return (tmp_iter);
    }
};

class Const_iterator_for_map: public Iterator_for_map
{
	public:
	Const_iterator_for_map(): Iterator_for_map()
	{
	}

	Const_iterator_for_map(const Const_iterator_for_map& i): Iterator_for_map(i)
	{}

	Const_iterator_for_map(const Iterator_for_map& i): Iterator_for_map(i)
	{}

	Const_iterator_for_map(Node *node, Node *root): Iterator_for_map(node, root)
	{};

	void operator = (const Const_iterator_for_map& i)
	{
		Iterator_for_map::node = i.node;
		Iterator_for_map::root = i.root;
	}

	virtual ~Const_iterator_for_map() {};

	Const_iterator_for_map(T* t): Iterator_for_map(t)
	{}

	const_reference operator * ()
	{
		return (Iterator_for_map::node->pair);
	};

	const_pointer operator -> ()
	{
		return (&Iterator_for_map::node->pair);
	};
};

class Const_Reverse_Iterator: public Reverse_Iterator<Iterator_for_map>
{
	public:
	Const_Reverse_Iterator() {};
	Const_Reverse_Iterator(const Iterator_for_map& i): Reverse_Iterator<Iterator_for_map>(i)
	{};
	Const_Reverse_Iterator(const Const_Reverse_Iterator& i): Reverse_Iterator<Iterator_for_map>(i)
	{};
	Const_Reverse_Iterator(const Reverse_Iterator<Iterator_for_map>& i): Reverse_Iterator<Iterator_for_map>(i)
	{};
	void operator = (const Reverse_Iterator<Iterator_for_map>& i)
	{
		Reverse_Iterator<Iterator_for_map>::current = i.current;
	}

	const_reference operator * () const
	{
		const_iterator a = Reverse_Iterator<Iterator_for_map>::current;
		return (*a);
	};

	const_pointer operator -> () const
	{
		const_iterator a = Reverse_Iterator<Iterator_for_map>::current;
		const_pointer cp = a.operator->();
		return (cp);
	};
};

typedef Iterator_for_map iterator;
typedef Reverse_Iterator<Iterator_for_map> reverse_iterator;
typedef Const_iterator_for_map const_iterator;
typedef Const_Reverse_Iterator const_reverse_iterator;

assistant():root(NULL),size_var(0){}
assistant(const assistant& x)
{
    root = x.copy_tree(root, NULL);
    size_var = x.size_var;
};

void operator = (const assistant& x)
{
    clear();
    root = x.copy_tree(root, NULL);
    size_var = x.size_var;
};

~assistant()
{
	clear();
}

Node *copy_tree(Node *root, Node *parent) const
{
    if (!root)
        return(NULL);
    Node *new_node = new Node(root->pair,NULL,NULL,parent);
    new_node->left = copy_tree(root->left, new_node);
    new_node->right = copy_tree(root->right, new_node);
    return (new_node);
}

Node *find_min_val(Node *root)
{
    Node *tmp = root;
    while (tmp && tmp->left)
        tmp = tmp->left;
    return (tmp);
}

void delete_key(Key key)
{
    root = delete_node(key,root);
}

void clear()
{
    while (root)
        delete_key(root->pair.first);
    root = NULL;
}

Node *delete_node(Key key, Node *node)
{
    if (node == NULL)
        return(node);
    if (key < node->pair.first)
        node->left = delete_node(key,node->left);
    else if (key > node->pair.first)
        node->right = delete_node(key,node->right);
    else
    {
        if (node->right == NULL)
        {
            Node *tmp = node->left;
            free(node);
            size_var-=1;
            return tmp;
        }
        else if (node->left == NULL)
        {
            Node *tmp = node->right;
            free(node);
            size_var-=1;
            return tmp;
        }
            Node *tmp = find_min_val(node->right);
            Node *right = node->right;
            Node *left = node->left;
            Node *parent = node->parent;
            free(node);
            node = new Node(value_type(tmp->pair.first,tmp->pair.second),left,right,parent);
            node->right = delete_node(tmp->pair.first, node->right);
    }
        return (node);
}
void insert_node(value_type pair)
{
    root =  insert_node(pair,root,NULL);
}
Node *insert_node(value_type pair, Node *node, Node *parent)
{
    if (node == NULL)
    {
        Node *tmp = new Node(pair,NULL,NULL,NULL);
        tmp->parent = parent;
        size_var+=1;
        return (tmp);
    }
    if (key_comp_var(pair.first,node->pair.first))
        node->left = insert_node(pair,node->left,node);
    else if (!key_comp_var(pair.first,node->pair.first) && pair.first != node->pair.first)
        node->right = insert_node(pair,node->right,node);
    return (node);
};

mapped_type &find_value(Key key)
{
    return (find_value(key,root,NULL));
}

mapped_type &find_value(Key key, Node *node, Node *parent)
{
    (void)parent;
    if (node == NULL)
    {
        root = insert_node(value_type(key, mapped_type()),root,NULL);
        return (find_value(key, root, NULL));
    }
    if (key == node->pair.first)
        return (node->pair.second);
    if (node->pair.first < key)
        return (find_value(key,node->right,node));
    return (find_value(key,node->left,node));
}

Node *find_node(Key key, Node *node) const
{
    if (node == NULL)
        return(NULL);
    if (node->pair.first == key)
        return (node);
    if (key_comp_var(node->pair.first,key))
        return (find_node(key,node->right));
    else
        return (find_node(key,node->left));
}
iterator begin()
{
    Node *tmp = root;
    while (tmp && tmp->left)
        tmp = tmp->left;
    
    return iterator(tmp,root);
}
const_iterator begin() const
{
    Node *tmp = root;
    while (tmp && tmp->left)
        tmp = tmp->left;
    
    return const_iterator(tmp,root);
}
iterator end()
{
    return iterator(NULL,root);
}

const_iterator end() const
{
    return const_iterator(NULL,root);
}
reverse_iterator rbegin()
{
    return (reverse_iterator(iterator(--end())));
}
const_reverse_iterator rbegin() const
{
        return (const_reverse_iterator(iterator(--end())));
}
reverse_iterator rend()
{
    return (reverse_iterator(iterator(--begin())));    
}
const_reverse_iterator rend() const
{
    return (const_reverse_iterator(iterator(--begin())));
}
iterator find_iter(const key_type &key) const
{
    Node *tmp = find_node(key,root);
    if (tmp != NULL)
        return (iterator(tmp,root));
    else
        return (end());
}
size_type size() const {
    return (size_var);
}

void swap (assistant& x)
{
    Node *tmp_node;
    size_type tmp_size;

    tmp_node = root;
    root = x.root;
    x.root = tmp_node;

    tmp_size = size_var;
    size_var = x.size_var;
    x.size_var = tmp_size; 
}

};

template < class Key, class T, class Compare = less<Key>,                  
class Alloc = allocator<pair<const Key,T> > > 
class map
{


public:
typedef Key key_type;
typedef T mapped_type;		
typedef pair<const key_type,mapped_type> value_type;		
typedef Compare key_compare;
typedef Alloc allocator_type;
typedef value_type& reference;
typedef const pair<const key_type,mapped_type>& const_reference;
typedef value_type* pointer;
typedef const value_type* const_pointer;
typedef ptrdiff_t difference_type;
typedef size_t size_type;
typedef typename assistant<Key,T,Compare,Alloc>::Iterator_for_map iterator;
typedef typename assistant<Key,T,Compare,Alloc>::const_iterator const_iterator;
typedef typename assistant<Key,T,Compare,Alloc>::reverse_iterator reverse_iterator;
typedef typename assistant<Key,T,Compare,Alloc>::const_reverse_iterator const_reverse_iterator;

protected:
class Value_Comp_Class
{
    public:
    bool operator()(const_reference a, const_reference b)
    {
        return (a.first < b.first);
    }
};

public:
typedef Value_Comp_Class value_compare;
private:
assistant<Key,T,Compare,Alloc>	assistant;
allocator_type 					allocator;
key_compare 					key_comp_var;
value_compare					value_comp_var;
public:

map(){}


map (const map& x)
{
    assistant = x.assistant;
}

template <class InputIterator> 
map (InputIterator first, InputIterator last)
    {
        while (first != last)
        {
            assistant.insert_node(*first);
            first++;
        }
    }

void operator =(const map & x)
{
    assistant = x.assistant;
}

~map(){}

bool empty() const
{
    return (assistant.size()==0);
}

size_type size() const{
    return (assistant.size());
}

iterator begin()
{
    return assistant.begin();
}
const_iterator begin() const
{
    
    return  assistant.begin();
}
iterator end()
{
    return assistant.end();
}

const_iterator end() const
{
    return  assistant.end();
}
reverse_iterator rbegin()
{
    return  assistant.rbegin();
}
const_reverse_iterator rbegin() const
{
        return  assistant.rbegin();
}
reverse_iterator rend()
{
    return  assistant.rend();
}
const_reverse_iterator rend() const
{
    return  assistant.rend();
}

size_type max_size() const
{
    return std::numeric_limits<size_type>::max()/(sizeof(value_type)+4*8);
}

mapped_type& operator[] (const key_type& k)
{
    return assistant.find_value(k);
 //   return find_value(k, root, NULL);
}
	
pair<iterator,bool> insert (const value_type& val)
{
    size_type tmp_size = assistant.size();
    assistant.insert_node(val);
    return (pair<iterator,bool>(assistant.find_iter(val.first),(assistant.size() >tmp_size)));

}

iterator insert (iterator position, const value_type& val)
{
    (void)position;
    assistant.insert_node(val);
    return assistant.find_iter(val.first);
}

template <class InputIterator>
  void insert (InputIterator first, InputIterator last)
{
    while (first != last)
    {
        insert(*first);
        first++;
    }
}

void erase (iterator position)
{
    assistant.delete_key(position->first);
}
size_type erase (const key_type& k)
{
    size_type tmp_size = assistant.size();
    assistant.delete_key(k);
    return (tmp_size - assistant.size());
}

void erase (iterator first, iterator last)
{
    iterator tmp;
    while (first != last)
    {
        tmp = first;
        tmp++;
        assistant.delete_key((*first).first);
        first = tmp;
        if (first == end())
            return;
    }
}

key_compare key_comp() const
{
    return this->key_comp_var;
}

value_compare value_comp() const
{
    return this->value_comp_var;
}

void swap(map &x)
{
    assistant.swap(x.assistant);
}

void clear()
{
    assistant.clear();
}

iterator find (const key_type& k)
{
    return assistant.find_iter(k);
}
const_iterator find (const key_type& k) const
{
    return assistant.ind_iter(k);
}
size_type count (const key_type& k) const
{
    if (assistant.find_iter(k) != assistant.end())
        return 1;
    else
        return 0;
}

iterator lower_bound (const key_type& k)
{
    for (iterator tmp = assistant.begin(); tmp != assistant.end(); tmp++)
        if (!key_comp_var((*tmp).first,k))
            return(tmp);
    return (assistant.end());
}
const_iterator lower_bound (const key_type& k) const
{
    for (iterator tmp = assistant.begin(); tmp != assistant.end(); tmp++)
        if (!key_comp_var((*tmp).first,k))
            return(tmp);
    return (assistant.end());
}
iterator upper_bound (const key_type& k)
{
    iterator tmp = assistant.begin();
    while (tmp != assistant.end())
    {
        if (key_comp_var(k,(*tmp).first))
            return(tmp);
        tmp++;
    }
    return (assistant.end());
}
const_iterator upper_bound (const key_type& k) const
{
    for (iterator tmp = assistant.begin(); tmp != assistant.end(); tmp++)
        if (key_comp_var(k,(*tmp).first))
            return(tmp);
    return (assistant.end());
}
pair<const_iterator,const_iterator> equal_range (const key_type& k) const
{
    return make_pair(lower_bound(k),upper_bound(k));
}
pair<iterator,iterator>             equal_range (const key_type& k)
{
    return make_pair(lower_bound(k),upper_bound(k));
}

};
};

#endif