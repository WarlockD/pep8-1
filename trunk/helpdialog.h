#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QtGui/QDialog>

#include <QTreeWidgetItem>

namespace Ui {
    class HelpDialog;
}

class HelpDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(HelpDialog)
public:
    explicit HelpDialog(QWidget *parent = 0);
    virtual ~HelpDialog();

private:
    Ui::HelpDialog *m_ui;

private slots:
   void on_itemClicked(QTreeWidgetItem*,int);
   void on_currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*);

public slots:
   void on_menuItem_WritingPrograms_clicked();
   void on_menuItem_MachineLanguage_clicked();
   void on_menuItem_AssemblyLanguage_clicked();
   void on_menuItem_DebuggingPrograms_clicked();
   void on_menuItem_BreakPoints_clicked();
   void on_menuItem_SymbolicTrace_clicked();
   void on_menuItem_ByteConverter_clicked();
   void on_menuItem_InterruptHandlers_clicked();
   void on_menuItem_Reference_clicked();
   void on_menuItem_InstructionSet_clicked();
   void on_menuItem_DotCommands_clicked();
   void on_menuItem_AddressingModes_clicked();
   void on_menuItem_Examples_clicked();
   void on_menuItem_OperatingSystem_clicked();
};

#endif // HELPDIALOG_H