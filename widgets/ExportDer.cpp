/*
 * Copyright (C) 2001 Christian Hohnstaedt.
 *
 *  All rights reserved.
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  - Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * This program links to software with different licenses from:
 *
 *	http://www.openssl.org which includes cryptographic software
 *	written by Eric Young (eay@cryptsoft.com)"
 *
 *	http://www.trolltech.com
 *
 *
 *
 * http://www.hohnstaedt.de/xca
 * email: christian@hohnstaedt.de
 *
 * $Id$
 *
 */


#include "ExportDer.h"
#include "lib/base.h"

#include <Qt/qcombobox.h>
#include <Qt/qlineedit.h>
#include <Qt/qfiledialog.h>

ExportDer::ExportDer(QWidget *parent, QString fname, QString dpath,
		QString _filter)
	:QDialog(parent)
{
	setupUi(this);
	filename->setText(fname);
	setWindowTitle(tr(XCA_TITLE));
	QStringList sl;
	sl << "PEM" << "DER";

	exportFormat->addItems(sl);
	dirPath = dpath;
	filter = _filter;
}

void ExportDer::on_fileBut_clicked()
{
	QStringList filt;
	filt.append(filter);
	filt.append(tr("All Files ( *.* )"));
	QString s = "", fn;
	QFileDialog *dlg = new QFileDialog(this);
	dlg->setWindowTitle(tr("Save as"));
	dlg->setFilters(filt);
	dlg->setFileMode( QFileDialog::AnyFile );
	fn = filename->text();
	fn = fn.mid(fn.lastIndexOf(QDir::separator()) +1, -1);
	dlg->selectFile( fn );
	dlg->setDirectory(dirPath);
	if (dlg->exec())
		if (!dlg->selectedFiles().isEmpty())
			s = dlg->selectedFiles()[0];
	if (! s.isEmpty()) {
		QDir::convertSeparators(s);
		filename->setText(s);
	}
	dirPath = dlg->directory().path();
	on_exportFormat_activated(0);
	delete dlg;
}

void ExportDer::on_exportFormat_activated(int)
{
	char *suffix[] = { "pem", "der" };
	int selected = exportFormat->currentIndex();
	QString fn = filename->text();
	QString nfn = fn.left(fn.lastIndexOf('.')+1) + suffix[selected];
	filename->setText(nfn);
}
