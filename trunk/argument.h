#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "asm.h"
#include "pep.h"

// Abstract Argument class
class Argument
{
    friend class Asm;
public:
    virtual ~Argument() { }
    virtual int getArgumentValue() = 0;
    virtual QString getArgumentString() = 0;
};

// Concrete argument classes
// All methods are defined in this argument.h file.
class CharArgument: public Argument
{
    friend class Asm;
private:
    QString charValue;
public:
    CharArgument(QString cValue) { charValue = cValue; }
    int getArgumentValue() { return Asm::charStringToInt(charValue); }
    QString getArgumentString() { return charValue; }
};

class DecArgument: public Argument
{
private:
    int decValue;
public:
    DecArgument(int dValue) { decValue = dValue; }
    int getArgumentValue() { return decValue; }
    QString getArgumentString() { return QString("%1").arg(decValue); }
};

class HexArgument: public Argument
{
private:
    int hexValue;
public:
    HexArgument(int hValue) { hexValue = hValue; }
    int getArgumentValue() { return hexValue; }
    QString getArgumentString() { return "0x" + QString("%1").arg(hexValue, 4, 16, QLatin1Char('0')).toUpper(); }
};

class StringArgument: public Argument
{
private:
    QString stringValue;
public:
    StringArgument(QString sValue) { stringValue = sValue; }
    int getArgumentValue() {
        if (stringValue.length() == 1) {
            return stringValue[0].toAscii();
        }
        else {
            return stringValue[1].toAscii() + 256 * stringValue[0].toAscii();
        }
    }
    QString getArgumentString() { return stringValue; }
};

class SymbolRefArgument: public Argument
{
private:
    QString symbolRefValue;
public:
    SymbolRefArgument(QString sRefValue) { symbolRefValue = sRefValue; }
    int getArgumentValue() { return Pep::symbolTable.value(symbolRefValue); }
    QString getArgumentString() { return symbolRefValue; }
};

#endif // ARGUMENT_H
