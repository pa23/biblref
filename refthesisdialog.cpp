/*
    biblref
    Creation of bibliographic references.

    File: refthesisdialog.cpp

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

#include "refthesisdialog.h"
#include "ui_refthesisdialog.h"

#include <QPlainTextEdit>
#include <QTextCursor>
#include <QString>
#include <QStringList>
#include <QMessageBox>

RefThesisDialog::RefThesisDialog(QPlainTextEdit *pte, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RefThesisDialog) {

    ui->setupUi(this);
    plainTextEdit = pte;
}

RefThesisDialog::~RefThesisDialog() {

    delete ui;
}

void RefThesisDialog::on_pushButton_add_clicked() {

    QStringList authors = ui->lineEdit_authors->
            text().split(";", QString::SkipEmptyParts);

    if ( ui->lineEdit_authors->text().isEmpty() || authors.isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Тезис доклада"
                              "\" необходима информация об авторах.");
        return;
    }

    if ( ui->lineEdit_reportsubj->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Тезис доклада"
                              "\" необходимо указать тему доклада.");
        return;
    }

    if ( ui->lineEdit_conference->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Тезис доклада"
                              "\" необходима информация о конференции.");
        return;
    }

    if ( ui->lineEdit_city->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Тезис доклада"
                              "\" необходима информация о городе.");
        return;
    }

    //

    QString bibref("");

    for ( ptrdiff_t i=0; i<authors.count(); i++ ) {

        authors[i] = authors[i].trimmed();
    }

    if ( authors.count() < 4 ) {

        QStringList firstAuthName = authors[0].split(" ");

        bibref += firstAuthName[firstAuthName.count()-1] + ", ";

        for ( ptrdiff_t i=0; i<firstAuthName.count()-1; i++ ) {

            bibref += firstAuthName[i] + " ";
        }
    }

    bibref += ui->lineEdit_reportsubj->text() + " / ";

    for ( ptrdiff_t i=0; i<authors.count(); i++ ) {

        bibref += authors[i] + ", ";
    }

    bibref.chop(2);

    bibref += " // "
            + ui->lineEdit_conference->text()
            + " : тез. докл. ";

    if ( !ui->lineEdit_thesrepors->text().isEmpty() ) {

        bibref += ui->lineEdit_thesrepors->text()
                + " ";
    }

    bibref += "― ";

    if ( ui->spinBox_volume->value() != 0 &&
         ui->spinBox_part->value() != 0) {

        bibref += "Т. "
                + QString::number(ui->spinBox_volume->value())
                + ", ч. "
                + QString::number(ui->spinBox_part->value())
                + ". ― ";
    }

    bibref += ui->lineEdit_city->text()
            + ", "
            + QString::number(ui->spinBox_year->value())
            + ". ― C. ";

    if ( ui->spinBox_startpage->value() == ui->spinBox_endpage->value() ) {

        bibref += QString::number(ui->spinBox_startpage->value())
                + ".";
    }
    else {

        bibref += QString::number(ui->spinBox_startpage->value())
                + "―"
                + QString::number(ui->spinBox_endpage->value())
                + ".";
    }

    //

    plainTextEdit->moveCursor(QTextCursor::End);
    plainTextEdit->appendPlainText(bibref);
}
