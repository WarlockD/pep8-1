#include "cpupane.h"
#include "ui_cpupane.h"
#include "sim.h"
#include "pep.h"
#include "enu.h"

CpuPane::CpuPane(QWidget *parent) :
        QWidget(parent),
        m_ui(new Ui::CpuPane)
{
    m_ui->setupUi(this);
}

CpuPane::~CpuPane()
{
    delete m_ui;
}

void CpuPane::updateCpu() {
    Enu::EAddrMode addrMode = Pep::decodeAddrMode[Sim::instructionSpecifier];

    m_ui->cpuNLabel->setText(Sim::nBit ? "1" : "0");
    m_ui->cpuZLabel->setText(Sim::zBit ? "1" : "0");
    m_ui->cpuVLabel->setText(Sim::vBit ? "1" : "0");
    m_ui->cpuCLabel->setText(Sim::cBit ? "1" : "0");

    m_ui->cpuAHexLabel->setText(QString("0x") + QString("%1").arg(Sim::accumulator, 4, 16, QLatin1Char('0')).toUpper());
    m_ui->cpuADecLabel->setText(QString("%1").arg(Sim::toSignedDecimal(Sim::accumulator)));

    m_ui->cpuXHexLabel->setText(QString("0x") + QString("%1").arg(Sim::indexRegister, 4, 16, QLatin1Char('0')).toUpper());
    m_ui->cpuXDecLabel->setText(QString("%1").arg(Sim::toSignedDecimal(Sim::indexRegister)));

    m_ui->cpuSPHexLabel->setText(QString("0x") + QString("%1").arg(Sim::stackPointer, 4, 16, QLatin1Char('0')).toUpper());
    m_ui->cpuSPDecLabel->setText(QString("%1").arg(Sim::stackPointer));

    m_ui->cpuPCHexLabel->setText(QString("0x") + QString("%1").arg(Sim::programCounter, 4, 16, QLatin1Char('0')).toUpper());
    m_ui->cpuPCDecLabel->setText(QString("%1").arg(Sim::programCounter));

    m_ui->cpuInstrSpecBinLabel->setText(QString("%1").arg(Sim::instructionSpecifier, 8, 2, QLatin1Char('0')).toUpper());
    m_ui->cpuInstrSpecMnemonLabel->setText(" " + Pep::enumToMnemonMap.value(Pep::decodeMnemonic[Sim::instructionSpecifier])
                                           + Pep::commaSpaceToAddrMode(addrMode));

    if (Pep::decodeAddrMode.value(Sim::instructionSpecifier) == Enu::NONE) {
        m_ui->cpuOprndSpecHexLabel->setText("");
        m_ui->cpuOprndSpecDecLabel->setText("");
        m_ui->cpuOprndHexLabel->setText("");
        m_ui->cpuOprndDecLabel->setText("");
    }
    else {
        m_ui->cpuOprndSpecHexLabel->setText(QString("0x") + QString("%1").arg(Sim::operandSpecifier, 4, 16, QLatin1Char('0')).toUpper());
        m_ui->cpuOprndSpecDecLabel->setText(QString("%1").arg(Sim::toSignedDecimal(Sim::operandSpecifier)));
        m_ui->cpuOprndHexLabel->setText(QString("0x") + QString("%1").arg(Sim::readWordOprnd(addrMode), 4, 16, QLatin1Char('0')).toUpper());
        m_ui->cpuOprndDecLabel->setText(QString("%1").arg(Sim::toSignedDecimal(Sim::readWordOprnd(addrMode))));
    }
}

void CpuPane::clearCpu()
{
    m_ui->cpuNLabel->setText("");
    m_ui->cpuZLabel->setText("");
    m_ui->cpuVLabel->setText("");
    m_ui->cpuCLabel->setText("");

    m_ui->cpuAHexLabel->setText("");
    m_ui->cpuADecLabel->setText("");

    m_ui->cpuXHexLabel->setText("");
    m_ui->cpuXDecLabel->setText("");

    m_ui->cpuSPHexLabel->setText("");
    m_ui->cpuSPDecLabel->setText("");

    m_ui->cpuPCHexLabel->setText("");
    m_ui->cpuPCDecLabel->setText("");

    m_ui->cpuInstrSpecBinLabel->setText("");
    m_ui->cpuInstrSpecMnemonLabel->setText("");

    m_ui->cpuOprndSpecHexLabel->setText("");
    m_ui->cpuOprndSpecDecLabel->setText("");
    m_ui->cpuOprndHexLabel->setText("");
    m_ui->cpuOprndDecLabel->setText("");
}

void CpuPane::runClicked() {
    m_ui->pepTraceLoadCheckBox->setChecked(false);
    m_ui->pepTraceProgramCheckBox->setChecked(false);
    m_ui->pepTraceTrapsCheckBox->setChecked(false);
}

void CpuPane::startDebuggingClicked() {
    if (m_ui->pepTraceLoadCheckBox->isChecked() || m_ui->pepTraceProgramCheckBox->isChecked() || m_ui->pepTraceTrapsCheckBox->isChecked()) {
        // do nothing
    } else {
        m_ui->pepTraceProgramCheckBox->setChecked(true);
    }
}

void CpuPane::setExecutionState(bool b)
{
    m_ui->pepTraceLoadCheckBox->setDisabled(b);
    m_ui->pepTraceProgramCheckBox->setDisabled(b);
    m_ui->pepTraceTrapsCheckBox->setDisabled(b);
}

void CpuPane::highlightOnFocus()
{
    if (m_ui->pepCpuLabel->hasFocus()) { // Never has focus, which is fine
        m_ui->pepCpuLabel->setAutoFillBackground(true);
    }
    else {
        m_ui->pepCpuLabel->setAutoFillBackground(false);
    }
}

bool CpuPane::hasFocus()
{
    return m_ui->pepCpuLabel->hasFocus();
}

void CpuPane::undo()
{
    // does nothing with our current implementation
}

void CpuPane::redo()
{
    // does nothing with our current implementation
}

void CpuPane::cut()
{
    // does nothing with our current implementation
}

void CpuPane::copy()
{
    // does nothing with our current implementation
}

void CpuPane::paste()
{
    // does nothing with our current implementation
}
