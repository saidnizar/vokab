#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class HomeWidget : public QWidget {
  Q_OBJECT

public:
  explicit HomeWidget(QWidget *parent = nullptr);

private slots:
  void onAddButtonClicked();
  void onExerciseButtonClicked();

private:
  void setupUI();
  QPushButton *m_exercise_btn;
  QPushButton *m_add_btn;
  QPushButton *m_view_btn;
};

#endif // HOMEWIDGET_H
