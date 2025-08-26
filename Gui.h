#pragma once

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>

class Gui : public QWidget {
    Q_OBJECT
public:
    explicit Gui(const QString& userName, QWidget *parent = nullptr);

private:
    QVBoxLayout *layout;
    QTextEdit *terminal;
    QPushButton *welcomeButton;
    QPushButton *messageButton;
    QPushButton *exitButton;
    QPushButton *device1Button;
    QPushButton *device2Button;
    QPushButton *device3Button;
    QString userName;
};