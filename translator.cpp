#include "translator.h"



Translator::Translator(QString fileName, QObject *parent) : QObject(parent),
    _row(1),
    _column(0)
{
    _position = -1;

    _in.setFileName(fileName);

    if(_in.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        _readStreem = new QTextStream(&_in);
    }
    else {
        qDebug() << "Can't open file " + fileName + " for reading";
    }
}

//--------------------------------------------------------------------------
// проверка на конец файла
//--------------------------------------------------------------------------
bool Translator::EndOfFile()
{
    return _readStreem->atEnd();
  //  return false;
//    if(_value == '\0')
//    {
//        Next();
//        return true ; //_in.atEnd();
//    }
//    else {
//        return false;
//    }
}

//--------------------------------------------------------------------------
// берет из файла очередной символ, фиксирует его значение
//--------------------------------------------------------------------------
bool Translator::Next()
{
   bool flag = true;
   auto str = _readStreem->readLine();

   qDebug() << "=======================================================";
   qDebug() << "Current:\t[ " << _row  <<" ]\t" << qPrintable(str);

   _words.clear();

   Split(str);
   qDebug() << "Split:\t";

   for(int i=0; i < _words.count();i++)
   {

       qDebug() << "[ " << _row  << ", " <<_column-(_words.count()-(i+1)) << " ]\t" << qPrintable(_words[i]); //.toLocal8Bit().data()
   }


   if(_readStreem->atEnd())
   {
       qDebug () << "END";
       flag = true;
   }
   else {

       flag = false;
   }


    _row++;
    _column = 0;

    return flag;

  //  *_readStreem >> _value;


//    _prevColumn = _column;
//    if(_value == '\n')
//    {
//        _row++;
//        _column = 0;

//         qDebug() << "[ " << _row  << ", " <<_column << " ]\t" << _word;
//        _word = "";
//    }
//    else
//    {
//        _column++;

//        if(_value != ' ')
//        {
//            if(_value != '\t')
//            {
//                _word +=_value;
//            }
//        }
//        else {
//            qDebug() << "[ " << _row  << ", " <<_column << " ]\t" << _word;
//            _word = "";
//        }

//        // qDebug() << "[ " << _row  << ", " <<_column << " ]\t" << _word;
//    }



}

//Разбить строку
void Translator::Split(QString str)
{

    QString split_str = "";
    //Разбить строку
    for(int i=0; i < str.count();i++)
    {
        auto one = str[i].toLatin1();
        switch (one) {
        case '{':
            {
                _words.append(QString(one));
              //  _words_lex.append(lcLFigure); // Добавить лексему {
                split_str = "";
                break;
            }
        case '}':
            {
                if(split_str != "")
                {
                    _words.append(split_str);

                }

                _words.append(QString(one));
               // _words_lex.append(lcLFigure); // Добавить лексему }

                //Код для вставки ; после } скобочек
//                if(i+1 < str.count())
//                {
//                   _words.append(QString(str[i+1].toLatin1()));
//                }
                split_str = "";
                break;
            }
        case '(':
            {
                if(split_str != "")
                {
                    _words.append(split_str);
                }
                _words.append(QString(one));
                split_str = "";
                break;
            }
        case ')':
            {
                if(split_str != "")
                {
                    _words.append(split_str);
                }

                _words.append(QString(one));
                split_str = "";
                break;
            }
        case '=':
            {
                if(split_str != "")
                {
                    _words.append(split_str);
                }

                _words.append(QString(one));
                split_str = "";
                break;
            }
        case ' ':
            {
                if(split_str != "")
                {

                  _words.append(split_str);
                  split_str = "";
                }
                break;
            }
        case '\t':
            {
                if(split_str != "")
                {
                  _words.append(split_str);
                  split_str = "";
                }
                break;
            }
        case ',':
            {
                if(split_str != "")
                {
                  _words.append(split_str);
                  _words.append(QString(one));
                  split_str = "";
                }
                break;
            }
        case ';':
            {
                if(split_str != "")
                {
                  _words.append(split_str);
                  _words.append(QString(one));
                  split_str = "";
                }
                break;
            }
        default:
            {

                //Переменная для слова
                split_str+=str[i];

                // НЕ разбирать коментарии (выход из цикла)
                if(split_str == "//")
                {
                  split_str = "";
                  i = str.count();
                  break;
                }
            }
        }
    }

    if(split_str != "")
    {
        _words.append(split_str);
        split_str = "";
    }



    //Подсчитать количество слов в строке;
    _column = _words.count();
}

// возвращается назад на один символ
void Translator::Prev()
{
    if(_value == '\n')
        _row--;
    _column = _prevColumn - 1;

    _readStreem->seek(_readStreem->pos()-1);

//    _in.unget();
//    _in.unget();
//    _in.get(_value);
}
