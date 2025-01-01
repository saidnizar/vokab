#ifndef FLASHCARDWIDGET_H
#define FLASHCARDWIDGET_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QVBoxLayout>

class FlashcardWidget : public QDialog {
  Q_OBJECT

public:
  explicit FlashcardWidget(QWidget *parent = nullptr,
                           const QString &front_text = "",
                           const QString &back_text = "");

private slots:
  void flip();
  void onVerifyClicked();
  void onNextClicked();

private:
  QPushButton *flashcardButton; // Button styled as a flashcard
  QLineEdit *answerInput;       // Input field for user to type the answer
  QPushButton *verifyButton;    // Button to verify the answer
  QPushButton *nextButton;      // Button to move to the next flashcard
  QPushButton *cancelButton;    // Button to cancel or close
  QString frontText;            // Text displayed on the front of the flashcard
  QString backText;             // Text displayed on the back of the flashcard
  bool isFlipped;               // Tracks if the flashcard is flipped
};

#endif // FLASHCARDWIDGET_H
