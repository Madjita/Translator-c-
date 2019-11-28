#ifndef SPACE_H
#define SPACE_H

#include "globals.h"

#include <iostream>
#include <map>
#include <list>
#include <vector>

using namespace std;


//Класс отвечающий за область видимости переменных, функций
class Space
{
public:
    Space();

    string name; // название класса  (либо global -- как глобальный объект)


    //Переменная которая хранит номер строки
    //Набор ликсем в <string> и  самих данных <string>
    //map<int,vector<map<string,string>>> map_word_lex; //лексемы слов

    //Переменная которая хранит номер строки
    //Набор ликсем в позиции лексемы и самих данных <string>
    map<int,vector<vector<map<string,LexClass>>>> map_word_lex; //лексемы слов


    Space* begin; // указатель на первый объект являющимся 'global'
    Space* parent; //предыдущее значение у 'globals' = nullptr

    //{
    //имя переменной -ключ
    //тип лексемы в строке - данные
    //} -ключ
    //{
    //имя типа -ключ
    //тип лексемы в строке - данные
    //} -данные типа
    map<map<string,string>,map<string,string>> variables; //массив переменных с информацией о их типе данных

    //ключ - название функции
    //данные  - лист глобальных функций в виде объектов namspace
    //map<map<string,string>,list<Space*>> listSpace; // глобальные функции
    list<Space*> listSpace;

    void push_back(Space *item);
    void push_back_variables(map<string, string> name, map<string, string> type);
};

#endif // SPACE_H
