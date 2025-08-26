#include <iostream>
#include <streambuf>
#include <string>

#include <QApplication>
#include <QDialog>
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


// Custom streambuf to redirect std::cout to QTextEdit
// to do: factor out into own file
// class QTextEditStream : public std::streambuf
// {
// public:
//     QTextEditStream(QTextEdit *edit) : edit(edit) {}

// protected:
//     int_type overflow(int_type v) override
//     {
//         if (v == '\n')
//         {
//             edit->append(QString::fromStdString(buffer));
//             buffer.clear();
//         }
//         else
//         {
//             buffer += v;
//         }
//         return v;
//     }
//     std::string buffer;
//     QTextEdit *edit;
// };

class DeviceDialog : public QDialog {
public:
    DeviceDialog(const QString& deviceName, QWidget *parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle(deviceName);
        QVBoxLayout *layout = new QVBoxLayout(this);
        QLabel *statusLabel = new QLabel("Status: Connected");
        QPushButton *sendButton = new QPushButton("Send Command");
        QPushButton *disconnectButton = new QPushButton("Disconnect");

        layout->addWidget(statusLabel);
        layout->addWidget(sendButton);
        layout->addWidget(disconnectButton);

        connect(sendButton, &QPushButton::clicked, [deviceName]() {
            std::cout << deviceName.toStdString() << ": Command sent!" << std::endl;
        });
        connect(disconnectButton, &QPushButton::clicked, this, &QDialog::accept);
    }
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Prompt user for name
    QString userName = QInputDialog::getText(nullptr, "Welcome", "Please enter your name: ");

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