#include "tester.hpp"

static void constructors()
{
	std::cout << BOLDYELLOW << "\n------ CONSTRUCTORS AND METHODS -------\n\n" << RESET;

	std::queue<int> s;
	ft::queue<int> ms;
	ft_print("queue() ", s.size(), ms.size());
	std::queue<std::string> s1;
	ft::queue<std::string> ms1;
	ft_print("queue() ", s1.size(), ms1.size());
	ft::queue<char, ft::list<char> > ms2;
	ft_print("queue() ", s.size(), ms2.size());

	ft_print("empty() ", s.empty(), ms.empty());
	s.push(1);
	ms.push(1);
	ft_print("empty() ", s.empty(), ms.empty());
	ft_print("size() ", s.size(), ms.size());
	ft_print("push and front() ", s.front(), ms.front());
	s.push(2);
	ms.push(2);
	ft_print("push and back() ", s.back(), ms.back());
	ft_print("push and front() ", s.front(), ms.front());
	s.push(3);
	ms.push(3);
	ft_print("push and back() ", s.back(), ms.back());
	ft_print("size() ", s.size(), ms.size());
	ft_print("push and front() ", s.front(), ms.front());
	ft_print("push and back() ", s.size(), ms.size());
	s.pop();
	ms.pop();
	ft_print("size() ", s.size(), ms.size());
	ft_print("pop and back() ", s.back(), ms.back());
	s.pop();
	ms.pop();
	ft_print("size() ", s.size(), ms.size());
	ft_print("pop and back() ", s.back(), ms.back());
}

static void operators()
{
	std::cout << BOLDYELLOW << "\n------ RELATIONAL OPERATORS -------\n\n" << RESET;
	std::queue<int> v;
	ft::queue<int> mv;
	std::queue<int> v2;
	ft::queue<int> mv2;
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

	std::queue<std::string> v3;
	ft::queue<std::string> mv3;
	std::queue<std::string> v4;
	ft::queue<std::string> mv4;

	ft_print("v == v", v3 == v4, mv3 == mv4);
	ft_print("v != v", v3 != v4, mv3 != mv4);
	ft_print("v < v", v3 < v4, mv3 < mv4);
	ft_print("v <= v", v3 <= v4, mv3 <= mv4);
	ft_print("v > v", v3 > v4, mv3 > mv4);
	ft_print("v >= v", v3 >= v4, mv3 >= mv4);


}


void test_queue()
{
	std::cout << BOLDMAGENTA << "\n------TEST queue----------\n\n" << RESET;
	constructors();
	operators();
}
