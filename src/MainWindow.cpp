#include <QFormLayout>
#include <QLineEdit>
#include <QPixmap>
#include <QWidgetAction>
#include <iostream>

#include "AuthDialog.h"
#include "HomeWidget.h"
#include "MainWindow.h"
#include "User.h"
#include "VocabFileHandler.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   // Create a central widget for the main window
   m_central_widget = new QWidget(this);

   // Create a vertical layout
   m_layout = new QVBoxLayout();

   // Add a welcome label
   m_welcome_label = new QLabel("Welcome to the Vokab Project!");
   m_welcome_label->setAlignment(Qt::AlignCenter); // Center the text
   m_welcome_label->setStyleSheet("font-size: 24px; font-weight: bold;"); // Customize the style
   // Load the logo as a QPixmap
   QPixmap logoPixmap("../vokab.png");

   logoPixmap =
       logoPixmap.scaled(200, 200, Qt::KeepAspectRatio); // Resize if needed
   // Create a QLabel to display the logo
   QLabel *logoLabel = new QLabel();
   logoLabel->setPixmap(logoPixmap);
   logoLabel->setAlignment(Qt::AlignCenter); // Center align the logo

   // Add widgets to the layout
   m_layout->addWidget(logoLabel);
   m_layout->addWidget(m_welcome_label);


   // Set spacing and margins
   m_layout->setSpacing(20);
   m_layout->setContentsMargins(50, 50, 50, 50);

   // Set the layout to the central widget
   m_central_widget->setLayout(m_layout);

   // Set the central widget to the main window
   setCentralWidget(m_central_widget);

 
  // Create the menu bar
   QMenuBar *menuBar = new QMenuBar(this);

   /*  QPixmap logoPixmap("../vokab.png");
     logoPixmap = logoPixmap.scaled(50, 50, Qt::KeepAspectRatio); // Resize if
     needed

           // Create a QLabel to hold the logo
           QLabel* logoLabel = new QLabel();
           logoLabel->setPixmap(logoPixmap);

           // Use QWidgetAction to add QLabel to QMenuBar
           QWidgetAction* logoAction = new QWidgetAction(menuBar);
           logoAction->setDefaultWidget(logoLabel);

           // Add the logo to the menu bar
           menuBar->addAction(logoAction);
   */
   // Create menus
   m_profile_menu = menuBar->addMenu("Profile");
   QMenu* helpMenu = menuBar->addMenu("Help");
  
   // Add actions to the "File" menu
   m_login_action = new QAction("Login", this);
   m_profile_menu->addAction(m_login_action);


   // Add actions to the "File" menu
   m_register_action = new QAction("Register", this);
   m_profile_menu->addAction(m_register_action);

    // Add actions to the "File" menu
   m_exit_action = new QAction("Exit", this);
   m_profile_menu->addAction(m_exit_action);

 
   // Add actions to the "Help" menu
   QAction* aboutAction = new QAction("About", this);
   helpMenu->addAction(aboutAction);
  
   // Set the menu bar for the main window
   setMenuBar(menuBar);
  
   // Connect actions to slots
   connect(m_exit_action, &QAction::triggered, this, &QMainWindow::close); // Close the application
   connect(m_login_action, &QAction::triggered, this, &MainWindow::onLoginClicked); // Close the application
   connect(m_register_action, &QAction::triggered, this, &MainWindow::onRegisterClicked); // Close the application
   connect(aboutAction, &QAction::triggered,
           [this]() { QMessageBox::information(this, "About", "vokab v1.0"); });
   User &user = User::getInstance();
   if (user.loadPreviousSession())
     onRegisterOrLoginClicked();
}

MainWindow::~MainWindow()
{
  delete m_layout;
  delete m_welcome_label;
  delete m_central_widget;
	delete m_login_action;
	delete m_register_action;
	if (m_logout_action) delete m_logout_action;
	delete m_exit_action;
}

void MainWindow::onLoginClicked() {
  AuthDialog dialog(AuthDialog::Login, this);
  if (dialog.exec() == QDialog::Accepted) {
    // Retrieve user inputs from the dialog
    QString username = dialog.getUsername();
    QString password = dialog.getPassword();
    User &user = User::getInstance();
    if (user.logInUser(username.toStdString(), password.toStdString()))
      onRegisterOrLoginClicked();
    else
      QMessageBox::information(this, "Vokab", " user does not exist");
  }
}

void MainWindow::onRegisterClicked() {
  AuthDialog dialog(AuthDialog::Register, this);
  if (dialog.exec() == QDialog::Accepted) {
    // Retrieve user inputs from the dialog
    QString username = dialog.getUsername();
    QString password = dialog.getPassword();

    User &user = User::getInstance();
    if (user.registerUser(username.toStdString(), password.toStdString()))
      onRegisterOrLoginClicked();
    else
      QMessageBox::information(this, "Vokab", " username already exist");
  }
}

void MainWindow::onRegisterOrLoginClicked()
{
	replaceCentralWidget();
	// Add actions to the "File" menu
 
	m_profile_menu->removeAction(m_login_action);
	m_profile_menu->removeAction(m_register_action);
	if (!m_logout_action) m_logout_action = new QAction("Logout", this);
  connect(m_logout_action, &QAction::triggered, this, &MainWindow::onLogoutClicked); // Close the application
  m_profile_menu->insertAction(m_exit_action, m_logout_action);
}

void MainWindow::onLogoutClicked()
{
		// Remove the current central widget
    QWidget* oldWidget = takeCentralWidget();
    if (m_logged_widget) {
       delete m_logged_widget; // Clean up memory
				m_logged_widget = nullptr;
				
    }

    // Set the new central widget
    setCentralWidget(m_central_widget);

		m_profile_menu->removeAction(m_logout_action);
                m_profile_menu->insertAction(m_exit_action, m_register_action);
                m_profile_menu->insertAction(m_register_action, m_login_action);

                User &user = User::getInstance();
                user.logoutUser();
                VocabFileHandler *vocab_handler =
                    VocabFileHandler::getInstance();
                vocab_handler->destroyInstance();
}


void MainWindow::replaceCentralWidget() {

  HomeWidget *homeWidget = new HomeWidget(this);

  // Remove the current central widget
  QWidget *oldWidget = takeCentralWidget();

  oldWidget->setParent(nullptr);
  // Set the new central widget
  setCentralWidget(homeWidget);
}

