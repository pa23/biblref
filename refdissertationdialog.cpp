/*
    biblref
    Creation of bibliographic references.

    File: refdissertationdialog.cpp

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

#include "refdissertationdialog.h"
#include "ui_refdissertationdialog.h"

#include <QPlainTextEdit>
#include <QTextCursor>
#include <QString>
#include <QStringList>
#include <QMessageBox>

RefDissertationDialog::RefDissertationDialog(QPlainTextEdit *pte,
                                             QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RefDissertationDialog) {

    ui->setupUi(this);
    plainTextEdit = pte;
}

RefDissertationDialog::~RefDissertationDialog() {

    delete ui;
}

void RefDissertationDialog::on_pushButton_add_clicked() {

    if ( ui->lineEdit_author->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Диссертация"
                              "\" необходима информация об авторе.");
        return;
    }

    if ( ui->lineEdit_title->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Диссертация"
                              "\" необходимо указать тему работы.");
        return;
    }

    if ( ui->lineEdit_academicdeg->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Диссертация"
                              "\" необходимо указать ученую степень.");
        return;
    }

    if ( ui->lineEdit_speccode->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Диссертация"
                              "\" необходимо указать код специальности.");
        return;
    }

    if ( ui->lineEdit_city->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Диссертация"
                              "\" необходимо указать город.");
        return;
    }

    //

    QString bibref("");

    QStringList authName = ui->lineEdit_author->text().split(" ");

    bibref += authName[authName.count()-1] + ", ";

    for ( ptrdiff_t i=0; i<authName.count()-1; i++ ) {

        bibref += authName[i] + " ";
    }

    bibref += ui->lineEdit_title->text()
            + " : дис. ... "
            + ui->lineEdit_academicdeg->text()
            + ": "
            + ui->lineEdit_speccode->text()
            + ". ― "
            + ui->lineEdit_city->text()
            + ", "
            + QString::number(ui->spinBox_year->value())
            + ". ― "
            + QString::number(ui->spinBox_pages->value())
            + " с.";

    //

    plainTextEdit->moveCursor(QTextCursor::End);
    plainTextEdit->appendPlainText(bibref);
}
