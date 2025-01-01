#include "FlashcardWidget.h"
#include "User.h"
#include "VocabFileHandler.h"
#include <QSequentialAnimationGroup>

FlashcardWidget::FlashcardWidget(QWidget *parent, const QString &front_text,
                                 const QString &back_text)
    : QDialog(parent), frontText(front_text), backText(back_text),
      isFlipped(false) {
  setWindowTitle("Flashcard");
  setFixedSize(300, 300);

  // Create the flashcard button
  flashcardButton = new QPushButton(frontText, this);
  flashcardButton->setStyleSheet(
      "font-size: 18px; background-color: #F0E68C; border: 2px solid #BDB76B; "
      "border-radius: 10px;");
  flashcardButton->setFixedSize(200, 100);
  connect(flashcardButton, &QPushButton::clicked, this, &FlashcardWidget::flip);

  // Create the answer input field
  answerInput = new QLineEdit(this);
  answerInput->setPlaceholderText("Enter your answer...");

  // Create buttons
  verifyButton = new QPushButton("Verify", this);
  nextButton = new QPushButton("Next", this);
  cancelButton = new QPushButton("Cancel", this);

  connect(verifyButton, &QPushButton::clicked, this,
          &FlashcardWidget::onVerifyClicked);
  connect(nextButton, &QPushButton::clicked, this,
          &FlashcardWidget::onNextClicked);
  connect(cancelButton, &QPushButton::clicked, this,
          &FlashcardWidget::reject); // Reject the dialog when cancel is clicked

  // Layouts
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(flashcardButton);
  mainLayout->addWidget(answerInput);
  mainLayout->setAlignment(
      flashcardButton, Qt::AlignHCenter); // Center horizontally in the layout

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(verifyButton);
  buttonLayout->addWidget(nextButton);
  buttonLayout->addWidget(cancelButton);

  mainLayout->addLayout(buttonLayout);

  setLayout(mainLayout);
}

void FlashcardWidget::flip() {
  // Ensure the flashcard button geometry is valid
  QRect initialGeometry = flashcardButton->geometry();
  QRect shrinkGeometry = initialGeometry;
  shrinkGeometry.setWidth(initialGeometry.width() / 2); // Shrink to half-width

  // Animation: Shrink to simulate flipping
  QPropertyAnimation *shrink =
      new QPropertyAnimation(flashcardButton, "geometry", this);
  shrink->setDuration(200); // Duration of shrink animation
  shrink->setStartValue(initialGeometry);
  shrink->setEndValue(shrinkGeometry);

  // Change text after shrink
  connect(shrink, &QPropertyAnimation::finished, this,
          [this, initialGeometry]() {
            flashcardButton->setText(isFlipped ? frontText
                                               : backText); // Update text
            isFlipped = !isFlipped; // Toggle flipped state
          });

  // Animation: Expand back to original size
  QPropertyAnimation *expand =
      new QPropertyAnimation(flashcardButton, "geometry", this);
  expand->setDuration(200); // Duration of expand animation
  expand->setStartValue(shrinkGeometry);
  expand->setEndValue(initialGeometry);

  // Sequentially execute animations
  QSequentialAnimationGroup *flipAnimation =
      new QSequentialAnimationGroup(this);
  flipAnimation->addAnimation(shrink);
  flipAnimation->addAnimation(expand);
  flipAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void FlashcardWidget::onVerifyClicked() {
  QString userAnswer = answerInput->text();

  if (userAnswer.compare(backText, Qt::CaseInsensitive) == 0) {
    // Correct answer: flip the flashcard to show the answer
    if (!isFlipped) {
      flashcardButton->setText(backText); // Set the correct answer immediately
      flip();                             // Flip the flashcard
    }
    flashcardButton->setStyleSheet(
        "font-size: 18px; background-color: #90EE90; border: 2px solid "
        "#006400; border-radius: 10px;"); // Green color

    // QMessageBox::information(this, "Correct!", "Your answer is correct!");
  } else {
    // Incorrect answer: show the correct answer and flip the flashcard
    if (!isFlipped) {
      flashcardButton->setText(backText); // Set the correct answer immediately
      isFlipped = true;                   // Mark the flashcard as flipped
    }
    flashcardButton->setStyleSheet(
        "font-size: 18px; background-color: #FF7F7F; border: 2px solid "
        "#8B0000; border-radius: 10px;"); // Red color
    //    QMessageBox::warning(this, "Incorrect", "The correct answer is: " +
    //    backText);
  }
}

void FlashcardWidget::onNextClicked() {

  User &user = User::getInstance();
  VocabFileHandler *vocab_handler =
      VocabFileHandler::getInstance(QString::number(user.getUserID()) + ".vkb");
  VocabFileHandler::VocabStruct vocab;
  if (!vocab_handler->getNextEntry(vocab)) {
    QMessageBox::information(this, "Vokab!", "No More Vocabulary found!");
  } else {
    if (isFlipped) {
      flip();
      flashcardButton->setStyleSheet(
          "font-size: 18px; background-color: #F0E68C; border: 2px solid "
          "#BDB76B; border-radius: 10px;");
    }
    frontText = QString::fromStdString(vocab.word);
    backText = QString::fromStdString(vocab.translation);
    flashcardButton->setText(frontText);
    answerInput->clear();
    answerInput->setPlaceholderText("Enter your answer...");
  }
}
