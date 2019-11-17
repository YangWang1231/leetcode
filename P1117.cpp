
#include<mutex>
#include<condition_variable>
#include<functional>
using namespace std;

class H2O {
private:
	mutex m_mutex;
	condition_variable m_cvar;
	int		m_hydrogen_count;
	int		m_oxygen_count;
public:
	H2O() {
		m_hydrogen_count = 0;
		m_oxygen_count = 0;
	}

	void hydrogen(function<void()> releaseHydrogen) {
		while (true)
		{
			unique_lock lck{ m_mutex };
			m_cvar.wait(lck, [this] { return m_hydrogen_count < 2; });

			// releaseHydrogen() outputs "H". Do not change or remove this line.
			releaseHydrogen();

			m_hydrogen_count++;
			if (m_hydrogen_count == 2)
			{
				m_oxygen_count = 0;
			}
			m_cvar.notify_one();
		}
	}

	void oxygen(function<void()> releaseOxygen) {
		while (true)
		{
			unique_lock lck{ m_mutex };
			m_cvar.wait(lck, [this] { return m_oxygen_count < 1; });
			// releaseOxygen() outputs "O". Do not change or remove this line.
			releaseOxygen();

			m_oxygen_count++;
			if (m_hydrogen_count == 2) {
				m_hydrogen_count = 0;
			}
			m_cvar.notify_one();
		}
		
	}
};

#include<thread>
H2O g_h2o;


//void main()
//{
//	thread t1{ &H2O::hydrogen, &g_h2o, [] { printf("H"); } };
//	thread t2{ &H2O::oxygen, &g_h2o, [] { printf("O"); } };
//
//	t1.join();
//	t2.join();
//}