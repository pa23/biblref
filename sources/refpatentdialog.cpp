/*
    biblref
    Creation of bibliographic references.

    File: refpatentdialog.cpp

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

    if ( ui->lineEdit_authors->text().isEmpty() ||
         authors.isEmpty() ||
         ui->lineEdit_country->text().isEmpty() ||
         ui->lineEdit_classification->text().isEmpty() ||
         ui->lineEdit_title->text().isEmpty() ) {

        QMessageBox::warning(
                    this, "biblref",
                    "Для формирования ссылки типа \"Патент / Полезная модель\" необходимы следующие данные: "
                    "информация об авторах, страна, информация о классификации документа, название.\n\n"
                    "Так как вы выполнили не все требования, ссылка будет неполноценной."
                    );
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
