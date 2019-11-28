#ifndef THREADPULL_H
#define THREADPULL_H


#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <map>

using namespace std;

class ThreadPull
{
public:
    ThreadPull();
    ~ThreadPull();


    bool chakeNameThread(string name);
    void push_back(string nameThread, promise<bool> *promes, future<void> *thread);

    bool stopThread(string nameThread);


private:
    unsigned int num_threads;

    map<string,future<void>*> mapThreads;
    map<string,promise<bool>*> mapThreadsPromes;

};
#endif // THREADPULL_H
