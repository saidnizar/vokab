#include "vokab.h"
#include <QtWidgets>

Vokab::Vokab(QWidget *parent)
    : QMainWindow(parent)
{
  QWidget * wdg = new QWidget(this);
  QVBoxLayout *vlay = new QVBoxLayout(wdg);
  QPushButton *btn1 = new QPushButton("btn1");
  vlay->addWidget(btn1);
  QPushButton *btn2 = new QPushButton("btn2");
  vlay->addWidget(btn2);
  QPushButton *btn3 = new QPushButton("btn3");
  vlay->addWidget(btn3);
  wdg->setLayout(vlay);
  setCentralWidget(wdg);
}

Vokab::~Vokab()
{
    //delete ui;
}

