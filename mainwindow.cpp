#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QSettings>
#include <QApplication>
#include <QPrinter>
#include <QPrintDialog>
#include <QFontDialog>
#include <QTextDocument>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pep.h"
#include "sim.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);

    // Left pane setup
    sourceCodePane = new SourceCodePane(ui->codeSplitter);
    delete ui->SourceCodeWidgetPane;
    objectCodePane = new ObjectCodePane(ui->codeSplitter);
    delete ui->ObjectCodeWidgetPane;
    assemblerListingPane = new AssemblerListingPane(ui->codeSplitter);
    delete ui->AssemblerListingWidgetPane;
    listingTracePane = new ListingTracePane(ui->traceSplitter);
    delete ui->ListingTraceWidgetPane;
    memoryTracePane = new MemoryTracePane(ui->traceSplitter);
    delete ui->MemoryTraceWidgetPane;
    ui->pepCodeTraceTab->setCurrentIndex(0);

    // Middle pane setup
    cpuPane = new CpuPane(ui->middleSplitter);
    ui->middleSplitter->insertWidget(0, cpuPane); // Move cpu pane to index 0 (above I/O tabs).
    delete ui->CpuWidgetPane;
    inputPane = new InputPane(ui->batchSplitter);
    delete ui->InputWidgetPane;
    outputPane = new OutputPane(ui->batchSplitter);
    delete ui->OutputWidgetPane;
    terminalPane = new TerminalPane(ui->terminalSplitter);
    delete ui->TerminalWidgetPane;
    ui->pepInputOutputTab->setCurrentIndex(0);

    // Right pane setup
    memoryDumpPane = new MemoryDumpPane(ui->horizontalSplitter);
    delete ui->MemoryDumpWidgetPane;

    // Dialog boxes setup
    redefineMnemonicsDialog = new RedefineMnemonicsDialog(this);
    helpDialog = new HelpDialog(this);

    connect(helpDialog, SIGNAL(clicked()), this, SLOT(helpCopyToSourceButtonClicked()));

    // Byte converter setup
    byteConverterDec = new ByteConverterDec();
    ui->byteConverterToolBar->addWidget(byteConverterDec);
    byteConverterHex = new ByteConverterHex();
    ui->byteConverterToolBar->addWidget(byteConverterHex);
    byteConverterBin = new ByteConverterBin();
    ui->byteConverterToolBar->addWidget(byteConverterBin);
    byteConverterChar = new ByteConverterChar();
    ui->byteConverterToolBar->addWidget(byteConverterChar);
    connect(byteConverterDec, SIGNAL(textEdited(const QString &)), this, SLOT(slotByteConverterDecEdited(const QString &)));
    connect(byteConverterHex, SIGNAL(textEdited(const QString &)), this, SLOT(slotByteConverterHexEdited(const QString &)));
    connect(byteConverterBin, SIGNAL(textEdited(const QString &)), this, SLOT(slotByteConverterBinEdited(const QString &)));
    connect(byteConverterChar, SIGNAL(textEdited(const QString &)), this, SLOT(slotByteConverterCharEdited(const QString &)));

    // Pep tables setup
    Pep::initEnumMnemonMaps();
    Pep::initAddrModesMap();
    Pep::initMnemonicMaps();
    Pep::initDecoderTables();

    // Adjust initial configuration
    ui->horizontalSplitter->widget(2)->hide();
    ui->horizontalSplitter->widget(0)->resize(QSize(800,1)); // Enlarge Code/Trace pane on left.
    ui->codeSplitter->widget(0)->resize(QSize(1, 800)); // Enlarge Source Code pane.
    ui->middleSplitter->widget(1)->resize(QSize(1, 600)); // Enlarge Input pane.

    // Save system setup
    readSettings();

    // Install OS into memory
    Pep::memAddrssToAssemblerListing = &Pep::memAddrssToAssemblerListingOS;
    Pep::listingRowChecked = &Pep::listingRowCheckedOS;
    if (sourceCodePane->installDefaultOs()) {
        sourceCodePane->getAssemblerListingList();
        listingTracePane->setListingTrace(sourceCodePane->getAssemblerListingList(), sourceCodePane->getHasCheckBox());
        ui->statusbar->showMessage("OS installed", 4000);
    }
    else {
        ui->statusbar->showMessage("OS assembly failed", 4000);
    }

    // Focus highlighting, actions enable/disable
    connect(qApp->instance(), SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(mainWindowUtilities(QWidget*, QWidget*)));

    connect(objectCodePane, SIGNAL(undoAvailable(bool)), this, SLOT(setUndoability(bool)));
    connect(objectCodePane, SIGNAL(redoAvailable(bool)), this, SLOT(setRedoability(bool)));
    connect(sourceCodePane, SIGNAL(undoAvailable(bool)), this, SLOT(setUndoability(bool)));
    connect(sourceCodePane, SIGNAL(redoAvailable(bool)), this, SLOT(setRedoability(bool)));
    connect(inputPane, SIGNAL(undoAvailable(bool)), this, SLOT(setUndoability(bool)));
    connect(inputPane, SIGNAL(redoAvailable(bool)), this, SLOT(setRedoability(bool)));
    connect(terminalPane, SIGNAL(undoAvailable(bool)), this, SLOT(setUndoability(bool)));
    connect(terminalPane, SIGNAL(redoAvailable(bool)), this, SLOT(setRedoability(bool)));

    // Simulator signals
    connect(cpuPane, SIGNAL(updateSimulationView()), this, SLOT(updateSimulationView()));
    connect(cpuPane, SIGNAL(executionComplete()), this, SLOT(on_actionBuild_Stop_Debugging_triggered()));
    connect(cpuPane, SIGNAL(appendOutput(QString)), this, SLOT(appendOutput(QString)));
    connect(cpuPane, SIGNAL(resumeButtonClicked()), this, SLOT(resumeButtonClicked()));
    connect(cpuPane, SIGNAL(singleStepButtonClicked()), this, SLOT(singleStepButtonClicked()));
    connect(cpuPane, SIGNAL(vonNeumannStepped()), this, SLOT(vonNeumannStepped()));
    connect(cpuPane, SIGNAL(waitingForInput()), this, SLOT(waitingForInput()));

    connect(cpuPane, SIGNAL(waitingForInput()), this, SLOT(waitingForInput()));
    connect(terminalPane, SIGNAL(inputReceived()), this, SLOT(inputReceived()));

    // Recent files
    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActs[i] = new QAction(this);
        recentFileActs[i]->setVisible(false);
        connect(recentFileActs[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }
    separatorAct = ui->menu_File->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i)
        ui->menu_File->addAction(recentFileActs[i]);
    updateRecentFileActions();

    memoryDumpPane->refreshMemory();

    qApp->installEventFilter(this);

    // Hide memory trace pane, because nothing is implemented there (for now!)
    memoryTracePane->hide();

    if (Pep::getSystem() == "Mac") {
        QMenu *dockMenu = new QMenu;
        // This is an example action. Implementing it for when I think of what we ought to do with this menu.
        // I think I may have to fix window modality before it's especially useful (bring all to front item).
        dockMenu->addAction("Assemble");
        connect(dockMenu, SIGNAL(triggered(QAction*)), this, SLOT(on_actionBuild_Assemble_triggered()));

        extern void qt_mac_set_dock_menu(QMenu *);
        qt_mac_set_dock_menu(dockMenu);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Protected closeEvent
 void MainWindow::closeEvent(QCloseEvent *event)
 {
     if (maybeSaveSource() && maybeSaveObject()) {
         writeSettings();
         cpuPane->interruptExecution();
         event->accept();
     }
     else {
         event->ignore();
     }
 }

// Save methods
bool MainWindow::saveSource()
{
    if (curSourceFile.isEmpty()) {
        return on_actionFile_Save_Source_As_triggered();
    }
    else {
        return saveFileSource(curSourceFile);
    }
}

bool MainWindow::saveObject()
{
    if (curObjectFile.isEmpty()) {
        return on_actionFile_Save_Object_As_triggered();
    }
    else {
        return saveFileObject(curObjectFile);
    }
}

void MainWindow::readSettings()
{
    QSettings settings("Pep/8", "Dialog");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings()
{
    QSettings settings("Pep/8", "Dialog");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

bool MainWindow::maybeSaveSource()
{
    if (sourceCodePane->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, "Pep/8",
                                   "The source code has been modified.\n"
                                   "Do you want to save your changes?",
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return saveSource();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

bool MainWindow::maybeSaveObject()
{
    if (objectCodePane->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, "Pep/8",
                                   "The object code has been modified.\n"
                                   "Do you want to save your changes?",
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return saveObject();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QRegExp rx(".*.pepo");
    Enu::EPane pane;
    if (rx.exactMatch(strippedName(fileName))) {
        if (maybeSaveObject()) {
            // Set object code pane text
            objectCodePane->setObjectCodePaneText(in.readAll());
            pane = Enu::EObject;
            setCurrentFile(fileName, pane);
            statusBar()->showMessage(tr("File loaded"), 4000);
        }
    }
    else if (maybeSaveSource()) {
        // Set source code pane text
        sourceCodePane->setSourceCodePaneText(in.readAll());
        pane = Enu::ESource;
        setCurrentFile(fileName, pane);
        statusBar()->showMessage(tr("File loaded"), 4000);
    }
    QApplication::restoreOverrideCursor();
}

bool MainWindow::saveFileSource(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << sourceCodePane->toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName, Enu::ESource);
    statusBar()->showMessage("Source saved", 4000);
    return true;
}

bool MainWindow::saveFileObject(const QString &fileName) // Copied and pasted, change.
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << objectCodePane->toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName, Enu::EObject);
    statusBar()->showMessage("Object code saved", 4000);
    return true;
}

bool MainWindow::saveFileListing(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Pep/8"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << assemblerListingPane->toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName, Enu::EListing);
    statusBar()->showMessage("Assembler listing saved", 4000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName, Enu::EPane pane)
{
    if (pane == Enu::ESource) {
        curSourceFile = fileName;
        sourceCodePane->setModifiedFalse();
    }
    else if (pane == Enu::EObject) {
        curObjectFile = fileName;
        objectCodePane->setModifiedFalse();
    }
    else if (pane == Enu::EListing) {
        curListingFile = fileName;
    }

    QString shownName;
    if (pane == Enu::ESource) {
        if (curSourceFile.isEmpty()) {
            shownName = "untitled.pep";
        }
        else {
            shownName = strippedName(curSourceFile);
        }
        sourceCodePane->setCurrentFile(shownName);
    }
    else if (pane == Enu::EObject) {
        if (curObjectFile.isEmpty()) {
            shownName = "untitled.pepo";
        }
        else {
            shownName = strippedName(curObjectFile);
        }
        objectCodePane->setCurrentFile(shownName);
    }
    else if (pane == Enu::EListing) {
        if (curListingFile.isEmpty()) {
            shownName = "untitled.pepl";
        }
        else {
            shownName = strippedName(curListingFile);
        }
        assemblerListingPane->setCurrentFile(shownName);
    }
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

// Recent files:
void MainWindow::updateRecentFileActions()
{
    QSettings settings("Pep/8", "Recent Files");
    QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(files[i]));
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActs[j]->setVisible(false);

    separatorAct->setVisible(numRecentFiles > 0);
}

bool MainWindow::assemble()
{
    Pep::memAddrssToAssemblerListing = &Pep::memAddrssToAssemblerListingProg;
    Pep::listingRowChecked = &Pep::listingRowCheckedProg;
    Pep::burnCount = 0;
    if (sourceCodePane->assemble()) {
        if (Pep::burnCount > 0) {
            QString errorString = ";ERROR: .BURN not allowed in program unless installing OS.";
            sourceCodePane->appendMessageInSourceCodePaneAt(0, errorString);
            assemblerListingPane->clearAssemblerListing();
            objectCodePane->clearObjectCode();
            listingTracePane->clearListingTrace();
            ui->pepCodeTraceTab->setCurrentIndex(0); // Make source code pane visible
            return false;
        }
        else {
            objectCodePane->setObjectCode(sourceCodePane->getObjectCode());
            assemblerListingPane->setAssemblerListing(sourceCodePane->getAssemblerListingList());
            listingTracePane->setListingTrace(sourceCodePane->getAssemblerListingList(), sourceCodePane->getHasCheckBox());

            QString temp = curSourceFile;
            if (!curSourceFile.isEmpty()) {
                if (temp.endsWith(".pep", Qt::CaseInsensitive) || temp.endsWith(".txt", Qt::CaseInsensitive)) {
                    temp.chop(4);
                }
                temp.append(".pepo");
                curObjectFile = temp;
                setCurrentFile(curObjectFile, Enu::EObject);
                temp.chop(5);
                temp.append(".pepl");
                curListingFile = temp;
                setCurrentFile(curListingFile, Enu::EListing);
            }
            else {
                setCurrentFile("", Enu::EObject);
                setCurrentFile("", Enu::EListing);
            }
            ui->actionEdit_Format_From_Listing->setEnabled(true);
            return true;
        }
    }
    assemblerListingPane->clearAssemblerListing();
    objectCodePane->clearObjectCode();
    listingTracePane->clearListingTrace();
    ui->pepCodeTraceTab->setCurrentIndex(0); // Make source code pane visible
    return false;
}

bool MainWindow::load()
{
    QList<int> objectCodeList;
    if (objectCodePane->getObjectCode(objectCodeList)) {
        Sim::loadMem(objectCodeList);
        memoryDumpPane->refreshMemoryLines(0, objectCodeList.size());
        memoryDumpPane->highlightMemory(true);
        return true;
    }    
    return false;
}

void MainWindow::setDebugState(bool b)
{
    ui->actionFile_New->setDisabled(b);
    ui->actionFile_Open->setDisabled(b);
    ui->actionEdit_Format_From_Listing->setDisabled(b);
    ui->actionBuild_Assemble->setDisabled(b);
    ui->actionBuild_Load->setDisabled(b);
    ui->actionBuild_Execute->setDisabled(b);
    ui->actionBuild_Run_Source->setDisabled(b);
    ui->actionBuild_Start_Debugging_Source->setDisabled(b);
    ui->actionBuild_Run_Object->setDisabled(b);
    ui->actionBuild_Start_Debugging_Object->setDisabled(b);
    ui->actionBuild_Start_Debugging_Loader->setDisabled(b);
    ui->actionBuild_Stop_Debugging->setDisabled(!b);
    ui->actionBuild_Interrupt_Execution->setDisabled(!b);
    ui->actionEdit_Remove_Error_Messages->setDisabled(b);
    inputPane->setReadOnly(b);
    sourceCodePane->setReadOnly(b);
    objectCodePane->setReadOnly(b);
    listingTracePane->setDebuggingState(b);
    cpuPane->setDebugState(b);
    cpuPane->setButtonsEnabled(b);
    memoryDumpPane->highlightMemory(b);
    if (b) {
        Pep::memAddrssToAssemblerListing = &Pep::memAddrssToAssemblerListingProg;
        Pep::listingRowChecked = &Pep::listingRowCheckedProg;
    }
    else {
        ui->pepInputOutputTab->setTabEnabled(1, true);
        ui->pepInputOutputTab->setTabEnabled(0, true);
    }
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if ((keyEvent->modifiers() & Qt::ControlModifier) && (keyEvent->key() == Qt::Key_Period)) {
            on_actionBuild_Interrupt_Execution_triggered();
            return true;
        }
    }
    else if (event->type() == QEvent::FileOpen) {
        loadFile(static_cast<QFileOpenEvent *>(event)->file());
        return true;
    }
    return false;
}

// File MainWindow triggers
void MainWindow::on_actionFile_New_triggered()
{
    if (maybeSaveSource() && maybeSaveObject()) {
        sourceCodePane->clearSourceCode();
        objectCodePane->clearObjectCode();
        assemblerListingPane->clearAssemblerListing();
        listingTracePane->clearListingTrace();
        cpuPane->clearCpu();
        outputPane->clearOutput();
        // Do we want to clear input as well?
        setCurrentFile("", Enu::ESource);
        setCurrentFile("", Enu::EObject);
        setCurrentFile("", Enu::EListing);
    }
}

void MainWindow::on_actionFile_Open_triggered()
{
    if (maybeSaveSource()) {
        QString fileName = QFileDialog::getOpenFileName(
                this,
                "Open text file",
                "",
                "Text files (*.pepo *.txt *.pep)");
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::on_actionFile_Save_Source_triggered()
{
    if (curSourceFile.isEmpty()) {
        return on_actionFile_Save_Source_As_triggered();
    }
    else {
        return saveFileSource(curSourceFile);
    }
}

bool MainWindow::on_actionFile_Save_Source_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
            this,
            "Save Source Code",
            curSourceFile.isEmpty() ? "untitled.pep" : curSourceFile,
            "Pep8 Source (*.pep *.txt)");
    if (fileName.isEmpty())
        return false;

    QSettings settings("Pep/8", "Recent Files");
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > MaxRecentFiles)
        files.removeLast();

    settings.setValue("recentFileList", files);

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
        if (mainWin)
            mainWin->updateRecentFileActions();
    }

    return saveFileSource(fileName);
}

bool MainWindow::on_actionFile_Save_Object_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
            this,
            "Save Object Code",
            curObjectFile.isEmpty() ? "untitled.pepo" : curObjectFile,
            "Pep8 Object (*.pepo *.txt)");
    if (fileName.isEmpty())
        return false;

    QSettings settings("Pep/8", "Recent Files");
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > MaxRecentFiles)
        files.removeLast();

    settings.setValue("recentFileList", files);

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
        if (mainWin)
            mainWin->updateRecentFileActions();
    }

    return saveFileObject(fileName);
}

bool MainWindow::on_actionFile_Save_Listing_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
            this,
            "Save Assembler Listing",
            curListingFile.isEmpty() ? "untitled.pepl" : curListingFile,
            "Pep8 Listing (*.pepl)");
    if (fileName.isEmpty()) {
        return false;
    }
    return saveFileListing(fileName);
}

void MainWindow::on_actionFile_Print_Source_triggered()
{
    QTextDocument document(sourceCodePane->toPlainText(), this);
    document.setDefaultFont(QFont("Courier", 10, -1));

    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle("Print Source Code");
    if (dialog->exec() == QDialog::Accepted) {
        document.print(&printer);
    }
}

void MainWindow::on_actionFile_Print_Object_triggered()
{
    QTextDocument document(objectCodePane->toPlainText(), this);
    document.setDefaultFont(QFont("Courier", 10, -1));

    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle("Print Object Code");
    if (dialog->exec() == QDialog::Accepted) {
        document.print(&printer);
    }

}

void MainWindow::on_actionFile_Print_Listing_triggered()
{
    QTextDocument document(assemblerListingPane->toPlainText(), this);
    document.setDefaultFont(QFont("Courier", 10, -1));

    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle("Print Assembler Listing");
    if (dialog->exec() == QDialog::Accepted) {
        document.print(&printer);
    }

}

// Edit MainWindow triggers
void MainWindow::on_actionEdit_Undo_triggered()
{
    if (sourceCodePane->hasFocus()) {
        sourceCodePane->undo();
    }
    else if (objectCodePane->hasFocus()) {
        objectCodePane->undo();
    }
    else if (inputPane->hasFocus()) {
        inputPane->undo();
    }
}

void MainWindow::on_actionEdit_Redo_triggered()
{
    if (sourceCodePane->hasFocus()) {
        sourceCodePane->redo();
    }
    else if (objectCodePane->hasFocus()) {
        objectCodePane->redo();
    }
    else if (inputPane->hasFocus()) {
        inputPane->redo();
    }
}

void MainWindow::on_actionEdit_Cut_triggered()
{
    if (sourceCodePane->hasFocus()) {
        sourceCodePane->cut();
    }
    else if (objectCodePane->hasFocus()) {
        objectCodePane->cut();
    }
    else if (inputPane->hasFocus()) {
        inputPane->cut();
    }
}

void MainWindow::on_actionEdit_Copy_triggered()
{
    if (sourceCodePane->hasFocus()) {
        sourceCodePane->copy();
    }
    else if (objectCodePane->hasFocus()) {
        objectCodePane->copy();
    }
    else if (assemblerListingPane->hasFocus()) {
        assemblerListingPane->copy();
    }
    else if (inputPane->hasFocus()) {
        inputPane->copy();
    }
    else if (outputPane->hasFocus()) {
        outputPane->copy();
    }
    else if (terminalPane->hasFocus()) {
        terminalPane->copy();
    }
    else if (memoryDumpPane->hasFocus()) {
        memoryDumpPane->copy();
    }
    else if (helpDialog->hasFocus()) {
        helpDialog->copy();
    }
}

void MainWindow::on_actionEdit_Paste_triggered()
{
    if (sourceCodePane->hasFocus()) {
        sourceCodePane->paste();
    }
    else if (objectCodePane->hasFocus()) {
        objectCodePane->paste();
    }
    else if (inputPane->hasFocus()) {
        inputPane->paste();
    }
}

void MainWindow::on_actionEdit_Format_From_Listing_triggered()
{
    QStringList assemblerListingList = sourceCodePane->getAssemblerListingList();
    assemblerListingList.replaceInStrings(QRegExp("^............."), "");
    assemblerListingList.removeAll("");
    if (!assemblerListingList.isEmpty()) {
        sourceCodePane->setSourceCodePaneText(assemblerListingList.join("\n"));
    }
}

void MainWindow::on_actionEdit_Font_triggered()
{
    if (sourceCodePane->hasFocus()) {
        sourceCodePane->setFont();
    }
    else if (objectCodePane->hasFocus()) {
        objectCodePane->setFont();
    }
    else if (assemblerListingPane->hasFocus()) {
        assemblerListingPane->setFont();
    }
    else if (listingTracePane->hasFocus()) {
        listingTracePane->setFont();
    }
    else if (memoryTracePane->hasFocus()) {
        memoryTracePane->setFont();
    }
    else if (inputPane->hasFocus()) {
        inputPane->setFont();
    }
    else if (outputPane->hasFocus()) {
        outputPane->setFont();
    }
    else if (terminalPane->hasFocus()) {
        terminalPane->setFont();
    }
    else if (memoryDumpPane->hasFocus()) {
        memoryDumpPane->setFont();
    }
    else if (cpuPane->hasFocus()) {
    }
}

void MainWindow::on_actionEdit_Remove_Error_Messages_triggered()
{
    sourceCodePane->removeErrorMessages();
}

// Build MainWindow triggers
void MainWindow::on_actionBuild_Assemble_triggered()
{
    if (assemble()) {
        ui->statusbar->showMessage("Assembly succeeded", 4000);
    }
    else {
        ui->statusbar->showMessage("Assembly failed", 4000);
    }
}

void MainWindow::on_actionBuild_Load_triggered()
{
    if (load()) {
        ui->statusbar->showMessage("Load succeeded", 4000);
    }
    else {
        ui->statusbar->showMessage("Load failed", 4000);
    }
}

void MainWindow::on_actionBuild_Execute_triggered()
{
    Sim::stackPointer = Sim::readWord(Pep::dotBurnArgument - 7);
    Sim::programCounter = 0x0000;
    setDebugState(true);
    Sim::trapped = false;
    listingTracePane->setDebuggingState(false);
    cpuPane->setButtonsEnabled(false);
    cpuPane->runClicked();
    cpuPane->clearCpu();
    sourceCodePane->setReadOnly(true);
    objectCodePane->setReadOnly(true);
    if (ui->pepInputOutputTab->currentIndex() == 0) {
        ui->pepInputOutputTab->setTabEnabled(1, false);
        outputPane->clearOutput();
        QString s = inputPane->toPlainText();
        if (!s.endsWith("\n")) {
            s.append("\n");
        }
        Sim::inputBuffer = s;
        cpuPane->runWithBatch();
    }
    else {
        ui->pepInputOutputTab->setTabEnabled(0, false);
        Sim::inputBuffer.clear();
        terminalPane->clearTerminal();
        cpuPane->runWithTerminal();
    }
    // Other things may go here.
}

void MainWindow::on_actionBuild_Run_Source_triggered()
{
    if (assemble() && load()) {
        on_actionBuild_Execute_triggered();
    }
}

void MainWindow::on_actionBuild_Start_Debugging_Source_triggered()
{
    if (load()) {
        ui->statusbar->showMessage("Load succeeded", 4000);
        Sim::stackPointer = Sim::readWord(Pep::dotBurnArgument - 7);
        Sim::programCounter = 0x0000;

        setDebugState(true);
        Sim::trapped = false;

        if (ui->pepInputOutputTab->currentIndex() == 0) {
            ui->pepInputOutputTab->setTabEnabled(1, false);
            outputPane->clearOutput();
            QString s = inputPane->toPlainText();
            if (!s.endsWith("\n")) {
                s.append("\n");
            }
            Sim::inputBuffer = s;
        }
        else {
            ui->pepInputOutputTab->setTabEnabled(0, false);
            Sim::inputBuffer.clear();
            terminalPane->clearTerminal();
        }

        ui->pepCodeTraceTab->setCurrentIndex(1); // Make listing trace pane visible

        cpuPane->updateCpu();
        listingTracePane->setDebuggingState(true);
    }
    else {
        ui->statusbar->showMessage("Load failed", 4000);
    }
}

void MainWindow::on_actionBuild_Run_Object_triggered()
{
    if (load()) {
        ui->statusbar->showMessage("Load succeeded", 4000);
        on_actionBuild_Execute_triggered();
    }
    else {
        ui->statusbar->showMessage("Load failed", 4000);
    }
}

void MainWindow::on_actionBuild_Start_Debugging_Object_triggered()
{
    if (load()) {
        Sim::stackPointer = Sim::readWord(Pep::dotBurnArgument - 7);
        Sim::programCounter = 0x0000;

        setDebugState(true);
        Sim::trapped = false;

        ui->statusbar->showMessage("Load succeeded", 4000);
        cpuPane->updateCpu();
        listingTracePane->setDebuggingState(true);
        if (ui->pepInputOutputTab->currentIndex() == 0) {
            ui->pepInputOutputTab->setTabEnabled(1, false);
            outputPane->clearOutput();
            QString s = inputPane->toPlainText();
            if (!s.endsWith("\n")) {
                s.append("\n");
            }
            Sim::inputBuffer = s;
        }
        else {
            ui->pepInputOutputTab->setTabEnabled(0, false);
            Sim::inputBuffer.clear();
            terminalPane->clearTerminal();
        }
    }
    else {
        ui->statusbar->showMessage("Load failed", 4000);
    }
}

void MainWindow::on_actionBuild_Start_Debugging_Loader_triggered()
{
    Sim::stackPointer = Sim::readWord(Pep::dotBurnArgument - 5);
    // 5 is the vector offset from the last byte of the OS for the System stack pointer
    Sim::programCounter = Sim::readWord(Pep::dotBurnArgument - 3);
    // 3 is the vector offset from the last byte of the OS for the Loader program counter

    Pep::memAddrssToAssemblerListing = &Pep::memAddrssToAssemblerListingOS;
    Pep::listingRowChecked = &Pep::listingRowCheckedOS;
    Sim::trapped = true;

    Sim::inputBuffer = objectCodePane->toPlainText();
    inputPane->setText(objectCodePane->toPlainText());
    ui->pepInputOutputTab->setCurrentIndex(0);
    ui->pepCodeTraceTab->setCurrentIndex(1);

    ui->actionFile_New->setDisabled(true);
    ui->actionFile_Open->setDisabled(true);
    ui->actionEdit_Format_From_Listing->setDisabled(true);
    ui->actionBuild_Assemble->setDisabled(true);
    ui->actionBuild_Load->setDisabled(true);
    ui->actionBuild_Execute->setDisabled(true);
    ui->actionBuild_Run_Source->setDisabled(true);
    ui->actionBuild_Start_Debugging_Source->setDisabled(true);
    ui->actionBuild_Run_Object->setDisabled(true);
    ui->actionBuild_Start_Debugging_Object->setDisabled(true);
    ui->actionBuild_Start_Debugging_Loader->setDisabled(true);
    ui->actionBuild_Stop_Debugging->setDisabled(false);
    ui->actionBuild_Interrupt_Execution->setDisabled(false);
    ui->actionEdit_Remove_Error_Messages->setDisabled(true);
    inputPane->setReadOnly(true);
    sourceCodePane->setReadOnly(true);
    objectCodePane->setReadOnly(true);
    cpuPane->traceTraps(true);
    cpuPane->setDebugState(true);
    cpuPane->setButtonsEnabled(true);
    memoryDumpPane->highlightMemory(true);
    listingTracePane->setDebuggingState(true);

    cpuPane->updateCpu();
}

void MainWindow::on_actionBuild_Stop_Debugging_triggered()
{
    on_actionBuild_Interrupt_Execution_triggered();
    setDebugState(false);

    mainWindowUtilities(0, 0);
}

void MainWindow::on_actionBuild_Interrupt_Execution_triggered()
{
    cpuPane->interruptExecution();
    setDebugState(true);
    cpuPane->updateCpu();
    listingTracePane->updateListingTrace();
    // Other things need to happen here?
}

// View MainWindow triggers
void MainWindow::on_actionView_Code_Only_triggered()
{
    ui->horizontalSplitter->widget(0)->show();
    ui->horizontalSplitter->widget(1)->hide();
    ui->horizontalSplitter->widget(2)->hide();
}

void MainWindow::on_actionView_Code_CPU_triggered()
{
    ui->horizontalSplitter->widget(0)->show();
    ui->horizontalSplitter->widget(1)->show();
    ui->horizontalSplitter->widget(2)->hide();

}

void MainWindow::on_actionView_Code_CPU_Memory_triggered()
{
    memoryDumpPane->updateMemory();
    memoryDumpPane->highlightMemory(ui->actionBuild_Stop_Debugging->isEnabled());
    ui->horizontalSplitter->widget(0)->show();
    ui->horizontalSplitter->widget(1)->show();
    ui->horizontalSplitter->widget(2)->show();
}

void MainWindow::on_actionView_Code_Tab_triggered()
{
    ui->pepCodeTraceTab->setCurrentIndex(0);
}

void MainWindow::on_actionView_Trace_Tab_triggered()
{
    ui->pepCodeTraceTab->setCurrentIndex(1);
}

void MainWindow::on_actionView_Batch_I_O_Tab_triggered()
{
    ui->pepInputOutputTab->setCurrentIndex(0);
    if (ui->horizontalSplitter->widget(1)->isHidden()) {
        on_actionView_Code_CPU_triggered();
    }
}

void MainWindow::on_actionView_Terminal_Tab_triggered()
{
    ui->pepInputOutputTab->setCurrentIndex(1);
    if (ui->horizontalSplitter->widget(1)->isHidden()) {
        on_actionView_Code_CPU_triggered();
    }
}

// System MainWindow triggers

void MainWindow::on_actionSystem_Redefine_Mnemonics_triggered()
{
    redefineMnemonicsDialog->show();
}

void MainWindow::on_actionSystem_Assemble_Install_New_OS_triggered()
{
    Pep::burnCount = 0;
    Pep::memAddrssToAssemblerListing = &Pep::memAddrssToAssemblerListingOS;
    Pep::listingRowChecked = &Pep::listingRowCheckedOS;
    if (sourceCodePane->assemble()) {
        if (Pep::burnCount == 0) {
            QString errorString = ";ERROR: .BURN required to install OS.";
            sourceCodePane->appendMessageInSourceCodePaneAt(0, errorString);
            assemblerListingPane->clearAssemblerListing();
            objectCodePane->clearObjectCode();
            listingTracePane->clearListingTrace();
            ui->statusbar->showMessage("Assembly failed", 4000);
        }
        else if (Pep::burnCount > 1) {
            QString errorString = ";ERROR: Program contain more than one .BURN.";
            sourceCodePane->appendMessageInSourceCodePaneAt(0, errorString);
            assemblerListingPane->clearAssemblerListing();
            objectCodePane->clearObjectCode();
            listingTracePane->clearListingTrace();
            ui->statusbar->showMessage("Assembly failed", 4000);
        }
        else {
            // Adjust for .BURN
            int addressDelta = Pep::dotBurnArgument - Pep::byteCount + 1;
            QMutableMapIterator <QString, int> i(Pep::symbolTable);
            while (i.hasNext()) {
                i.next();
                if (Pep::adjustSymbolValueForBurn.value(i.key())) {
                    i.setValue(i.value() + addressDelta);
                }
            }
            sourceCodePane->adjustCodeList(addressDelta);
            Pep::romStartAddress += addressDelta;
            objectCodePane->setObjectCode(sourceCodePane->getObjectCode());
            assemblerListingPane->setAssemblerListing(sourceCodePane->getAssemblerListingList());
            listingTracePane->setListingTrace(sourceCodePane->getAssemblerListingList(), sourceCodePane->getHasCheckBox());
            sourceCodePane->installOS();
            memoryDumpPane->refreshMemory();
            ui->statusbar->showMessage("Assembly succeeded, OS installed", 4000);
        }
    }
    else {
        assemblerListingPane->clearAssemblerListing();
        objectCodePane->clearObjectCode();
        listingTracePane->clearListingTrace();
        ui->statusbar->showMessage("Assembly failed", 4000);
    }
}

void MainWindow::on_actionSystem_Reinstall_Default_OS_triggered()
{
    Pep::memAddrssToAssemblerListing = &Pep::memAddrssToAssemblerListingOS;
    Pep::listingRowChecked = &Pep::listingRowCheckedOS;
    if (sourceCodePane->installDefaultOs()) {
        sourceCodePane->getAssemblerListingList();
        listingTracePane->setListingTrace(sourceCodePane->getAssemblerListingList(), sourceCodePane->getHasCheckBox());
        ui->statusbar->showMessage("OS installed", 4000);
    }
    else {
        ui->statusbar->showMessage("OS assembly failed", 4000);
    }
}

// Help MainWindow triggers
void MainWindow::on_actionHelp_triggered()
{
    if (helpDialog->isHidden()) {
        helpDialog->setHidden(false);
    }
    else {
        helpDialog->raise();
        helpDialog->activateWindow();
    }
 }

void MainWindow::on_actionHelp_Machine_Language_triggered()
{
    helpDialog->show();
    helpDialog->machineLanguageClicked();
}

void MainWindow::on_actionHelp_Assembly_Language_triggered()
{
    helpDialog->show();
    helpDialog->assemblyLanguageClicked();
}

void MainWindow::on_actionHelp_Debugging_Programs_triggered()
{
    helpDialog->show();
    helpDialog->debuggingProgramsClicked();
}

void MainWindow::on_actionHelp_Writing_Interrupt_Handlers_triggered()
{
    helpDialog->show();
    helpDialog->writingTrapHandlersClicked();
}

void MainWindow::on_actionHelp_Pep_8_Reference_triggered()
{
    helpDialog->show();
    helpDialog->pep8ReferenceClicked();
}

void MainWindow::on_actionHelp_Examples_triggered()
{
    helpDialog->show();
    helpDialog->examplesClicked();
}

void MainWindow::on_actionHelp_Pep_8_Operating_System_triggered()
{
    helpDialog->show();
    helpDialog->operatingSystemClicked();
}

void MainWindow::on_actionAbout_Pep8_triggered()
{

}

void MainWindow::helpCopyToSourceButtonClicked()
{
    helpDialog->hide();
    if (ui->actionBuild_Stop_Debugging->isEnabled()) {
        ui->statusbar->showMessage("Copy to source failed, in debugging mode", 4000);
    }
    Enu::EPane destPane;
    Enu::EPane inputDest;
    QString input = "";
    QString code = helpDialog->getCode(destPane, inputDest, input);
    ui->pepCodeTraceTab->setCurrentIndex(0);
    if (destPane == Enu::ESource) {
        if (maybeSaveSource()) {
            setCurrentFile("", Enu::ESource);
            sourceCodePane->setSourceCodePaneText(code);
            assemblerListingPane->clearAssemblerListing();
            objectCodePane->clearObjectCode();
            listingTracePane->clearListingTrace();
            statusBar()->showMessage("Copied to source", 4000);
        }
    }
    else if (maybeSaveObject()) {
        setCurrentFile("", Enu::EObject);
        objectCodePane->setObjectCodePaneText(code);
        sourceCodePane->clearSourceCode();
        assemblerListingPane->clearAssemblerListing();
        listingTracePane->clearListingTrace();
        statusBar()->showMessage("Copied to object", 4000);
    }
    if (inputDest == Enu::ETerminal) {
        ui->pepInputOutputTab->setCurrentIndex(1);
    }
    else {
        if (!input.isEmpty()) {
            inputPane->setText(input);
            ui->pepInputOutputTab->setCurrentIndex(0);
        }
    }
}

void MainWindow::on_actionAbout_Qt_triggered()
{

}

void MainWindow::slotByteConverterDecEdited(const QString &str)
{
    if (str.length() > 0) {
        bool ok;
        int data = str.toInt(&ok, 10);
        byteConverterHex->setValue(data);
        byteConverterBin->setValue(data);
        byteConverterChar->setValue(data);
    }
}

void MainWindow::slotByteConverterHexEdited(const QString &str)
{
    if (str.length() >= 2) {
        if (str.startsWith("0x")) {
            QString hexPart = str;
            hexPart.remove(0, 2);
            if (hexPart.length() > 0) {
                bool ok;
                int data = hexPart.toInt(&ok, 16);
                byteConverterDec->setValue(data);
                byteConverterBin->setValue(data);
                byteConverterChar->setValue(data);
            }
            else {
                // Exactly "0x" remains, so do nothing
            }
        }
        else {
            // Prefix "0x" was mangled
            byteConverterHex->setValue(-1);
        }
    }
    else {
        // Prefix "0x" was shortened
        byteConverterHex->setValue(-1);
    }
}

void MainWindow::slotByteConverterBinEdited(const QString &str)
{
    if (str.length() > 0) {
        bool ok;
        int data = str.toInt(&ok, 2);
        byteConverterDec->setValue(data);
        byteConverterHex->setValue(data);
        byteConverterChar->setValue(data);
    }
}

void MainWindow::slotByteConverterCharEdited(const QString &str)
{
    if (str.length() > 0) {
        int data = (int)str[0].toAscii();
        byteConverterDec->setValue(data);
        byteConverterHex->setValue(data);
        byteConverterBin->setValue(data);
    }
}

// Focus Coloring. Activates and deactivates undo/redo/cut/copy/paste actions contextually
void MainWindow::mainWindowUtilities(QWidget *, QWidget *)
{
    sourceCodePane->highlightOnFocus();
    objectCodePane->highlightOnFocus();
    assemblerListingPane->highlightOnFocus();
    listingTracePane->highlightOnFocus();
    memoryTracePane->highlightOnFocus();
    inputPane->highlightOnFocus();
    outputPane->highlightOnFocus();
    terminalPane->highlightOnFocus();
    memoryDumpPane->highlightOnFocus();

    if (sourceCodePane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(ui->actionBuild_Stop_Debugging->isEnabled() || !sourceCodePane->isUndoable());
        ui->actionEdit_Redo->setDisabled(ui->actionBuild_Stop_Debugging->isEnabled() || !sourceCodePane->isRedoable());
        ui->actionEdit_Cut->setDisabled(ui->actionBuild_Stop_Debugging->isEnabled());
        ui->actionEdit_Copy->setDisabled(false);
        ui->actionEdit_Paste->setDisabled(ui->actionBuild_Stop_Debugging->isEnabled());
    }
    else if (objectCodePane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(ui->actionBuild_Stop_Debugging->isEnabled() || !objectCodePane->isUndoable());
        ui->actionEdit_Redo->setDisabled(ui->actionBuild_Stop_Debugging->isEnabled() || !objectCodePane->isRedoable());
        ui->actionEdit_Cut->setDisabled(ui->actionBuild_Stop_Debugging->isEnabled());
        ui->actionEdit_Copy->setDisabled(false);
        ui->actionEdit_Paste->setDisabled(ui->actionBuild_Stop_Debugging->isEnabled());
    }
    else if (assemblerListingPane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(true);
        ui->actionEdit_Redo->setDisabled(true);
        ui->actionEdit_Cut->setDisabled(true);
        ui->actionEdit_Copy->setDisabled(false);
        ui->actionEdit_Paste->setDisabled(true);
    }
    else if (listingTracePane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(true);
        ui->actionEdit_Redo->setDisabled(true);
        ui->actionEdit_Cut->setDisabled(true);
        ui->actionEdit_Copy->setDisabled(true);
        ui->actionEdit_Paste->setDisabled(true);
    }
    else if (memoryTracePane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(true);
        ui->actionEdit_Redo->setDisabled(true);
        ui->actionEdit_Cut->setDisabled(true);
        ui->actionEdit_Copy->setDisabled(true);
        ui->actionEdit_Paste->setDisabled(true);
    }
    else if (inputPane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(ui->actionBuild_Stop_Debugging->isEnabled() || !inputPane->isUndoable());
        ui->actionEdit_Redo->setDisabled(ui->actionBuild_Stop_Debugging->isEnabled() || !inputPane->isRedoable());
        ui->actionEdit_Cut->setDisabled(ui->actionBuild_Stop_Debugging->isEnabled());
        ui->actionEdit_Copy->setDisabled(false);
        ui->actionEdit_Paste->setDisabled(ui->actionBuild_Stop_Debugging->isEnabled());
    }
    else if (outputPane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(true);
        ui->actionEdit_Redo->setDisabled(true);
        ui->actionEdit_Cut->setDisabled(true);
        ui->actionEdit_Copy->setDisabled(false);
        ui->actionEdit_Paste->setDisabled(true);
    }
    else if (terminalPane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(true);
        ui->actionEdit_Redo->setDisabled(true);
        ui->actionEdit_Cut->setDisabled(true);
        ui->actionEdit_Copy->setDisabled(false);
        ui->actionEdit_Paste->setDisabled(true);
    }
    else if (memoryDumpPane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(true);
        ui->actionEdit_Redo->setDisabled(true);
        ui->actionEdit_Cut->setDisabled(true);
        ui->actionEdit_Copy->setDisabled(false);
        ui->actionEdit_Paste->setDisabled(true);
    }
    else if (helpDialog->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(true);
        ui->actionEdit_Redo->setDisabled(true);
        ui->actionEdit_Cut->setDisabled(true);
        ui->actionEdit_Copy->setDisabled(false);
        ui->actionEdit_Paste->setDisabled(true);
    }
}

void MainWindow::setUndoability(bool b)
{
    if (sourceCodePane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(!b);
    }
    else if (objectCodePane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(!b);
    }
    else if (inputPane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(!b);
    }
    else if (terminalPane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(!b);
    }
}

void MainWindow::setRedoability(bool b)
{
    if (sourceCodePane->hasFocus()) {
        ui->actionEdit_Redo->setDisabled(!b);
    }
    else if (objectCodePane->hasFocus()) {
        ui->actionEdit_Redo->setDisabled(!b);
    }
    else if (inputPane->hasFocus()) {
        ui->actionEdit_Redo->setDisabled(!b);
    }
    else if (terminalPane->hasFocus()) {
        ui->actionEdit_Redo->setDisabled(!b);
    }
}

void MainWindow::updateSimulationView()
{
    listingTracePane->updateListingTrace();
    if (!memoryDumpPane->isHidden()) {
        memoryDumpPane->updateMemory();
        memoryDumpPane->highlightMemory(true);
    }
}

void MainWindow::vonNeumannStepped()
{
    memoryDumpPane->cacheModifiedBytes();
}

void MainWindow::appendOutput(QString str)
{
    if (ui->pepInputOutputTab->currentIndex() == 0) { // batch output
        outputPane->appendOutput(str);
    }
    else { // terminal output
        terminalPane->appendOutput(str);
    }
}

// Recent files
void MainWindow::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        loadFile(action->data().toString());
}

void MainWindow::waitingForInput()
{
    terminalPane->waitingForInput();
    mainWindowUtilities(0, 0);
}

void MainWindow::inputReceived()
{
    if (cpuPane->waitingState() == Enu::EDebugSSWaiting) {
        cpuPane->singleStepWithTerminal();
    }
    else if (cpuPane->waitingState() == Enu::EDebugResumeWaiting) {
        cpuPane->resumeWithTerminal();
    }
    else if (cpuPane->waitingState() == Enu::ERunWaiting) {
        cpuPane->runWithTerminal();
    }
}

void MainWindow::resumeButtonClicked()
{
    if (ui->pepInputOutputTab->currentIndex() == 0) { // batch input
        cpuPane->resumeWithBatch();
    }
    else { // terminal input
        cpuPane->resumeWithTerminal();
    }
}

void MainWindow::singleStepButtonClicked()
{
    if (ui->pepInputOutputTab->currentIndex() == 0) { // batch input
        cpuPane->singleStepWithBatch();
    }
    else { // terminal input
        cpuPane->singleStepWithTerminal();
    }
}

