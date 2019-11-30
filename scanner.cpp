#include "Scanner.h"

//// Записываем новое имя в переменную
#define ENUM_TO_STR(ENUM) std::string(#ENUM)



Scanner::Scanner()
{
    vector<vector<string>> forwardOperends;
    forwardOperends.push_back({}); // без навправления
    forwardOperends.push_back({}); // левый
    forwardOperends.push_back({}); // правый
    vector<string> operands = {"::","[]","()",".","->"};
    zapolnenieOperationsPriorityForward(operands,16,2);
    operands = {"++","--"};
    zapolnenieOperationsPriorityForward(operands,15,1);
    operands = {"++","--","sizeof","sizeof()","^","!","-","+","&","*","new","new []","delete","delete []"};
    zapolnenieOperationsPriorityForward(operands,14,1);
    operands = {"(type)","casting"};
    zapolnenieOperationsPriorityForward(operands,14,0);
    operands = {"*","/","%"};
    zapolnenieOperationsPriorityForward(operands,13,2);
    operands = {"+","-"};
    zapolnenieOperationsPriorityForward(operands,12,2);
    operands = {">>","<<"};
    zapolnenieOperationsPriorityForward(operands,11,2);
    operands = {"<","<=",">",">="};
    zapolnenieOperationsPriorityForward(operands,10,2);
    operands = {"==","!="};
    zapolnenieOperationsPriorityForward(operands,9,2);
    operands = {"&"};
    zapolnenieOperationsPriorityForward(operands,8,2);
    operands = {"^"};
    zapolnenieOperationsPriorityForward(operands,7,2);
    operands = {"|"};
    zapolnenieOperationsPriorityForward(operands,6,2);
    operands = {"&&"};
    zapolnenieOperationsPriorityForward(operands,5,2);
    operands = {"||"};
    zapolnenieOperationsPriorityForward(operands,4,2);
    operands = {"?:"};
    zapolnenieOperationsPriorityForward(operands,3,1);
    operands = {"=","*=","/=","%=","+=","-=","<<=",">>=","&=","^=","|=","throw"};
    zapolnenieOperationsPriorityForward(operands,2,1);
    operands = {","};
    zapolnenieOperationsPriorityForward(operands,1,2);


    //Ключевые слова
    addKeyWords(keyASM,"asm");
    addKeyWords(keyAUTO,"auto");
    addKeyWords(keyBREAK,"break");
    addKeyWords(keyCASE,"case");
    addKeyWords(keyCATCH,"catch");
    addKeyWords(keyCHAR,"char");
    addKeyWords(keyCLASS,"class");
    addKeyWords(keyCONST,"const");
    addKeyWords(keyCONTINUE,"continue");
    addKeyWords(keyCONSTEXPR,"constexpr");
    addKeyWords(keyDEFAULT,"default");
    addKeyWords(keyDELETE,"delete");
    addKeyWords(keyDO,"do");
    addKeyWords(keyDOUBLE,"double");
    addKeyWords(keyELSE,"else");
    addKeyWords(keyENUM,"enum");
    addKeyWords(keyEXPLICIT,"explicit");
    addKeyWords(keyEXTERN,"extern");
    addKeyWords(keyFLOAT,"float");
    addKeyWords(keyFOR,"for");
    addKeyWords(keyFRIEND,"friend");
    addKeyWords(keyGOTO,"goto");
    addKeyWords(keyIF,"if");
    addKeyWords(keyINLINE,"inline");
    addKeyWords(keyINT,"int");
    addKeyWords(keyLONG,"long");
    addKeyWords(keyMUTABLE,"mutable");
    addKeyWords(keyNEW,"new");
    addKeyWords(keyOPERATOR,"operator");
    addKeyWords(keyPRIVATE,"private");
    addKeyWords(keyPROTECTED,"protected");
    addKeyWords(keyPUBLIC,"public");
    addKeyWords(keyREGISTER,"register");
    addKeyWords(keyRETURN,"return");
    addKeyWords(keySHORT,"short");
    addKeyWords(keySIGNED,"signed");
    addKeyWords(keySIZEOF,"sizeof");
    addKeyWords(keySTATIC,"static");
    addKeyWords(keySTRUCT,"struct");
    addKeyWords(keySWITCH,"switch");
    addKeyWords(keyTEMPLATE,"template");
    addKeyWords(keyTHIS,"this");
    addKeyWords(keyTRY,"try");
    addKeyWords(keyTHROW,"throw");
    addKeyWords(keyTYPEDEF,"typedef");
    addKeyWords(keyTYPENAME,"typename");
    addKeyWords(keyTRUE,"true");
    addKeyWords(keyFALSE,"false");
    addKeyWords(keyUNION,"union");
    addKeyWords(keyUNSIGNED,"unsigned");
    addKeyWords(keyVIRTUAL,"virtual");
    addKeyWords(keyVOID,"void");
    addKeyWords(keyVOLATILE,"volatile");
    addKeyWords(keyWHILE,"while");
    addKeyWords(keyBOOL,"bool");
    addKeyWords(keyNULLPTTR,"nullptr");
    addKeyWords(keyNAMESPACE,"namespace");
    addKeyWords(keySTATIC_CAST,"static_cast");
    addKeyWords(keyUSING,"using");



    //Массив типов данных
    addTypes(keyVOID,"void");
    addTypes(keyBOOL,"bool");
    addTypes(keyCHAR,"char");
    addTypes(keyINT,"int");
    addTypes(keyFLOAT,"float");
    addTypes(keyDOUBLE,"double");

    addTypes(lcType,"string");
    addTypes(lcType,"list");
    addTypes(lcType,"map");


    spaces.name = "global";
    spaces.begin = &spaces;

    itemSpaces = spaces.begin;

    //Массив хранит в себе объект который будет собираться
    listItemSpaces.push_back(itemSpaces); //может не понадобиться
}

//Разбор строк на лексемы
int Scanner::workLexer(const vector<string> &list)
{

    unsigned int row =0;

    while(next(list[row],row))
    {
        if(row < list.size()-1)
        {
            row++;
        }
        else {
            break;
        }

    }

    cout << "Scanner finished work"<<endl;

    cout << "Create list lexems"<<endl;
    list_word_lex_string.clear();
    //идем по строчно
    for(int i=0; i < map_word_lex.size();i++)
    {
        auto vector_lex = map_word_lex.find(i)->second;

        //идем по вектору лексем
        for(int j=0; j < vector_lex.size();j++)
        {
            //идем по лексемам
            for(auto& item_lex : vector_lex[j])
            {
                //идем по значениям
                for(auto& item_data : item_lex.second)
                {
                    list_word_lex_string.push_back(item_data.first);
                }
            }
        }
    }
    cout << "List lexems finished work"<<endl;

    return 0;
}

bool Scanner::next(string row_str, unsigned int row)
{
    auto search =map_word_lex.find(row);

    if(search == map_word_lex.end())
    {
        vector<map<LexClass,map<string,string>>> vector_lex;
        map_word_lex.insert(make_pair(row,vector_lex));
    }



    string word = "";
    char ch;
    string s2 = row_str;
    string type_template = "";
    string type_template_lex = "";

    bool flag_lcQuotes = false;
    //bool flag_addClassFun = false;


    for (unsigned int i=0;i < row_str.size();i++)
    {

        ch = row_str[i];

        ////////

        switch (ch)
        {
        case ' ':
        {

            if(flag_lcQuotes)
            {
                continue;
            }

            if(word.size() == 0)
            {
                word ="";
                continue;
            }

            if(type_template.size() >0)
            {

                addHardTypeVariable(row,word,type_template,type_template_lex);
                type_template = "";
                type_template_lex = "";
                word ="";
                continue;
            }

            if(word == "include")
            {
                addMapLex(row,lcInclude,toEnumString(lcInclude),word);
                s2.erase(0,i);

                s2.erase(0,1);
                s2.erase(s2.size()-1,s2.size());
                addWordIncludes(lcInclude,s2);

                addMapLex(row,lcInclude,s2,s2);
                word ="";
                return true;
            }


            bool ok = false;
            //это ключевое слово ?
            auto searchKey =keyWords.find(word);
            if(searchKey != keyWords.end())
            {
                //Найденное ключевое слово является ли типом данных ?
                ok = findTypeData(searchKey->first);

                if(ok) // Это тип данных
                {
                    // Это ключевое слово и тип данных
                    addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);

                    word ="";
                    continue;
                }
                else {
                    //Это не тип данных
                    addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);
                    word ="";
                    continue;
                }
            }
            else
            {
                //Это не ключевое слово

                // Это тип данных ?
                ok = findTypeData(word);
                if(ok) // Это тип данных
                {
                    auto searchType = types[word];
                    addMapLex(row,searchType,toEnumString(searchType),word);
                    word ="";
                    continue;
                }
                else {
                    //Это не тип данных


                    // Есть ли предыдущие лексемы ?
                    if(map_word_lex.at(row).size() > 0)
                    {
                        //Это имя переменной ?
                        //Предыдущая ликсема является типом данных?

                        auto firstLex = getFirslex(row);

                        if(firstLex == "typedef")
                        {
                            //Данная переменная является новым типом данных
                            //Проверка на переменную имени класса
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                            addTypes(lcLabel,word);
                            word ="";
                            continue;
                        }

                        if(firstLex == "using")
                        {
                            auto lastLex = getLastlex(row);

                            if(lastLex == "namespace")
                            {
                                //Данная переменная является новым типом данных
                                //Проверка на переменную имени класса
                                addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                                addTypes(lcLabel,word);
                                word ="";
                                continue;
                            }

                        }


                        auto lastLex = getLastlex(row);


                        if(lastLex == "class")
                        {
                            //Проверка на переменную имени класса
                            addMapLex(row,lcLabelClass,toEnumString(lcLabelClass),word);
                            addClassWords(lcLabelClass,word);
                            word ="";
                            continue;
                        }

                        if(row,map_word_lex.at(row).size() > 2)
                        {
                            auto lexPosition = getlex(row,map_word_lex.at(row).size()-2);
                            if(lexPosition == "=" && lastLex == "*")
                            {
                                //Перед именем переменной стоит указатель разыминовывания
                                //Значит данное значение скороее всего Имя переменоой
                                addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                                word ="";
                                continue;
                            }
                        }


                        ok = findTypeData(lastLex);
                        if(ok)
                        {
                            //Предыдущее значчение является типом
                            //Значит данное значение скороее всего Имя переменоой

                            //Новое
                            //Проверить в текущем объекте простарнства имен на существование переменной
                            bool findWord = false; // флаг объявленна ли переменная
                            for(auto item : itemSpaces->variables)
                            {
                                //написать проверку на меременную
                                auto nameWord = item.first.begin()->second;
                                if(word == nameWord)
                                {
                                    //Значит дананя переменная уже есть
                                    findWord = true;
                                    //Значит дананя переменная уже есть
                                    //Так как мы были в '=' значит ошибка присваения
                                    cout<<endl;
                                    cout <<"Row["<<row<<"] ) ERROR : Redeclaring a declared variable = '" <<word<<"'"<<endl;
                                    cout<<endl;
                                    return false;
                                }
                            }
                            if(findWord)
                            {
                                //Переменная существует в списке объявлений

                                //Проверить не логические ли происходят с переменной ?
                                //Ошибка обявлениия переменной второй раз
                                //Error
                            }
                            else
                            {
                                //Переменная не существует в списке объявлений
                                //Проверить не логические ли происходят с переменной ?

                                //Так как мы нашли равенство то добать переменную в область видимости
                                //Значит данное значение скороее всего Имя переменоой
                                addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                                auto item = map_word_lex.at(row);
                                auto itemType = item.begin()->begin()->second;
                                auto itemName = item[item.size()-1].begin()->second;
                                itemSpaces->push_back_variables(itemName,itemType);
                            }


                            //Старое
//                            ok = addWordWords(lcLabel,word); // добавили переменную в массив переменных
//                            if(ok)
//                                cout << "Add WordWords : " << word<<endl;
//                            else
//                                cout << "Don't add WordWords : " << word<<endl;
                        }
                        else {
                            //Предыдущее значчение не является типом

                            auto lable = findLable(word);

                            switch (lable)
                            {
                            case 0:
                            {
                                ok = false;
                                //Это обявленная переменная?
                                ok = findWordWords(word,itemSpaces);
                                if(ok)
                                {
                                    //да
                                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                                }
                                else {

                                    cout <<endl;
                                    //Это тип данных?
                                    ok = findTypeData(word);
                                    if(ok)
                                    {
                                        addMapLex(row,lcType,toEnumString(lcType),word);
                                    }
                                    else
                                    {
                                        //ПРоверить слишком много проверок на типы данных

                                        //Добавить в пространство имен
                                        addVariable(row,word);




                                        //addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                                        //addWordWords(lcLabel,word); // добавили тип данных в массив переменных
                                        word ="";
                                        continue;
                                    }

                                }
                                break;
                            }
                            case 1: //Целое число
                                addMapLex(row,kwINT,toEnumString(kwINT),word);
                                break;
                            case -1: //Дробное
                                addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                                break;
                            }

                        }
                    }
                    else {
                        //Предыдущих лексем нет то
                        //Значит данное значение скороее всего Имя переменоой
                        addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        ok = addWordWords(lcLabel,word); // добавили переменную в массив переменных
//                        if(ok)
//                            cout << "Add WordWords : " << word<<endl;
//                        else
//                            cout << "Don't add WordWords : " << word<<endl;

                    }

                    word ="";
                    continue;
                }

            }
            break;
        }
        case ';':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            //Нужно для того чтобы вернуться на последний элимент из списка
            itemSpaces = listItemSpaces.back();



            addMapLex(row,lcSemicolon,toEnumString(lcSemicolon),";");
            word ="";
            continue;
            break;
        }
        case '+':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            bool ok = false;

            if(word.size() > 0)
            {
                //Есть значение
                //Является ли слово объявленной именем переменной?
                ok = findWordWords(word);
                if(ok)
                {
                    //Значит данное значение скороее всего Имя переменоой
                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                }
                else
                {

                    //Является ли числом ?

                    auto lable = findLable(word);

                    switch (lable)
                    {
                    case 0:
                    {
                        ok = false;
                        //Это обявленная переменная?
                        ok = findWordWords(word);
                        if(ok)
                        {
                            //да
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        else {
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        break;
                    }
                    case 1: //Целое число
                        addMapLex(row,kwINT,toEnumString(kwINT),word);
                        break;
                    case -1: //Дробное
                        addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                        break;
                    }


                }
            }
            addMapLex(row,lcPlus,toEnumString(lcPlus),"+");
            word ="";
            continue;
            break;
        }
        case '-':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            bool ok = false;

            if(word.size() > 0)
            {
                //Есть значение
                //Является ли слово объявленной именем переменной?
                ok = findWordWords(word);
                if(ok)
                {
                    //Значит данное значение скороее всего Имя переменоой
                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                }
                else
                {
                    //Является ли числом ?

                    auto lable = findLable(word);

                    switch (lable)
                    {
                    case 0:
                    {
                        ok = false;
                        //Это обявленная переменная?
                        ok = findWordWords(word);
                        if(ok)
                        {
                            //да
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        else {
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        break;
                    }
                    case 1: //Целое число
                        addMapLex(row,kwINT,toEnumString(kwINT),word);
                        break;
                    case -1: //Дробное
                        addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                        break;
                    }
                }
            }
            addMapLex(row,lcMinus,toEnumString(lcMinus),"-");
            word ="";
            continue;
            break;
        }
        case '%':
        {

            if(flag_lcQuotes)
            {
                continue;
            }

            if(word.size() >0)
            {

                // Это тип данных ?
                bool ok = findTypeData(word);
                if(ok) // Это тип данных
                {
                    auto searchType = types.find(word);
                    // Это тип данных
                    addMapLex(row,searchType->second,toEnumString(searchType->second),searchType->first);
                }
                else {
                    //Это не тип данных

                    //Есть значение
                    //Является ли слово объявленной именем переменной?
                    ok = findWordWords(word);
                    if(ok)
                    {
                        //Значит данное значение скороее всего Имя переменоой
                        addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                    }
                    else
                    {

                        //Является ли числом ?

                        auto lable = findLable(word);

                        switch (lable)
                        {
                        case 0:
                        {
                            ok = false;
                            //Это обявленная переменная?
                            ok = findWordWords(word);
                            if(ok)
                            {
                                //да
                                addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                            }
                            else {
                                addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                            }
                            break;
                        }
                        case 1: //Целое число
                            addMapLex(row,kwINT,toEnumString(kwINT),word);
                            break;
                        case -1: //Дробное
                            addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                            break;
                        }


                    }
                }

            }

            addMapLex(row,lcPercent,toEnumString(lcPercent),"*");
            word ="";
            continue;
            break;
        }
        case '=':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            bool ok = false;

            if(word.size() > 0)
            {
                //Есть значение
                //Является ли слово объявленной именем переменной?
                //Новыя проверка на объявление переменной

                // Есть ли предыдущие лексемы ?
                if(map_word_lex.at(row).size() > 0)
                {

                    //Проверить в текущем объекте простарнства имен на существование переменной
                    bool findWord = false; // флаг объявленна ли переменная
                    for(auto item : itemSpaces->variables)
                    {

                        //написать проверку на меременную
                        auto nameWord = item.first.begin()->second;
                        if(word == nameWord)
                        {
                            //Значит дананя переменная уже есть
                            findWord = true;
                            //Значит дананя переменная уже есть
                            break;

                        }
                    }
                    if(findWord)
                    {

                        //Переменная существует в списке объявлений
                        addMapLex(row,lcLabel,toEnumString(lcLabel),word);

                        auto firstLex= getFirslex(row);

                        if(firstLex == "*")
                        {
                            //Разименование объекта
                            //Переменная существует в списке объявлений
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                            word ="";
                            continue;
                        }

                        //Проверить не логические ли происходят с переменной ?
                        //Чем является следующий символ?
                        switch (s2[i+1])
                        {
                        case '=':
                            //Условие равнества
                            addMapLex(row,lcEqual,toEnumString(lcEqual),"==");
                            word ="";
                            continue;
                        default:
                            {
                                //Так как мы были в '=' значит ошибка присваения
                                cout<<endl;
                                cout <<"Row["<<row<<"] ) ERROR : Redeclaring a declared variable = '" <<word<<"'"<<endl;
                                cout<<endl;
                                return false;
                                break;
                            }
                        }

                        //Не является булевым вырожением


                        //Ошибка обявлениия переменной второй раз
                        //Error
                    }
                    else
                    {
                        //Переменная не существует в списке объявлений
                        //Проверить не логические ли происходят с переменной ?

                        //Так как мы нашли равенство то добать переменную в область видимости
                        //Значит данное значение скороее всего Имя переменоой
                        addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        auto item = map_word_lex.at(row);
                        auto itemType = item.begin()->begin()->second;
                        auto itemName = item[item.size()-1].begin()->second;
                        itemSpaces->push_back_variables(itemName,itemType);
                    }
                }
                else
                {
                       //Нет предыдущих лексем , но есть даннаые (наверняка это переменная )

                        //Проверка на число либо переменную
                       auto lable = findLable(word);
                       switch (lable)
                       {
                       case 0:
                       {
                           ok = false;
                           //Это обявленная переменная в данном пространстве имен?
                           ok = findWordWords(word,itemSpaces);
                           if(ok)
                           {
                               //да
                               addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                           }
                           else
                           {
                                cout << "Error :" << word << " Don't currect Label."<<endl;
                                word ="";
                                continue;
                           }
                           break;
                       }
                       case 1: //Целое число
                           cout << "Error :" << word << " Don't currect Label. It is INT"<<endl;
                           break;
                       case -1: //Дробное
                           cout << "Error :" << word << " Don't currect Label. It is FLOAT"<<endl;
                           break;
                       }
                }

            }

            // Есть ли предыдущие лексемы ?
            if(map_word_lex.at(row).size() > 0)
            {
                //Если предыдущее было имя переменной, то это присваивание
                //Предыдущая ликсема является ли именем переменной?
                auto lastLex = getLastlex(row);
                ok = findWordWords(lastLex);
                if(ok)
                {
                    //Предыдущее значчение является именем переменной
                    //Значит данное значение скороее всего Присваивание
                    addMapLex(row,lcAssign,toEnumString(lcAssign),"=");
                }
                else {
                    //Предыдущее значчение не является именем переменной

                    switch (lastLex[0])
                    {
                    case '=':
                        //Условие равнества
                        replaceLastMapLex(row,lcEqual,toEnumString(lcEqual),"==");
                        break;
                    case '!':
                        //условие не равнества
                        replaceLastMapLex(row,lcNotEqual,toEnumString(lcNotEqual),"!=");
                        break;
                    case '>':
                        //Больше равно
                        replaceLastMapLex(row,lcLargerEQ,toEnumString(lcLargerEQ),">=");
                        break;
                    case '<':
                        //меньше равно
                        replaceLastMapLex(row,lcSmallerEQ,toEnumString(lcSmallerEQ),"<=");
                        break;
                    default:
                        addMapLex(row,lcAssign,toEnumString(lcAssign),"=");
                        break;
                    }

                }
            }
            else {
                //Предыдущих лексем нет то
                //Значит Есть только '=' а это ошибка
                //error
            }

            word ="";
            continue;
            break;
        }
        case '>':
        {

            if(flag_lcQuotes)
            {
                continue;
            }

            bool ok = false;

            if(word.size() > 0)
            {
                //Есть значение
                //Является ли слово объявленной именем переменной?
                ok = findWordWords(word);
                if(ok)
                {
                    //Значит данное значение скороее всего Имя переменоой
                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                }
                else
                {
                    //Предыдущее значчение не является именем переменной

                    auto lable = findLable(word);
                    switch (lable)
                    {
                    case 0:
                    {
                        ok = false;
                        //Это обявленная переменная?
                        ok = findWordWords(word);
                        if(ok)
                        {
                            //да
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        else {

                            //Подумать что делать если это не обявленная переменная
                            //Пока что определять как тип данных
                            addMapLex(row,lcType,toEnumString(lcType),word);
                            type_template+=word+">"; //Собираем сложнй тип данных
                            type_template_lex+=toEnumString(lcType)+" "+toEnumString(lcLarger)+" ";
                        }
                        break;
                    }
                    case 1: //Целое число
                        addMapLex(row,kwINT,toEnumString(kwINT),word);
                        break;
                    case -1: //Дробное
                        addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                        break;
                    }
                }
            }
            else
            {
                if(type_template.size() > 0)
                {
                    type_template+=">"; //Собираем сложнй тип данных
                    type_template_lex+=toEnumString(lcLarger);
                }
            }


            // Есть ли предыдущие лексемы ?
            if(map_word_lex.at(row).size() > 0)
            {
                //Если предыдущее было имя переменной, то это присваивание
                //Предыдущая ликсема является ли именем переменной?
                auto lastLex = getLastlex(row);
                ok = findWordWords(lastLex);
                if(ok)
                {
                    //Предыдущее значчение является именем переменной
                    // Значит скорее всего это побитовая операция илл
                }
                else {
                    //Предыдущее значчение не является именем переменной

                    switch (lastLex[0])
                    {
                    case '-':
                        //Условие равнества
                        replaceLastMapLex(row,lcLink,toEnumString(lcLink),"->");
                        word ="";
                        continue;
                        break;
                    }

                }
            }
            else {
                //Предыдущих лексем нет то
                //Значит Есть только '>' а это ошибка
                //error
            }



            addMapLex(row,lcLarger,toEnumString(lcLarger),">");
            word ="";
            continue;
            break;
        }
        case '<':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            if(word == "include")
            {
                addMapLex(row,lcInclude,toEnumString(lcInclude),word);


                s2.erase(0,i);

                s2.erase(0,1);
                s2.erase(s2.size()-1,s2.size());
                addWordIncludes(lcInclude,s2);

                addMapLex(row,lcInclude,s2,s2);
                word ="";
                return true;
            }

            if(word.size() > 0)
            {
                //Проверка на ключевое слово
                //это ключевое слово ?
                auto searchKey =keyWords.find(word);
                if(searchKey != keyWords.end())
                {
                    //Найденное ключевое слово
                    addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);
                }
                else
                {
                    bool ok = false;

                    // Есть ли предыдущие лексемы ?
                    if(map_word_lex.at(row).size() > 0)
                    {
                        string lastLex = getLastlex(row);
                        string firstLex = getFirslex(row);

                        if(firstLex == "for")
                        {
                            //Значит сдесь условие
                            auto lable = findLable(word);
                            switch (lable)
                            {
                            case 0: //Переменная
                                addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                                break;
                            case 1: //Целое число
                                addMapLex(row,kwINT,toEnumString(kwINT),word);
                                break;
                            case -1: //Дробное
                                addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                                break;
                            }

                        }
                        else
                        {
                            if(lastLex == "const")
                            {
                                //Значит данное значение скороее всего тип данных
                                addMapLex(row,lcType,toEnumString(lcType),word);
                                addTypes(lcType,word);
                            }
                            else
                            {

                                //Есть значение
                                //Является ли слово объявленной именем переменной?
                                ok = findWordWords(word);
                                if(ok)
                                {
                                    //Значит данное значение скороее всего Имя переменоой
                                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                                }
                                else
                                {
                                    //Предыдущее значчение не является именем переменной

                                    auto lable = findLable(word);
                                    switch (lable)
                                    {
                                    case 0:
                                    {
                                        ok = false;
                                        //Это обявленная переменная?
                                        ok = findWordWords(word);
                                        if(ok)
                                        {
                                            //да
                                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                                        }
                                        else {

                                            //Выдать исключение на не объявленную пременную
                                            //Пока что считать типом данных
                                            addMapLex(row,lcType,toEnumString(lcType),word);
                                            type_template+=word+"<"; //Собираем сложнй тип данных
                                            type_template_lex+=toEnumString(lcType)+" "+toEnumString(lcSmaller)+" ";
                                        }
                                        break;
                                    }
                                    case 1: //Целое число
                                        addMapLex(row,kwINT,toEnumString(kwINT),word);
                                        break;
                                    case -1: //Дробное
                                        addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {

                        //Значит данное значение скороее всего тип данных
                        addMapLex(row,lcType,toEnumString(lcType),word);
                        type_template+=word+"<"; //Собираем сложнй тип данных
                        type_template_lex+=toEnumString(lcType)+" "+toEnumString(lcSmaller)+" ";
                        //addTypes(lcType,word);
                    }
                }

            }

            addMapLex(row,lcSmaller,toEnumString(lcSmaller),"<");
            word ="";
            continue;
            break;
        }
        case '(':
        {

            if(flag_lcQuotes)
            {
                continue;
            }

            if(word.size() == 0)
            {
                addMapLex(row,lcLCircle,toEnumString(lcLCircle),"(");
                word ="";
                continue;
            }

            bool ok = false;
            // Есть ли предыдущие лексемы ?
            if(map_word_lex.at(row).size() > 0)
            {
                //это ключевое слово ?
                auto searchKey =keyWords.find(word);
                if(searchKey != keyWords.end())
                {
                    addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);
                }
                else
                {
                    //Это не ключевое слово



                    //                    string searchFist = getLastlex(row);

                    //                    if(searchFist == "+" || searchFist == "-" || searchFist == "*" || searchFist == "/" || searchFist == "%")
                    //                    {
                    //                        addMapLex(row,lcLCircle,toEnumString(lcLCircle),"(");
                    //                        word ="";
                    //                        continue;
                    //                    }



                    //Слово является именм функции?
                    addMapLex(row,lcFunLabel,toEnumString(lcFunLabel),word);
                    addFunClassVariable(row,word);

                    addWordFunWords(lcFunLabel,word);
                }
            }
            else {
                //Предыдущих лексем нет то
                //Значит в строке Есть только '(' а это ошибка
                //error


                //Проверка на ключевое слово
                //это ключевое слово ?
                auto searchKey =keyWords.find(word);
                if(searchKey != keyWords.end())
                {
                    //Найденное ключевое слово
                    SWITCH(searchKey->first)
                    {
                        CASE("for"):
                        {
                            addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);

                            //Добавить пространство имен for
                            addFunClassVariable(row,searchKey->first);
                            listItemSpaces.push_back(itemSpaces);
                            break;
                        }
                        DEFAULT:
                        addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);
                        break;
                    }



                }
                else
                {
                    //Происходит вызов функции в одну строчку

                    //Является ли данная фунция объявлением функции в нутри класса?
                    addMapLex(row,lcFunLabel,toEnumString(lcFunLabel),word);

                    //Находимся ли мы в пространстве имен объявления класса?
                    auto serchClassType = types.find(itemSpaces->name);
                    if(serchClassType != types.end())
                    {
                        //Да находимся в объявлении класса значит сдесь объявление функций
                        //Добавить данную функцию в список функций:
                        addFunClassVariable(row,word);

                    }
                }

            }

            addMapLex(row,lcLCircle,toEnumString(lcLCircle),"(");
            word ="";
            continue;

            break;
        }
        case ',':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            bool ok = false;
            if(word.size() > 0)
            {

                // Есть ли предыдущие лексемы ?
                if(map_word_lex.at(row).size() > 0)
                {

                    if(map_word_lex.at(row).size() > 3)
                    {
                        //Если 1,2 позиция есть объявление функции то
                        auto item2 =map_word_lex.at(row)[1].begin()->first;
                        auto item3 =map_word_lex.at(row)[2].begin()->first;
                        if((item2 == lcFunLabel && item3 == lcLCircle) || (item2 == lcLabelClass && item3 == lcColon))
                        {

                            auto nameFun = map_word_lex.at(row)[1].begin()->second.rbegin()->second;
                            //Проверка на есть ли у этой функции аргументы
                            if(nameFun != itemSpaces->name)
                            {
                                //Нужно создать объект Space и добавить пространсто имен
                                Space* newSpace = new Space;
                                newSpace->name = nameFun;
                                //Добавить в объект который собирается функцию и вернуть указатель на новый объект который нужно собирать
                                itemSpaces->push_back(newSpace);
                                itemSpaces = newSpace;
                                listItemSpaces.push_back(itemSpaces);
                            }
                            else
                            {
                                if(type_template.size() > 0 )
                                {
                                    if(type_template.back() == '>' && word.size() > 0)
                                    {
                                        //Добавить переменную с новым типом
                                        //Новое
                                        //Проверить в текущем объекте простарнства имен на существование переменной
                                        addHardTypeVariable(row,word,type_template,type_template_lex);
                                        type_template = "";
                                        type_template_lex = "";
                                        word ="";
                                        continue;


                                        //Проверить нижний код (заглушка на время)
//                                        addMapLex(row,lcComma,toEnumString(lcComma),",");
//                                        word ="";
//                                        continue;
                                    }
                                    type_template+=word+",";
                                    type_template_lex+=toEnumString(lcType)+" "+toEnumString(lcComma)+"";
                                    //Проверить нижний код (заглушка на время)
                                    addMapLex(row,lcComma,toEnumString(lcComma),",");
                                    word ="";
                                    continue;
                                }
                            }

                           //раз в данной строке есть объявление функции то добавить переменные в область видимости
                           if(addVariable(row,word) == false)
                           {
                               //Error
                               return false;
                           }
                           //Проверить нижний код (заглушка на время)
                           addMapLex(row,lcComma,toEnumString(lcComma),",");
                           word ="";
                           continue;
                        }

                    }



                    auto serchLastlex = getLastlex(row);
                    auto serchFirslex = getFirslex(row);
                    if(serchLastlex == "<")
                    {
                        //Значит данное значение скороее всего Тип данных
                        addMapLex(row,lcType,toEnumString(lcType),word);
                        type_template+=word+","; //Собираем сложнй тип данных
                        type_template_lex+=toEnumString(lcType)+" "+toEnumString(lcComma)+" ";
                    }
                    else
                    {

                        ok = findTypeData(serchFirslex);
                        if(ok)
                        {
                            //Значит данное значение скороее всего Имя переменоой
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);

                            ok = addWordWords(lcLabel,word); // добавили переменную в массив переменных
//                            if(ok)
//                                cout << "Add WordWords : " << word<<endl;
//                            else
//                                cout << "Don't add WordWords : " << word<<endl;

                        }
                        else {
                            auto lable = findLable(word);
                            switch (lable)
                            {
                            case 0:
                            {
                                ok = false;
                                //Это обявленная переменная?
                                ok = findWordWords(word);
                                if(ok)
                                {
                                    //да
                                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                                }
                                else {
                                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                                }
                                break;
                            }
                            case 1: //Целое число
                                addMapLex(row,kwINT,toEnumString(kwINT),word);
                                break;
                            case -1: //Дробное
                                addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                                break;
                            }
                        }

                    }
                }
                else
                {
                    //Значит данное значение скороее всего Имя переменоой
                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);

                    ok = addWordWords(lcLabel,word); // добавили переменную в массив переменных
//                    if(ok)
//                        cout << "Add WordWords : " << word<<endl;
//                    else
//                        cout << "Don't add WordWords : " << word<<endl;
                }
            }
            else
            {
                if(type_template.size() > 0)
                {
                    type_template+=","; //Собираем сложнй тип данных
                    type_template_lex+=toEnumString(lcComma)+" ";
                }
            }



            addMapLex(row,lcComma,toEnumString(lcComma),",");
            word ="";
            continue;
            break;
        }
        case ')':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            if(word.size() == 0)
            {
                addMapLex(row,lcRCircle,toEnumString(lcRCircle),")");
                word ="";
                continue;
            }
            bool ok = false;

            //cначало проверить предыдущую лексему
            auto serchLastlex = getLastlex(row);

            //Значит данное значение скороее всего Имя переменоой
            auto serchFirslex = getFirslex(row);
            ok = findTypeData(serchFirslex);

            if(serchLastlex == "=" || ok == false)
            {
                auto lable = findLable(word);
                switch (lable)
                {
                case 0:
                {
                    ok = false;
                    //Это обявленная переменная?
                    ok = findWordWords(word);
                    if(ok)
                    {
                        //да
                        addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                    }
                    else {
                        addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        //может быть тут нужен код добавки переменной в локальную среду оакружения
                    }
                    break;
                }
                case 1: //Целое число
                    addMapLex(row,kwINT,toEnumString(kwINT),word);
                    break;
                case -1: //Дробное
                    addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                    break;
                }
            }
            else
            {
                //Значит данное значение скороее всего Имя переменоой
                //Старая реализация
                //addMapLex(row,lcLabel,toEnumString(lcLabel),word);


                //Временно
                if(map_word_lex.at(row).size() > 3)
                {
                    //Если 1,2 позиция есть объявление функции то
                    auto item2 =map_word_lex.at(row)[1].begin()->first;
                    auto item3 =map_word_lex.at(row)[2].begin()->first;
                    if((item2 == lcFunLabel && item3 == lcLCircle) || (item2 == lcLabelClass && item3 == lcColon))
                    {

                        if(type_template.size() > 0)
                        {
                            //Добавить переменную с новым типом
                            //Новое
                            //Проверить в текущем объекте простарнства имен на существование переменной
                            addHardTypeVariable(row,word,type_template,type_template_lex);
                            type_template = "";
                            type_template_lex = "";
                            word ="";
                            continue;
                        }

                       //раз в данной строке есть объявление функции то добавить переменные в область видимости
                       if(addVariable(row,word) == false)
                       {
                           //Error
                           return false;
                       }
                    }
                }
            }



            addMapLex(row,lcRCircle,toEnumString(lcRCircle),")");
            //i++;
            word ="";
            continue;
            break;
        }
        case '{':
        {

            if(flag_lcQuotes)
            {
                continue;
            }



            //Проверка на ключевое слово
            //это ключевое слово ?
            auto searchKey =keyWords.find(word);
            if(searchKey != keyWords.end())
            {
                //Найденное ключевое слово
                if(searchKey->first == "else")
                {
                    addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);
                    addNewSpaceFun(row,word);
                }
            }

            addNewSpaceFun(row-1,word);

            addMapLex(row,lcLFigure,toEnumString(lcLFigure),"{");
            word ="";
            continue;
            break;
        }
        case '}':
        {

            if(flag_lcQuotes)
            {
                continue;
            }

            if(listItemSpaces.size() > 1)
            {
                listItemSpaces.pop_back();
                itemSpaces = *listItemSpaces.rbegin();
            }




            addMapLex(row,lcRFigure,toEnumString(lcRFigure),"}");
            word ="";
            continue;
            break;
        }
        case '\'':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            if(word.size() > 0)
            {
                addMapLex(row,lcCharConst,toEnumString(lcCharConst),word);
                //i++;
            }
            addMapLex(row,lcApostrophe,toEnumString(lcApostrophe),"'");
            word ="";
            continue;
            break;
        }
        case '#':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            addMapLex(row,lcLattice,toEnumString(lcLattice),"#");
            word ="";
            continue;
            break;
        }
        case '*':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            if(word.size() >0)
            {



                //Проверка на ключевое слово
                //это ключевое слово ?
                auto searchKey =keyWords.find(word);
                if(searchKey != keyWords.end())
                {
                    //Найденное ключевое слово

                    //Тип указателя
                    //addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);

                    // Это тип данных Указатель

                    //map_word_lex.at(row).back().erase(searchKey->second);

                    addMapLex(row,lcTypeStar,toEnumString(lcTypeStar),word+"*");
                    word ="";
                    continue;

                }
                else
                {
                    // Это тип данных ?
                    bool ok = findTypeData(word);
                    if(ok) // Это тип данных
                    {
                        //auto searchType = types[word];
                        // Это тип данных
                        addMapLex(row,lcTypeStar,toEnumString(lcTypeStar),word+"*");

                        if(type_template.size() > 0)
                        {
                            type_template+=word+"*";
                            type_template_lex+=toEnumString(lcTypeStar)+" ";
                        }

                        word ="";
                        continue;
                    }
                    else
                    {
                        //Это не тип данных

                        //Есть значение
                        //Является ли слово объявленной именем переменной?
                        ok = findWordWords(word);
                        if(ok)
                        {
                            //Значит данное значение скороее всего Имя переменоой
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        else
                        {

                            //Является ли числом ?

                            auto lable = findLable(word);

                            switch (lable)
                            {
                            case 0:
                            {
                                ok = false;
                                //Это обявленная переменная?
                                ok = findWordWords(word);
                                if(ok)
                                {
                                    //да
                                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                                }
                                else {
                                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                                }
                                break;
                            }
                            case 1: //Целое число
                                addMapLex(row,kwINT,toEnumString(kwINT),word);
                                break;
                            case -1: //Дробное
                                addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                                break;
                            }


                        }
                    }
                }
            }

            addMapLex(row,lcStar,toEnumString(lcStar),"*");
            word ="";
            continue;
            break;
        }
        case '&':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            bool ok = false;
            if(word.size() > 0)
            {
                // Это тип данных ?
                bool ok = findTypeData(word);
                if(ok) // Это тип данных
                {
                    auto searchType = types.find(word);
                    // Это тип данных
                    addMapLex(row,searchType->second,toEnumString(searchType->second),searchType->first);
                }
                else {
                    //Это не тип данных

                    // addMapLex(row,lcType,toEnumString(lcType),word);

                    //Есть значение
                    //Является ли слово объявленной именем переменной?
                    ok = findWordWords(word);
                    if(ok)
                    {
                        //Значит данное значение скороее всего Имя переменоой
                        addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                    }
                    else
                    {
                        //Является ли числом ?

                        auto lable = findLable(word);

                        switch (lable)
                        {
                        case 0:
                        {
                            ok = false;
                            //Это обявленная переменная?
                            ok = findWordWords(word);
                            if(ok)
                            {
                                //да
                                addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                            }
                            else {
                                addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                            }
                            break;
                        }
                        case 1: //Целое число
                            addMapLex(row,kwINT,toEnumString(kwINT),word);
                            break;
                        case -1: //Дробное
                            addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                            break;
                        }
                    }

                }
            }

            // Есть ли предыдущие лексемы ?
            if(map_word_lex.at(row).size() > 0)
            {
                //Если предыдущее было имя переменной, то это присваивание
                //Предыдущая ликсема является ли именем переменной?
                auto lastLex = getLastlex(row);
                ok = findWordWords(lastLex);
                if(ok)
                {
                    //Предыдущее значчение является именем переменной
                    // Значит скорее всего это побитовая операция илл
                }
                else {
                    //Предыдущее значчение не является именем переменной

                    switch (lastLex[0])
                    {
                    case '&':
                        //Условие равнества
                        replaceLastMapLex(row,lcDoubleImpersant,toEnumString(lcDoubleImpersant),"&&");
                        word ="";
                        continue;
                        break;
                    }

                }
            }
            else {
                //Предыдущих лексем нет то
                //Значит Есть только '&' а это ошибка
                //error
            }

            addMapLex(row,lcImpersant,toEnumString(lcImpersant),"&");
            word ="";
            continue;
            break;
        }
        case '/':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            if(word.size() >0)
            {

                // Это тип данных ?
                bool ok = findTypeData(word);
                if(ok) // Это тип данных
                {
                    auto searchType = types.find(word);
                    // Это тип данных
                    addMapLex(row,searchType->second,toEnumString(searchType->second),searchType->first);
                }
                else {
                    //Это не тип данных

                    //Есть значение
                    //Является ли слово объявленной именем переменной?
                    ok = findWordWords(word);
                    if(ok)
                    {
                        //Значит данное значение скороее всего Имя переменоой
                        addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                    }
                    else
                    {

                        //Является ли числом ?

                        auto lable = findLable(word);

                        switch (lable)
                        {
                        case 0:
                        {
                            ok = false;
                            //Это обявленная переменная?
                            ok = findWordWords(word);
                            if(ok)
                            {
                                //да
                                addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                            }
                            else {
                                addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                            }
                            break;
                        }
                        case 1: //Целое число
                            addMapLex(row,kwINT,toEnumString(kwINT),word);
                            break;
                        case -1: //Дробное
                            addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                            break;
                        }


                    }
                }

            }

            addMapLex(row,lcSlash,toEnumString(lcSlash),"/");
            word ="";
            continue;
            break;
        }
        case '[':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            bool ok = false;

            if(word.size() > 0)
            {


                //Проверка на ключевое слово
                //это ключевое слово ?
                auto searchKey =keyWords.find(word);
                if(searchKey != keyWords.end())
                {
                    //Найденное ключевое слово
                    addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);
                }
                else
                {


                    //Временно
                    if(map_word_lex.at(row).size() > 3)
                    {
                        //Если 1,2 позиция есть объявление функции то
                        auto item2 =map_word_lex.at(row)[1].begin()->first;
                        auto item3 =map_word_lex.at(row)[2].begin()->first;
                        if(item2 == lcFunLabel && item3 == lcLCircle)
                        {
                           //раз в данной строке есть объявление функции то добавить переменные в область видимости
                           if(addVariable(row,word) == false)
                           {
                               //Error
                               return false;
                           }
                        }
                    }

//                    //Есть значение
//                    //Является ли слово объявленной именем переменной?
//                    ok = findWordWords(word);
//                    if(ok)
//                    {
//                        //Значит данное значение скороее всего Имя переменоой
//                        addMapLex(row,lcLabel,toEnumString(lcLabel),word);
//                    }
//                    else
//                    {
//                        //Является ли числом ?
//                        auto lable = findLable(word);

//                        switch (lable)
//                        {
//                        case 0:
//                        {
//                            ok = false;
//                            //Это обявленная переменная?
//                            ok = findWordWords(word);
//                            if(ok)
//                            {
//                                //да
//                                addMapLex(row,lcLabel,toEnumString(lcLabel),word);
//                            }
//                            else {
//                                addMapLex(row,lcLabel,toEnumString(lcLabel),word);
//                                //Добавить переменную в массив переменных
//                                ok = addWordWords(lcLabel,word); // добавили переменную в массив переменных
//                                if(ok)
//                                    cout << "Add WordWords : " << word<<endl;
//                                else
//                                    cout << "Don't add WordWords : " << word<<endl;
//                            }
//                            break;
//                        }
//                        case 1: //Целое число
//                            addMapLex(row,kwINT,toEnumString(kwINT),word);
//                            break;
//                        case -1: //Дробное
//                            addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
//                            break;
//                        }
//                    }
                }
            }
            addMapLex(row,lcLSquare,toEnumString(lcLSquare),"[");
            word ="";
            continue;
            break;
        }
        case ']':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            bool ok = false;

            if(word.size() > 0)
            {
                //Есть значение
                //Является ли слово объявленной именем переменной?
                ok = findWordWords(word);
                if(ok)
                {
                    //Значит данное значение скороее всего Имя переменоой
                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                }
                else
                {
                    //Является ли числом ?
                    auto lable = findLable(word);

                    switch (lable)
                    {
                    case 0:
                    {
                        ok = false;
                        //Это обявленная переменная?
                        ok = findWordWords(word);
                        if(ok)
                        {
                            //да
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        else {
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                            //Добавить переменную в массив переменных
                        }
                        break;
                    }
                    case 1: //Целое число
                        addMapLex(row,kwINT,toEnumString(kwINT),word);
                        break;
                    case -1: //Дробное
                        //Убрать тут должна быть ошибка нельзя дробное число доабвлять в квадратные скобки
                        addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                        break;
                    }
                }
            }
            addMapLex(row,lcRSquare,toEnumString(lcRSquare),"]");
            word ="";
            continue;
            break;
        }
        case ':':
        {

            if(flag_lcQuotes)
            {
                continue;
            }

            //Проверка на класс или пространство имен
            if(word.size() > 0)
            {

                // Есть ли предыдущие лексемы ?
                if(map_word_lex.at(row).size() > 0)
                {
                    string firstLex = getFirslex(row);

                    if(firstLex == "case")
                    {
                        //Есть значение
                        //Является ли слово объявленной именем переменной?
                        bool ok = findWordWords(word);
                        if(ok)
                        {
                            //Значит данное значение скороее всего Имя переменоой
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        else
                        {
                            //Является ли числом ?

                            auto lable = findLable(word);

                            switch (lable)
                            {
                            case 0:
                            {
                                ok = false;
                                //Это обявленная переменная?
                                ok = findWordWords(word);
                                if(ok)
                                {
                                    //да
                                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                                }
                                else {
                                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                                }
                                break;
                            }
                            case 1: //Целое число
                                addMapLex(row,kwINT,toEnumString(kwINT),word);
                                break;
                            case -1: //Дробное
                                addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                                break;
                            case 2:
                            {
                                //hex
                                addMapLex(row,lcCharConst,toEnumString(lcCharConst),word);
                                break;
                            }
                            }
                        }
                    }
                    else {
                        //Проверка на переменную имени класса
                        addMapLex(row,lcLabelClass,toEnumString(lcLabelClass),word);
                        addClassWords(lcLabelClass,word);
                    }
                }
                else
                {
                    //Проверка на ключевое слово
                    //это ключевое слово ?
                    auto searchKey =keyWords.find(word);
                    if(searchKey != keyWords.end())
                    {
                        //Найденное ключевое слово
                        addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);
                    }

                }



            }


            addMapLex(row,lcColon,toEnumString(lcColon),":");
            word ="";
            continue;
            break;
        }
        case '?':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            bool ok = false;

            if(word.size() > 0)
            {
                //Есть значение
                //Является ли слово объявленной именем переменной?
                ok = findWordWords(word);
                if(ok)
                {
                    //Значит данное значение скороее всего Имя переменоой
                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                }
                else
                {
                    //Является ли числом ?
                    auto lable = findLable(word);

                    switch (lable)
                    {
                    case 0:
                    {
                        ok = false;
                        //Это обявленная переменная?
                        ok = findWordWords(word);
                        if(ok)
                        {
                            //да
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        else {
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        break;
                    }
                    case 1: //Целое число
                        addMapLex(row,kwINT,toEnumString(kwINT),word);
                        break;
                    case -1: //Дробное
                        addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                        break;
                    }
                }
            }

            addMapLex(row,lcQuestion,toEnumString(lcQuestion),"?");
            word ="";
            continue;
            break;
        }
        case '"':
        {

            if(word == "include")
            {
                addMapLex(row,lcInclude,toEnumString(lcInclude),word);


                s2.erase(0,i);

                s2.erase(0,1);
                s2.erase(s2.size()-1,s2.size());
                addWordIncludes(lcInclude,s2);

                addMapLex(row,lcInclude,s2,s2);
                word ="";
                return true;
            }

            if(flag_lcQuotes)
            {
                flag_lcQuotes = false;
                addMapLex(row,kwSTRING,toEnumString(kwSTRING),word);
            }
            else
            {
                flag_lcQuotes = true;
            }


            addMapLex(row,lcQuotes,toEnumString(lcQuotes),"\"");
            word ="";
            continue;
            break;
        }
        case '^':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            bool ok = false;

            if(word.size() > 0)
            {
                //Есть значение
                //Является ли слово объявленной именем переменной?
                ok = findWordWords(word);
                if(ok)
                {
                    //Значит данное значение скороее всего Имя переменоой
                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                }
                else
                {
                    //Является ли числом ?

                    auto lable = findLable(word);

                    switch (lable)
                    {
                    case 0:
                    {
                        ok = false;
                        //Это обявленная переменная?
                        ok = findWordWords(word);
                        if(ok)
                        {
                            //да
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        else {
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        break;
                    }
                    case 1: //Целое число
                        addMapLex(row,kwINT,toEnumString(kwINT),word);
                        break;
                    case -1: //Дробное
                        addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                        break;
                    }
                }
            }

            addMapLex(row,lcRoof,toEnumString(lcRoof),"^");
            word ="";
            continue;
            break;
        }
        case '|':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            bool ok = false;

            if(word.size() > 0)
            {
                //Есть значение
                //Является ли слово объявленной именем переменной?
                ok = findWordWords(word);
                if(ok)
                {
                    //Значит данное значение скороее всего Имя переменоой
                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                }
                else
                {
                    //Является ли числом ?

                    auto lable = findLable(word);

                    switch (lable)
                    {
                    case 0:
                    {
                        ok = false;
                        //Это обявленная переменная?
                        ok = findWordWords(word);
                        if(ok)
                        {
                            //да
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        else {
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        break;
                    }
                    case 1: //Целое число
                        addMapLex(row,kwINT,toEnumString(kwINT),word);
                        break;
                    case -1: //Дробное
                        addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                        break;
                    }
                }
            }

            // Есть ли предыдущие лексемы ?
            if(map_word_lex.at(row).size() > 0)
            {
                //Если предыдущее было имя переменной, то это присваивание
                //Предыдущая ликсема является ли именем переменной?
                auto lastLex = getLastlex(row);
                ok = findWordWords(lastLex);
                if(ok)
                {
                    //Предыдущее значчение является именем переменной
                    // Значит скорее всего это побитовая операция илл
                }
                else {
                    //Предыдущее значчение не является именем переменной

                    switch (lastLex[0])
                    {
                    case '|':
                        //Условие равнества
                        replaceLastMapLex(row,lcDoubleStick,toEnumString(lcDoubleStick),"||");
                        word ="";
                        continue;
                        break;
                    }

                }
            }
            else {
                //Предыдущих лексем нет то
                //Значит Есть только '|' а это ошибка
                //error
            }

            addMapLex(row,lcStick,toEnumString(lcStick),"|");
            word ="";
            continue;
            break;
        }
        case '!':
        {

            if(flag_lcQuotes)
            {
                continue;
            }

            bool ok = false;

            if(word.size() > 0)
            {
                //Есть значение
                //Является ли слово объявленной именем переменной?
                ok = findWordWords(word);
                if(ok)
                {
                    //Значит данное значение скороее всего Имя переменоой
                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                }
                else
                {
                    //Является ли числом ?

                    auto lable = findLable(word);

                    switch (lable)
                    {
                    case 0:
                    {
                        ok = false;
                        //Это обявленная переменная?
                        ok = findWordWords(word);
                        if(ok)
                        {
                            //да
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        else {
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        break;
                    }
                    case 1: //Целое число
                        addMapLex(row,kwINT,toEnumString(kwINT),word);
                        break;
                    case -1: //Дробное
                        addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                        break;
                    }
                }
            }

            addMapLex(row,lcExclamatory,toEnumString(lcExclamatory),"!");
            word ="";
            continue;
            break;
        }
        case '.':
        {
            if(flag_lcQuotes)
            {
                continue;
            }

            bool ok = false;

            if(word.size() > 0)
            {
                //Есть значение
                //Является ли слово объявленной именем переменной?
                ok = findWordWords(word);
                if(ok)
                {
                    //Значит данное значение скороее всего Имя переменоой
                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                }
                else
                {
                    //Является ли числом ?

                    auto lable = findLable(word);

                    switch (lable)
                    {
                    case 0:
                    {
                        ok = false;
                        //Это обявленная переменная?
                        ok = findWordWords(word);
                        if(ok)
                        {
                            //да
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        else {
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                        }
                        break;
                    }
                    case 1: //Целое число
                        //addMapLex(row,kwINT,toEnumString(kwINT),word);
                        word +=row_str[i];
                        continue;
                        break;
                    case -1: //Дробное
                        addMapLex(row,kwFLOAT,toEnumString(kwFLOAT),word);
                        break;
                    }
                }
            }


            addMapLex(row,lcPoint,toEnumString(lcPoint),".");
            word ="";
            continue;
            break;
        }
        }

        word +=row_str[i];
    }


    //Проверка на ключевое слово
    //это ключевое слово ?
    auto searchKey =keyWords.find(word);
    if(searchKey != keyWords.end())
    {
        //Найденное ключевое слово
        addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);
    }
    else
    {
        if(word.size() > 0)
        {

            // Есть ли предыдущие лексемы ?
            if(map_word_lex.at(row).size() > 0)
            {
                auto searchLastLex = getLastlex(row);

                if (searchLastLex == "enum")
                {
                    //Проверка на переменную имени класса
                    addMapLex(row,lcType,toEnumString(lcType),word);
                    addTypes(lcType,word);
                }
                else
                {
                    //Проверка на переменную имени класса
                    addMapLex(row,lcLabelClass,toEnumString(lcLabelClass),word);
                    addClassWords(lcLabelClass,word);
                    addTypes(lcLabelClass,word);
                }
            }


        }

    }


    return true;
}

void Scanner::zapolnenieOperationsPriorityForward(vector<string> operands, int priority, int forward)
{
    auto search =mapOperationsAndPriority.find(priority);

    vector<vector<string>> forwardOperends;
    if(search != mapOperationsAndPriority.end())
    {
        search->second[forward] = operands;
    }
    else {

        forwardOperends.push_back({}); // без навправления
        forwardOperends.push_back({}); // левый
        forwardOperends.push_back({}); // правый

        forwardOperends[forward] = operands;
        mapOperationsAndPriority.insert(make_pair(priority,forwardOperends));
    }




}

void Scanner::addMapLex(unsigned int row, LexClass lex, string lex_str, string data, int position)
{
    map<LexClass,map<string,string>> map_lex;
    map<string,string> map_lex_string;




    //
    auto search =map_word_lex.find(row);

    if(search != map_word_lex.end())
    {
        map_lex_string.insert(make_pair(lex_str,data));
        map_lex.insert(make_pair(lex,map_lex_string));

        search->second.push_back(map_lex);

    }

}

void Scanner::replaceLastMapLex(unsigned int row, LexClass lex, string lex_str, string data, int position)
{
    map<LexClass,map<string,string>> mapNew;
    map<string,string> mapNewItem;
    mapNewItem.insert(make_pair(lex_str,data));
    mapNew.insert(make_pair(lex,mapNewItem));

    auto end = map_word_lex.find(row)->second.end();
    map_word_lex.find(row)->second.erase(end);
    map_word_lex.find(row)->second.push_back(mapNew);

}

//Добавление ключевых слов
void Scanner::addKeyWords(LexClass data, string key)
{
    //    map<LexClass,string> map_keyWords;
    //    map_keyWords.insert(make_pair(key,data));
    //    keyWords.push_back(map_keyWords);

    keyWords.insert(make_pair(key,data));
}

//Добавление типов данных
void Scanner::addTypes(LexClass data, string key)
{
    //    map<LexClass,string> map_types;
    //    map_types.insert(make_pair(key,data));
    //    types.push_back(map_types);

    types.insert(make_pair(key,data));
}

bool Scanner::addWordWords(LexClass data, string key)
{
    auto serchwordWords = wordWords.find(key);
    if(serchwordWords != wordWords.end())
    {
        //Данной переменной ЕСТЬ в списке ( не добавлять)
        return false;
    }
    else
    {
        //Данной переменной нет в списке
        wordWords.insert(make_pair(key,data));
    }

    return true;
}

bool Scanner::addWordFunWords(LexClass data, string key)
{
    auto serchwordWords = wordFunWords.find(key);
    if(serchwordWords != wordFunWords.end())
    {
        //Данной переменной ЕСТЬ в списке ( не добавлять)
        return false;
    }
    else
    {
        //Данной переменной нет в списке
        wordFunWords.insert(make_pair(key,data));
    }

    return true;
}

bool Scanner::addWordIncludes(LexClass data, string key)
{
    auto serchwordWords = wordIncludes.find(key);
    if(serchwordWords != wordIncludes.end())
    {
        //Данной инклуд ЕСТЬ в списке ( не добавлять)
        return false;
    }
    else
    {
        //Данной инклуда нет в списке
        wordIncludes.insert(make_pair(key,data));
    }

    return true;
}

bool Scanner::addClassWords(LexClass data, string key)
{
    auto serchwordWords = wordClassWords.find(key);
    if(serchwordWords != wordClassWords.end())
    {
        //Данный класс ЕСТЬ в списке ( не добавлять)
        return false;
    }
    else
    {
        //Данного класса нет в списке
        wordClassWords.insert(make_pair(key,data));
    }

    return true;
}

string Scanner::toEnumString(LexClass lex)
{
    string findLex;
    switch (lex)
    {
    case keyASM:
        findLex = "keyASM";
        break;
    case keyAUTO:
        findLex = "keyAUTO";
        break;
    case keyBREAK:
        findLex = "keyBREAK";
        break;
    case keyCASE:
        findLex = "keyCASE";
        break;
    case keyCATCH:
        findLex = "keyCATCH";
        break;
    case keyCHAR:
        findLex = "keyCHAR";
        break;
    case keyCLASS:
        findLex = "keyCLASS";
        break;
    case keyCONST:
        findLex = "keyCONST";
        break;
    case keyCONTINUE:
        findLex = "keyCONTINUE";
    case keyCONSTEXPR:
        findLex = "keyCONSTEXPR";
        break;
    case keyDEFAULT:
        findLex = "keyDEFAULT";
        break;
    case keyDELETE:
        findLex = "keyDELETE";
        break;
    case keyDO:
        findLex = "keyDO";
        break;
    case keyDOUBLE:
        findLex = "keyDOUBLE";
        break;
    case keyELSE:
        findLex = "keyELSE";
        break;
    case keyENUM:
        findLex = "keyENUM";
        break;
    case keyEXPLICIT:
        findLex = "keyEXPLICIT";
        break;
    case keyEXTERN:
        findLex = "keyEXTERN";
        break;
    case keyFLOAT:
        findLex = "keyFLOAT";
        break;
    case keyFOR:
        findLex = "keyFOR";
        break;
    case keyFRIEND:
        findLex = "keyFRIEND";
        break;
    case keyGOTO:
        findLex = "keyGOTO";
        break;
    case keyIF:
        findLex = "keyIF";
        break;
    case keyINLINE:
        findLex = "keyINLINE";
        break;
    case keyINT:
        findLex = "keyINT";
        break;
    case keyLONG:
        findLex = "keyLONG";
        break;
    case keyMUTABLE:
        findLex = "keyMUTABLE";
        break;
    case keyNEW:
        findLex = "keyNEW";
        break;
    case keyOPERATOR:
        findLex = "keyOPERATOR";
        break;
    case keyPRIVATE:
        findLex = "keyPRIVATE";
        break;
    case keyPROTECTED:
        findLex = "keyPROTECTED";
        break;
    case keyPUBLIC:
        findLex = "keyPUBLIC";
        break;
    case keyREGISTER:
        findLex = "keyREGISTER";
        break;
    case keyRETURN:
        findLex = "keyRETURN";
        break;
    case keySHORT:
        findLex = "keySHORT";
        break;
    case keySIGNED:
        findLex = "keySIGNED";
        break;
    case keySIZEOF:
        findLex = "keySIZEOF";
        break;
    case keySTATIC:
        findLex = "keySTATIC";
        break;
    case keySTRUCT:
        findLex = "keySTRUCT";
        break;
    case keySWITCH:
        findLex = "keySWITCH";
        break;
    case keyTEMPLATE:
        findLex = "keyTEMPLATE";
        break;
    case keyTHIS:
        findLex = "keyTHIS";
        break;
    case keyTRY:
        findLex = "keyTRY";
        break;
    case keyTHROW:
        findLex = "keyTHROW";
        break;
    case keyTYPEDEF:
        findLex = "keyTYPEDEF";
        break;
    case keyTYPENAME:
        findLex = "keyTYPENAME";
    case keyTRUE:
        findLex = "keyTRUE";
        break;
    case keyFALSE:
        findLex = "keyFALSE";
        break;
    case keyUNION:
        findLex = "keyUNION";
        break;
    case keyUNSIGNED:
        findLex = "keyUNSIGNED";
        break;
    case keyVIRTUAL:
        findLex = "keyVIRTUAL";
        break;
    case keyVOID:
        findLex = "keyVOID";
        break;
    case keyVOLATILE:
        findLex = "keyVOLATILE";
        break;
    case keyWHILE:
        findLex = "keyWHILE";
        break;
    case keyBOOL:
        findLex = "keyBOOL";
        break;
    case keyNAMESPACE:
        findLex = "keyNAMESPACE";
        break;
    case keyNULLPTTR:
        findLex = "keyNULLPTTR";
        break;
    case keySTATIC_CAST:
        findLex ="keySTATIC_CAST";
        break;
    case keyUSING:
        findLex = "keyUSING";
        break;
    }


    switch (lex) {
    case kwINT:
        findLex = "kwINT";
        break;
    case kwBOOL:
        findLex = "kwBOOL";
        break;
    case kwFLOAT:
        findLex = "kwFLOAT";
        break;
    case kwDOUBLE:
        findLex = "kwDOUBLE";
        break;
    case kwCHAR:
        findLex = "kwCHAR";
        break;
    case kwSTRING:
        findLex = "kwSTRING";
        break;
    }

    switch (lex) {
    case lcTypeTemplate:
        findLex = "lcTypeTemplate";
        break;
    case lcLink:
        findLex = "lcLink";
        break;
    case lcLabelClass:
        findLex = "lcLabelClass";
        break;
    case lcPoint:
        findLex = "lcPoint";
        break;
    case lcExclamatory:
        findLex = "lcExclamatory";
        break;
    case lcDoubleStick:
        findLex = "lcDoubleStick";
        break;
    case lcDoubleImpersant:
        findLex = "lcDoubleImpersant";
        break;
    case lcStick:
        findLex = "lcStick";
        break;
    case lcRoof:
        findLex = "lcRoof";
        break;
    case lcQuotes:
        findLex = "lcQuotes";
        break;
    case lcQuestion:
        findLex = "lcQuestion";
        break;
    case lcColon:
        findLex = "lcColon";
        break;
    case lcLSquare:
        findLex = "lcLSquare";
        break;
    case lcRSquare:
        findLex = "lcRSquare";
        break;
    case lcSlash:
        findLex = "lcPercent";
        break;
    case lcPercent:
        findLex = "lcPercent";
        break;
    case lcImpersant:
        findLex = "lcImpersant";
        break;
    case lcStar:
        findLex = "lcStar";
        break;
    case lcInclude:
        findLex = "lcInclude";
        break;
    case lcLattice:
        findLex = "lcLattice";
        break;
    case lcNotEqual:
        findLex = "lcNotEqual";
        break;
    case lcType:
        findLex = "lcType";
        break;
    case lcTypeStar:
        findLex = "lcTypeStar";
        break;
    case lcLabel:
        findLex = "lcLabel";
        break;
    case lcEqual:
        findLex = "lcEqual";
        break;
    case lcAssign:
        findLex = "lcAssign";
        break;
    case lcSmallerEQ:
        findLex = "lcSmallerEQ";
        break;
    case lcLargerEQ:
        findLex = "lcLargerEQ";
        break;
    case lcFunLabel:
        findLex = "lcFunLabel";
        break;
    case lcRCircle:
        findLex = "lcRCircle";
        break;
    case lcLCircle:
        findLex = "lcLCircle";
        break;
    case lcRFigure:
        findLex ="lcRFigure";
        break;
    case lcLFigure:
        findLex = "lcLFigure";
        break;
    case lcComma:
        findLex = "lcComma";
        break;
    case lcSemicolon:
        findLex = "lcSemicolon";
        break;
    case lcCharConst:
        findLex = "lcCharConst";
        break;
    case lcApostrophe:
        findLex = "lcApostrophe";
        break;
    case lcLarger:
        findLex = "lcLarger";
        break;
    case lcPlus:
        findLex = "lcPlus";
        break;
    case lcSmaller:
        findLex = "lcSmaller";
        break;
    case lcMinus:
        findLex = "lcMinus";
        break;

    }

    return findLex;
}

bool Scanner::addVariable(unsigned int row, string word)
{
    //Проверить в текущем объекте простарнства имен на существование переменной
    bool findWord = false; // флаг объявленна ли переменная
    for(auto item : itemSpaces->variables)
    {
        //написать проверку на меременную
        auto nameWord = item.first.begin()->second;
        if(word == nameWord)
        {
            //Значит дананя переменная уже есть
            findWord = true;
            //Значит дананя переменная уже есть
            //Так как мы были в '=' значит ошибка присваения
            cout<<endl;
            cout <<"Row["<<row<<"] ) ERROR : Redeclaring a declared variable = '" <<word<<"'"<<endl;
            cout<<endl;
            return false;
        }
    }
    if(findWord)
    {
        //Переменная существует в списке объявлений

        //Проверить не логические ли происходят с переменной ?
        //Ошибка обявлениия переменной второй раз
        //Error
    }
    else
    {
        //Переменная не существует в списке объявлений
        //Проверить не логические ли происходят с переменной ?

        //Так как мы нашли равенство то добать переменную в область видимости
        //Значит данное значение скороее всего Имя переменоой
        addMapLex(row,lcLabel,toEnumString(lcLabel),word);
        auto item = map_word_lex.at(row);
        auto itemType = item[item.size()-2].begin()->second;
        auto itemName = item[item.size()-1].begin()->second;
        itemSpaces->push_back_variables(itemName,itemType);
    }

    return  true;
}

bool Scanner::addFunClassVariable(unsigned int row, string word)
{
    //Нужно создать объект Space и добавить пространсто имен
    Space* newSpace = new Space;
    newSpace->name = word;
    itemSpaces->push_back(newSpace);
    itemSpaces = newSpace;
    return true;
}

bool Scanner::addHardTypeVariable(unsigned int row, string word, string type_template, string type_template_lex)
{
    //Добавить переменную с новым типом
    //Новое
    //Проверить в текущем объекте простарнства имен на существование переменной
    bool findWord = false; // флаг объявленна ли переменная
    for(auto item : itemSpaces->variables)
    {
        //написать проверку на меременную
        auto nameWord = item.first.begin()->second;
        if(word == nameWord)
        {
            //Значит дананя переменная уже есть
            findWord = true;
            //Значит дананя переменная уже есть
            //Так как мы были в '=' значит ошибка присваения
            cout<<endl;
            cout <<"Row["<<row<<"] ) ERROR : Redeclaring a declared variable = '" <<word<<"'"<<endl;
            cout<<endl;
            return false;
        }
    }

    if(findWord)
    {
        //Переменная существует в списке объявлений

        //Проверить не логические ли происходят с переменной ?
        //Ошибка обявлениия переменной второй раз
        //Error
    }
    else
    {
        //Переменная не существует в списке объявлений
        //Проверить не логические ли происходят с переменной ?

        //Так как мы нашли равенство то добать переменную в область видимости
        //Значит данное значение скороее всего Имя переменоой
        addMapLex(row,lcLabel,toEnumString(lcLabel),word);
        auto item = map_word_lex.at(row);
        map<string,string> itemType;
        itemType.insert(make_pair(type_template_lex,type_template));
        addTypes(lcTypeTemplate,type_template);

        auto itemName = item[item.size()-1].begin()->second;
        itemSpaces->push_back_variables(itemName,itemType);
        type_template = "";
        type_template_lex = "";
    }

    //continue
}

bool Scanner::addNewSpaceFun(int row, string word)
{
    auto searchLabel = map_word_lex.at(row);
    for(auto it =searchLabel.begin(); it != searchLabel.end(); ++it)
    {

       auto item = *it;

       auto searchLabel_lcFunLabel = item.find(lcFunLabel);
       if(searchLabel_lcFunLabel !=item.end())
       {
           listItemSpaces.push_back(itemSpaces);
           break;
       }

       auto searchLabel_keyWHILE = item.find(keyWHILE);
       if(searchLabel_keyWHILE !=item.end())
       {
           //Нужно создать объект Space и добавить пространсто имен
           Space* newSpace = new Space;


           //Получить данные которые находятся в скобках while
           auto value = (it+1)->begin()->second;
           for (auto it2 =(it+1); it2 != searchLabel.end(); ++it2)
           {
               LexClass item = it2->begin()->first;

              if(item == lcRCircle)
              {
                   value = (--it2)->begin()->second;
                   break;

              }
           }

           newSpace->name = searchLabel_keyWHILE->second.rbegin()->second +"("+value.begin()->second+")";
           //Добавить в объект который собирается функцию и вернуть указатель на новый объект который нужно собирать
           itemSpaces->push_back(newSpace);
           itemSpaces = newSpace;
           listItemSpaces.push_back(itemSpaces);
           break;
       }


       auto searchLabel_lcLabelClass = item.find(lcLabelClass);
       if(searchLabel_lcLabelClass != item.end())
       {
           //Нужно создать объект Space и добавить пространсто имен
           Space* newSpace = new Space;

           newSpace->name = searchLabel_lcLabelClass->second.rbegin()->second;
           //Добавить в объект который собирается функцию и вернуть указатель на новый объект который нужно собирать
           itemSpaces->push_back(newSpace);
           itemSpaces = newSpace;
           listItemSpaces.push_back(itemSpaces);
           break;
       }

       auto searchLabel_keyIF = item.find(keyIF);
       if(searchLabel_keyIF != item.end())
       {
           //Нужно создать объект Space и добавить пространсто имен
           Space* newSpace = new Space;

           newSpace->name = searchLabel_keyIF->second.rbegin()->second;

           //Если я нашел последующий иф внутри какогото
           if(!itemSpaces->listSpace.empty())
           {
                itemSpaces = itemSpaces->listSpace.back();
           }


           //Добавить в объект который собирается функцию и вернуть указатель на новый объект который нужно собирать
           itemSpaces->push_back(newSpace);
           itemSpaces = newSpace;
           listItemSpaces.push_back(itemSpaces);

           break;
       }

       auto searchLabel_keyELSE = item.find(keyELSE);
       if(searchLabel_keyELSE != item.end())
       {
           //Нужно создать объект Space и добавить пространсто имен
           Space* newSpace = new Space;


           //Нужно найти последний иф и и дти от него

           itemSpaces = itemSpaces->listSpace.back();

           newSpace->name = searchLabel_keyELSE->second.rbegin()->second;
           //Добавить в объект который собирается функцию и вернуть указатель на новый объект который нужно собирать
           itemSpaces->push_back(newSpace);
           itemSpaces = newSpace;
           listItemSpaces.push_back(itemSpaces);
           break;
       }

       //keySWITCH
       auto searchLabel_keySWITCH = item.find(keySWITCH);
       if(searchLabel_keySWITCH != item.end())
       {
           //Может быть нужно дописать сбор переменной
           //Нужно создать объект Space и добавить пространсто имен
           Space* newSpace = new Space;

           //Получить данные ( которые находятся в скобках switch
           auto value = (it+1)->begin()->second;
           for (auto it2 =(it+1); it2 != searchLabel.end(); ++it2)
           {
               LexClass item = it2->begin()->first;

              if(item == lcRCircle)
              {
                   value = (--it2)->begin()->second;
                   break;

              }
           }


           newSpace->name = searchLabel_keySWITCH->second.rbegin()->second;
           //Добавить в объект который собирается функцию и вернуть указатель на новый объект который нужно собирать
           itemSpaces->push_back(newSpace);
           itemSpaces = newSpace;
           listItemSpaces.push_back(itemSpaces);
           break;
       }
       //keyCASE
       auto searchLabel_keyCASE = item.find(keyCASE);
       if(searchLabel_keyCASE != item.end())
       {
           //Нужно создать объект Space и добавить пространсто имен
           Space* newSpace = new Space;

           auto itemKeyCase = searchLabel_keyCASE->second.rbegin()->second;



           //Получить данные ( которые находятся в скобках switch
           auto value = (it+1)->begin()->second;
           for (auto it2 =(it+1); it2 != searchLabel.end(); ++it2)
           {

               LexClass item = it2->begin()->first;
               if(item == lcColon)
               {
                    item = (it2-1)->begin()->first;
                    value = (it2-1)->begin()->second;

                    if(item == lcApostrophe)
                    {
                        value = (it2-2)->begin()->second;
                        map <string,string> newItem;
                        newItem.insert(make_pair(value.begin()->first,value.begin()->second));

                        newSpace->name = itemKeyCase +" "+"'"+value.begin()->second+"'";
                    }
                    else {
                        newSpace->name = itemKeyCase +" "+value.begin()->second;
                    }
                    break;

               }

           }

           //Добавить в объект который собирается функцию и вернуть указатель на новый объект который нужно собирать
           itemSpaces->push_back(newSpace);
           itemSpaces = newSpace;
           listItemSpaces.push_back(itemSpaces);
           break;
       }
    }

    return true;
}

//Поиск типа данных
bool Scanner::findTypeData(string key)
{
    if(key == "*") // || key =="&"
    {
        return true;
    }
    auto serchType = types.find(key);
    if(serchType != types.end())
    {
        return true;
    }
    else
    {
        //Это не тип данных
        return false;
    }
}

bool Scanner::findWordWords(string key)
{
    auto serchWordWords = wordWords.find(key);
    if(serchWordWords != wordWords.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Scanner::findWordWords(string data, Space *space)
{
    vector<string> listVariable;
    //map<string,string> mapToFind;
    //mapToFind.insert(make_pair(toEnumString(lcLabel),data));
    auto listVariables = space->variables;


    for (auto it : listVariables)
    {
        for (auto it2 : it.first) {
            listVariable.push_back(it2.second);
        }
    }

    if(listVariable.size() >0)
    {
        for(int i=0; i < listVariable.size();i++)
        {
            if(listVariable[i]==data)
            {
                return true;
            }
        }
    }

    return false;
}

bool Scanner::findClassWords(string key)
{
    auto serchClassWords = wordClassWords.find(key);
    if(serchClassWords != wordClassWords.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Проверка на число или переменную
int Scanner::findLable(string word)
{

    if(word =="0")
    {
        //cout <<"Find int : " << word<<endl;
        return 1; //Целое число
    }

    if(word.size() > 2)
    {
        if(word[0] == '0' && word[1] == 'x' )
        {
            //cout <<"Find int : " << word<<endl;
            return 2; //Hex число
        }
    }

    auto findInt = atoi(word.c_str());
    auto findFloat = atof(word.c_str());
    if(findInt == 0 && findFloat == 0)
    {
        //cout <<"Find lable : " << word<<endl;
        return 0; //Переменная (не число)
    }
    else
    {
        if(findInt < findFloat)
        {
            //cout <<"Find float : " << word<<endl;
            return -1; //Дробное
        }
        else
        {
            //cout <<"Find int : " << word<<endl;
            return 1; //Целое число
        }
    }
}

string Scanner::getLastlex(unsigned int row)
{
    auto map1 = map_word_lex.at(row);
    auto map2 = map1[map1.size()-1].rend();
    LexClass map3 = map2->first; //Лежит предыдущая лексема
    auto map4 = map2->second; //Лежит предыдущая лексема
    auto map5 = map4.rend(); //Лежит предыдущая лексема
    auto lastLex = map5->second; //Лежит предыдущая лексема

    return lastLex;
}

string Scanner::getlex(unsigned int row, unsigned int positionLex)
{
    auto map1 = map_word_lex.at(row);
    auto map2 = map1[positionLex].rend();
    LexClass map3 = map2->first; //Лежит предыдущая лексема
    auto map4 = map2->second; //Лежит предыдущая лексема
    auto map5 = map4.rend(); //Лежит предыдущая лексема
    auto lastLex = map5->second; //Лежит предыдущая лексема

    return lastLex;
}

string Scanner::getFirslex(unsigned int row)
{
    auto map1 = map_word_lex.at(row);
    auto map2 = map1[0].rbegin();
    LexClass map3 = map2->first; //Лежит первая лексема
    auto map4 = map2->second; //Лежит первая лексема
    auto map5 = map4.rbegin(); //Лежит первая лексема
    auto lastLex = map5->second; //Лежит первая лексема

    return lastLex;
}


//Код обхода по всем функциям видимости

//                    for (auto it = listItemSpaces.rbegin(); it != listItemSpaces.rend(); ++it)
//                    {
//                        auto itemIt = *it;
//                        if(itemIt->variables.empty()) //если нет ни одной объявленной переменной то проверить в других областях видимсоти
//                        {
//                            continue;
//                        }

//                        for(auto item : itemIt->variables)
//                        {
//                            //написать проверку на меременную
//                            auto nameWord = item.first.begin()->second;
//                            if(word == nameWord)
//                            {
//                                //Значит дананя переменная уже есть
//                                findWord = true;
//                                break;
//    //                            //Значит дананя переменная уже есть
//    //                            //Так как мы были в '=' значит ошибка присваения
//    //                            cout<<endl;
//    //                            cout <<"Row["<<row<<"] ) ERROR : Redeclaring a declared variable = '" <<word<<"'"<<endl;
//    //                            cout<<endl;
//    //                            return false;
//                            }

//                        }
//                    }
