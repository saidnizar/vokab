#include "mainWindow.h"
#include "stylesheet.h"
#include <iostream>
#include <QFormLayout>
#include <QLineEdit>

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


   // Add widgets to the layout
   m_layout->addWidget(m_welcome_label);


   // Set spacing and margins
   m_layout->setSpacing(20);
   m_layout->setContentsMargins(50, 50, 50, 50);

   // Set the layout to the central widget
   m_central_widget->setLayout(m_layout);

   // Set the central widget to the main window
   setCentralWidget(m_central_widget);

 
  // Create the menu bar
   QMenuBar* menuBar = new QMenuBar(this);
  
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
   connect(aboutAction, &QAction::triggered, [this]() {
       QMessageBox::information(this, "About", "This is a sample application with a menu bar.");
       });
  
}

MainWindow::~MainWindow()
{
  delete m_layout;
  delete m_welcome_label;
  delete m_central_widget;
	if (m_dialog) delete m_dialog;
	delete m_login_action;
	delete m_register_action;
	if (m_logout_action) delete m_logout_action;
	delete m_exit_action;
}

void MainWindow::onLoginClicked() {
    // Handle login button click
    createRegisterOrLoginDialog(this, MainWindow::DIAG_TYPE::LOGIN);
    m_dialog->exec(); // Show login dialog
}

void MainWindow::onRegisterClicked() {
    // Handle register button click
    createRegisterOrLoginDialog(this, MainWindow::DIAG_TYPE::REGISTER);
    m_dialog->exec(); // Show register dialog
}

void MainWindow::createRegisterOrLoginDialog(QWidget* parent, DIAG_TYPE type) {
    // Create a simple register dialog
    if (!m_dialog) m_dialog = new QDialog(parent);
    if (type == MainWindow::DIAG_TYPE::REGISTER)
			m_dialog->setWindowTitle("Register");
		else 
			m_dialog->setWindowTitle("Login");

    QFormLayout* formLayout = new QFormLayout();
    QLineEdit* usernameField = new QLineEdit();
    QLineEdit* passwordField = new QLineEdit();
    passwordField->setEchoMode(QLineEdit::Password);
 
    QPushButton *signUpButton;	 		
    if (type == MainWindow::DIAG_TYPE::REGISTER)
		  signUpButton = new QPushButton("Register");
    else 
      signUpButton = new QPushButton("Login");
    
	  QPushButton* cancelButton = new QPushButton("Cancel");

    formLayout->addRow("Username:", usernameField);
    formLayout->addRow("Password:", passwordField);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(signUpButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout* dialogLayout = new QVBoxLayout(m_dialog);
    dialogLayout->addLayout(formLayout);
    dialogLayout->addLayout(buttonLayout);

    connect(cancelButton, &QPushButton::clicked, this, &MainWindow::onCancelClicked);
   	connect(signUpButton, &QPushButton::clicked, this, &MainWindow::onRegisterOrLoginClicked);

}

void MainWindow::onCancelClicked()
{
	m_dialog->reject();
	delete m_dialog;
	m_dialog = nullptr;
}
void MainWindow::onRegisterOrLoginClicked()
{
	replaceCentralWidget();
	m_dialog->accept();
	// Add actions to the "File" menu
 
	m_profile_menu->removeAction(m_login_action);
	m_profile_menu->removeAction(m_register_action);
	if (!m_logout_action) m_logout_action = new QAction("Logout", this);
  connect(m_logout_action, &QAction::triggered, this, &MainWindow::onLogoutClicked); // Close the application
  m_profile_menu->insertAction(m_exit_action, m_logout_action);

 	delete m_dialog;
	m_dialog = nullptr;

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
}


void MainWindow::replaceCentralWidget() {
    m_logged_widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(m_logged_widget);

    QLabel* thankYouLabel = new QLabel("Thank you for signing up!");
    thankYouLabel->setAlignment(Qt::AlignCenter);
    thankYouLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    layout->addWidget(thankYouLabel);
    layout->setAlignment(Qt::AlignCenter);

 
	// Remove the current central widget
    QWidget* oldWidget = takeCentralWidget();

		oldWidget->setParent(nullptr);
    // Set the new central widget
    setCentralWidget(m_logged_widget);
}

