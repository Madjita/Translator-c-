#include "filework.h"



FileWork::FileWork()
{
    backPosition_ =1;
    flagBack_ = false;
    isThreadRunning_ = false;
    dataReadyFlag_ = false;
    pos_ = 0;
    list_result_.clear();

    sem_init(&sem_,0,1);
}

FileWork::~FileWork()
{
    sem_destroy(&sem_);
}



void FileWork::process_start(string FName,bool flagFile)
{

    isThreadRunning_ = true;


    if(flagFile)
    {
        FName_ = FName;
        auto list = split(FName,"\\");
        auto name = *(list.rbegin());
        add_threadOnPull(name,&FileWork::readFile,this);
    }
    else
    {
        FName_ = "stringStreem";
        add_threadOnPull(FName_,&FileWork::readString2,this,FName);
    }


}





void FileWork::readFile(future<bool> stopFlag)
{
    unique_lock<mutex> ulock(currentFlagStartThreadMutex_);

    unsigned int n =0; // позиция конца символа
    char ch=0;  //Это переменная, в которую нужно считывать символы
    string s = "" ;  //Это строка, она в примере будет абзацем
    vector<string> v; //Вектор строк

    //Считаем текст с форматированием
    in_.open(FName_);     //открыли для чтения  файл

    if(!in_.is_open())
    {
            cout << "Don't open file :" <<FName_ <<endl;
            return;
    }

    list_result_.push_back(s);

    bool flag = false;
    bool flag_comment = false;

    while(1)
    {

        if (stopFlag.wait_for(chrono::microseconds(1)) == future_status::ready){
            cout << "thread stopped!\n";
            return;
        }

        ch = in_.get();


        if(ch == EOF)\
        {
            flag = false;
            if(flag == false)
            {
               // list_result_.push_back("");
               // list_result_[n] = s;
               // list_result_list_.push_back(split(list_result_[n]," "));
            }
            break;
        }

        if(flag_comment)
        {
            if(char(ch) == '\n')
            {
                flag_comment = false; //флаг отвечающий за коментарии
            }
            continue;
        }


        flag = false;

        dataReadyFlag_ = true;
        sem_wait(&sem_);
        dataReadyFlag_ = false;

        if(flagBack_ == false)
        {
            pos_ = in_.tellg();
            backPosition_ = 1;
        }
        else
            backPosition_++;


        n = list_result_.size()-1;



        //объяснение ниже
        if (char(ch)!='\n')
        {

            switch (ch)
            {
            case '/':
            {
                if(s.size() > 0)
                {
                    if(s[s.size()-1] == '/')
                    {
                        flag_comment=true;
                        s.pop_back();
                    }
                    else
                    {
                        s +=char(ch);
                    }
                }
                else
                {
                    s +=char(ch);
                }
                continue;
            }
            case '\t':
            {
                if(n > 0)
                {
                    auto sdfsd = list_result_[n].back();
                    if(list_result_[n].back() != ' ')
                    {
                        if(list_result_[n].back() != '\0')
                        {
                           s=s+' ';
                        }
                    }
                }

                break;
            }
            case '{':
            {
                s=s+char(ch);
                break;
            }
            case ';':
            {
                if(n > 0)
                {
                    if(list_result_[n].back() != ' ')
                    {
                       s=s+' ';
                    }
                }
                s=s+char(ch);
                break;
            }
            case ' ':
            {
                if(n >= 0)
                {
                    switch (list_result_[n].back())
                    {
                    case ',':
                    case '<':
                    case '>':
                    case ' ':
                    case '=':
                    case '+':
                    case '(':
                    case ')':
                    case '[':
                    case ']':
                    case '*':
                        //не записывать символ
                        break;
                    default:
                        s=s+char(ch);

                        //убираем первый пробел
                        if(s == " ")
                        {
                            s = "";
                        }
                        break;
                    }
                }
                break;
            }
            case '<':
            case '>':
            case '+':
            case '=':
            case ')':
            case '[':
            case ']':
            case '&':
            case '*':
            {
                if(n > 0)
                {
                    switch (list_result_[n].back())
                    {
                    case ' ':
                        s.erase(s.end()-1);
                        break;
                    }
                }
                s=s+char(ch);
                break;
            }
            default:
            {

                if(n > 0)
                {
                    switch (list_result_[n].back())
                    {
                    case '*':
                    case '&':
                        s=s+' ';
                        break;
                    }
                }


                s=s+char(ch);  //Считываем символ из файла и сразу проверяем его на признак переноса строки.
                break;
            }
            }

            if(n > 0)
            {
                list_result_[n] = s;
            }
        }
        else
        {
            flag_comment = false; //флаг отвечающий за коментарии

            if(n < 0)
            {
                list_result_.push_back(s);

            }
            //v.push_back(s); //Если текущий символ перенос, то записываем строку в вектор

            if(n < 0)
            {

            }
            else
            {
                list_result_[n] = s;
                list_result_list_.push_back(split(list_result_[n]," "));

                if(list_result_[n].size() == 0)
                {
                    list_result_.erase(list_result_.end());
                    list_result_list_.erase(list_result_list_.end());
                }
            }

            if(list_result_.size() >= 1)
            {
                list_result_.push_back("");
            }

            flag = true;

            s.clear(); //Очищаем строку
        }



       // cout<< "s = " << s <<endl;

       // sem_post(&sem_);

    }

    //sem_post(&sem_);
    in_.close(); //Закрываем файл

    isThreadRunning_ = false;

    return ;
}

void FileWork::readString2(string FName, future<bool> stopFlag)
{

}

void FileWork::readString(string fileData) //,future<bool> stopFlag
{
    unsigned int n =0; // позиция конца символа
    char ch=0;  //Это переменная, в которую нужно считывать символы
    string s = "";  //Это строка, она в примере будет абзацем
    vector<string> v; //Вектор строк

    list_result_.push_back(s);

    bool flag = false;
    bool flag_comment = false;

    for(int i = 0 ; i < fileData.size();i++)
    {


        ch = fileData[i];


        if(ch == EOF)
        {
            flag = false;
            if(flag == false)
            {
               // list_result_.push_back("");
               // list_result_[n] = s;
               // list_result_list_.push_back(split(list_result_[n]," "));
            }
            break;
        }

        if(flag_comment)
        {
            if(char(ch) == '\n')
            {
                flag_comment = false; //флаг отвечающий за коментарии
            }
            continue;
        }


        flag = false;

        dataReadyFlag_ = true;
        //sem_wait(&sem_);
        dataReadyFlag_ = false;

        if(flagBack_ == false)
        {
            pos_ = in_.tellg();
            backPosition_ = 1;
        }
        else
            backPosition_++;


        n = list_result_.size()-1;


        if(ch  == '\r')
        {
            continue;
        }

        //объяснение ниже
        if (ch !='\n')
        {

            switch (ch)
            {
            case '/':
            {
                if(s.size() > 0)
                {
                    if(s[s.size()-1] == '/')
                    {
                        flag_comment=true;
                        s.pop_back();
                    }
                    else
                    {
                        s +=char(ch);
                    }
                }
                else
                {
                    s +=char(ch);
                }
                continue;
            }
            case '\t':
            {
                if(n > 0)
                {
                    auto sdfsd = list_result_[n].back();
                    if(list_result_[n].back() != ' ')
                    {
                        if(list_result_[n].back() != '\0')
                        {
                           s=s+' ';
                        }
                    }
                }

                break;
            }
            case '{':
            {
                s=s+char(ch);
                break;
            }
            case ';':
            {
                if(n > 0)
                {
                    if(list_result_[n].back() != ' ')
                    {
                       s=s+' ';
                    }
                }
                s=s+char(ch);
                break;
            }
            case ' ':
            {
                if(n >= 0)
                {
                    switch (list_result_[n].back())
                    {
                    case ',':
                    case '<':
                    case '>':
                    case ' ':
                    case '=':
                    case '+':
                    case '(':
                    case ')':
                    case '[':
                    case ']':
                    case '*':
                        //не записывать символ
                        break;
                    default:
                        s=s+char(ch);

                        //убираем первый пробел
                        if(s == " ")
                        {
                            s = "";
                        }
                        break;
                    }
                }
                break;
            }
            case '<':
            case '>':
            case '+':
            case '=':
            case ')':
            case '[':
            case ']':
            case '&':
            case '*':
            {
                if(n > 0)
                {
                    switch (list_result_[n].back())
                    {
                    case ' ':
                        s.erase(s.end()-1);
                        break;
                    }
                }
                s=s+char(ch);
                break;
            }
            default:
            {

                if(n > 0)
                {
                    switch (list_result_[n].back())
                    {
                    case '*':
                    case '&':
                        s=s+' ';
                        break;
                    }
                }


                s=s+char(ch);  //Считываем символ из файла и сразу проверяем его на признак переноса строки.
                break;
            }
            }

            if(n > 0)
            {
                list_result_[n] = s;
            }
        }
        else
        {
            flag_comment = false; //флаг отвечающий за коментарии

            if(n < 0)
            {
                list_result_.push_back(s);

            }
            //v.push_back(s); //Если текущий символ перенос, то записываем строку в вектор

            if(n < 0)
            {

            }
            else
            {
                list_result_[n] = s;
                list_result_list_.push_back(split(list_result_[n]," "));

                if(list_result_[n].size() == 0)
                {
                    list_result_.erase(list_result_.end());
                    list_result_list_.erase(list_result_list_.end());
                }
            }

            if(list_result_.size() >= 1)
            {
                list_result_.push_back("");
            }

            flag = true;

            s.clear(); //Очищаем строку
        }

    }


    //
    isThreadRunning_ = false;

    return ;
}

void FileWork::seekgNext()
{
    in_.seekg(pos_,std::ios::beg);
}

void FileWork::seekgBack()
{
    int new_position = static_cast<int>(pos_)-backPosition_;
    in_.seekg(new_position,std::ios::beg);
}


vector<string> FileWork::getResult()
{
    lock_guard<mutex> guard(mtx);
    return list_result_;
}

vector<vector<string>> FileWork::getResult_list()
{
    lock_guard<mutex> guard(mtx);
    return list_result_list_;
}

void FileWork::Next()
{
    sem_post(&sem_);
}

bool FileWork::getCurrentWorkFlag()
{
    return dataReadyFlag_;
}

bool FileWork::getIsOpenFile()
{
    return in_.is_open();
}


