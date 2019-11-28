#ifndef SCANNER2_H
#define SCANNER2_H

#include <iostream>
#include <vector>

#include <mutex>
#include <semaphore.h>
#include <condition_variable>
#include <future>

#include <str_switch.h>

#include <map>
#include <list>

using namespace std;


////------------------------------------------------------------------------------
//// Список лексем разрабатываемого языка программирования
////------------------------------------------------------------------------------
enum LexClass
{

    //Реализованные

    lcLCircle,			// круглые скобки '('
    lcRCircle,			// круглые скобки ')'
    lcLSquare,			// квадратные скобки '['
    lcRSquare,			// квадратные скобки ']'
    lcLFigure,			// фигурные скобки '{'
    lcRFigure,			// фигурные скобки '}'

    lcQuestion,         // вопрос ?
    lcPercent,          // остаток от деления %
    lcExclamatory,      // восклицательный ! ( отрицание)
    lcNotEqual,         // Не равно '!='
    lcAssign,			// присваивание ':=' или '='
    lcEqual,			// равенство '=='
    lcLattice,          // include '#'
    lcInclude,			// include
    lcSmaller,			// меньше '<'
    lcLarger,			// больше '>'
    lcSmallerEQ,		// меньше или равно '<='
    lcLargerEQ,			// больше или равно '>='

    lcLink,             // ссылка '->'
    lcPoint,			// точка '.'
    lcStick,			// палка '|'
    lcDoubleStick,		// 2 палки '||'
    lcRoof,				// крышка '^'
    lcQuotes,           //Кавычки '"'
    lcType,             //Тип данных
    lcApostrophe,       //Апостроф '
    lcComma,			// запятая ','
    lcSemicolon,		// точка с запятой ';'
    lcColon,			// двоеточие ':'
    lcImpersant,		// имперсант '&'
    lcDoubleImpersant,  // 2 имперсант '&&'

    lcStar,				// звездочка '*'
    lcSlash,			// деление '/'
    lcPlus,				// плюс '+'
    lcMinus,			// минус '-'
    lcCharConst,		// символ


    lcLabelClass,       // метка имени класса
    lcLabel,			// метка
    lcFunLabel,         // метка функции


    //Типы данных
    kwBOOL,				// BOOLEAN
    kwINT,				// INTEGER
    kwFLOAT,			// FLOAT
    kwDOUBLE,			// DOUBLE
    kwCHAR,				// CHAR
    kwVOID,             // VOID
    kwSTRING,			// строка


    //Ключевые слова
    keyASM,
    keyAUTO,
    keyBREAK,
    keyCASE,
    keyCATCH,
    keyCHAR,
    keyCLASS,
    keyCONST,
    keyCONTINUE,
    keyCONSTEXPR,
    keyDEFAULT,
    keyDELETE,
    keyDO,
    keyDOUBLE,
    keyELSE,
    keyENUM,
    keyEXPLICIT,
    keyEXTERN,
    keyFLOAT,
    keyFOR,
    keyFRIEND,
    keyGOTO,
    keyIF,
    keyINLINE,
    keyINT,
    keyLONG,
    keyMUTABLE,
    keyNEW,
    keyOPERATOR,
    keyPRIVATE,
    keyPROTECTED,
    keyPUBLIC,
    keyREGISTER,
    keyRETURN,
    keySHORT,
    keySIGNED,
    keySIZEOF,
    keySTATIC,
    keySTRUCT,
    keySWITCH,
    keyTEMPLATE,
    keyTHIS,
    keyTHROW,
    keyTRY,
    keyTYPEDEF,
    keyTYPENAME,
    keyTRUE,
    keyFALSE,
    keyUNION,
    keyUNSIGNED,
    keyVIRTUAL,
    keyVOID,
    keyVOLATILE,
    keyWHILE,
    keyBOOL,
    keyNAMESPACE,
    keyNULLPTTR,
    keySTATIC_CAST,



    //Еще нету

    lcTab,              //табуляций '\t'



    lc2Points,			// две точки подряд '..'




    lcWave,				// ~



    lcNoValue,			// нет значения ''

    lcError,			// ошибка


    lcComment,			// комментарий
    lcSpace,			// пустой
    lcIgnore,			// игнорируемый

    lcIntNum,			// целое число
    lcRealNum,			// действительное число
    lcFloatNum,         // дробное число




    lcId,				// идентификатор

    //lcQualident,        // квалидент (двойной идентификатор)

    lcEof,				// конец файла

    kwARRAY,			// ARRAY
    kwBEGIN,			// BEGIN
    kwBY,				// BY
    kwCASE,				// CASE
    kwCONST,			// CONST
    kwDELETE,			// DELETE
    kwDIV,				// DIV
    kwDO,				// DO
    kwELSE,				// ELSE
    kwELSIF,			// ELSEIF
    kwEND,				// END
    kwEXIT,				// EXIT
    kwFALSE,			// FALSE
    kwFINALIZE,			// FINALIZE
    kwFOR,				// FOR
    kwGOTO,				// GOTO
    kwIF,				// IF
    kwIMPORT,			// IMPORT
    kwIN,				// IN
    kwIS,				// IS
    kwLOCAL,			// LOCAL
    kwLOOP,				// LOOP
    kwMOD,				// MOD
    kwMODULE,			// MODULE module
    kwNIL,				// NIL
    kwNEW,				// NEW
    kwOF,				// OF
    kwOR,				// OR
    kwPOINTER,			// POINTER
    kwPROCEDURE,		// PROCEDURE
    kwRECORD,			// RECORD
    kwREPEAT,			// REPEAT
    kwRETURN,			// RETURN
    kwTHEN,				// THEN
    kwTO,				// TO
    kwTRUE,				// TRUE
    kwTYPE,				// TYPE
    kwUNTIL,			// UNTIL
    kwVAR,				// VAR
    kwWHILE,			// WHILE
    kwWITH,				// WITH
    kwXOR,				// XOR

    kwDEFINITION,		// DEFINITION


    kwUNSINT,			// UNSIGNED
    //kwREAL,				// REAL




};


class Scanner2
{
public:
    Scanner2();



    int workLexer(const vector<string> &list);


    bool next(string row_str, unsigned int row);



    vector<string> list_word_lex_string;

private:
    void zapolnenieOperationsPriorityForward(vector<string> operands, int priority, int forward);
    void addMapLex(int row,LexClass lex,string lex_str,string data,int position = 0);
    void replaceLastMapLex(int row,LexClass lex,string lex_str,string data,int position = 0);

    //Вспомогательная функция
    void addKeyWords(LexClass data, string key); //функция добавления слова в массив Ключевых слов
    void addTypes(LexClass data, string key); //функция добавления слова в массив Типов данных
    bool addWordWords(LexClass data, string key); //функция добавления слова в массив Имен переменных
    bool addWordFunWords(LexClass data, string key);// функция добавления слова в массив Имен функций
    bool addWordIncludes(LexClass data, string key);// функция добавления слова в массив инклудов
    bool addClassWords(LexClass data, string key);// функция добавления слова в массив классов
    string toEnumString(LexClass lex);


    bool findTypeData(string key); //Поиск типа данных;
    bool findWordWords(string key); //Поиск имени переменных;
    bool findClassWords(string key); //Поиск имени классов;

    int findLable(string word); //Поиск целого числа, дробного или перменной;


    string getLastlex(int row);
    string getFirslex(int row);


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
 };

#endif // SCANNER2_H
