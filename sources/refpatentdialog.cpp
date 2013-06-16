/*
    biblref
    Creation of bibliographic references.

    File: refpatentdialog.cpp

    Copyright (C) 2012-2013 Artem Petrov <pa2311@gmail.com>

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

#include "refpatentdialog.h"
#include "ui_refpatentdialog.h"

#include <QPlainTextEdit>
#include <QTextCursor>
#include <QString>
#include <QStringList>
#include <QMessageBox>

RefPatentDialog::RefPatentDialog(QPlainTextEdit *pte, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RefPatentDialog) {

    ui->setupUi(this);
    plainTextEdit = pte;
}

RefPatentDialog::~RefPatentDialog() {

    delete ui;
}

void RefPatentDialog::on_pushButton_add_clicked() {

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

    if ( ui->comboBox_doctype->currentIndex() == PATENT ) {

        bibref += "Пат. ";
    }
    else if ( ui->comboBox_doctype->currentIndex() == PROFMODEL ) {

        bibref += "П. м. ";
    }

    bibref += QString::number(ui->spinBox_docnumber->value())
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

    bibref += ". ― Опубл. "
            + ui->dateEdit->text()
            + ", Бюл. № "
            + QString::number(ui->spinBox_bullnumber->value())
            + ".";

    //

    plainTextEdit->moveCursor(QTextCursor::End);
    plainTextEdit->appendPlainText(bibref);
}
