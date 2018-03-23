#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QWidget>
#include <QWindow>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT
public:
    Settings(QMap<QString,QString>* settingsMap, QWidget *parent = nullptr);
    ~Settings();

signals:

public slots:

private slots:
    void on_settings_save_button_clicked();

private:
    Ui::Settings *ui;
    QMap<QString,QString>* settingsP = nullptr;

};

#endif // SETTINGS_H
