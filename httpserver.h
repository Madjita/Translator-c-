#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "globalsfun.h"

#include <fstream>

#include <sstream>
#include <iostream>

#include "filework.h"
#include "scanner.h"

class HttpServer
{
public:
    HttpServer();


    int init(string ip,string port);

    bool process_start(string name);

    void worker(future<bool> stopFlag);

    void set_dir_exe(string dir);


    vector<string> split(string str, string token, int count = 0);


private:
     bool ReadAllBytes(char const* filename,vector<char>& result);

     bool readFile(string file, string &resultBuf);

private:
    string global_dir_exe;
    SOCKET listen_socket;
    SOCKET sock_server_hhtp;
};

#endif // HTTPSERVER_H
