#pragma once

#include <QDialog>


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