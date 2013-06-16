/*
    biblref
    Creation of bibliographic references.

    File: refdeposmanuscriptdialog.cpp

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

#include "refdeposmanuscriptdialog.h"
#include "ui_refdeposmanuscriptdialog.h"

#include <QPlainTextEdit>
#include <QTextCursor>
#include <QString>
#include <QStringList>
#include <QMessageBox>

RefDeposManuscriptDialog::RefDeposManuscriptDialog(QPlainTextEdit *pte,
                                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RefDeposManuscriptDialog) {

    ui->setupUi(this);
    plainTextEdit = pte;
}

RefDeposManuscriptDialog::~RefDeposManuscriptDialog() {

    delete ui;
}

void RefDeposManuscriptDialog::on_pushButton_add_clicked() {

    QStringList authors = ui->lineEdit_authors->
            text().split(";", QString::SkipEmptyParts);

    if ( ui->lineEdit_authors->text().isEmpty() || authors.isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Депонированная рукопись"
                              "\" необходима информация об авторах.");
        return;
    }

    if ( ui->lineEdit_title->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Депонированная рукопись"
                              "\" необходима информация о названии.");
        return;
    }

    if ( ui->lineEdit_organization_1->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Депонированная рукопись"
                              "\" необходима информация об организации.");
        return;
    }

    if ( ui->lineEdit_city->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Депонированная рукопись"
                              "\" необходимо указать город.");
        return;
    }

    if ( ui->lineEdit_organization_2->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Депонированная рукопись"
                              "\" необходима информация о принимающей "
                              "организации.");
        return;
    }

    if ( ui->lineEdit_regnumber->text().isEmpty() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Для ссылки типа \"Депонированная рукопись"
                              "\" необходимо указать регистрационный номер.");
        return;
    }

    //

    QString bibref("");

    for ( ptrdiff_t i=0; i<authors.count(); i++ ) {

        authors[i] = authors[i].trimmed();
    }

    QStringList firstAuthName = authors[0].split(" ");

    bibref += firstAuthName[firstAuthName.count()-1] + ", ";

    for ( ptrdiff_t i=0; i<firstAuthName.count()-1; i++ ) {

        bibref += firstAuthName[i] + " ";
    }

    bibref += ui->lineEdit_title->text() + " / ";

    for ( ptrdiff_t i=0; i<authors.count(); i++ ) {

        bibref += authors[i] + ", ";
    }

    bibref.chop(2);

    bibref += " ; "
            + ui->lineEdit_organization_1->text()
            + ". ― "
            + ui->lineEdit_city->text()
            + ", "
            + QString::number(ui->spinBox_year->value())
            + ". ― "
            + QString::number(ui->spinBox_pages->value())
            + " с. ― Деп. в "
            + ui->lineEdit_organization_2->text()
            + " "
            + ui->dateEdit->text()
            + ", № "
            + ui->lineEdit_regnumber->text()
            + ".";

    //

    plainTextEdit->moveCursor(QTextCursor::End);
    plainTextEdit->appendPlainText(bibref);
}
