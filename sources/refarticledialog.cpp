/*
    biblref
    Creation of bibliographic references.

    File: refarticledialog.cpp

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

#include "refarticledialog.h"
#include "ui_refarticledialog.h"

#include <QPlainTextEdit>
#include <QTextCursor>
#include <QString>
#include <QStringList>
#include <QMessageBox>

RefArticleDialog::RefArticleDialog(QPlainTextEdit *pte, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RefArticleDialog) {

    ui->setupUi(this);
    plainTextEdit = pte;
}

RefArticleDialog::~RefArticleDialog() {
    delete ui;
}

void RefArticleDialog::on_pushButton_add_clicked() {

    if ( ui->lineEdit_authors->text().isEmpty() ||
         ui->lineEdit_arttitle->text().isEmpty() ||
         ui->lineEdit_pubtitle->text().isEmpty() ||
         ui->spinBox_startpage->value() > ui->spinBox_endpage->value() ) {

        QMessageBox::warning(
                    this, "biblref",
                    "Для формирования ссылки типа \"Статья\" необходимы следующие данные: "
                    "информация об авторах, названия статьи и журнала, правильно выставленные номера страниц.\n\n"
                    "Так как вы выполнили не все требования, ссылка будет неполноценной."
                    );
    }

    //

    QString bibref("");

    QStringList authors = ui->lineEdit_authors->text().split(";", QString::SkipEmptyParts);

    if ( !authors.isEmpty() ) {

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
    }

    bibref += ui->lineEdit_arttitle->text() + " / ";

    if ( !authors.isEmpty() ) {

        for ( ptrdiff_t i=0; i<authors.count(); i++ ) {
            bibref += authors[i] + ", ";
        }
    }

    bibref.chop(2);

    bibref += " // "
            + ui->lineEdit_pubtitle->text()
            + ". ― "
            + QString::number(ui->spinBox_year->value())
            + ". ― ";

    if ( ui->spinBox_volume->value() != 0 ) {
        bibref += "Т. "
                + QString::number(ui->spinBox_volume->value())
                + ", ";
    }

    bibref += "№ "
            + QString::number(ui->spinBox_publication->value())
            + ". ― С. ";

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
