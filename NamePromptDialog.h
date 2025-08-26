#pragma once

#include <QDialog>
#include <QString>

class QLineEdit;

class NamePromptDialog : public QDialog {
    Q_OBJECT
public:
    explicit NamePromptDialog(QWidget *parent = nullptr);
    virtual ~NamePromptDialog();

    QString name() const;

private:
    QLineEdit *edit;
    QString m_name;
};