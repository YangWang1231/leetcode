#include<random>
#include<string>
#include<numeric>
#include<vector>
#include<iterator>
#include<mutex>
#include<deque>
#include<iostream>
#include<chrono>
#include<thread>
#include<iomanip>

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
			//cout << data << endl;
			fprintf(m_fp, "%s\n", data.c_str());
		}

	private:
		FILE* m_fp;
	};

	SerilPort::SerilPort()
	{
		m_fp = fopen("seril_out.dat", "w");
	}

	SerilPort::~SerilPort()
	{
		fclose(m_fp);
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

	class CMessage
	{
	public:
		friend std::ostream& operator << (std::ostream& os, const CMessage&);
		CMessage(string& msg, int properity, std::chrono::milliseconds cost):m_msg(msg),m_task_properity(properity),m_cost(cost) {}
		~CMessage();

	public:
		string m_msg;
		int	   m_task_properity;
		std::chrono::milliseconds m_cost;
	};

	std::ostream& operator << (std::ostream& os, const CMessage& msg)
	{
		os << "task properity" << msg.m_task_properity;

		return os;
	}


	CMessage::~CMessage()
	{
	}

	class CMessageQueue
	{
	public:
		CMessageQueue() {}
		~CMessageQueue();
		void send_message(const CMessage& msg) {
			std::scoped_lock lck{ m_mutex };
			m_message_q.push_back(msg);
			m_cond.notify_one();
		}

		CMessage fetch_message() {
			std::unique_lock lck{ m_mutex };
			m_cond.wait(lck, [this] {return !m_message_q.empty(); });

			auto m = m_message_q.front();
			m_message_q.pop_front();

			return std::move(m);
		}

		void print_messageQueue() 
		{//only print this for myself
			std::scoped_lock lck{ m_mutex };
			if (m_message_q.empty())
			{
				cout << "message queue empty." << endl;
				return;
			}

			auto f = m_message_q.cbegin();
			auto l = m_message_q.cend();
			std::copy(f, l, std::ostream_iterator<CMessage>(cout, " "));
			cout << endl;
		}

	private:
		std::condition_variable	m_cond;
		mutex			m_mutex;
		deque<CMessage> m_message_q;
	};

	CMessageQueue::~CMessageQueue()
	{
	}


	class CTask
	{
	public:
		CTask(string name, string msg, int properity, std::chrono::milliseconds time_period = 2ms):m_msg(msg),m_properity(properity),m_task_name(name),m_task_period(time_period) {}
		~CTask();
		void task_fun(CMessageQueue& m_q)
		{
			std::uniform_int_distribution<int> dist(1, 9);
			std::mt19937 gen(std::random_device{}());
			
			while (true) {
				std::this_thread::sleep_for(m_task_period);
				CMessage msg(m_msg, m_properity, std::chrono::milliseconds(dist(gen)));
				m_q.send_message(std::move(msg));
			}
		}

	private:
		int		m_properity; //task proerity.
		string	m_msg;		//every task send const message.
		string  m_task_name; 
		std::chrono::milliseconds	m_task_period; //ms
	};

	
	CTask::~CTask()
	{
	}

	CMessageQueue g_Q;

	void task_print_massageQueue(CMessageQueue& m_q)
	{
		while (true) {
			std::this_thread::sleep_for(100ms);
			m_q.print_messageQueue();
		}
	}

	void task_send_to_seril(CMessageQueue& m_q)
	{
		while (true)
		{
			auto msg = m_q.fetch_message();
			auto str = msg.m_msg;
			//split string by EOL
			string::size_type inx = str.find('\n');
			string msg2 = str.substr(inx + 1);
			str.erase(inx);

			port_driver.write_date(std::move(str));
			std::this_thread::sleep_for(2ms);
			port_driver.write_date(std::move(str));
		}
	}


	
	//void task4(CMessageQueue& m_q)
	//{//write to port period
	//	string message = "task4 output data to seril port.\ntask4 output end.";
	//	while (true) {
	//		std::this_thread::sleep_for(2ms);
	//		m_q.send_message(message);
	//	}
	//}

	//void task5(CMessageQueue& m_q)
	//{
	//	//write to port period
	//	string message = "task5 output data to seril port.\ntask5 output end.";
	//	while (true) {
	//		std::this_thread::sleep_for(3ms);
	//		m_q.send_message(message);
	//	}
	//}

	//void task6(CMessageQueue& m_q)
	//{
	//	//write to port period
	//	string message = "task6 output data to seril port.\ntask6 output end.";
	//	while (true) {
	//		std::this_thread::sleep_for(5ms);
	//		m_q.send_message(message);
	//	}
	//}
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

	/*std::thread t4{ task4 , std::ref(g_Q )};
	std::thread t5{ task5 , std::ref(g_Q) };
	std::thread t6{ task6 , std::ref(g_Q) };*/


	//t4.join();
	//t5.join();
	//t6.join();

	CTask taskobj1{ "task4","task4 output data to seril port.\ntask4 output end." ,100,4ms };
	CTask taskobj2{ "task5","task5 output data to seril port.\ntask5 output end." ,102,5ms };
	//create working task
	std::thread t4{ &CTask::task_fun, &taskobj1, std::ref(g_Q) };
	std::thread t5{ &CTask::task_fun, &taskobj2, std::ref(g_Q) };
	std::thread t_output{ task_send_to_seril , std::ref(g_Q) };

	//create debug task
	std::thread t_debug(task_print_massageQueue, std::ref(g_Q));


	t4.join();
	return 1;
}