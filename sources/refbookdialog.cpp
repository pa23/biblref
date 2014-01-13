/*
    biblref
    Creation of bibliographic references.

    File: refbookdialog.cpp

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

#include "refbookdialog.h"
#include "ui_refbookdialog.h"

#include <QPlainTextEdit>
#include <QTextCursor>
#include <QString>
#include <QStringList>
#include <QMessageBox>

RefBookDialog::RefBookDialog(QPlainTextEdit *pte, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RefBookDialog) {

    ui->setupUi(this);
    plainTextEdit = pte;
}

RefBookDialog::~RefBookDialog() {

    delete ui;
}

void RefBookDialog::on_pushButton_add_clicked() {

    QStringList authors = ui->lineEdit_authors->
            text().split(";", QString::SkipEmptyParts);

    if ( ui->lineEdit_authors->text().isEmpty() ||
         authors.isEmpty() ||
         ui->lineEdit_title->text().isEmpty() ||
         ui->lineEdit_city->text().isEmpty() ||
         ui->lineEdit_publish->text().isEmpty() ||
         ((ui->lineEdit_language->text().isEmpty() && !ui->lineEdit_translators->text().isEmpty()) ||
          (!ui->lineEdit_language->text().isEmpty() && ui->lineEdit_translators->text().isEmpty())) ||
         (ui->spinBox_publication->value() == 0 && !ui->lineEdit_comment->text().isEmpty()) ) {

        QMessageBox::warning(
                    this, "biblref",
                    "Для формирования ссылки типа \"Книга\" необходимы следующие данные: "
                    "информация об авторах, название, город, издательство; если издание переводное, "
                    "то необходимо указывать и язык оригинала, и редакторов перевода; если указывается "
                    "комментарий к изданию, то также необходимо указать и номер издания.\n\n"
                    "Так как вы выполнили не все требования, ссылка будет неполноценной."
                    );
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

    bibref += ui->lineEdit_title->text() + " / ";

    for ( ptrdiff_t i=0; i<authors.count(); i++ ) {

        bibref += authors[i] + ", ";
    }

    bibref.chop(2);

    if ( !ui->lineEdit_language->text().isEmpty()
         && !ui->lineEdit_translators->text().isEmpty() ) {

        bibref += " ; пер. с "
                + ui->lineEdit_language->text()
                + " под ред. ";

        QStringList translators = ui->lineEdit_translators->
                text().split(";", QString::SkipEmptyParts);

        for ( ptrdiff_t i=0; i<translators.count(); i++ ) {

            bibref += translators[i].trimmed() + ", ";
        }

        bibref.chop(2);
    }

    bibref += ".";

    if ( ui->spinBox_publication->value() != 0 ) {

        bibref += " ― "
                + QString::number(ui->spinBox_publication->value())
                + "-е изд.";
    }

    if ( !ui->lineEdit_comment->text().isEmpty() ) {

        bibref += ", " + ui->lineEdit_comment->text();
    }

    bibref += " ― "
            + ui->lineEdit_city->text()
            + ": "
            + ui->lineEdit_publish->text()
            + ", "
            + QString::number(ui->spinBox_year->value())
            + ". ― ";

    if ( ui->spinBox_volume->value() != 0 ) {

        bibref += "Т. "
                + QString::number(ui->spinBox_volume->value())
                + ". ― ";
    }

    bibref += QString::number(ui->spinBox_pages->value()) + " с.";

    if ( !ui->lineEdit_isbn->text().isEmpty() ) {

        bibref += " ― ISBN " + ui->lineEdit_isbn->text() + ".";
    }

    //

    plainTextEdit->moveCursor(QTextCursor::End);
    plainTextEdit->appendPlainText(bibref);
}
