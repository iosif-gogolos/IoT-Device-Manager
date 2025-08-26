#include <iostream>

#include <QApplication>
#include <QInputDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QObject>
#include <QTextEdit>
#include <QPalette>
#include <QColor>
#include <QString>

#include "QTextEditStream.h"
#include "DeviceDialog.h"
#include "NamePromptDialog.h"
#include "Gui.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    NamePromptDialog prompt;
    if (prompt.exec() != QDialog::Accepted || prompt.name().isEmpty())
        return 0;

    QString userName = prompt.name();

    if (userName.isEmpty()){
        return 0;
    }

    // set custom color palette
    QPalette customPalette;

    // customPalette.setColor();
    customPalette.setColor(QPalette::Window, QColor(30, 30, 30));
    customPalette.setColor(QPalette::WindowText, Qt::white);
    customPalette.setColor(QPalette::Base, QColor(20, 20, 20));
    customPalette.setColor(QPalette::AlternateBase, QColor(30, 30, 30));
    customPalette.setColor(QPalette::ToolTipBase, Qt::white);
    customPalette.setColor(QPalette::ToolTipText, Qt::white);
    customPalette.setColor(QPalette::Text, Qt::white);
    customPalette.setColor(QPalette::Button, QColor(30, 30, 30));
    customPalette.setColor(QPalette::ButtonText, Qt::white);
    customPalette.setColor(QPalette::BrightText, Qt::red);
    customPalette.setColor(QPalette::Highlight, QColor(0, 120, 215));
    customPalette.setColor(QPalette::HighlightedText, Qt::white);
    app.setPalette(customPalette);

   

    QWidget *window = new QWidget;
    window->setWindowTitle(userName + "'s IoT-Manager" );
    QVBoxLayout *layout = new QVBoxLayout(window);

    QTextEdit *terminal = new QTextEdit;
    terminal->setReadOnly(true);

     // Style for rounder, blue-accented, dark widgets
    QString styleSheet = R"(
        QWidget {
            background-color: #1e1e1e;
            color: #ffffff;
        }
        QTextEdit {
            border-radius: 12px;
            border: 2px solid #0078d7;
            background-color: #23272e;
            color: #ffffff;
            padding: 8px;
        }
        QPushButton {
            border-radius: 10px;
            background-color: #23272e;
            color: #ffffff;
            border: 2px solid #0078d7;
            padding: 8px 16px;
        }
        QPushButton:hover {
            background-color: #0078d7;
            color: #ffffff;
        }
    )";

    window->setStyleSheet(styleSheet);

    // Redirect std::cout to QTextEdit
    QTextEditStream *editStream = new QTextEditStream(terminal);
    std::cout.rdbuf(editStream);

    QPushButton *welcomeButton = new QPushButton("Greet the user");
    QPushButton *messageButton = new QPushButton("Send message to device");
    QPushButton *exitButton = new QPushButton("Click to end the program");

    QPushButton *device1Button = new QPushButton("Open Smart light bulb 1");
    QPushButton *device2Button = new QPushButton("Open Smart Speaker 1");
    QPushButton *device3Button = new QPushButton("Open Air Consitioner 1");

    layout->addWidget(device1Button);
    layout->addWidget(device2Button);
    layout->addWidget(device3Button);

    QObject::connect(device1Button, &QPushButton::clicked, [&]() {
        DeviceDialog dlg(userName + "'s Smart light bulb 1", window);
        dlg.exec();
    });
    QObject::connect(device2Button, &QPushButton::clicked, [&]() {
        DeviceDialog dlg(userName + "'s Smart Speaker 1", window);
        dlg.exec();
    });
    QObject::connect(device3Button, &QPushButton::clicked, [&]() {
        DeviceDialog dlg(userName + "'s Open Air Consitioner 1", window);
        dlg.exec();
    });

    layout->addWidget(welcomeButton);
    layout->addWidget(messageButton);

    layout->addWidget(device1Button);
    layout->addWidget(device2Button);
    layout->addWidget(device3Button);

    layout->addWidget(exitButton);
    layout->addWidget(terminal);

    // Connect exitButton to close the window
    QObject::connect(exitButton, &QPushButton::clicked, window, &QWidget::close);

    // connect messageButton to print to the console
    QObject::connect(messageButton, &QPushButton::clicked, [userName]()
                      { std::cout << "A new message sent from " << userName.toStdString() << std::endl; });

    // Connect welcomeButton to print the user
    QObject::connect(welcomeButton, &QPushButton::clicked, [userName]()
                      { std::cout << "Welcome to IoT-Manager, " << userName.toStdString() << "!" << std::endl; });

    window->show();

    return app.exec();
}