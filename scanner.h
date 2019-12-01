#ifndef SCANNER_H
#define SCANNER_H




#include "globals.h"
#include "space.h"
#include "str_switch.h"


#include <iostream>
#include <vector>
#include <mutex>
#include <semaphore.h>
#include <condition_variable>
#include <map>
#include <list>
#include <sstream>
#include <iostream>

using namespace std;


class Scanner
{
public:
    Scanner();
    ~Scanner();

    int workLexer(const vector<string> &list);
    bool next(string row_str, unsigned int row);
    map<int,vector<map<LexClass,map<string,string>>>> getMapWorldLex();
    string getLexString();
    vector<string> list_word_lex_string;
    vector<string> countTab; // Количество табуляции в каждой строчке

private:
    void zapolnenieOperationsPriorityForward(vector<string> operands, int priority, int forward);
    void addMapLex(unsigned int row,LexClass lex,string lex_str,string data,int position = 0);
    void replaceLastMapLex(unsigned int row,LexClass lex,string lex_str,string data,int position = 0);

    //Вспомогательная функция
    void addKeyWords(LexClass data, string key); //функция добавления слова в массив Ключевых слов
    void addTypes(LexClass data, string key); //функция добавления слова в массив Типов данных
    bool addWordWords(LexClass data, string key); //функция добавления слова в массив Имен переменных
    bool addWordFunWords(LexClass data, string key);// функция добавления слова в массив Имен функций
    bool addWordIncludes(LexClass data, string key);// функция добавления слова в массив инклудов
    bool addClassWords(LexClass data, string key);// функция добавления слова в массив классов
    string toEnumString(LexClass lex);

    //Пространство имен
    bool addVariable(unsigned int row,string word);
    //Добавить объявленную функцию
    bool addFunClassVariable(unsigned int row,string word);
    //Добавить сложный тип данных
    bool addHardTypeVariable(unsigned int row,string word,string type_template, string type_template_lex);
    bool addNewSpaceFun(int row,string word); // Добавление новой области видимости относительно функций (и ключевых слов)


    bool findTypeData(string key); //Поиск типа данных;
    bool findWordWords(string key); //Поиск имени переменных;
    bool findWordWords(string key,Space* space); //Поиск имени переменных в определенном пространстве имен;
    bool findClassWords(string key); //Поиск имени классов;



    int findLable(string word); //Поиск целого числа, дробного или перменной;



    string getLastlex(unsigned int row);
    string getlex(unsigned int row,unsigned int positionLex);
    string getFirslex(unsigned int row);


    vector<LexClass> list_word_lex_; // лексемы слов
    vector<string> list_word_type_; // массив найденных типов данных
    vector<string> list_word_name_; // массив найденных имен данных


    //map<int,vector<map<int,vector<string>>>> mapOperationsAndPriority;

    map<int,vector<vector<string>>> mapOperationsAndPriority;

    map<int,vector<map<LexClass,map<string,string>>>> map_word_lex; //лексемы слов


    //Типы данных
    map<string,LexClass> types; // массив всех типов данных
    map<string,LexClass> keyWords; // массив ключевых слов


    map<string,LexClass> wordWords;  //Массив имен переменных
    map<string,LexClass> wordFunWords; //Массив имен функций
    map<string,LexClass> wordClassWords; // Массив инклудов
    map<string,LexClass> wordIncludes; // Массив инклудов

    Space spaces; // Переменная глобального пространства имен

    list<Space*> listItemSpaces; // массив  Указателей на объект который сейчас собирается

    Space* itemSpaces; //Указатель на объект который сейчас собирается

    bool flagComment;

 };

#endif // SCANNER_H
