#pragma once

#include <streambuf>
#include <string>
#include <QTextEdit>
#include <QString>

class QTextEditStream : public std::streambuf
{
public:
    QTextEditStream(QTextEdit *edit) : edit(edit) {}

protected:
    int_type overflow(int_type v) override
    {
        if (v == '\n')
        {
            edit->append(QString::fromStdString(buffer));
            buffer.clear();
        }
        else
        {
            buffer += v;
        }
        return v;
    }
    std::string buffer;
    QTextEdit *edit;
};