#ifndef VOKAB_H
#define VOKAB_H

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

  enum DIAG_TYPE{
    REGISTER,
    LOGIN
  };


private slots:
void onLoginClicked();
void onRegisterClicked();
void onRegisterOrLoginClicked();
void onCancelClicked();
void onLogoutClicked();
void createRegisterOrLoginDialog(QWidget *parent, MainWindow::DIAG_TYPE type);
void replaceCentralWidget();

private:
  QWidget *m_central_widget; 
  QWidget *m_logged_widget = nullptr; 
  QVBoxLayout *m_layout;
  QLabel *m_welcome_label;
  QDialog *m_dialog = nullptr;
  QMenu* m_profile_menu;
  QAction* m_login_action;
  QAction* m_register_action;
  QAction* m_exit_action;
  QAction* m_logout_action = nullptr ;
};
#endif // VOKAB_H
