#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QDialog>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
void onLoginClicked();
void onRegisterClicked();
void onRegisterOrLoginClicked();
void onLogoutClicked();
void replaceCentralWidget();

private:
  QWidget *m_central_widget; 
  QWidget *m_logged_widget = nullptr; 
  QVBoxLayout *m_layout;
  QLabel *m_welcome_label;
  QMenu* m_profile_menu;
  QAction* m_login_action;
  QAction* m_register_action;
  QAction* m_exit_action;
  QAction* m_logout_action = nullptr ;
};
#endif // VOKAB_H
