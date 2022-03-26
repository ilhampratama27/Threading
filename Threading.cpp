#include <iostream> 
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

mutex mu;
condition_variable cond;
int cnt = 1;

void oodThread()
{
    for (; cnt < 20;)
    {
        unique_lock<mutex> locker(mu);
        cond.wait(locker, []() { return (cnt % 2 == 1); });
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Odd Thread: " << cnt << endl;
        cnt++;
        locker.unlock();
        cond.notify_all();
    }

}

void evenThread()
{
    for (; cnt < 20;)
    {
        unique_lock <mutex> locker(mu);
        cond.wait(locker, []() { return (cnt % 2 == 0); });
        this_thread::sleep_for(chrono::duration<double>(2.5));
        cout << "Even Thread: " << cnt << endl;
        cnt++;
        locker.unlock();
        cond.notify_all();
    }
}

int main()
{
    thread t1(oodThread);
    thread t2(evenThread);
    t1.join();
    t2.join();
   return 0;
}
