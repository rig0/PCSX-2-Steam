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
#include <sys/stat.h>


using namespace std;


//---------------DECLARING FUNCTIONS---------------//

inline bool FileStatus (const string& fileName);

string replaceChar(string text, const char f, const char r);

//bool chkForbiddenChar(string s);

string ExePath();

void compileExe();

//---------------INITIALIZING GUI---------------//

PCSX2Steam::PCSX2Steam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PCSX2Steam)
{
    ui->setupUi(this);

    //setWindowFlags (Qt::FramelessWindowHint);

    //-----Check if "Emulator" directory exists. If it doesn't, throw an error and close.

    if (FileStatus("..\\Emulator") == 0)
    {
        QMessageBox msgBox;
        msgBox.critical(0,"\"Emulator\" Directory not found!","\"..\\Emulator\" directory does not exist! Please read the Readme file");
        exit (EXIT_FAILURE);
    }

    //-----Check if "compiler" directory exists. If it doesn't, throw an error and close.

    if (FileStatus("compiler") == 0)
    {
        QMessageBox msgBox;
        msgBox.critical(0,"\"compiler\" Directory not found!","\"compiler\" directory does not exist! Please read the Readme file");
        exit (EXIT_FAILURE);
    }

}
PCSX2Steam::~PCSX2Steam()
{
    delete ui;
}

//---------BROWSE FOR ICON, PLACE PATH IN FORM AND PREVIEW ON BUTTON---------//

void PCSX2Steam::on_iconPicBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Icon"), QString(),tr("Icon (*.ico)"));

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
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

//-----BROWSE FOR GAME IMAGE (.ISO, .BIN, ETC) AND PLACE IN 'PATH' FORM-----//

void PCSX2Steam::on_dirBrowseBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Game Image"), QString(),tr("PCSX2 Game Images (*.iso *.bin *.img *.nrg *.mdf *.z *.z2 *.bz2 *.dump)"));

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        ui->dirInput->setText(fileName);
        file.close();
    }
}

//------------------------BEGIN CREATING SHORTCUT------------------------//

void PCSX2Steam::on_createButton_clicked()
{
    //-----Check if "NAME" input is empty. If it is, throw an error.

    QString nameChk_qs = ui->nameInput->text();

    if ( nameChk_qs.toStdString() == "" )
    {
        QMessageBox msgBox;
        msgBox.warning(0,"Error","Name field can't be left empty!");
        return;
    }

    ///-----To Do: Check if "NAME" input is valid (No \\/:?\"<>|*). If it' is's not, throw an error.
    /*
        if ( chkForbiddenChar(nameChk_qs.toStdString()))
            {
                QMessageBox msgBox;
                msgBox.warning(0,"Error","Illegal character in Name field! ex. \\/:?\"<>|*");
                return;
            }
    */
    //-----Check if "GAME PATH" input is empty. If it is, throw an error.

    QString direChk_qs = ui->dirInput->text();

    if ( direChk_qs.toStdString() == "" )
    {
        QMessageBox msgBox;
        msgBox.warning(0,"Error","Path field can't be left empty!");
        return;
    }

    ///-----To Do: Check if "GAME PATH" input is valid (No Spaces). If it's not, throw an error.

    //-----Check if "ICON" input is empty. If it is, throw an alert and opt to continue or stop.

    QString iconChk_qs = ui->iconInput->text();

    if ( iconChk_qs.toStdString() == "" )
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText("No Icon chosen.");
        msgBox.setInformativeText("Are you sure you want to continue with no icon?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();

        switch (ret)
        {
        case QMessageBox::Yes:
        {
            QFile::copy(":/res/imgs/noicon.ico" , "src/noicon.ico");
            string ic0Path = replaceChar(ExePath()+ "/src/noicon.ico",'\\','/');
            ui->iconInput->setText(QString::fromStdString(ic0Path));
            break;
        }
        case QMessageBox::No:
        {
            break;
            return;
        }
        }
    }
        compileExe();
}

//-------------------------------------------------------------------------//
//--------------------------- F U N C T I O N S ---------------------------//
//-------------------------------------------------------------------------//

//-------------------CHECKS IF FILE OR DIRECTORY EXISTS--------------------//

inline bool FileStatus (const string& fileName)
{
  struct stat buffer;
  return (stat (fileName.c_str(), &buffer) == 0);
}

//-----------------REPLACES SPECIFIED CHARACTER IN STRING-----------------//

string replaceChar(string text, const char f, const char r)
{
    for(int i = 0; i < text.size(); i++)
    {
        if(text[i] == f)
            text[i] = r;
    }
    return text;
}

//------------------STORES CURRENT DIRECTORY TO STRING------------------//

string ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    return string( buffer ).substr( 0, pos);
}

//-------------------CHECKS FOR FORBIDDEN CHARACTERS--------------------//
/*
bool chkForbiddenChar(string text)
{
    string illegalChars = "\\/:?\"<>|*";
    for (int i = 0; i < text.size(); i++)
    {
        bool found = illegalChars.find(text) != string::npos;
        if(found)
        {
            return true;
            break;
        }
    }
    return false;
}
*/
//---------------------------COMPILES THE .EXE-------------------------//

void PCSX2Steam::compileExe()
{
    //-----Check if "src" directory exists. If it doesn't, create it.
    //-----If it cannot be created, throw an error and close.

    string srcDir = "src";
    if (CreateDirectoryA(srcDir.c_str(), NULL) ||
            ERROR_ALREADY_EXISTS == GetLastError())
    {
        //---'src' created.
    }
    else
    {
        QMessageBox msgBox;
        msgBox.critical(0,"Oops!","Could not create temporary directory. Exiting.");
        exit (EXIT_FAILURE);
    }

    //---------------CREATE MAIN.CPP---------------//

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

    //---------------CREATE RESOURCES.RC---------------//

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

    //-----RETREIVING THE NAME, REMOVING SPACES FROM IT, & CREATING COMPILE COMMAND-----//

    QString pcsxCompile1 = "cd compiler\\bin\\ && mingw32-g++.exe -Wall -fexceptions -O2 -c ..\\..\\src\\main.cpp -o ..\\..\\src\\main.o && windres.exe -J rc -O coff -i ..\\..\\src\\resources.rc -o ..\\..\\src\\resources.res && mingw32-g++.exe -o ..\\..\\..\\";
    QString PS2 = "[PS2]";
    QString pcsxName = ui->nameInput->text();
    QString EXE = ".exe";
    QString pcsxCompile2 = " ..\\..\\src\\main.o ..\\..\\src\\resources.res -s";

        //--Removing spaces from name to make compile command cmd friendly.
        QString pcsxName_qs = QString::fromStdString(replaceChar(pcsxName.toStdString(),' ','_'));

    QString pcsxCompileCommand_qs = (pcsxCompile1 + PS2 + pcsxName_qs + EXE + pcsxCompile2);
    QByteArray array = pcsxCompileCommand_qs.toLocal8Bit();
    const char* pcsxCompileCommand_cc = array.data();

    //-----BEGIN COMPILING MAIN.CPP & RESOURCES.RC | CREATES .EXE-----//

        system(pcsxCompileCommand_cc);

    //-----RENAME [PS2]LAUNCHER_NAME.EXE TO REMOVE UNDERSCORES-----//

    QString exeName__ = PS2 + pcsxName_qs + EXE;
    QString exeName_s = PS2 + pcsxName + EXE;
    QString exePath__ = "..\\" + exeName__;
    QString exePath_s = "..\\" + exeName_s;
    QByteArray exeArray__ = exePath__.toLocal8Bit().constData();;
    const char* exePath__cc = exeArray__.data();
    QByteArray exeArray_s = exePath_s.toLocal8Bit().constData();;
    const char* exePath_scc = exeArray_s.data();

    rename(exePath__cc,exePath_scc);

        //-----CONFIRM WHETHER .EXE WAS COMPILED SUCCESFULY OR NOT-----//

    if ( FileStatus(exePath_s.toStdString()) == 0)
    {
        QMessageBox msgBox;
        msgBox.critical(0,"Error","There was an error compiling. "
                                "\n\nHint: Make sure there are no illegal characters in the Name field \n\nex. \\ / : ? \" < > | * )");
    }
    else
    {
        QString msg = exeName_s + " was successfuly created.";
        QMessageBox msgBox;
        msgBox.information(0,"All Done!",msg);

        //-----CLEAR ALL FORMS-----//

        on_resetButton_clicked();
    }

}

void PCSX2Steam::on_resetButton_clicked()
{
    ui->nameInput->setText("");
    ui->iconInput->setText("");
    ui->dirInput->setText("");
    ui->iconPicBtn->setIcon(QIcon());
}
