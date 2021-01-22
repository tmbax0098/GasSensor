#ifndef PASSWORDCERTIFICATEWINDOW_H
#define PASSWORDCERTIFICATEWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <keyboardwindow.h>

namespace Ui {
class PasswordCertificateWindow;
}

class PasswordCertificateWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PasswordCertificateWindow(QWidget *parent = nullptr);
    ~PasswordCertificateWindow();

    bool reset() const;

    QSqlDatabase getDatabase() const;
    void setDatabase(const QSqlDatabase &value);

signals :
    void login();

private slots:

    void on_pushButtonEditPassword_clicked();

    void on_btnCertificate_clicked();

private:
    Ui::PasswordCertificateWindow *ui;

    KeyboardWindow keyboardWindow;
    QSqlDatabase database;


    void closeAllconnection();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);

    void showEvent(QShowEvent *event);
};

#endif // PASSWORDCERTIFICATEWINDOW_H
