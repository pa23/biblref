/*
    biblref
    Creation of bibliographic references.

    File: refinventsertificatedialog.h

    Copyright (C) 2012-2014 Artem Petrov <pa2311@gmail.com>

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

#ifndef REFINVENTSERTIFICATEDIALOG_H
#define REFINVENTSERTIFICATEDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class RefInventSertificateDialog;
}

class RefInventSertificateDialog : public QDialog {

    Q_OBJECT

public:
    explicit RefInventSertificateDialog(QPlainTextEdit *, QWidget *parent = 0);
    ~RefInventSertificateDialog();

private slots:
    void on_pushButton_add_clicked();

private:
    Ui::RefInventSertificateDialog *ui;
    QPlainTextEdit *plainTextEdit;

};

#endif // REFINVENTSERTIFICATEDIALOG_H
