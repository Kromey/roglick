#include <iostream>

/**
 * Can a template class be sub-classed and specialized by a non-template class?
 * Let's find out...
 */

//This class is a template (duh!)
template <typename T>
class Base
{
	public:
		virtual void print() { std::cout << "Base: " << myobj << std::endl; };
	protected:
		T myobj;
};

//This class is a specialized non-template (also duh!)
class Special : public Base<int>
{
	public:
		Special(int foo) { myobj = foo; };
};

int main()
{
	Special foo(45);
	foo.print();
}
