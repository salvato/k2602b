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

#include "channeltab.h"

#include <QGridLayout>


ChannelTab::ChannelTab(K2602B_Channel* pCh, QWidget *parent)
    : QWidget{parent}
    , pChannel(pCh)
{
    pSourceMode = new QComboBox();
    pSourceMode->addItems(QStringList(QList<QString>{"Source I",
                                                     "Source V"}));
    pSourceRangeLabel  = new QLabel("Range");
    pSourceRangeLabel->setMaximumWidth(120);
    pSourceRangeCombo  = new QComboBox();
    pSourceRangeCombo->addItems(QStringList(QList<QString>{"AUTO", "MANUAL"}));
    pSourceRangeCombo->setMaximumWidth(120);
    pSourceRangeEdit = new QLineEdit("0.0");
    pSourceRangeEdit->setAlignment(Qt::AlignRight);
    pSourceRangeEdit->setMaximumWidth(120);

    pSourceValueLabel = new QLabel("Value");
    pSourceValueLabel->setMaximumWidth(120);
    pSourceValueEdit = new QLineEdit("0.0");
    pSourceValueEdit->setMaximumWidth(120);
    pSourceValueEdit->setAlignment(Qt::AlignRight);

    pMeasureMode = new QComboBox();
    pMeasureMode->addItems(QStringList(QList<QString>{"Measure I",
                                                      "Measure V"}));
    pMeasureRangeLabel  = new QLabel("Range");
    pMeasureRangeLabel->setMaximumWidth(120);
    pMeasureRangeCombo  = new QComboBox();
    pMeasureRangeCombo->addItems(QStringList(QList<QString>{"AUTO", "MANUAL"}));
    pMeasureRangeCombo->setMaximumWidth(120);
    pMeasureRangeEdit = new QLineEdit("0.0");
    pMeasureRangeEdit->setAlignment(Qt::AlignRight);
    pMeasureRangeEdit->setMaximumWidth(120);

    pMeasureValueLabel = new QLabel("Value");
    pMeasureValueLabel->setMaximumWidth(120);
    pMeasureValueEdit = new QLineEdit("---");
    pMeasureValueEdit->setMaximumWidth(120);
    pMeasureValueEdit->setAlignment(Qt::AlignRight);
    pMeasureValueEdit->setReadOnly(true);


    pOnOffLabel = new QLabel("Output");
    pOnOffLabel->setMaximumWidth(120);
    pOnOffButton = new QCheckBox("On/Off");

    QGridLayout* pLayout = new QGridLayout();

    pLayout->addWidget(pSourceMode,         0, 0, 1, 1);
    pLayout->addWidget(pSourceRangeLabel,   0, 1, 1, 1, Qt::AlignRight);
    pLayout->addWidget(pSourceRangeCombo,   0, 2, 1, 1);
    pLayout->addWidget(pSourceRangeEdit,    0, 3, 1, 1);
    pLayout->addWidget(pSourceValueLabel,   0, 4, 1, 1, Qt::AlignRight);
    pLayout->addWidget(pSourceValueEdit,    0, 5, 1, 1);

    pLayout->addWidget(pMeasureMode,        1, 0, 1, 1);
    pLayout->addWidget(pMeasureRangeLabel,  1, 1, 1, 1, Qt::AlignRight);
    pLayout->addWidget(pMeasureRangeCombo,  1, 2, 1, 1);
    pLayout->addWidget(pMeasureRangeEdit,   1, 3, 1, 1);
    pLayout->addWidget(pMeasureValueLabel,  1, 4, 1, 1, Qt::AlignRight);
    pLayout->addWidget(pMeasureValueEdit,   1, 5, 1, 1);

    pLayout->addWidget(pOnOffLabel,         2, 0, 1, 1, Qt::AlignRight);
    pLayout->addWidget(pOnOffButton,        2, 1, 1, 1);

    setLayout(pLayout);

    InitSignals();

    onSourceRangeChangedUi(0);
    onSourceModeChangedUi(0);

    restoreSettings();
}


void
ChannelTab::saveSettings() {
}


void
ChannelTab::restoreSettings() {
}


void
ChannelTab::InitSignals() {
    connect(pSourceMode, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onSourceModeChangedUi(int)));
    connect(pMeasureMode, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onMeasureModeChangedUi(int)));
    connect(pSourceRangeCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onSourceRangeChangedUi(int)));
    connect(pOnOffButton, SIGNAL(stateChanged(int)),
            this, SLOT(onOnOffChangedUi(int)));
}


void
ChannelTab::onSourceRangeChangedUi(int selectedItem) {
    QString sValue = pSourceRangeCombo->itemText(selectedItem);
    if(sValue == "AUTO") {
        pSourceRangeEdit->setDisabled(true);
    }
    else { // MANUAL
        pSourceRangeEdit->setEnabled(true);
    }
}


void
ChannelTab::onSourceModeChangedUi(int selectedItem) {
    pMeasureMode->setCurrentIndex(1-selectedItem);
    QString sValue = pSourceMode->itemText(selectedItem);
    if(sValue.contains("I")) {
    }
    else { // Measure
    }
}


void
ChannelTab::onMeasureModeChangedUi(int selectedItem) {
    pSourceMode->setCurrentIndex(1-selectedItem);
    QString sValue = pMeasureMode->itemText(selectedItem);
    if(sValue.contains("I")) {
    }
    else { // Measure
    }
}


void
ChannelTab::onOnOffChangedUi(int) {
    pChannel->setOnOff(pOnOffButton->isChecked());
    bool bResult = pChannel ->getOnOff();
    pOnOffButton->setChecked(bResult);
//    qDebug() << __FILE__ << "Line:" <<__LINE__ << bResult;
}
