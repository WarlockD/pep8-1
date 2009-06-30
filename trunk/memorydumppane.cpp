#include "memorydumppane.h"
#include "ui_memorydumppane.h"
#include "sim.h"

MemoryDumpPane::MemoryDumpPane(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::MemoryDumpPane)
{
    m_ui->setupUi(this);

    QObject::connect(m_ui->pepMemRefreshButton, SIGNAL(clicked()), this, SLOT(on_pepMemRefreshButton_clicked()));
}

MemoryDumpPane::~MemoryDumpPane()
{
    delete m_ui;
}

void MemoryDumpPane::refreshMemory()
{
    QStringList memoryDump;
    QString memoryDumpLine;
    QChar ch;
    for (int i = 0; i < 65536; i += 8) {
        memoryDumpLine = "";
        memoryDumpLine.append(QString("%1 | ").arg(i, 4, 16, QLatin1Char('0')).toUpper());
        for (int j = 0; j < 8; j++) {
            memoryDumpLine.append(QString("%1 ").arg(Sim::Mem[i + j], 2, 16, QLatin1Char('0')).toUpper());
        }
        memoryDumpLine.append("|");
        for (int j = 0; j < 8; j++) {
            ch = QChar(Sim::Mem[i + j]);
            if (ch.isPrint()) {
                memoryDumpLine.append(ch);
            } else {
                memoryDumpLine.append(".");
            }
        }
        memoryDump.append(memoryDumpLine);
    }
    m_ui->pepMemoryDumpTextEdit->setText(memoryDump.join("\n"));
}

int MemoryDumpPane::memDumpPaneWidth()
{
    return 300;
//    QTextCursor cursor(m_ui->pepMemoryDumpTextEdit->document());
//    cursor.setPosition(0);
//    cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
//    m_ui->pepMemoryDumpTextEdit->lineWidth()
}

void MemoryDumpPane::highlightOnFocus()
{
    if (m_ui->pepMemoryDumpTextEdit->hasFocus()) {
        m_ui->pepMemoryDumpLabel->setAutoFillBackground(true);
    }
    else {
        m_ui->pepMemoryDumpLabel->setAutoFillBackground(false);
    }
}

bool MemoryDumpPane::hasFocus()
{
    return m_ui->pepMemoryDumpTextEdit->hasFocus();
}

void MemoryDumpPane::undo()
{
    // does nothing with our current implementation
}

void MemoryDumpPane::redo()
{
    // does nothing with our current implementation
}

void MemoryDumpPane::cut()
{
    // read only pane, not allowed
}

void MemoryDumpPane::copy()
{
    m_ui->pepMemoryDumpTextEdit->copy();
}

void MemoryDumpPane::paste()
{
    // does nothing with our current implementation
}

void MemoryDumpPane::on_pepMemRefreshButton_clicked()
{
    int scrollBarPosition = m_ui->pepMemoryDumpTextEdit->verticalScrollBar()->value();
    refreshMemory();
    m_ui->pepMemoryDumpTextEdit->verticalScrollBar()->setValue(scrollBarPosition);
}



