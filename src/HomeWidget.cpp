#include "HomeWidget.h"
#include "AddDialog.h"
#include "FlashcardWidget.h"
#include "User.h"

HomeWidget::HomeWidget(QWidget *parent) : QWidget(parent) { setupUI(); }

void HomeWidget::setupUI() {
  QVBoxLayout *layout = new QVBoxLayout(this);

  User &user = User::getInstance();
  std::string label = "What do you want to do " + user.getUsername() + " ?";
  QLabel *thankYouLabel = new QLabel(QString::fromUtf8(label.c_str()));
  thankYouLabel->setAlignment(Qt::AlignCenter);
  thankYouLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

  QPushButton *m_exercise_btn = new QPushButton("Exercise");
  m_exercise_btn->setStyleSheet("background-color: lightblue; color: black; "
                                "font-size: 16px; border-radius: 5px;");
  connect(m_exercise_btn, &QPushButton::clicked, this,
          &HomeWidget::onExerciseButtonClicked);

  QPushButton *m_add_btn = new QPushButton("Add New Vokab");
  m_add_btn->setStyleSheet("background-color: lightblue; color: black; "
                           "font-size: 16px; border-radius: 5px;");
  connect(m_add_btn, &QPushButton::clicked, this,
          &HomeWidget::onAddButtonClicked);

  QPushButton *m_view_btn = new QPushButton("View All Vokab");
  m_view_btn->setStyleSheet("background-color: lightblue; color: black; "
                            "font-size: 16px; border-radius: 5px;");

  layout->addWidget(thankYouLabel);
  layout->addWidget(m_exercise_btn);
  layout->addWidget(m_add_btn);
  layout->addWidget(m_view_btn);
  layout->setAlignment(Qt::AlignCenter);

  setLayout(layout);
}

void HomeWidget::onAddButtonClicked() {
  AddDialog dialog(this);
  if (dialog.exec() == QDialog::Accepted) {
    // Retrieve user inputs from the dialog
  }
}

// Define the slot
void HomeWidget::onExerciseButtonClicked() {
  User &user = User::getInstance();
  VocabFileHandler *vocab_handler =
      VocabFileHandler::getInstance(QString::number(user.getUserID()) + ".vkb");
  VocabFileHandler::VocabStruct vocab;
  if (!vocab_handler->getNextEntry(vocab)) {
    QMessageBox::information(this, "Vokab!", "No Vocabulary found!");
  } else {
    QString frontText = QString::fromStdString(vocab.word);
    QString backText = QString::fromStdString(vocab.translation);
    FlashcardWidget *flashcard = new FlashcardWidget(this, frontText, backText);
    flashcard->exec(); // Automatically delete the widget when closed
    delete flashcard;
  }
}
