#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QtGui/QDialog>
#include <QTreeWidgetItem>
#include "pephighlighter.h" // For syntax highlighting
#include "cpphighlighter.h"
#include "enu.h"

namespace Ui {
    class HelpDialog;
}

class HelpDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(HelpDialog)
public:
    explicit HelpDialog(QWidget *parent = 0);
    virtual ~HelpDialog();

    void machineLanguageClicked();
    void assemblyLanguageClicked();
    void memoryDumpClicked();
    void breakPointsClicked();
    void symbolicTraceClicked();
    void byteConverterClicked();
    void interruptHandlersClicked();
    void instructionSetClicked();
    void dotCommandsClicked();
    void addressingModesClicked();
    void examplesClicked();
    void operatingSystemClicked();
    QString getCode(Enu::EPane &destPane, Enu::EPane &inputDest, QString &input);

    bool hasFocus();
    // Post: returns true if either of the text edits have focus

    void copy();
    // Post: the text edit that has focus has the copy() operation performed

private:
    Ui::HelpDialog *m_ui;

    void selectItem(QString string);
    PepHighlighter *leftHighlighter;
    CppHighlighter *rightCppHighlighter;
    PepHighlighter *rightPepHighlighter;

    enum Row {
        eWRITING = 0,
        eDEBUGGING = 1,
        eINTERRUPT = 2,
        eREFERENCE = 3,
        eEXAMPLES = 4,
        eOS = 5,

        eASSEMBLY = 1,
        eMACHINE = 0,

        eMEMORYDUMP = 0,
        eBREAK = 1,
        eSYMTRACE = 2,
        eBYTECONVERTER = 3,

        eINSTRUCTION = 0,
        eDOTCMD = 1,
        eADDRMODE = 2,

        eFIG432 = 0,
        eFIG434 = 1,
        eFIG435 = 2,
        eFIG436 = 3,
        eFIG503  = 4,
        eFIG506  = 5,
        eFIG507  = 6,
        eFIG510 = 7,
        eFIG511 = 8,
        eFIG512 = 9,
        eFIG513 = 10,
        eFIG514a= 11,
        eFIG514b= 12,
        eFIG515 = 13,
        eFIG516 = 14,
        eFIG518 = 15,
        eFIG521 = 16,
        eFIG526 = 17,
        eFIG601 = 18,
        eFIG604 = 19,
        eFIG606 = 20,
        eFIG608 = 21,
        eFIG610 = 22,
        eFIG612 = 23,
        eFIG614 = 24,
        eFIG616 = 25,
        eFIG618 = 26,
        eFIG621 = 27,
        eFIG623 = 28,
        eFIG625 = 29,
        eFIG627 = 30, // Interactive input
        eFIG629 = 31, // Interactive input
        eFIG632 = 32,
        eFIG634 = 33,
        eFIG636 = 34,
        eFIG638 = 35,
        eFIG640 = 36, // Interactive input
        eFIG641 = 37,
        eFIG643 = 38,
        eFIG645 = 39,
        eFIG647 = 40,
    };

private slots:
    void onCurrentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*);

signals:
    void clicked();
};

#endif // HELPDIALOG_H
