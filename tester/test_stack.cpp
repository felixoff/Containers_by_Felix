#include "tester.hpp"

static void constructors()
{
	std::cout << BOLDYELLOW << "\n------ CONSTRUCTORS AND METHODS -------\n\n" << RESET;
	std::stack<int> s;
	ft::stack<int> ms;
	ft_print("stack() ", s.size(), ms.size());
	std::stack<std::string> s1;
	ft::stack<std::string> ms1;
	ft_print("stack() ", s1.size(), ms1.size());
	ft::stack<char, ft::list<char> > ms2;
	ft_print("stack() ", s.size(), ms2.size());

	ft_print("empty() ", s.empty(), ms.empty());
	s.push(1);
	ms.push(1);
	ft_print("empty() ", s.empty(), ms.empty());
	ft_print("size() ", s.size(), ms.size());
	ft_print("push and top() ", s.top(), ms.top());
	s.push(2);
	ms.push(2);
	ft_print("push and top() ", s.top(), ms.top());
	s.push(3);
	ms.push(3);
	ft_print("push and top() ", s.top(), ms.top());
	ft_print("size() ", s.size(), ms.size());
	ft_print("push and top() ", s.size(), ms.size());
	s.pop();
	ms.pop();
	ft_print("size() ", s.size(), ms.size());
	ft_print("pop and top() ", s.top(), ms.top());
	s.pop();
	ms.pop();
	ft_print("size() ", s.size(), ms.size());
	ft_print("pop and top() ", s.top(), ms.top());

}

static void operators()
{
	std::cout << BOLDYELLOW << "\n------ RELATIONAL OPERATORS -------\n\n" << RESET;
	std::stack<int> v;
	ft::stack<int> mv;
	std::stack<int> v2;
	ft::stack<int> mv2;
	for (int i = 0; i < 10; i++)
	{
		v.push(i);
		mv.push(i);
		v2.push(-i);
		mv2.push(-i);
	}

	ft_print("v == v", v == v2, mv == mv2);
	ft_print("v != v", v != v2, mv != mv2);
	ft_print("v < v", v < v2, mv < mv2);
	ft_print("v <= v", v <= v2, mv <= mv2);
	ft_print("v > v", v > v2, mv > mv2);
	ft_print("v >= v", v >= v2, mv >= mv2);

	v2.push(42);
	mv2.push(42);

	ft_print("v == v", v == v2, mv == mv2);
	ft_print("v != v", v != v2, mv != mv2);
	ft_print("v < v", v < v2, mv < mv2);
	ft_print("v <= v", v <= v2, mv <= mv2);
	ft_print("v > v", v > v2, mv > mv2);
	ft_print("v >= v", v >= v2, mv >= mv2);

	// v2.push(18);
	// mv2.push(35);
	// swap(v, v2);
	// ft_print("Swap ", v.size(), mv.size());
	// ft_print("Swap ", v2.size(), mv2.size());

	std::stack<std::string> v3;
	ft::stack<std::string> mv3;
	std::stack<std::string> v4;
	ft::stack<std::string> mv4;

	ft_print("v == v", v3 == v4, mv3 == mv4);
	ft_print("v != v", v3 != v4, mv3 != mv4);
	ft_print("v < v", v3 < v4, mv3 < mv4);
	ft_print("v <= v", v3 <= v4, mv3 <= mv4);
	ft_print("v > v", v3 > v4, mv3 > mv4);
	ft_print("v >= v", v3 >= v4, mv3 >= mv4);


}

void test_stack()
{
	std::cout << BOLDMAGENTA << "\n------TEST stack----------\n\n" << RESET;

	constructors();
	operators();
}
