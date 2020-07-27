#include "utils.h"
#include "modeeditdialog.h"
#include "ui_modeeditdialog.h"

#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>
#include <QtDebug>
#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonObject>

ModeEditDialog::ModeEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeEditDialog)
{
    ui->setupUi(this);

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ModeEditDialog::onAccepted);
}

ModeEditDialog::~ModeEditDialog()
{
    delete ui;
}

void ModeEditDialog::showContextMenu(const QPoint &pos)
{
    // Handle global position
    QPoint globalPos = ui->listWidget->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.addAction("Delete", this, SLOT(deleteItem()));

    // Show context menu at handling position
    myMenu.exec(globalPos);
}

void ModeEditDialog::deleteItem()
{
    QListWidgetItem *item = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete item;
}

int ModeEditDialog::onEdit(QString name, QStringList process)
{
    ui->nameEdit->setText(name);
    ui->listWidget->addItems(process);
    return this->exec();
}

bool ModeEditDialog::isDuplicated(QString name)
{
    for(int i = 0; i < ui->listWidget->count(); ++i)
    {
        QString str = ui->listWidget->item(i)->text();
        if (str == name)
            return true;
    }

    return false;
}

QJsonArray ModeEditDialog::getAllItems()
{
    QJsonArray array;
    for(int i = 0; i < ui->listWidget->count(); ++i) {
        array.append(ui->listWidget->item(i)->text());
    }
    return array;
}

void ModeEditDialog::on_addBtn_clicked()
{
    QString name = ui->processEdit->text();
    if (!name.endsWith(".exe") && !name.isEmpty())
        name += ".exe";

    if (name.isEmpty()) {
        QMessageBox::information(NULL, tr("Information"), tr("Please enter a process name"));
    }

    if (!isDuplicated(name)) {
        ui->listWidget->addItem(name);
    }
}

void ModeEditDialog::onAccepted()
{
    if (ui->nameEdit->text().isEmpty()) {
        QMessageBox::information(NULL, tr("Information"), tr("Please enter a mode name"));
        return;
    }

    QJsonObject object;
    object["name"] = ui->nameEdit->text();
    object["process"] = getAllItems();

    QJsonDocument JSONDoc(object);

    QString file = QDir::toNativeSeparators(Utils::getConfigPath() + "/mode/" + ui->nameEdit->text() + ".json");

    QFile JSONFile(file);
    JSONFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);

    JSONFile.write(JSONDoc.toJson());
    JSONFile.close();

    this->accept();
}

void ModeEditDialog::on_scanBtn_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "Select a folder", ".", QFileDialog::ShowDirsOnly);
    if (path.isEmpty()) {
        return;
    }
    QDirIterator it(path, QStringList() << "*.exe", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        QString exe = it.fileName();
        if (!isDuplicated(exe)) {
            ui->listWidget->addItem(exe);
        }
    }
    QMessageBox::information(NULL, tr("Information"), tr("Scan completed"));
}
