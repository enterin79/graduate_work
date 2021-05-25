#ifndef HELP_H
#define HELP_H

#include <QDialog>

namespace Ui {
class Help;
}
/*Класс окна справки
 * Позволяет выводить информацию в удобном для чтения виде
 *
 * Поле:
 * ui - экемпляр формы графического интерфейса.
 *
 * Методы:
 * Help - конструктор класса по умолчанию;
 * ~Help - деструктор класса;
 * setText - процедура установки текста в элемент;
 * on_btHelpOK_clicked - событие закрытия формы.
*/
class Help : public QDialog
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = nullptr);
    ~Help();
    void setText(QString *text);


public slots:
    void on_btHelpOK_clicked();

private:
    Ui::Help *ui;
};

#endif // HELP_H
