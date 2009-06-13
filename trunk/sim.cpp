#include "sim.h"
#include "pep.h"
#include <QDebug>

using namespace Enu;

// The machine
QVector<int> Sim::Mem(65536);
bool Sim::nBit, Sim::zBit, Sim::vBit, Sim::cBit;
int Sim::accumulator;
int Sim::indexRegister;
int Sim::stackPointer;
int Sim::programCounter;
int Sim::instructionSpecifier;
int Sim::operandSpecifier;

void Sim::loadMem(QList<int> objectCodeList) {
    for (int i = 0; objectCodeList.length() > 0; i++) {
        Mem[i] = objectCodeList.takeAt(0);
    }
}

int Sim::readByte(int memAddr)
{
    return Mem[memAddr % 65536];
}

int Sim::readWord(int memAddr)
{
    return 256 * Mem[memAddr % 65536] + Mem[(memAddr + 1) % 65536];
}

int Sim::readByteOprnd(Enu::EAddrMode addrMode)
{
    switch (addrMode) {
    case Enu::NONE:
        break;
    case Enu::I:
        return operandSpecifier;
    case Enu::D:
        return readByte(operandSpecifier);
    case Enu::N:
        return readByte(readWord(operandSpecifier));
    case Enu::S:
        return readByte(stackPointer + operandSpecifier);
    case Enu::SF:
        return readByte(readWord(stackPointer + operandSpecifier));
    case Enu::X:
        return readByte(operandSpecifier + indexRegister);
    case Enu::SX:
        return readByte(stackPointer + operandSpecifier + indexRegister);
    case Enu::SXF:
        return readByte(readWord(stackPointer + operandSpecifier) + indexRegister);
    case Enu::ALL:
        break;
    }
    return 0;
}

int Sim::readWordOprnd(Enu::EAddrMode addrMode)
{
    switch (addrMode) {
    case Enu::NONE:
        break;
    case Enu::I:
        return operandSpecifier;
    case Enu::D:
        return readWord(operandSpecifier);
    case Enu::N:
        return readWord(readWord(operandSpecifier));
    case Enu::S:
        return readWord(stackPointer + operandSpecifier);
    case Enu::SF:
        return readWord(readWord(stackPointer + operandSpecifier));
    case Enu::X:
        return readWord(operandSpecifier + indexRegister);
    case Enu::SX:
        return readWord(stackPointer + operandSpecifier + indexRegister);
    case Enu::SXF:
        return readWord(readWord(stackPointer + operandSpecifier) + indexRegister);
    case Enu::ALL:
        break;
    }
    return 0;
}

void Sim::writeByte(int memAddr, int value)
{
    Mem[memAddr % 65536] = value;
}

void Sim::writeWord(int memAddr, int value)
{
    Mem[memAddr % 65536] = value / 256;
    Mem[(memAddr + 1) % 65536] = value % 256;
}

void Sim::writeByteOprnd(Enu::EAddrMode addrMode, int value)
{
    switch (addrMode) {
    case Enu::NONE:
        break;
    case Enu::I:
        // illegal
        break;
    case Enu::D:
        writeByte(readWord(operandSpecifier), value);
        break;
    case Enu::N:
        writeByte(readWord(readWord(operandSpecifier)), value);
        break;
    case Enu::S:
        writeByte(readWord(stackPointer + operandSpecifier), value);
        break;
    case Enu::SF:
        writeByte(readWord(readWord(stackPointer + operandSpecifier)), value);
    case Enu::X:
        writeByte(readWord(operandSpecifier + indexRegister), value);
    case Enu::SX:
        writeByte(readWord(stackPointer + operandSpecifier + indexRegister), value);
    case Enu::SXF:
        writeByte(readWord(readWord(stackPointer + operandSpecifier) + indexRegister), value);
    case Enu::ALL:
        break;
    }
}

void Sim::writeWordOprnd(Enu::EAddrMode addrMode, int value)
{
    switch (addrMode) {
    case Enu::NONE:
        break;
    case Enu::I:
        // illegal
        break;
    case Enu::D:
        writeWord(readWord(operandSpecifier), value);
        break;
    case Enu::N:
        writeWord(readWord(readWord(operandSpecifier)), value);
        break;
    case Enu::S:
        writeWord(readWord(stackPointer + operandSpecifier), value);
        break;
    case Enu::SF:
        writeWord(readWord(readWord(stackPointer + operandSpecifier)), value);
    case Enu::X:
        writeWord(readWord(operandSpecifier + indexRegister), value);
    case Enu::SX:
        writeWord(readWord(stackPointer + operandSpecifier + indexRegister), value);
    case Enu::SXF:
        writeWord(readWord(readWord(stackPointer + operandSpecifier) + indexRegister), value);
    case Enu::ALL:
        break;
    }
}

void Sim::vonNeumanStep()
{
    // Fetch
    instructionSpecifier = readByte(programCounter);
    // Increment
    programCounter = (programCounter + 1) % 65536;
    // Decode
    if (!Pep::isUnaryMap[Pep::decodeMnemonic[instructionSpecifier]]) {
        operandSpecifier = readWord(programCounter);
        programCounter = (programCounter + 2) % 65536;
    }
    // Execute
//    qDebug() << Pep::enumToMnemonMap[Pep::decodeMnemonic[instructionSpecifier]];
    switch (Pep::decodeMnemonic[instructionSpecifier]) {
    case ADDA:
        break;
    case ADDSP:
        break;
    case ADDX:
        break;
    case ANDA:
        break;
    case ANDX:
        break;
    case ASLA:
        break;
    case ASLX:
        break;
    case ASRA:
        break;
    case ASRX:
        break;
    case BR:
        break;
    case BRC:
        break;
    case BREQ:
        break;
    case BRGE:
        break;
    case BRGT:
        break;
    case BRLE:
        break;
    case BRLT:
        break;
    case BRNE:
        break;
    case BRV:
        break;
    case CALL:
        break;
    case CHARI:
        break;
    case CHARO:
        break;
    case CPA:
        break;
    case CPX:
        break;
    case DECI:
        break;
    case DECO:
        break;
    case LDA:
        break;
    case LDBYTEA:
        break;
    case LDBYTEX:
        break;
    case LDX:
        break;
    case MOVFLGA:
        break;
    case MOVSPA:
        break;
    case NEGA:
        break;
    case NEGX:
        break;
    case NOP:
        break;
    case NOP0:
        break;
    case NOP1:
        break;
    case NOP2:
        break;
    case NOP3:
        break;
    case NOTA:
        break;
    case NOTX:
        break;
    case ORA:
        break;
    case ORX:
        break;
    case RET0:
        break;
    case RET1:
        break;
    case RET2:
        break;
    case RET3:
        break;
    case RET4:
        break;
    case RET5:
        break;
    case RET6:
        break;
    case RET7:
        break;
    case RETTR:
        break;
    case ROLA:
        break;
    case ROLX:
        break;
    case RORA:
        break;
    case RORX:
        break;
    case STA:
        break;
    case STBYTEA:
        break;
    case STBYTEX:
        break;
    case STOP:
        break;
    case STRO:
        break;
    case STX:
        break;
    case SUBA:
        break;
    case SUBSP:
        break;
    case SUBX:
        break;
    default:
        qDebug() << "Invalid instruction?!";
    }
}




