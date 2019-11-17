#include<functional>

using namespace std;

class FooBar {
private:
	int n;

public:
	FooBar(int n) {
		this->n = n;
	}

	void foo(function<void()> printFoo) {

		for (int i = 0; i < n; i++) {

			// printFoo() outputs "foo". Do not change or remove this line.
			printFoo();
		}
	}

	void bar(function<void()> printBar) {

		for (int i = 0; i < n; i++) {

			// printBar() outputs "bar". Do not change or remove this line.
			printBar();
		}
	}
};

#include<stdio.h>
#include<mutex>
#include<condition_variable>

FooBar	g_obj{ 100 };
mutex	g_mutex;
condition_variable g_cvar_foo;
condition_variable g_cvar_bar;

bool	g_flag_foo = true;
bool	g_flag_bar = false;

void printFoo()
{
	unique_lock lck{ g_mutex };
	g_cvar_foo.wait(lck, [] { return g_flag_foo == true; });
	printf("foo");
	g_flag_foo = false;
	g_flag_bar = true;
	g_cvar_bar.notify_one();
}

void printBar()
{
	unique_lock lck{ g_mutex };
	g_cvar_bar.wait(lck, [] {return g_flag_bar == true; });
	printf("bar");
	g_flag_bar = false;
	g_flag_foo = true;
	g_cvar_foo.notify_one();
}

#include<thread>
void main()
{
	thread t1(&FooBar::foo, &g_obj, printFoo);
	thread t2(&FooBar::bar, &g_obj, printBar);

	t1.join();
	t2.join();
}