/* MIT License

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

    pReadingTimer = new QTimer();
    connect(pReadingTimer, SIGNAL(timeout()),
            this, SLOT(onTimeToGetMeasurement()));
    pReadingTimer->start(1000);

    QApplication::restoreOverrideCursor();
}


K2602BWindow::~K2602BWindow() {
}


void
K2602BWindow::closeEvent(QCloseEvent*) {
    for(int i=0; i<2; i++) {
        pK2602B->pChannel[i]->setOnOff(false);
        pK2602B->pChannel[i]->abort();
    }
    pK2602B->gotoLocal(); // <--- Not working...
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
//#ifndef QT_NO_DEBUG
//    qDebug() << __FILE__
//             << "Line:"
//             << __LINE__
//             << __FUNCTION__;
//#endif
    for(int i=0; i<2; i++) {
        pChannelTab[i]->setOnOff_Ui(pK2602B->pChannel[i]->isOn());
        pChannelTab[i]->setSourceMode_Ui(pK2602B->pChannel[i]->isSourceV());
        pChannelTab[i]->setSourceValue_Ui(pK2602B->pChannel[i]->getSourceValue());
        pChannelTab[i]->setSourceRange_Ui(pK2602B->pChannel[i]->getSourceRange());
        pChannelTab[i]->setMeasureRange_Ui(pK2602B->pChannel[i]->getMeasureRange());
        pChannelTab[i]->setLimit_Ui(pK2602B->pChannel[i]->getLimit());
        pChannelTab[i]->setNPLC_Ui(pK2602B->pChannel[i]->getNPLC());
    }
}


void
K2602BWindow::onTimeToGetMeasurement() {
    QString sReadings = QString();
    for(int i=0; i<2; i++) {
        if(pK2602B->pChannel[i]->isOn()) {
            sReadings += QString("Channel %1: %2 ")
                           .arg(pK2602B->pChannel[i]->getName())
                           .arg(pK2602B->pChannel[i]->getSingleMeasure());
        }
    }
    pStatusBar->showMessage(sReadings);
}
