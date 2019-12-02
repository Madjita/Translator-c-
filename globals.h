#ifndef GLOBALS_H
#define GLOBALS_H

////------------------------------------------------------------------------------
//// Список лексем разрабатываемого языка программирования
////------------------------------------------------------------------------------
enum LexClass
{

    //Реализованные
    lcNull,
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

    lcWave,				// ~
    lcLink,             // ссылка '->'
    lcPoint,			// точка '.'
    lcStick,			// палка '|'
    lcDoubleStick,		// 2 палки '||'
    lcRoof,				// крышка '^'
    lcQuotes,           //Кавычки '"'
    lcType,             //Тип данных
    lcTypeTemplate,     //Тип данных Составной (шаблонный)
    lcTypeStar,         //Тип данных + Указатель
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
    keyUSING,

    //Временные (реализованны из STD ) может нужно убрать как функции а не ключевые слова
    keyCOUT,
    keyENDL,



    //Еще нету

    lcTab,              //табуляций '\t'
    lc2Points,			// две точки подряд '..'

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


#endif // GLOBALS_H
