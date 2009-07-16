#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "byteconverterdec.h"
#include "byteconverterhex.h"
#include "byteconverterbin.h"
#include "byteconverterchar.h"

// Left pane
#include "sourcecodepane.h"
#include "objectcodepane.h"
#include "assemblerlistingpane.h"
#include "listingtracepane.h"
#include "memorytracepane.h"

// Middle pane
#include "cpupane.h"
#include "inputpane.h"
#include "outputpane.h"
#include "terminalpane.h"

// Right pane
#include "memorydumpwindow.h"// Dialog boxes
#include "redefinemnemonicsdialogow.h#include "helpdialogow.h"

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

otected:
    void closeEvent(QCloseEvent *eventw();

private:
    Ui::MainWindowClass *uii    // Left pane
    SourceCodePane *sourceCodePane;
    ObjectCodePane *objectCodePane;
    AssemblerListingPane *assemblerListingPane;
    ListingTracePane *listingTracePane;
    MemoryTracePane *memoryTracePane;

    // Middle pane
    CpuPane *cpuPane;
    InputPane *inputPane;
    OutputPane *outputPane;
    TerminalPane *terminalPane;

    // Right pane
    MemoryDumpPane *memoryDumpPane;

    // Dialog boxes
    RedefineMnemonicsDialog *redefineMnemonicsDialog;
    HelpDialog *helpDialog;

    // Byte converter
    ByteConverterDec *byteConverterDec;
    ByteConverterHex *byteConverterHex;
    ByteConverterBin *byteConverterBin;
    ByteConverterChar *byteConverterChar;

    // Save methods
    bool saveSource();
    bool saveObject();
    bool saveListing();
    void readSettings();
    void writeSettings();
    bool maybeSaveSource();
    bool maybeSaveObject();
    void loadFile(const QString &fileName);
    bool saveFileSource(const QString &fileName);
    bool saveFileObject(const QString &fileName);
    bool saveFileListing(const QString &fileName);
    void setCurrentFile(const QString &fileName, QString pane);
    QString strippedName(const QString &fullFileName);

    QString curSourceFile;
    QString curObjectFile;
    QString curListingFile;

    // Recent Files methods
    void updateRecentFileActions();
    enum { MaxRecentFiles = 5};
    QAction *recentFileActs[MaxRecentFiles];
    QAction *separatorAct;

    bool assemble();
    bool load();

    void setDebugState(bool b);

    bool eventFilter(QObject *, QEvent *event);

private slots:
    // File
    void on_actionFile_New_triggered();
    void on_actionFile_Open_triggered();
    bool on_actionFile_Save_Source_triggered();
    bool on_actionFile_Save_Object_triggered();
    bool on_actionFile_Save_Source_As_triggered();
    bool on_actionFile_Save_Object_As_triggered();
    bool on_actionFile_Save_Listing_As_triggered();
    void on_actionFile_Print_Source_triggered();
    void on_actionFile_Print_Object_triggered();
    void on_actionFile_Print_Listing_triggered();

    // Edit
    void on_actionEdit_Undo_triggered();
    void on_actionEdit_Redo_triggered();
    void on_actionEdit_Cut_triggered();
    void on_actionEdit_Copy_triggered();
    void on_actionEdit_Paste_triggered();
    void on_actionEdit_Format_From_Listing_triggered();
    void on_actionEdit_Font_triggered();
    void on_actionEdit_Remove_Error_Messages_triggered();

    // Build
    void on_actionBuild_Assemble_triggered();
    void on_actionBuild_Load_triggered();
    void on_actionBuild_Execute_triggered();
    void on_actionBuild_Run_Source_triggered();
    void on_actionBuild_Start_Debugging_Source_triggered();
    void on_actionBuild_Run_Object_triggered();
    void on_actionBuild_Start_Debugging_Object_triggered();
    void on_actionBuild_Stop_Debugging_triggered();
    void on_actionBuild_Interrupt_Execution_triggered();

    // View
    void on_actionView_Code_Only_triggered();
    void on_actionView_Code_CPU_triggered();
    void on_actionView_Code_CPU_Memory_triggered();
    void on_actionView_Code_Tab_triggered();
    void on_actionView_Trace_Tab_triggered();
    void on_actionView_Batch_I_O_Tab_triggered();
    void on_actionView_Terminal_Tab_triggered();

    // System
    void on_actionSystem_Redefine_Mnemonics_triggered();
    void on_actionSystem_Assemble_Install_New_OS_triggered();
    void on_actionSystem_Reinstall_Default_OS_triggered();

    // Help
    void on_actionHelp_triggered();
    void on_actionHelp_Assembly_Language_triggered();
    void on_actionHelp_Machine_Language_triggered();
    void on_actionHelp_Break_Points_triggered();
    void on_actionHelp_Symbolic_Trace_triggered();
    void on_actionHelp_Byte_Converter_triggered();
    void on_actionHelp_Writing_Interrupt_Handlers_triggered();
    void on_actionHelp_Instruction_Set_triggered();
    void on_actionHelp_Dot_Commands_triggered();
    void on_actionHelp_Addressing_Modes_triggered();
    void on_actionHelp_Examples_triggered();
    void on_actionPep_8_Operating_System_triggered();
    void on_actionAbout_Pep8_triggered();
    void on_actionAbout_Qt_triggered();

    void helpCopyToSourceButtonClicked();

    // Byte converter
    void slotByteConverterDecEdited(const QString &);
    void slotByteConverterHexEdited(const QString &);
    void slotByteConverterBinEdited(const QString &);
    void slotByteConverterCharEdited(const QString &);

    // Focus coloring Undo/Redo/Cut/Copy/Paste activate/deactivate
    void mainWindowUtilities(QWidget *, QWidget *);
    void setUndoability(bool b);
    void setRedoability(bool b);

    // For updating the CPU and Memory trace from listing trace pane
    void updateSimulationView();
    void updateMemoryDisplays();
    void appendOutput(QString str);

    void resumeButtonClicked();
    void singleStepButtonClicked();

    // Recent files
    void openRecentFile();

    /*
    These belong in the other panes
    // Trace
    void on_pepMemSingleStepPushButton_clicked();
    void on_pepMemResumePushButton_clicked();
    void pepResumePushButtonClicked();

    // Memory pane
    void on_pepMemRefreshPushButton_clicked();

    // CPU stats
    void slotSaveTraceProgram(int);
    void slotSaveTraceTraps(int);
    void slotSaveTraceLoader(int);
*/

};

#endif // MAINWINDOW_H
