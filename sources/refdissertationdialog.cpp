/*
    biblref
    Creation of bibliographic references.

    File: refdissertationdialog.cpp

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

    if ( ui->lineEdit_author->text().isEmpty() ||
         ui->lineEdit_title->text().isEmpty() ||
         ui->lineEdit_academicdeg->text().isEmpty() ||
         ui->lineEdit_city->text().isEmpty() ) {

        QMessageBox::warning(
                    this, "biblref",
                    "Для формирования ссылки типа \"Диссертация / Автореферат\" необходимы следующие данные: "
                    "информация об авторе, тема работы, ученая степень, город.\n\n"
                    "Так как вы выполнили не все требования, ссылка будет неполноценной."
                    );
    }

    //

    QString bibref("");

    QStringList authName = ui->lineEdit_author->text().split(" ");

    if ( !authName.isEmpty() ) {
        
        bibref += authName[authName.count()-1] + ", ";

        for ( ptrdiff_t i=0; i<authName.count()-1; i++ ) {
            bibref += authName[i] + " ";
        }
    }

    bibref += ui->lineEdit_title->text();

    if ( ui->checkBox_authabstract->isChecked() ) {
        bibref += " : автореферат дис. ... ";
    }
    else {
        bibref += " : дис. ... ";
    }

    bibref += ui->lineEdit_academicdeg->text();

    if ( !ui->lineEdit_speccode->text().isEmpty() ) {
        bibref += ": "
                + ui->lineEdit_speccode->text();
    }

    bibref += ". ― "
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
