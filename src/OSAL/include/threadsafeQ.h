#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable> 
#include <chrono>
template<typename Data>
class threadsafeQ
{
private:
    std::queue<Data> the_queue;
    std::mutex the_mutex;
    std::condition_variable the_condition_variable;
public:
    void push(Data const& data)
    {
		std::unique_lock<std::mutex> lock(the_mutex);
        the_queue.push(data);
		lock.unlock();
        the_condition_variable.notify_all();
    }

    bool empty() const
    {
		std::unique_lock<std::mutex> lock(the_mutex);
        return the_queue.empty();
    }

    bool try_pop(Data& popped_value)
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        if(the_queue.empty())
        {
            return false;
        }
        
        popped_value=the_queue.front();
        the_queue.pop();
        return true;
    }

    void wait_and_pop(Data& popped_value)
    {		
        std::unique_lock<std::mutex> lock(the_mutex);
        the_condition_variable.wait(lock, [=](){return !the_queue.empty();});
        popped_value=the_queue.front();
        the_queue.pop();

    }
   bool wait_and_pop(unsigned long timeout,Data& popped_value)
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        auto now = std::chrono::steady_clock::now();
		if(the_condition_variable.wait_until(lock, now + std::chrono::microseconds(timeout), [=](){return !the_queue.empty();}))
        {
			popped_value=the_queue.front();
			the_queue.pop();
			return true;
		}
		else 
		{
			return false;
		}
    }

};

/*
#include <pthread.h> 
#include <semaphore.h>

using namespace std;

template <typename Type>
 class ConcurrentQueue : public queue<Type>
 {
	 public:
	   ConcurrentQueue()
	    { 
			sem_init(&sem, 0, 0);
			pthread_mutex_init(&lock, NULL);
		}

		virtual ~ConcurrentQueue()
		{
			pthread_mutex_destroy(&lock);
			sem_destroy(&sem);
		}

		void push(const Type& x)
		{ 
			pthread_mutex_lock(&lock);
			queue<Type>::push(x);
			pthread_mutex_unlock(&lock);
			sem_post(&sem);
		}

		Type pop() 
		{ 
			Type t;
			sem_wait(&sem);
			pthread_mutex_lock(&lock);
			t = queue<Type>::front();
			queue<Type>::pop();
			pthread_mutex_unlock(&lock);
			return t;
		} 
	private:
		pthread_mutex_t lock; sem_t sem;
};

*/
