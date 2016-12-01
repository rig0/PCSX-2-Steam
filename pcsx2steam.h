#ifndef PCSX2STEAM_H
#define PCSX2STEAM_H

#include <QMainWindow>

namespace Ui {
class PCSX2Steam;
}

class PCSX2Steam : public QMainWindow
{
    Q_OBJECT

public:
    explicit PCSX2Steam(QWidget *parent = 0);
    ~PCSX2Steam();

private slots:
    void on_iconPicBtn_clicked();

    void on_dirBrowseBtn_clicked();

    void on_createButton_clicked();

    void compileExe();

    void on_resetButton_clicked();

private:
    Ui::PCSX2Steam *ui;
};

#endif // PCSX2STEAM_H
