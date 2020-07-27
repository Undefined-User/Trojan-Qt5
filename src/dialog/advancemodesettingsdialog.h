#ifndef ADVANCEMODESETTINGSDIALOG_H
#define ADVANCEMODESETTINGSDIALOG_H

#include <QDialog>
#include "confighelper.h"

namespace Ui {
class AdvanceModeSettingsDialog;
}

class AdvanceModeSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdvanceModeSettingsDialog(ConfigHelper *ch, QWidget *parent = 0);
    ~AdvanceModeSettingsDialog();

private:
    Ui::AdvanceModeSettingsDialog *ui;
    ConfigHelper *helper;

    void refresh();
    void deleteMode();

private slots:
    void onAccepted();
    void on_addBtn_clicked();
    void on_editBtn_clicked();
    void on_deleteBtn_clicked();
};

#endif // ADVANCEMODESETTINGSDIALOG_H
