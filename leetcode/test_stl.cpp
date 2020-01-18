/*
code example from:
"STL Algorithms in Action"
        Michael VanLoon
        CPPcon 2015
*/


#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
#include <list>
#include <numeric>
#include <random>
#include<map>
#include<string>
#include<iomanip>
#include<set>

using std::string;


namespace test_stl {

    void copy_example()
    {
        std::vector<int> from_vector(10);
        std::iota(from_vector.begin(), from_vector.end(), 0);

        std::cout << "from_vector contains: ";

        std::copy(from_vector.begin(), from_vector.end(),
            std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';

        std::vector<int> to_vector;
        std::copy(from_vector.begin(), from_vector.end(),
            std::back_inserter(to_vector));
        // or, alternatively,
        //  std::vector<int> to_vector(from_vector.size());
        //  std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
        // either way is equivalent to
        //  std::vector<int> to_vector = from_vector;

        std::cout << "to_vector contains: ";

        std::copy(to_vector.begin(), to_vector.end(),
            std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
    }

    void itoa_example()
    {
        std::list<int> l(10);
        std::iota(l.begin(), l.end(), -4);

        std::vector<std::list<int>::iterator> v(l.size());
        std::iota(v.begin(), v.end(), l.begin());

        std::shuffle(v.begin(), v.end(), std::mt19937{ std::random_device{}() });

        std::cout << "Contents of the list: ";
        for (auto n : l) std::cout << n << ' ';
        std::cout << '\n';

        std::cout << "Contents of the list, shuffled: ";
        for (auto i : v) std::cout << *i << ' ';
        std::cout << '\n';
    }

    void random_device_example()
    {
        std::random_device rd;
        std::map<int, int> hist;
        std::uniform_int_distribution<int> dist(0, 9);
        std::mt19937 gen(std::random_device{}());
        for (int n = 0; n < 20000; ++n) {
            //++hist[dist(rd)]; // note: demo only: the performance of many 
            //                  // implementations of random_device degrades sharply
            //                  // once the entropy pool is exhausted. For practical use
            //                  // random_device is generally only used to seed 
            //                  // a PRNG such as mt19937
            ++hist[dist(gen)];
        }
        for (auto p : hist) {
            std::cout << p.first << " : " << std::string(p.second / 100, '*') << '\n';
        }
    }

    template<typename Cont>
    typename Cont::const_iterator checkDeviation(const Cont& cont, double allowed_dev)
    {
        return adjacent_find(cont.begin(), cont.end(),
            [allowed_dev](auto& v1, auto& v2)
            {
                auto limit = v1 * allowed_dev;
                return (v2 > v1 + limit) ||
                    (v2 < v1 - limit);
            });
    }

    void adjacent_find_test()
    {
        typedef std::vector<double> vecDbl_t;
        using std::endl;
        using std::cout;

        vecDbl_t v{ 1.0, 1.05, 1.06, 1.04, 1.09, 1.15, 1.2 };

        vecDbl_t::const_iterator it = checkDeviation(v, 0.1);
        if (it == v.end())
            cout << "Vector is within deviation limits" << endl;
        else
            cout << "Vector outside deviation limits, values " << *it << " and "
            << *(it + 1) << ", at position " << it - v.begin() + 1 << endl;

        v.push_back(2.0);

        it = checkDeviation(v, 0.1);
        if (it == v.end())
            cout << "Vector is within deviation limits" << endl;
        else
            cout << "Vector outside deviation limits, values " << *it << " and "
            << *(it + 1) << ", at position " << it - v.begin() + 1 << endl;
    }

    struct Person {
        string first;
        string middle;
        string last;
        //¡­ other Person stuff¡­
        friend std::ostream& operator << (std::ostream& os, const Person& p);
    };

    std::ostream& operator << (std::ostream& os, const Person& p) {
        os << std::left << std::setw(15) << p.first;
        os << std::left << std::setw(5) << p.middle;
        os << std::left << std::setw(15) << p.last;

        return os;
    }

    void sort_test()
    {
        std::vector<Person> v{
            { "Joe", "P", "Smith" },
            { "Jane", "Q", "Jones" },
            { "Frank", "P", "Johnson" },
            { "Sarah", "B", "Smith" },
            { "Joe", "X", "Jones" },
            { "Joe", "A", "Smith" } };

        // Sort by least influential data first
        std::sort(v.begin(), v.end(),
            [](const Person& a, const Person& b) { return a.middle < b.middle; });

        std::stable_sort(v.begin(), v.end(),
            [](const Person& a, const Person& b) { return a.first < b.first; });

        std::stable_sort(v.begin(), v.end(),
            [](const Person& a, const Person& b) { return a.last < b.last; });
        // Sort by most influential data last

        std::copy(v.begin(), v.end(), std::ostream_iterator<Person>(std::cout, "\n"));

        //partial_sort example
        std::vector<int> v1{ 42, 17, 89, 22, 34, 78, 63, 12, 57, 99 };
        std::partial_sort(v1.begin(), v1.begin() + 5, v1.begin() + 8, std::greater<int>());
        std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }


    /*
    given set A and set B:
    std::set_different = A and ~B | A - B
    std::set_symmetric_difference = (A or B) and ~(A and B) | (A or B) - (A and B)
    the implementation is good:
    https://en.cppreference.com/w/cpp/algorithm/set_difference
    https://en.cppreference.com/w/cpp/algorithm/set_symmetric_difference
    */
    //
    void set_different_test()
    {
        std::set<string> current{ "one", "two", "three", "four", "five" };
        std::set<string> update{ "one", "three", "four", "six", "seven" };

        std::vector<string> new_items, removed_items;

        std::set_difference(current.begin(), current.end(),
            update.begin(), update.end(),
            back_inserter(removed_items));

        std::cout << "removed items: " << std::endl;
        std::copy(removed_items.begin(), removed_items.end(), std::ostream_iterator<string>(std::cout, "  "));
        std::cout << std::endl;

        std::set_difference(update.begin(), update.end(),
            current.begin(), current.end(),
            back_inserter(new_items));

        std::cout << "new items: " << std::endl;
        std::copy(new_items.begin(), new_items.end(), std::ostream_iterator<string>(std::cout, "  "));
        std::cout << std::endl;
    }

    void set_symmetric_difference_test()
    {
        std::vector<int> v1{ 1,2,3,4,5,5,6,6,6,7,8 };
        std::vector<int> v2{ 5,  7,  9,10 };
        std::sort(v1.begin(), v1.end());
        std::sort(v2.begin(), v2.end());

        std::vector<int> v_symDifference;

        std::set_symmetric_difference(
            v1.begin(), v1.end(),
            v2.begin(), v2.end(),
            std::back_inserter(v_symDifference));

        for (int n : v_symDifference)
            std::cout << n << ' ';
    }

    void set_class_test()
    {
        std::vector<int> v_int{ 1,2,2,3,4,4,5,2,7,8 };
        std::set<int> int_set(v_int.begin(), v_int.end());
        std::copy(int_set.begin(), int_set.end(), std::ostream_iterator<int>(std::cout, " "));
    }


    class MyClass
    {
        friend std::ostream& operator << (std::ostream&, const MyClass&);
    public:
        MyClass();
        ~MyClass();
        MyClass(const MyClass&);
    private:
        string m_name = "hello";
    };

    std::ostream& operator << (std::ostream& os, const MyClass& obj)
    {
        os << obj.m_name << std::endl;
        return os;
    }

    MyClass::MyClass(const MyClass& o)
    {
        string m_name = o.m_name;
        std::cout << "Myclass copy construct was called." << std::endl;
    }

    MyClass::MyClass()
    {
        std::cout << "Myclass construct was called." << std::endl;
    }

    MyClass::~MyClass()
    {
        std::cout << "Myclass destruct was called." << std::endl;
    }

    void test_for_loop()
    {
        MyClass temp;
        std::vector<MyClass> obj_vec(4, temp);

        //without temp object created
        std::copy(obj_vec.begin(), obj_vec.end(), std::ostream_iterator<MyClass>(std::cout, " "));
        std::cout << std::endl;

        //auto without reference, create temp object each iertation.
        for (auto e : obj_vec) {
            std::cout << e << " ";
        }
        std::cout << std::endl;

        //auto& was VERY IMPORTANT!!
        //auto with reference, not create temp object.
        for (auto& e : obj_vec) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
}


//int main()
//{
//    using namespace test_stl;
//    test_for_loop();
//    //set_class_test();
//    //set_symmetric_difference_test();
//    //set_different_test();
//    //sort_test();
//    //adjacent_find_test();
////    itoa_example();
//    //random_device_example();
//}