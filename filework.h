#ifndef FILEWORK_H
#define FILEWORK_H


#include <iostream>
#include <vector>
#include <fstream>

#include <mutex>
#include <semaphore.h>
#include <condition_variable>


#include <future>


#include "threadpull.h"
#include "globalsfun.h"


extern vector<string> split(string str, string token, int count = 0);

using namespace std;

class FileWork
{
public:
    FileWork();
    ~FileWork();

    void readFile(future<bool> stopFlag);
    void readString2(string FName,future<bool> stopFlag);
    void readString(string FName); // future<bool> stopFlag
    void process_start(string FName,bool flagFile);


   // vector<string> split(string str, string token,int count = 0);


    void seekgNext();
    void seekgBack();

    vector<string> getResult();
    vector<vector<string>>  getResult_list();

    void Next();

    bool getCurrentWorkFlag();
    bool getIsOpenFile();





    ////////////

    mutex currentFlagStartThreadMutex_;
    mutex currentFlagMutex_;
    sem_t  sem_;

    condition_variable_any dataReadyCondition_;
    bool dataReadyFlag_;

    bool isThreadRunning_;

    bool flagBack_;


    std::future<void> this_trhead;

private:
    ifstream in_;
    std::ios::pos_type pos_;
    vector<string> list_result_;
    vector<vector<string>> list_result_list_;
    string FName_;

    int backPosition_;

    mutex mtx;
};

#endif // FILEWORK_H
