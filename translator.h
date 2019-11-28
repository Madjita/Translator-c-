#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>

#include <QDebug>
#include <QFile>

#include <QMap>

////------------------------------------------------------------------------------
//// Список лексем разрабатываемого языка программирования
////------------------------------------------------------------------------------
/*enum LexClass2
{
    lcLCircle,			// круглые скобки '('
    lcRCircle,			// круглые скобки ')'
    lcLSquare,			// квадратные скобки '['
    lcRSquare,			// квадратные скобки ']'
    lcLFigure,			// фигурные скобки '{'
    lcRFigure,			// фигурные скобки '}'

    lcTab,              //табуляций '\t'

    lcPoint,			// точка '.'
    lcComma,			// запятая ','
    lcSemicolon,		// точка с запятой ';'
    lcColon,			// двоеточие ':'

    lc2Points,			// две точки подряд '..'

    lcImpersant,		// имперсант '&'
    lcRoof,				// крышка '^'
    lcStick,			// палка '|'
    lcWave,				// ~

    lcStar,				// звездочка '*'
    lcSlash,			// деление '/'
    lcPlus,				// плюс '+'
    lcMinus,			// минус '-'

    lcAssign,			// присваивание ':='
    lcEqual,			// равенство '='
    lcNotEqual,			// не равно '#'
    lcSmaller,			// меньше '<'
    lcLarger,			// больше '>'
    lcSmallerEQ,		// меньше или равно '<='
    lcLargerEQ,			// больше или равно '>='

    lcNoValue,			// нет значения ''

    lcError,			// ошибка


    lcComment,			// комментарий
    lcSpace,			// пустой
    lcIgnore,			// игнорируемый

    lcIntNum,			// целое число
    lcRealNum,			// действительное число

    lcCharConst,		// символ
    lcString,			// строка

    lcId,				// идентификатор
    lcLabel,			// метка
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

    kwBOOL,				// BOOLEAN
    kwUNSINT,			// UNSIGNED
    kwINT,				// INTEGER
    kwCHAR				// CHAR
    //kwREAL				// REAL
};
*/

class Translator : public QObject
{
    Q_OBJECT
public:
    explicit Translator(QString fileName,QObject *parent = nullptr);

    //--------------------------------------------------------------------------
    // проверка на конец файла
    //--------------------------------------------------------------------------
    bool EndOfFile();

    //--------------------------------------------------------------------------
    // берет из файла очередной символ, фиксирует его значение
    //--------------------------------------------------------------------------
    bool Next();

    //--------------------------------------------------------------------------
    // Разбивание строки на слова.
    //--------------------------------------------------------------------------
    void Split(QString str);
signals:

private slots:



    // возвращается назад на один символ
    void Prev();

private:
    int _row;           // текущая строка
    int _column;		//    -    столбец

    long long _position;	// запомненная позиция
    int _prevColumn;		// предыдущий столбец
    char _value;            // значение текущего символа

   // QVector<LexClass2> _words_lex; // лексемы слов

    QStringList _words;
    QString _word;          //слово

    QFile _in;
    QTextStream* _readStreem = nullptr;


  //  LexClass _lc;			// класс лексемы
};

#endif // TRANSLATOR_H
