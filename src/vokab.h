#ifndef VOKAB_H
#define VOKAB_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Vokab; }
QT_END_NAMESPACE

class Vokab : public QMainWindow
{
    Q_OBJECT

public:
    Vokab(QWidget *parent = nullptr);
    ~Vokab();

private:
};
#endif // VOKAB_H
