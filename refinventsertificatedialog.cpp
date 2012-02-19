/*
    biblref
    Creation of bibliographic references.

    File: refinventsertificatedialog.cpp

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

#include "refinventsertificatedialog.h"
#include "ui_refinventsertificatedialog.h"

#include <QPlainTextEdit>
#include <QTextCursor>
#include <QString>
#include <QStringList>
#include <QMessageBox>

RefInventSertificateDialog::RefInventSertificateDialog(QPlainTextEdit *pte,
                                                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RefInventSertificateDialog) {

    ui->setupUi(this);
    plainTextEdit = pte;
}

RefInventSertificateDialog::~RefInventSertificateDialog() {

    delete ui;
}

void RefInventSertificateDialog::on_pushButton_add_clicked() {

    QStringList authors = ui->lineEdit_authors->
            text().split(";", QString::SkipEmptyParts);

    if ( ui->lineEdit_authors->text().isEmpty() || authors.isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Патент"
                              "\" необходима информация об авторах.");
        return;
    }

    if ( ui->lineEdit_country->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Патент"
                              "\" необходимо указать страну.");
        return;
    }

    if ( ui->lineEdit_classification->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Патент"
                              "\" необходимо указать информацию "
                              "о классификации документа.");
        return;
    }

    if ( ui->lineEdit_title->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Патент"
                              "\" необходимо указать название.");
        return;
    }

    //

    QString bibref("");

    bibref += "А.с. "
            + QString::number(ui->spinBox_docnumber->value())
            + " "
            + ui->lineEdit_country->text()
            + ", "
            + ui->lineEdit_classification->text()
            + ". "
            + ui->lineEdit_title->text()
            + " / ";

    for ( ptrdiff_t i=0; i<authors.count(); i++ ) {

        bibref += authors[i].trimmed() + ", ";
    }

    bibref.chop(2);

    bibref += ".";

    //

    plainTextEdit->moveCursor(QTextCursor::End);
    plainTextEdit->appendPlainText(bibref);
}
