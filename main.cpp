//#include <QCoreApplication>
//#include <QTextCodec>

#include "globals.h"

#include "threadpull.h"
#include "scanner.h"
#include <iostream>
#include <fstream>

#include <unistd.h>


#include "str_switch.h"
#include "filework.h"
#include "httpserver.h"
#include "globalsfun.h"


using namespace  std;



static mutex splitMutex;
ThreadPull* threadPulls = new ThreadPull; //Переменная хранящая в себе пул всех потоков

vector<string> split(string str, string token, int count)
{

    std::unique_lock<std::mutex> ulock(splitMutex);
    vector<string>result;
    if(count > 0)
    {
        // Выделение первой части строки
        char* istr = strtok(strdup(str.c_str()),token.c_str());
        result.push_back(string(istr));
        istr = strtok (nullptr,"");

        if(istr != nullptr)
            result.push_back(string(istr));
    }
    else {
        while(str.size()){
            unsigned int index = str.find(token);
            if(index != string::npos){
                result.push_back(str.substr(0,index));
                str = str.substr(index+token.size());
                if(str.size()==0)result.push_back(str);
            }else{
                result.push_back(str);
                str = "";
            }
        }
    }
    return result;
}


int main(int argc, char *argv[])
{

    string dir = argv[0];
    for(unsigned int i = dir.size(); i > 0;--i)
    {
        if(dir[i] == '\\')
        {
            dir.erase(i,dir.size());
            break;
        }
    }

    string ipServer = "127.0.0.1";
    string portServer = "8000";

    HttpServer http;
    http.set_dir_exe(dir);
    if (http.init(ipServer,portServer) == 0)
    {
       if(http.process_start("HTTP:"+ipServer+":"+portServer))
       {
            cout << "HHTP Server : START  = "<<ipServer<<":"<<portServer<<endl;
       }
       else
       {
           cout << "Error : Don't open server"<<endl;
       }
    }

    system("pause");

    //Корректное закрытие всех потоков (если такие имеются)
    delete threadPulls;
    cout << "Exit"<<endl;
    return 0;
}
