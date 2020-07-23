#ifndef MODEEDITDIALOG_H
#define MODEEDITDIALOG_H

#include <QDialog>
#include <QJsonArray>

namespace Ui {
class ModeEditDialog;
}

class ModeEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModeEditDialog(QWidget *parent = nullptr);
    ~ModeEditDialog();

    bool isDuplicated(QString name);

    int onEdit(QString name, QStringList process);

private slots:
    void showContextMenu(const QPoint &pos);
    void deleteItem();
    void on_addBtn_clicked();
    QJsonArray getAllItems();
    void onAccepted();

    void on_scanBtn_clicked();

private:
    Ui::ModeEditDialog *ui;
};

#endif // MODEEDITDIALOG_H
