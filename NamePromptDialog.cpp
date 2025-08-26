#include "NamePromptDialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
//#include "moc_NamePromptDialog.cpp"

NamePromptDialog::NamePromptDialog(QWidget *parent)
    : QDialog(parent), edit(new QLineEdit)
{
    setWindowTitle("Welcome");
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Please enter your name:");
    QPushButton *okButton = new QPushButton("OK");

    layout->addWidget(label);
    layout->addWidget(edit);
    layout->addWidget(okButton);

    // Style
    QString styleSheet = R"(
        QDialog, QWidget {
            background-color: #1e1e1e;
            color: #ffffff;
        }
        QLineEdit {
            border-radius: 10px;
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
    setStyleSheet(styleSheet);

    connect(okButton, &QPushButton::clicked, this, [this]() {
        if (!edit->text().isEmpty()) {
            m_name = edit->text();
            accept();
        }
    });
    connect(edit, &QLineEdit::returnPressed, okButton, &QPushButton::click);
}

NamePromptDialog::~NamePromptDialog() {}

QString NamePromptDialog::name() const {
    return m_name;
}