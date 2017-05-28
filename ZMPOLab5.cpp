#include <iostream>
#include <sstream>

#include "MySet.h"
#include "Tuple.h"

using namespace std;
using namespace zmpo;

bool mySort(int* a, int* b)
{
	return *a < *b;
}

int main()
{
	MySet<std::string> set;
	for (int i = 0; i < 10; i++)
	{
		std::stringstream ss;
		ss << "q";
		for (int j = 0; j <= i; j++)
		{
			ss << j;
			set += ss.str();
		}
	}
	set.sort([](std::string* a, std::string* b)
	{
		return a->length()<b->length();
	});
	cout << set << endl;

	MySet<Tuple<int, double> > ms;
	ms.add(Tuple<int, double>(1, 1.1));
	ms.add(Tuple<int, double>(0, 2.2));
	ms.add(Tuple<int, double>(2, 0.1));
	cout << ms << endl;
	ms.sort([](Tuple<int, double>* a, Tuple<int, double>* b)
	{
		return a->getA() < b->getA();
	});
	cout << ms << endl;
	ms.sort([](Tuple<int, double>* a, Tuple<int, double>* b)
	{
		return a->getB() < b->getB();
	});
	cout << ms << endl;

	MySet<int> s;
	int i = 1;
	s.add(i);
	s.add(3);
	s.add(2);
	s.add(7);
	s.add(4);
	s.add(0);
	s.add(42);
	s.add(41);
	MySet<int> s1;
	s1.add(101);
	s1.add(500);
	MySet<int> s2;
	s2.add(1000);
	MySet<int> s3 = s1 + s2;
	cout << s3 << endl;
	s += s3;
	cout << s << endl;
	bool (*sortMethod)(int*, int*) = [](int* a, int *b)
	{	return *a<*b;};
	s.sort(sortMethod);
	s -= s1;
	cout << s << endl;
	MySet<int> s4;
	s4.add(101);
	s4 += 500;
	cout << (s1 == s4) << endl;
	cout << s << endl;

	return 0;
}
