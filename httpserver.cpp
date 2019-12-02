#include "httpserver.h"

HttpServer::HttpServer()
{
    ///Создать новый поток в котором запустить сервер Http
    global_dir_exe ="";
}

bool  HttpServer::ReadAllBytes(char const* filename,vector<char>& result)
{
    ifstream file(filename, ios::binary);

    if (file.fail()) {
        perror(filename);
        return false;
    }

    // copies all data into buffer
    vector<char> prov(
                (istreambuf_iterator<char>(file)),
                (istreambuf_iterator<char>()));

    result = prov;

    file.close();

    return true;
}

bool HttpServer::readFile(string fileStream, string &resultBuf)
{
    FileWork file;
    //file.process_start(fileStream,false);

    cout << "readString"<<endl;
    //file.readString(fileStream);

    vector<string> v;

    cout << "  v = file.getResult();"<<endl;
    // v = file.getResult();

    v = split(fileStream,"\r\n");
    if(*v.rbegin() == "")
        v.pop_back();

    cout << "  v = " << v.size()<<endl;

    //Преобразовать текст в лексемы
    Scanner scan;
    scan.workLexer(v);

    cout << "Lex the end :"<<endl;


    int count_t = 0;
    bool flag_ferstWordInStr = true;
    bool flag_dontNextLine = false;
    bool flag_enum = false;

    //stringstream file_sss;


    if(scan.list_word_lex_string.size() == 0)
    {
        cout << "EROOR"<<endl;
    }

    // for(unsigned int i=0;i < scan.list_word_lex_string.size();i++)

    resultBuf += scan.getLexString();


    /*for(auto it=mapLex.begin(); it !=mapLex.end();it++)
    {
        for(int j=0; j < scan.countTab[it->first];j++)
        {
            file_sss << '\t';
        }

        auto vector_lex = it->second;

        //идем по вектору лексем
        for(auto j=0; j < vector_lex.size();j++)
        {
            //идем по лексемам
            for(auto& item_lex : vector_lex[j])
            {
                //идем по значениям
                for(auto& item_data : item_lex.second)
                {
                    file_sss << item_data.first << " ";
                }
            }
        }

        if(it->first != mapLex.size()-1)
            file_sss << '\n';
        /*
        auto ch = scan.list_word_lex_string[i];
        string ch_next = "";
        string ch_above = "";
        string ch_double_above = "";

        if(i < scan.list_word_lex_string.size()-1)
        {
            ch_next = scan.list_word_lex_string[i+1];
        }
        if(i > 0)
        {
            ch_above = scan.list_word_lex_string[i-1];
        }
        if(i > 1)
        {
            ch_double_above = scan.list_word_lex_string[i-2];
        }

        if(ch == "keyFOR")
        {
            flag_dontNextLine = true;
        }


        if(ch == "lcLFigure")
        {
            flag_dontNextLine = false;
            flag_ferstWordInStr = true;
            file_sss <<"\r\n";
            for (int j=0; j < count_t;j++)
            {
                file_sss << "\t";
            }

            file_sss<< ch <<"\r\n";

            count_t++;
        }
        else
        {
            if(ch == "lcRFigure")
            {
                count_t--;;
                flag_ferstWordInStr= true;
                flag_enum = false;
            }

            if(flag_ferstWordInStr)
            {
                for (int j=0; j < count_t;j++)
                {
                    file_sss << "\t";
                }

                flag_ferstWordInStr = false;
            }

            if(ch == "lcSemicolon" && ch_next != "lcSemicolon" && ch_next != "lcRCircle" && !flag_dontNextLine) //
            {
                flag_ferstWordInStr = true;
            }

            file_sss << ch <<" ";
        }

        if((ch == "lcSemicolon" && ch_next != "lcSemicolon" && ch_next != "lcRCircle" && !flag_dontNextLine) || ch == "lcRFigure")
        {
            file_sss <<"\r\n";
            flag_ferstWordInStr= true;
            flag_dontNextLine = false;
        }
        //        if(ch_above == "lcInclude")
        //        {
        //           file_sss <<"\r\n";
        //           flag_ferstWordInStr= true;
        //           flag_dontNextLine = false;
        //        }

        //кастыль
        if(ch_double_above == "lcLattice" || (ch_double_above == "keyCASE" && (ch_next != "lcLFigure" && ch_next !="lcApostrophe")))
        {
            file_sss <<"\r\n";
            flag_ferstWordInStr= true;
            flag_dontNextLine = false;

        }

        if(ch == "keyENUM")
        {
            flag_enum = true;
        }

        if((ch == "lcComma" || ch == "lcColon") &&  (flag_enum || ch_above == "keyPUBLIC" || ch_above == "keyPRIVATE" || ch_above == "keyPROTECTED"))
        {
            file_sss <<"\r\n";
            flag_ferstWordInStr= true;
            flag_dontNextLine = false;
        }
    }*/


    ofstream file_ExampleLex;
    file_ExampleLex.open(string("log_lexem.txt").c_str(), ios::binary);
    file_ExampleLex.close();
    file_ExampleLex.open(string("log_lexem.txt").c_str(), ios::binary | ios::app);
    file_ExampleLex << resultBuf;



    return true;
}

int HttpServer::init(string ip,string port)
{


#ifdef _WIN32

    sock_server_hhtp = 0;
    SOCKET listener = 0;
#else
    int sock, listener;
    struct sockaddr_in addr;
#endif


    int bytes_read;

#ifdef _WIN32
    // служебная структура для хранение информации
    // о реализации Windows Sockets
    WSADATA wsaData;
    // старт использования библиотеки сокетов процессом
    // (подгружается Ws2_32.dll)
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Если произошла ошибка подгрузки библиотеки
    if (result != 0) {
        cerr << "WSAStartup failed: " << result << "\n";
        return result;
    }

    struct addrinfo* addr = nullptr; // структура, хранящая информациюs
    // об IP-адресе  слущающего сокета

    // Шаблон для инициализации структуры адреса
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));

    // AF_INET определяет, что используется сеть для работы с сокетом
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; // Задаем потоковый тип сокета
    hints.ai_protocol = IPPROTO_TCP; // Используем протокол TCP
    // Сокет биндится на адрес, чтобы принимать входящие соединения
    hints.ai_flags = AI_PASSIVE;

    // Инициализируем структуру, хранящую адрес сокета - addr.
    // HTTP-сервер будет висеть на 8000-м порту локалхоста
    result = getaddrinfo(ip.c_str(),port.c_str(), &hints, &addr);

    // Если инициализация структуры адреса завершилась с ошибкой,
    // выведем сообщением об этом и завершим выполнение программы
    if (result != 0) {
        cerr << "getaddrinfo failed: " << result << "\n";
        WSACleanup(); // выгрузка библиотеки Ws2_32.dll
        return 1;
    }

    // Создание сокета
    listen_socket = socket(addr->ai_family, addr->ai_socktype,
                           addr->ai_protocol);
    // Если создание сокета завершилось с ошибкой, выводим сообщение,
    // освобождаем память, выделенную под структуру addr,
    // выгружаем dll-библиотеку и закрываем программу
    if (listen_socket == INVALID_SOCKET) {
        cerr << "Error at socket: " << WSAGetLastError() << "\n";
        freeaddrinfo(addr);
        WSACleanup();
        return 1;
    }

    // Привязываем сокет к IP-адресу
    result = bind(listen_socket, addr->ai_addr, (int)addr->ai_addrlen);

    // Если привязать адрес к сокету не удалось, то выводим сообщение
    // об ошибке, освобождаем память, выделенную под структуру addr.
    // и закрываем открытый сокет.
    // Выгружаем DLL-библиотеку из памяти и закрываем программу.
    if (result == SOCKET_ERROR) {
        cerr << "bind failed with error: " << WSAGetLastError() << "\n";
        freeaddrinfo(addr);
        closesocket(listen_socket);
        WSACleanup();
        return 1;
    }
    // Инициализируем слушающий сокет
    if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR) {
        cerr << "listen failed with error: " << WSAGetLastError() << "\n";
        closesocket(listen_socket);
        WSACleanup();
        return 1;
    }

#else
    listener = socket(AF_INET,SOCK_STREAM,0);
    if(listener < 0)
    {
        printf("soket error\n");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);//3425
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(::bind(listener, (struct sockaddr *)&addr,sizeof(addr)) < 0 )
    {
        printf("Error bind\n");

    }
    listen(listener,SOMAXCONN);

    char* getIp = new char(50);
    strcpy(getIp,inet_ntoa( addr.sin_addr ));
    cout << "Server ip : " << getIp << endl;
#endif


    std::chrono::system_clock clk;
    std::chrono::system_clock::time_point start, end;


    vector<char> resultBuf;
    vector<string> list_http;
    vector<string> list_one_line;
    vector<string> get_parametrs;



    char* query = (char*)calloc(500000,sizeof(char));//500000
    char* get_get = (char*)calloc(100,sizeof(char));
    char* get = (char*)calloc(1024,sizeof(char));

    char buf[1024];

    memset(query,'\0',sizeof(query));
    memset(query,'\0',sizeof(get_get));
    memset(buf,'\0',sizeof(buf));


    return 0;
}

bool HttpServer::process_start(string name)
{
    return add_threadOnPull(name,&HttpServer::worker,this);
}

void HttpServer::worker(future<bool> stopFlag)
{
    std::chrono::system_clock clk;
    std::chrono::system_clock::time_point start, end;

    vector<char> resultBuf;
    vector<string> list_http;
    string http_fileData = "";
    vector<string> list_one_line;
    vector<string> get_parametrs;

    int bytes_read = 0;
    //char *buf = new char;

    vector<char> buf(BUFSIZ);
    vector<char> query;

    char* get_get = (char*)calloc(100,sizeof(char));
    char* get = (char*)calloc(1024,sizeof(char));


    char getIp[100] = {'\0'};
    unsigned int getPort =0;


    cout << endl;
    cout << "HTTP Server is listening..." << endl;

    int size = 0;
    string HttpStr ="";

    bool flagWaitClient = true;
    while(1)
    {

        if(flagWaitClient)
        {
            cout << "HTTP Server wait for client..." << endl;
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        int select_res = 0;
        fd_set s_set;
        FD_ZERO(&s_set);
        FD_SET(listen_socket, &s_set);
        timeval timeout = {1, 0};

        while (true)
        {
            flagWaitClient = false;
            select_res = select(static_cast<int>(listen_socket) + 1, &s_set, nullptr, nullptr, &timeout);
            if (select_res)
            {
                break;
            }
        }

        if (select_res == SOCKET_ERROR)
        {
            //Остановить работу потока по флагу
            if (stopFlag.wait_for(chrono::microseconds(1)) == future_status::ready)
            {
                cout << "thread 'worker' stopped!\n";
                return;
            }
            continue;
        }

        flagWaitClient = true;
        /////////////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
        // Принимаем входящие соединения
        sock_server_hhtp = accept(listen_socket, nullptr, nullptr);
        start = clk.now();

        if (sock_server_hhtp == INVALID_SOCKET) {
            cerr << "accept failed: " << WSAGetLastError() << "\n";
            closesocket(listen_socket);
            WSACleanup();
            return ;
        }
#else

        sock_server_hhtp = accept(listener,0 ,0);
        start = clk.now();

        if(sock_server_hhtp < 0 )
        {
            printf("accept\n");
            //exit(3);
        }
#endif


        //Остановить работу потока по флагу
        if (stopFlag.wait_for(chrono::microseconds(1)) == future_status::ready)
        {
            cout << "thread 'worker' stopped!\n";
            return;
        }


        while(1)
        {

            //Остановить работу потока по флагу
            if (stopFlag.wait_for(chrono::microseconds(1)) == future_status::ready)
            {
                cout << "thread 'worker' stopped!\n";
                return;
            }
            SOCKADDR_IN addr;
#ifdef _WIN32
            int addrLen = sizeof(addr);
#elif
            unsigned int addrLen = sizeof (addr);
#endif


            //Собираем пакет нужной длины
            while (true)
            {
                bytes_read = ::recv(sock_server_hhtp,buf.data(),static_cast<int>(buf.size()),MSG_PEEK);

                if(buf.size() > bytes_read)
                {
                    bytes_read = ::recv(sock_server_hhtp,buf.data(),static_cast<int>(buf.size()),0);
                    buf.resize(static_cast<unsigned int>(bytes_read));
                    break;
                }

                if(buf.size() == bytes_read)
                {
                    bytes_read *=2;
                    buf.resize(static_cast<unsigned int>(bytes_read));
                }
                else
                {
                    bytes_read = ::recv(sock_server_hhtp,buf.data(),static_cast<int>(buf.size()),0);
                    break;
                }
            }


            strcpy(getIp,inet_ntoa(addr.sin_addr));
            getPort = ntohs(addr.sin_port );

            cout << "Get http from "<<getIp<<":"<<getPort<<": Read bytes = " << bytes_read<< " Data: "<<endl;

            if (bytes_read == -1)
            {
                // Handle error
                cout << "Get http from "<<getIp<<":"<<getPort<<": Read bytes = " << bytes_read<< " Data: " <<"Handle error"<<endl;
                break;
            }


            string HttpStr = "HTTP/1.1 200 OK\r\n";
            HttpStr +="Date: SUN,10 Feb 2019 03:51:41 GMT\r\n";
            HttpStr +="Content-Type: text/html;charset=utf-8\r\n";
            HttpStr +="Connection: keep-alive\r\n";
            HttpStr +="Keep-Alive: timeout=1\r\n";
            HttpStr +="Server: zeadboar\r\n";
            HttpStr +="X-Pingback://webgyry.info/xmlrpc.php\r\n\r\n";

            query.clear();
            query.resize(HttpStr.size());
            copy(HttpStr.begin(), HttpStr.end(), query.begin());


            if(buf.size() > 5)
            {
                string howPost = "";

                for(unsigned int i=0;i < 5; i++)
                {
                    if(buf[i] == ' ')
                    {
                        break;
                    }
                    howPost+=buf[i];
                }


                if(howPost == "POST")
                {
                    list_http.clear();
                    list_one_line.clear();
                    http_fileData="";

                    //SPLit http
                    list_http = split(buf.data(),"-----------------------------");
                    list_one_line = split(list_http.at(0)," ");

                    cout << "list_http.size() = " << list_http.size()<<endl;
                    if(list_http.size() > 2)
                    {
                        for(int i=1;i < list_http.size()-1;i++)
                        {
                            http_fileData +=list_http[i];
                        }
                    }

                    //Проверка есть ли GEt данные или нет
                    auto get_parametrs = split(list_one_line.at(1),"?",1);

                    if(get_parametrs.empty() == false)
                        strcpy(get,get_parametrs.at(0).c_str());
                    else {
                        strcpy(get,"/");
                    }



                }

                if(howPost == "GET")
                {
                    //SPLit http
                    list_http = split(buf.data(),"\r\n");
                    list_one_line = split(list_http.at(0)," ");

                    //Проверка есть ли GEt данные или нет
                    auto get_parametrs = split(list_one_line.at(1),"?",1);

                    if(get_parametrs.empty() == false)
                        strcpy(get,get_parametrs.at(0).c_str());
                    else {
                        strcpy(get,"/");
                    }
                }
            }


            if(string(get) == "/favicon.ico")
            {
                HttpStr = "HTTP/1.1 404 Not Found\r\n";
                HttpStr +="Date: SUN,10 Feb 2019 03:51:41 GMT\r\n";
                HttpStr +="Content-Type: text/html;charset=utf-8\r\n";
                HttpStr +="Connection: close\r\n";
                HttpStr +="Server: zeadboar\r\n";
                HttpStr +="X-Pingback://webgyry.info/xmlrpc.php\r\n\r\n";
                query.clear();
                query.resize(HttpStr.size());
                copy(HttpStr.begin(), HttpStr.end(), query.begin());
                ::send(sock_server_hhtp,query.data(),static_cast<int>(query.size()),0);
                break;
            }




            if(string(get) == "/upload")
            {
                cout << "upload "<<endl;

                HttpStr = "HTTP/1.1 200 OK\r\n";
                HttpStr +="Date: SUN,10 Feb 2019 03:51:41 GMT\r\n";
                HttpStr +="Content-type: text;charset=utf-8\r\n"; //application/x-www-form-urlencoded
                //HttpStr +="Connection: close\r\n";
                HttpStr +="Connection: keep-alive\r\n";
                HttpStr +="Keep-Alive: timeout=100\r\n";
                HttpStr +="Server: zeadboar\r\n";
                HttpStr +="X-Pingback://webgyry.info/xmlrpc.php\r\n\r\n";


                auto listFile = split(http_fileData,"\r\n\r\n");

                auto file = http_fileData;
                file.erase(0,listFile[0].size()+4);


                cout << "readFile"<<endl;


                readFile(file,HttpStr);


                query.clear();
                query.resize(HttpStr.size());
                copy(HttpStr.begin(), HttpStr.end(), query.begin());


                ::send(sock_server_hhtp,query.data(),static_cast<int>(query.size()),0);
                break;

            }


            if(string(get) == "/")
            {
#ifdef _WIN32
                auto newStr = global_dir_exe+"\\1.html";
                ReadAllBytes(newStr.c_str(),resultBuf);

#else
                ReadAllBytes("/mnt/1.html",resultBuf);
#endif
            }
            else
            {
#ifdef _WIN32
                auto strGET = (string)get;
                strGET.erase(strGET.begin(),strGET.begin()+1);
                strGET = global_dir_exe+"\\"+strGET;
                ReadAllBytes(strGET.c_str(),resultBuf);


                strGET.erase(0,strGET.size()-3);
                if(strGET == "css")
                {
                    HttpStr = "HTTP/1.1 200 OK\r\n";
                    HttpStr +="Date: SUN,10 Feb 2019 03:51:41 GMT\r\n";
                    HttpStr +="Content-type: text/css\r\n";
                    HttpStr +="Connection: keep-alive\r\n";
                    HttpStr +="Keep-Alive: timeout=1\r\n";
                    HttpStr +="Server: zeadboar\r\n";
                    HttpStr +="X-Pingback://webgyry.info/xmlrpc.php\r\n\r\n";

                    query.clear();
                    query.resize(HttpStr.size());
                    copy(HttpStr.begin(), HttpStr.end(), query.begin());
                }

#else
                auto strGET = "/mnt/"+(string)get;
                ReadAllBytes(strGET.c_str(),resultBuf);
#endif
            }




            /////////////
            copy(resultBuf.begin(), resultBuf.end(), std::back_inserter(query));

            size = static_cast<int>(query.size());

            printf("Size responce data : %d\n",size);

            end = clk.now();
            ::send(sock_server_hhtp,query.data(),size,0);

            //cout <<"Time microseconds: \t" << chrono::duration_cast<chrono::microseconds>(end-start).count() << endl;
            cout <<"Request processing took time milliseconds: \t" << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;
            //cout <<"Time seconds: \t" << chrono::duration_cast<chrono::seconds>(end-start).count() << endl;

            break;
        }

#ifdef _WIN32
        closesocket(sock_server_hhtp);
#else
        close(sock_server_hhtp);
#endif

        resultBuf.clear();
        query.clear();

        for(int i=0; i < buf.size();i++)
        {
            buf[i] = '\0';
        }

    }

    return ;
}

void HttpServer::set_dir_exe(string dir)
{
    global_dir_exe = dir;
}

vector<string> HttpServer::split(string str, string token, int count)
{

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
            int index = static_cast<int>(str.find(token));
            if(index != static_cast<int>(string::npos))
            {
                result.push_back(str.substr(0,static_cast<unsigned int>(index)));

                str = str.substr(static_cast<unsigned int>(index)+token.size());
                if(str.size()==0)result.push_back(str);
            }else{
                result.push_back(str);
                str = "";
            }
        }
    }
    return result;

}
