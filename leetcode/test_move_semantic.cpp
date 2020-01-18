/*
used to learn C++ 11 move semantic.
*/

#include<iostream>
#include<string>
class MyClass
{
	friend std::ostream& operator << (std::ostream&, const MyClass&);
public:
	MyClass(std::string name):m_name(name) {}
	MyClass(){} //provide default constructor, but use default value. according to C++ conf
	~MyClass();

private:
	std::string m_name = "hello wordl.";
};


std::ostream& operator << (std::ostream& os,const MyClass& obj)
{
	os << obj.m_name << std::endl;
	return os;
}



MyClass::~MyClass()
{
}

/*
if I just provide lvalue defination, and call function like this:
	fun(std::move(obj_default_constr));
there will be a compile error:
	message : A non-const reference may only be bound to an lvalue
	error C2664: 'void fun(MyClass &)': cannot convert argument 1 from 'MyClass' to 'MyClass &'
*/
void fun(MyClass& x)
{
	std::cout << "(MyClass& x)	" << "was called." << std::endl;
	std::cout << x << std::endl;
}

void fun(MyClass&& x)
{
	std::cout << "fun(MyClass&& x)	" << "was called." << std::endl;
	std::cout << x << std::endl;
}

#include<utility>
//int main()
//{
//	MyClass obj_default_constr;
//	MyClass obj_name("bye bye.");
//
//	fun(std::move(obj_default_constr));
//	fun(obj_name);
//	return 0;
//}