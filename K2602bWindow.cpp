/*
MIT License

// Copyright (c) 2021 Gabriele Salvato

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
*/

#include "K2602bWindow.h"

#include <QApplication>


K2602BWindow::K2602BWindow(QString sK2602B_Address, QWidget *parent)
    : QWidget(parent)
    , sAddress(sK2602B_Address)
{
    QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));

    pTabWidget = new QTabWidget();
    pTabWidget->setDisabled(true);

    pK2602B = new k2602b(sAddress);
    if(pK2602B->Init()) {
        pTabWidget->setEnabled(true);
    }

    pChannelTab[0] = new ChannelTab(pK2602B->pChannel[0]);
    pChannelTab[1] = new ChannelTab(pK2602B->pChannel[1]);
    pStatusBar = new QStatusBar();

    restoreSettings();
    initLayout();

    updateUi();

    QApplication::restoreOverrideCursor();
}


K2602BWindow::~K2602BWindow() {
}


void
K2602BWindow::closeEvent(QCloseEvent*) {
    pK2602B->closeConnection();
}


void
K2602BWindow::saveSettings() {
}


void
K2602BWindow::restoreSettings() {
}


void
K2602BWindow::initLayout() {
    pTabWidget->addTab(pChannelTab[0], "Channel A");
    pTabWidget->addTab(pChannelTab[1], "Channel B");

    pMainLayout = new QVBoxLayout();
    pMainLayout->addWidget(pTabWidget);
    //pMainLayout->addWidget(&buttonBox);
    pMainLayout->addWidget(pStatusBar);

    setLayout(pMainLayout);
}


void
K2602BWindow::initMessages() {

}


void
K2602BWindow::updateUi() {
    for(int i=0; i<2; i++) {
        pChannelTab[i]->setOnOff_Ui(pK2602B->pChannel[i]->getOnOff());
        pChannelTab[i]->setSourceMode_Ui(pK2602B->pChannel[i]->getSourceV());
    }
}
