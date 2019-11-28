#include "space.h"

Space::Space()
{
    name = "";
    begin = nullptr;
    parent = nullptr;
}

void Space::push_back(Space* item)
{
    item->begin = begin;
    item->parent = this;
    listSpace.push_back(item);
}

void Space::push_back_variables(map<string, string> key, map<string, string> data)
{
    auto serchVariables = variables.find(key);
    if(serchVariables != variables.end())
    {
        //Данная переменная есть не добавлять
    }
    else
    {
        // данной переменной нет добавить
        variables.insert(make_pair(key,data));
    }


}
