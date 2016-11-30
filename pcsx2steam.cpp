#include "pcsx2steam.h"
#include "ui_pcsx2steam.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QProcess>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <shellapi.h>
#include <tlhelp32.h>

using namespace std;

//-----FUNCTION FOR REPLACING SPACES WITH UNDERSCORES-----//

string space2underscore(string text)
{
    for(int i = 0; i < text.size(); i++)
        {
        if( isspace(text[i]) )
            text[i] = '_';
        }
    return text;
}

//-----INITIALIZING GUI WINDOW-----//

PCSX2Steam::PCSX2Steam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PCSX2Steam)
{
    ui->setupUi(this);
    //setWindowFlags (Qt::FramelessWindowHint);

    ///---------------TO DO: ERROR HANDLING---------------///
    ///
    ///-----Check if "Emulator" directory exists. If it doesn't, throw an error and close.
    ///
    ///-----Check if "compiler" directory exists. If it doesn't, throw an error and close.
    ///
    ///-----Check if "src" directory exists. If it doesn't, create it.
    ///-----If it cannot be created, throw an error and close.

}

PCSX2Steam::~PCSX2Steam()
{
    delete ui;
}

//-----BROWSE FOR ICON AND PREVIEW ON BUTTON-----//

void PCSX2Steam::on_iconPicBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Icon"), QString(),tr("Icon (*.ico)"));

        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            }
            QTextStream in(&file);
            ui->iconInput->setText(fileName);
            QString iconPreview = """" + fileName + """";
            ui->iconPicBtn->setIcon(QIcon(iconPreview));
            ui->iconPicBtn->setIconSize(QSize(80,80));
            file.close();
        }
}

//-----BROWSE FOR GAME IMAGE (.ISO, .BIN, ETC) AND FILL INPUT BOX-----//

void PCSX2Steam::on_dirBrowseBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),tr("PCSX2 Game Images (*.iso *.bin *.img)"));

        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            }
            QTextStream in(&file);
            ui->dirInput->setText(fileName);
            file.close();
        }
}

//-----BEGIN CREATING SHORTCUT-----//

void PCSX2Steam::on_createButton_clicked()
{
    ///---------------TO DO: ERROR HANDLING---------------///
    ///
    ///-----Check if "NAME" input is empty. If it is, throw an error.
    ///-----Check if "NAME" input is valid (No ~`!@#$%^&*+=). If it' is's not, throw an error.
    ///
    ///-----Check if "GAME PATH" input is empty. If it is, throw an error.
    ///-----Check if "GAME PATH" input is valid (No Spaces). If it' is's not, throw an error.
    ///
    ///-----Check if "ICON" input is empty. If it is, throw an alert and opt to continue or stop.

    //-----CREATE MAIN.CPP-----//

    QString GameDir_qs = ui->dirInput->text();
    const char* GameDir_cc = GameDir_qs.toLocal8Bit().constData();
    const char* cppFileLoc = "src/main.cpp";

        ofstream cppFile;
        cppFile.open(cppFileLoc);
        cppFile << "#define WINVER 0x0500" << endl;
        cppFile << "#include <iostream>" << endl;
        cppFile << "#include <windows.h>" << endl;
        cppFile << "#include <cstdlib>" << endl;
        cppFile << "#include <shellapi.h>" << endl;
        cppFile << "#include <tlhelp32.h>" << endl;
        cppFile << endl;
        cppFile << "using namespace std;" << endl;
        cppFile << endl;
        cppFile << "void Start(LPCTSTR pName, LPCTSTR pArgs){" << endl;
        cppFile << "    ShellExecute(NULL,\"open\",pName,pArgs,NULL,SW_SHOW);" << endl;
        cppFile << "}" << endl;
        cppFile << endl;
        cppFile << "int main()" << endl;
        cppFile << "{" << endl;
        cppFile << "    FreeConsole();" << endl;
        cppFile << "    Start(\"Emulator\\\\pcsx2.exe\", \"" << GameDir_cc << " --nogui --fullboot\");"<< endl;
        cppFile << "    return 0;" << endl;
        cppFile << "}" << endl;
        cppFile.close();

    //-----CREATE RESOURCES.RC-----//

    QString iconDir_qs = ui->iconInput->text();
    const char* iconDir_cc = iconDir_qs.toLocal8Bit().constData();
    const char* rcFileLoc = "src/resources.rc";

        ofstream rcFile;
        rcFile.open(rcFileLoc);
        rcFile << "#define VOS_NT_WINDOWS32             0x00040004L" << endl;
        rcFile << "#define VFT_APP                      0x00000001L" << endl;
        rcFile << endl;
        rcFile << "A ICON MOVEABLE PURE LOADONCALL DISCARDABLE \"" << iconDir_cc << "\"" << endl;
        rcFile << endl;
        rcFile << "1 VERSIONINFO" << endl;
        rcFile << "FILEVERSION 1,0,0,1" << endl;
        rcFile << "PRODUCTVERSION 1,0,0,1" << endl;
        rcFile << "FILETYPE VFT_APP" << endl;
        rcFile << "{" << endl;
        rcFile << "  BLOCK \"StringFileInfo\"" << endl;
        rcFile << "	 {" << endl;
        rcFile << "		 BLOCK \"040904E4\"" << endl;
        rcFile << "		 {" << endl;
        rcFile << "			 VALUE \"CompanyName\", \"RAMBO\"" << endl;
        rcFile << "			 VALUE \"FileVersion\", \"1.0.0.1\"" << endl;
        rcFile << "			 VALUE \"FileDescription\", \"PCSX2\"" << endl;
        rcFile << "			 VALUE \"InternalName\", \"PCSX2Launcher\"" << endl;
        rcFile << "			 VALUE \"LegalCopyright\", \"RAMBO 2016\"" << endl;
        rcFile << "			 VALUE \"LegalTrademarks\", \"RAMBO\"" << endl;
        rcFile << "			 VALUE \"OriginalFilename\", \"PCSX2Launcher\"" << endl;
        rcFile << "			 VALUE \"ProductName\", \"PCSX2Launcher\"" << endl;
        rcFile << "			 VALUE \"ProductVersion\", \"Initial\"" << endl;
        rcFile << "		 }" << endl;
        rcFile << "	 }" << endl;
        rcFile << "  BLOCK \"VarFileInfo\"" << endl;
        rcFile << "	 {" << endl;
        rcFile << "		 VALUE \"Translation\", 0x0409, 1252" << endl;
        rcFile << "	 }" << endl;
        rcFile << "}" << endl;
        rcFile.close();

    //-----RETREIVING THE NAME, REMOVING SPACES (CMD FRIENDLY), & PLUGIN IT INTO COMPILER-----//
    //----COMPILER USED IS CODEBLOCKS MINGW32 WITH DEFAULT SETTINGS + RESOURCE.RC FOR ICON----//

    QString pcsxCompile1 = "cd compiler\\bin\\ && mingw32-g++.exe -Wall -fexceptions -O2 -c ..\\..\\src\\main.cpp -o ..\\..\\src\\main.o && windres.exe -J rc -O coff -i ..\\..\\src\\resources.rc -o ..\\..\\src\\resources.res && mingw32-g++.exe -o ..\\..\\..\\";
    QString PS2 = "[PS2]";
    QString pcsxName = ui->nameInput->text();
    QString EXE = ".exe";
    QString pcsxCompile2 = " ..\\..\\src\\main.o ..\\..\\src\\resources.res -s";

        //--REMOVE SPACES FROM NAME

        string pcsxName_ = space2underscore(pcsxName.toStdString());
        QString pcsxName_qs = QString::fromStdString(pcsxName_);

    QString pcsxCompileCommand_qs = (pcsxCompile1 + PS2 + pcsxName_qs + EXE + pcsxCompile2);
    QByteArray array = pcsxCompileCommand_qs.toLocal8Bit();
    const char* pcsxCompileCommand_cc = array.data();

    //-----BEGIN COMPILING MAIN.CPP & RESOURCES.RC | CREATES .EXE-----//

        system(pcsxCompileCommand_cc);

    //-----RENAME [PS2]LAUNCHER_NAME.EXE TO REMOVE UNDERSCORES-----//

    QString exeDir = "..\\";
    QString exeName__ = PS2 + pcsxName_qs + EXE;
    QString exeName_s = PS2 + pcsxName + EXE;
    QString exePath__ = exeDir + exeName__;
    QString exePath_s = exeDir + exeName_s;
    QByteArray exeArray__ = exePath__.toLocal8Bit().constData();;
    const char* exePath__cc = exeArray__.data();
    QByteArray exeArray_s = exePath_s.toLocal8Bit().constData();;
    const char* exePath_scc = exeArray_s.data();

        rename(exePath__cc,exePath_scc);

    ///---Give user confirmation that everything went well and provide exe path---

    //-----CLEAR ALL INPUTS AND RESEST-----//

    ///---Clear inputs for reuse---

    //-----UNCOMMENT TO PROOF CHECK A STRING-----//

        //ui->iconInput->setText(exePath__cc);
        //ui->dirInput->setText(exePath_scc);

}

