#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>

class AuthDialog : public QDialog {
  Q_OBJECT

public:
  enum Mode { Login, Register };

  explicit AuthDialog(Mode mode, QWidget *parent = nullptr)
      : QDialog(parent), currentMode(mode) {
    // Set window title based on the mode
    setWindowTitle(mode == Login ? "Login" : "Register");

    // Create form layout
    QFormLayout *formLayout = new QFormLayout();

    // Create input fields
    usernameField = new QLineEdit(this);
    passwordField = new QLineEdit(this);
    passwordField->setEchoMode(QLineEdit::Password); // Hide password input

    // Create buttons
    mainButton = new QPushButton(this);
    cancelButton = new QPushButton("Cancel", this);

    // Set the main button text based on the mode
    mainButton->setText(mode == Login ? "Login" : "Register");

    // Add fields to the layout
    formLayout->addRow("Username:", usernameField);
    formLayout->addRow("Password:", passwordField);

    // Add buttons horizontally
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(mainButton);
    buttonLayout->addWidget(cancelButton);

    // Create a vertical layout for the dialog
    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    dialogLayout->addLayout(formLayout);
    dialogLayout->addLayout(buttonLayout);

    // Connect Cancel button to close the dialog
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    // Connect the main button to handle the operation (login or register)
    connect(mainButton, &QPushButton::clicked, this,
            &AuthDialog::onMainButtonClicked);
  }

  // Getters for user input
  QString getUsername() const { return usernameField->text(); }

  QString getPassword() const { return passwordField->text(); }

private slots:
  void onMainButtonClicked() {
    // Validate the inputs
    if (usernameField->text().isEmpty() || passwordField->text().isEmpty()) {
      // Optional: Show a message box or validation error
      return;
    }

    // Logic specific to Login or Register
    if (currentMode == Login) {
      // Handle login logic (e.g., authenticate the user)
    } else if (currentMode == Register) {
      // Handle register logic (e.g., save the user to the database)
    }

    accept(); // Close the dialog and mark it as accepted
  }

private:
  Mode currentMode;
  QLineEdit *usernameField;
  QLineEdit *passwordField;
  QPushButton *mainButton;
  QPushButton *cancelButton;
};

#endif
