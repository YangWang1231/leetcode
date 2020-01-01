#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>
#include <functional>
#include <iostream>
#include<string>
using std::string;
using boost::future;
using boost::async;
//using boost::then;

void accumulate(boost::promise<int>& p)
{
    int sum = 0;
    for (int i = 0; i < 5; ++i)
        sum += i;
    p.set_value(sum);
}

//int main()
//{
//    boost::future<int> f1 = async([]() { return 123; });
//    
//    boost::future<int> f2 = f1.then([](future<int> f) { return f.get() + 10; }); // here .get() won't block });
//    std::cout << "result is " << f2.get() << std::endl;
//
//    boost::promise<int> p;
//    boost::future<int> f = p.get_future();
//    boost::thread t{ accumulate, std::ref(p) };
//    std::cout << f.get() << '\n';
//}