#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>

#include "User.h"
#include "VocabFileHandler.h"

class AddDialog : public QDialog {
  Q_OBJECT

public:
  explicit AddDialog(QWidget *parent = nullptr) : QDialog(parent) {
    // Set window title based on the mode
    setWindowTitle("Add new vocabulary");

    // Create form layout
    QFormLayout *formLayout = new QFormLayout();

    // Create input fields
    wordField = new QLineEdit(this);
    translationField = new QLineEdit(this);
    exampleField = new QLineEdit(this);

    // Create buttons
    addButton = new QPushButton("Add", this);
    cancelButton = new QPushButton("Cancel", this);

    // Add fields to the layout
    formLayout->addRow("Word(DE):", wordField);
    formLayout->addRow("Translation(EN):", translationField);
    formLayout->addRow("Example:", exampleField);

    // Add buttons horizontally
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    // Create a vertical layout for the dialog
    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    dialogLayout->addLayout(formLayout);
    dialogLayout->addLayout(buttonLayout);

    // Connect Cancel button to close the dialog
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    // Connect the main button to handle the operation (login or register)
    connect(addButton, &QPushButton::clicked, this, &AddDialog::onAddClicked);
  }

private slots:
  void onAddClicked() {
    // Validate the inputs
    if (wordField->text().isEmpty() || translationField->text().isEmpty()) {
      return;
    }
    // Optional: Show a message box or validation error
    User &user = User::getInstance();
    VocabFileHandler *vocab_handler = VocabFileHandler::getInstance(
        QString::number(user.getUserID()) + ".vkb");
    VocabFileHandler::VocabStruct vocab;
    vocab.word = wordField->text().toStdString();
    vocab.translation = translationField->text().toStdString();
    vocab.example = " ";
    vocab_handler->addVocabEntry(vocab);

    accept(); // Close the dialog and mark it as accepted
  }

private:
  QLineEdit *wordField;
  QLineEdit *translationField;
  QLineEdit *exampleField;
  QPushButton *addButton;
  QPushButton *cancelButton;
};

#endif
