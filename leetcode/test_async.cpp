#include<string>
#include<vector>
#include<mutex>
#include<deque>
#include<iostream>
#include<chrono>
#include<thread>

namespace test_async {
	using std::cout;
	using std::vector;
	using std::string;
	using std::endl;
	using std::mutex;
	using std::deque;
	using namespace std::chrono_literals;

	class SerilPort
	{
	public:
		SerilPort();
		~SerilPort();
		void transfor(const string& data)
		{
			cout << data << endl;
		}

	private:

	};

	SerilPort::SerilPort()
	{
	}

	SerilPort::~SerilPort()
	{
	}

	//seril port driver.
	class Seril_Driver
	{
	public:
		Seril_Driver(SerilPort&& port) :m_port(port) {}
		~Seril_Driver();
		void write_date(const string& data)
		{
			m_port.transfor(data);
		}

	private:
		SerilPort m_port;
	};


	Seril_Driver::~Seril_Driver()
	{
	}



	SerilPort g_port;
	Seril_Driver port_driver(std::move(g_port)); //resource to be raced.
	mutex lock;

	void task1()
	{//write to port period
		while (true) {
			std::this_thread::sleep_for(6ms);
			std::scoped_lock l{ lock };
			port_driver.write_date("task1 output data to seril port.");
			std::this_thread::sleep_for(2ms);
			port_driver.write_date("task1 output end.");
		}
	}

	void task2()
	{
		//write to port period
		while (true) {
			std::this_thread::sleep_for(3ms);
			std::scoped_lock l{ lock };
			port_driver.write_date("task2 output data to seril port.");
			std::this_thread::sleep_for(1ms);
			port_driver.write_date("task2 output end.");
		}
	}

	void task3()
	{
		//write to port period
		while (true) {
			std::this_thread::sleep_for(2ms);
			std::scoped_lock l{ lock };
			port_driver.write_date("task3 output data to seril port.");
			std::this_thread::sleep_for(1ms);
			port_driver.write_date("task3 output end.");
		}
	}



	class CMessageQueue
	{
	public:
		CMessageQueue() {}
		~CMessageQueue();
		void send_message(const string& msg) {
			std::scoped_lock lck{ m_mutex };
			m_message_q.push_back(msg);
			m_cond.notify_one();
		}

		string fetch_message() {
			std::unique_lock lck{ m_mutex };
			m_cond.wait(lck, [this] {return !m_message_q.empty(); });

			auto m = m_message_q.front();
			m_message_q.pop_front();

			return m;
		}

	private:
		std::condition_variable	m_cond;
		mutex		  m_mutex;
		deque<string> m_message_q;
	};

	CMessageQueue::~CMessageQueue()
	{
	}

	CMessageQueue g_Q;

	void task_send_to_seril(CMessageQueue& m_q)
	{
		while (true)
		{
			string msg = m_q.fetch_message();
			
			//split string by EOL
			string::size_type inx = msg.find('\n');
			string msg2 = msg.substr(inx + 1);
			msg.erase(inx);

			port_driver.write_date(std::move(msg));
			std::this_thread::sleep_for(2ms);
			port_driver.write_date(std::move(msg2));
		}
	}

	void task4(CMessageQueue& m_q)
	{//write to port period
		string message = "task4 output data to seril port.\ntask4 output end.";
		while (true) {
			std::this_thread::sleep_for(2ms);
			m_q.send_message(message);
		}
	}

	void task5(CMessageQueue& m_q)
	{
		//write to port period
		string message = "task5 output data to seril port.\ntask5 output end.";
		while (true) {
			std::this_thread::sleep_for(3ms);
			m_q.send_message(message);
		}
	}

	void task6(CMessageQueue& m_q)
	{
		//write to port period
		string message = "task6 output data to seril port.\ntask6 output end.";
		while (true) {
			std::this_thread::sleep_for(5ms);
			m_q.send_message(message);
		}
	}
}

int main()
{
	using namespace test_async;
	//std::thread t1{ task1};
	//std::thread t2{ task2};
	//std::thread t3{ task3};

	//t1.join();
	//t2.join();
	//t3.join();

	std::thread t4{ task4 , std::ref(g_Q )};
	std::thread t5{ task5 , std::ref(g_Q) };
	std::thread t6{ task6 , std::ref(g_Q) };
	std::thread t_output{ task_send_to_seril , std::ref(g_Q) };

	t4.join();
	t5.join();
	t6.join();

	return 1;
}