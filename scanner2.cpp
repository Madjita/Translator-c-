#include "scanner2.h"

//// Записываем новое имя в переменную
#define ENUM_TO_STR(ENUM) std::string(#ENUM)

vector<string> split(string str, string token , int count =0);



Scanner2::Scanner2()
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



    //Массив типов данных
    addTypes(keyVOID,"void");
    addTypes(keyBOOL,"bool");
    addTypes(keyCHAR,"char");
    addTypes(keyINT,"int");
    addTypes(keyFLOAT,"float");
    addTypes(keyDOUBLE,"double");


    //    addWordFunWords(lcFunLabel,"sizeof");
    //    addWordFunWords(lcFunLabel,"switch");
    //    addWordFunWords(lcFunLabel,"switch");



    cout << "LOL";
}

//Разбор строк на лексемы
int Scanner2::workLexer(const vector<string> &list)
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

    return 0;
}

bool Scanner2::next(string row_str, unsigned int row)
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

    bool flag_lcQuotes = false;
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

                    //Нужно отправить в функцию которая будет решать какое это ключевое слово ?
//                    if(searchKey->first == "return")
//                    {
//                        addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);

//                        word ="";
//                        continue;
//                    }

//                    if(searchKey->first == "extern")
//                    {
//                        addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);

//                        word ="";
//                        continue;
//                    }

//                    if(searchKey->first == "new")
//                    {
//                        addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);

//                        word ="";
//                        continue;
//                    }

                }
            }
            else
            {
                //Это не ключевое слово

                // Это тип данных ?
                ok = findTypeData(word);
                if(ok) // Это тип данных
                {
                    auto searchType = types.find(word);
                    // Это тип данных
                    addMapLex(row,searchType->second,toEnumString(searchType->second),searchType->first);
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


                        auto lastLex = getLastlex(row);


                        if(lastLex == "class")
                        {
                            //Проверка на переменную имени класса
                            addMapLex(row,lcLabelClass,toEnumString(lcLabelClass),word);
                            addClassWords(lcLabelClass,word);
                            word ="";
                            continue;
                        }



                        ok = findTypeData(lastLex);
                        if(ok)
                        {
                            //Предыдущее значчение является типом
                            //Значит данное значение скороее всего Имя переменоой
                            addMapLex(row,lcLabel,toEnumString(lcLabel),word);

                            ok = addWordWords(lcLabel,word); // добавили переменную в массив переменных
                            if(ok)
                                cout << "Add WordWords : " << word<<endl;
                            else
                                cout << "Don't add WordWords : " << word<<endl;
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
                                ok = findWordWords(word);
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
                                        addMapLex(row,lcType,toEnumString(lcType),word);
                                        addTypes(lcType,word); // добавили тип данных в массив переменных
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
                        if(ok)
                            cout << "Add WordWords : " << word<<endl;
                        else
                            cout << "Don't add WordWords : " << word<<endl;

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
                ok = findWordWords(word);
                if(ok)
                {
                    //Значит данное значение скороее всего Имя переменоой
                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);
                }
                else
                {
                    //Значит данное значение скороее всего Имя переменоой
                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);

                    ok = addWordWords(lcLabel,word); // добавили переменную в массив переменных
                    if(ok)
                        cout << "Add WordWords : " << word<<endl;
                    else
                        cout << "Don't add WordWords : " << word<<endl;
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
                        //                    case '+':

                        //                        addMapLex(row,lcPlus,toEnumString(lcPlus),"+=");
                        //                        break;
                        //                    case '-':

                        //                        addMapLex(row,lcMinus,toEnumString(lcMinus),"-=");
                        //                        break;
                        //                    case '*':

                        //                        addMapLex(row,lcStar,toEnumString(lcStar),"*=");
                        //                        break;
                        //                    case '%':

                        //                        addMapLex(row,lcPercent,toEnumString(lcPercent),"%=");
                        //                        break;
                        //                    case '/':

                        //                        addMapLex(row,lcSlash,toEnumString(lcSlash),"/=");
                        //                        break;
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
                //Значит Есть только '|' а это ошибка
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
                    // if(searchKey->first == "if")
                    //  {
                    addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);
                    //}

                    // if(searchKey->first == "for")
                    // {
                    // addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);
                    //}
                }
                else
                {
                    //Происходит вызов функции в одну строчку
                    addMapLex(row,lcFunLabel,toEnumString(lcFunLabel),word);
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

            if(word.size() > 0)
            {

                auto serchFirslex = getFirslex(row);
                bool ok = false;

                ok = findTypeData(serchFirslex);
                if(ok)
                {
                    //Значит данное значение скороее всего Имя переменоой
                    addMapLex(row,lcLabel,toEnumString(lcLabel),word);

                    ok = addWordWords(lcLabel,word); // добавили переменную в массив переменных
                    if(ok)
                        cout << "Add WordWords : " << word<<endl;
                    else
                        cout << "Don't add WordWords : " << word<<endl;

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

            //Значит данное значение скороее всего Имя переменоой
            auto serchFirslex = getFirslex(row);
            bool ok = false;

            ok = findTypeData(serchFirslex);
            if(ok)
            {
                //Значит данное значение скороее всего Имя переменоой
                addMapLex(row,lcLabel,toEnumString(lcLabel),word);

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
                }
            }

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
                    addMapLex(row,searchKey->second,toEnumString(searchKey->second),searchKey->first);
                }
                else
                {
                    // Это тип данных ?
                    bool ok = findTypeData(word);
                    if(ok) // Это тип данных
                    {
                        auto searchType = types.find(word);
                        // Это тип данных
                        addMapLex(row,searchType->second,toEnumString(searchType->second),searchType->first);
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
                                ok = addWordWords(lcLabel,word); // добавили переменную в массив переменных
                                if(ok)
                                    cout << "Add WordWords : " << word<<endl;
                                else
                                    cout << "Don't add WordWords : " << word<<endl;
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
            //Проверка на переменную имени класса
            addMapLex(row,lcLabelClass,toEnumString(lcLabelClass),word);
            addClassWords(lcLabelClass,word);
        }

    }


    return true;
}

void Scanner2::zapolnenieOperationsPriorityForward(vector<string> operands, int priority, int forward)
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

void Scanner2::addMapLex(int row,LexClass lex, string lex_str, string data, int position)
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

void Scanner2::replaceLastMapLex(int row, LexClass lex, string lex_str, string data, int position)
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
void Scanner2::addKeyWords(LexClass data, string key)
{
    //    map<LexClass,string> map_keyWords;
    //    map_keyWords.insert(make_pair(key,data));
    //    keyWords.push_back(map_keyWords);

    keyWords.insert(make_pair(key,data));
}

//Добавление типов данных
void Scanner2::addTypes(LexClass data, string key)
{
    //    map<LexClass,string> map_types;
    //    map_types.insert(make_pair(key,data));
    //    types.push_back(map_types);

    types.insert(make_pair(key,data));
}

bool Scanner2::addWordWords(LexClass data, string key)
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

bool Scanner2::addWordFunWords(LexClass data, string key)
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

bool Scanner2::addWordIncludes(LexClass data, string key)
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

bool Scanner2::addClassWords(LexClass data, string key)
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

string Scanner2::toEnumString(LexClass lex)
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

//Поиск типа данных
bool Scanner2::findTypeData(string key)
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

bool Scanner2::findWordWords(string key)
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

bool Scanner2::findClassWords(string key)
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
int Scanner2::findLable(string word)
{

    if(word =="0")
    {
        cout <<"Find int : " << word<<endl;
        return 1; //Целое число
    }

    if(word.size() > 2)
    {
        if(word[0] == '0' && word[1] == 'x' )
        {
            cout <<"Find int : " << word<<endl;
            return 2; //Hex число
        }
    }

    auto findInt = atoi(word.c_str());
    auto findFloat = atof(word.c_str());
    if(findInt == 0 && findFloat == 0)
    {
        cout <<"Find lable : " << word<<endl;
        return 0; //Переменная (не число)
    }
    else
    {
        if(findInt < findFloat)
        {
            cout <<"Find float : " << word<<endl;
            return -1; //Дробное
        }
        else
        {
            cout <<"Find int : " << word<<endl;
            return 1; //Целое число
        }
    }

}

string Scanner2::getLastlex(int row)
{
    auto map1 = map_word_lex.at(row);
    auto map2 = map1[map1.size()-1].rend();
    LexClass map3 = map2->first; //Лежит предыдущая лексема
    auto map4 = map2->second; //Лежит предыдущая лексема
    auto map5 = map4.rend(); //Лежит предыдущая лексема
    auto lastLex = map5->second; //Лежит предыдущая лексема

    return lastLex;
}

string Scanner2::getFirslex(int row)
{
    auto map1 = map_word_lex.at(row);
    auto map2 = map1[0].rbegin();
    LexClass map3 = map2->first; //Лежит первая лексема
    auto map4 = map2->second; //Лежит первая лексема
    auto map5 = map4.rbegin(); //Лежит первая лексема
    auto lastLex = map5->second; //Лежит первая лексема

    return lastLex;
}

