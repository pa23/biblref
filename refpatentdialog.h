/*
    biblref
    Creation of bibliographic references.

    File: refpatentdialog.h

    Copyright (C) 2012 Artem Petrov <pa2311@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef REFPATENTDIALOG_H
#define REFPATENTDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class RefPatentDialog;
}

class RefPatentDialog : public QDialog {

    Q_OBJECT

public:

    explicit RefPatentDialog(QPlainTextEdit *pte, QWidget *parent = 0);
    ~RefPatentDialog();

private slots:

    void on_pushButton_add_clicked();

private:

    Ui::RefPatentDialog *ui;
    QPlainTextEdit *plainTextEdit;

};

#endif // REFPATENTDIALOG_H
