#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QMap<QString,QString> *settingsMap, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->lptdata_line_edit->setText(settingsMap->value("LptData"));
    ui->lptstatus_line_edit->setText(settingsMap->value("LptStatus"));
    ui->lptconfig_line_edit->setText(settingsMap->value("LptConfig"));
    ui->serverip_line_edit->setText(settingsMap->value("ServerIp"));
    ui->serverport_line_edit->setText(settingsMap->value("ServerPort"));
    settingsP = settingsMap;
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_settings_save_button_clicked()
{
    QString savePath;
    savePath = "settings.txt";
    if (savePath.size())
    {
        QFile saveFile(savePath);
        if (!saveFile.open(QIODevice::WriteOnly | QIODevice::Text )) return;
        QTextStream out(&saveFile);
        out << "LptData = " << ui->lptdata_line_edit->text() << endl;
        out << "LptStatus = " << ui->lptstatus_line_edit->text() << endl;
        out << "LptConfig = " << ui->lptconfig_line_edit->text() << endl;
        out << "ServerIp = " << ui->serverip_line_edit->text() << endl;
        out << "ServerPort = " << ui->serverport_line_edit->text() << endl;
        saveFile.close();
    }

    settingsP->insert("LptData", ui->lptdata_line_edit->text());
    settingsP->insert("LptStatus", ui->lptstatus_line_edit->text());
    settingsP->insert("LptConfig", ui->lptconfig_line_edit->text());
    settingsP->insert("ServerIp", ui->serverip_line_edit->text());
    settingsP->insert("ServerPort", ui->serverport_line_edit->text());
}
