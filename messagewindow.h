#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class MessageWindow;
}

class MessageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MessageWindow(QWidget *parent = nullptr);
    ~MessageWindow();

    void showMessage(QString message ="");

private:
    Ui::MessageWindow *ui;
};

#endif // MESSAGEWINDOW_H
