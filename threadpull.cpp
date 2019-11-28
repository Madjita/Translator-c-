#include "threadpull.h"




ThreadPull::ThreadPull()
{
    //количество ядер в системе то есть количество реально параллельных потоков
    num_threads = thread::hardware_concurrency();
}

ThreadPull::~ThreadPull()
{
    for(auto item: mapThreads)
    {
        stopThread(item.first);
    }

    cout << "ALL Threads are terminate"<<endl;
}


bool ThreadPull::chakeNameThread(string name)
{
    auto search = mapThreads.find(name);

    if(search != mapThreads.end())
    {
        return true;

    }

    return false;
}

void ThreadPull::push_back(string nameThread, promise<bool> *promes, future<void> *th)
{
    mapThreadsPromes.insert(make_pair(nameThread,promes));
    mapThreads.insert(make_pair(nameThread,th));

}

bool ThreadPull::stopThread(string nameThread)
{

    if(!chakeNameThread(nameThread))
    {
        cout <<"Error: This name  '" << nameThread<<"' is already there"<<endl;
        return false;
    }

    auto th = mapThreads.find(nameThread)->second;
    auto stopSignal = mapThreadsPromes.find(nameThread)->second;

    cout << "Wait Stop thread : " << nameThread<<endl;
    stopSignal->set_value(true);
    th->wait();

    cout << "Wait Stop thread : " << nameThread << " is TRUE";
    return true;
}

