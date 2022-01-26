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
#include <QGroupBox>


ChannelTab::ChannelTab(K2602B_Channel* pCh, QWidget *parent)
    : QWidget(parent)
    , pChannel(pCh)
{
    CreateUiElements();
    // Styles
    sNormalStyle = pMeasureNPLCEdit->styleSheet();
    sErrorStyle  = "QLineEdit { ";
    sErrorStyle += "color: rgb(255, 255, 255);";
    sErrorStyle += "background: rgb(255, 0, 0);";
    sErrorStyle += "selection-background-color: rgb(128, 128, 255);";
    sErrorStyle += "}";
    InitLayout();
    restoreSettings();
    InitSignals();
}


void
ChannelTab::closeEvent(QCloseEvent*event) {
    saveSettings();
    QWidget::closeEvent(event);
}


void
ChannelTab::CreateUiElements() {
    // Labels
    pSourceModeLabel         = new QLabel("Mode", this);
    pSourceRangeLabel        = new QLabel("Range", this);
    pSourceValueLabel        = new QLabel("Value", this);
    pSourceStartLabel        = new QLabel("Sweep Start", this);
    pSourceStopLabel         = new QLabel("Sweep Stop", this);
    pSourceNpointsLabel      = new QLabel("Sweep Points", this);
    pSourceSettlingTimeLabel = new QLabel("Settling Time [s]", this);
    pOnTimeLabel             = new QLabel("On Time [s]", this);
    pOffTimeLabel            = new QLabel("Off Time[s]", this);
    pBiasLabel               = new QLabel("Bias", this);
    pMeasureRangeLabel       = new QLabel("Range", this);
    pMeasureLimitLabel       = new QLabel("Limit", this);
    pMeasureNPLCLabel        = new QLabel("NPLC", this);
    pOnOffLabel              = new QLabel("Output", this);

    // ComboBoxes
    pSourceModeCombo   = new QComboBox(this);
    pSourceRangeCombo  = new QComboBox(this);
    pMeasureRangeCombo = new QComboBox(this);

    // LineEdits
    pSourceRangeEdit        = new QLineEdit("0.0", this);
    pSourceValueEdit        = new QLineEdit("0.0", this);
    pSourceStartEdit        = new QLineEdit("0.0", this);
    pSourceStopEdit         = new QLineEdit("1.0e-6", this);
    pSourceSettlingTimeEdit = new QLineEdit("0.1", this);
    pSourceNpointsEdit      = new QLineEdit("11", this);
    pMeasureRangeEdit       = new QLineEdit("0.0", this);
    pMeasureLimitEdit       = new QLineEdit("0.0", this);
    pMeasureNPLCEdit        = new QLineEdit("0", this);
    pOnTimeEdit             = new QLineEdit("0.1", this);
    pOffTimeEdit            = new QLineEdit("0.1", this);
    pBiasEdit               = new QLineEdit("0.1", this);

    // CheckBoxes
    pMeasureCurrent    = new QCheckBox("Current", this);
    pMeasureVoltage    = new QCheckBox("Voltage", this);
    pMeasureResistance = new QCheckBox("Resistance", this);
    pMeasurePower      = new QCheckBox("Power", this);
    pComplianceButton  = new QCheckBox("Compliance", this);
    pOnOffButton       = new QCheckBox("On/Off", this);

    // ComboBoxes Initialization
    pSourceModeCombo->addItems(QStringList(QList<QString> {
                                               "Source V",
                                               "Source I",
                                               "Dc Sweep V",
                                               "Dc Sweep I",
                                               "Plsd Sweep V",
                                               "Plsd Sweep I"}));
    pSourceRangeCombo->addItems(QStringList(QList<QString> {
                                                "AUTO",
                                                "MANUAL"}));
    pMeasureRangeCombo->addItems(QStringList(QList<QString> {
                                                 "AUTO",
                                                 "MANUAL"}));
    // Ui Elements Attributes
    pComplianceButton->setLayoutDirection(Qt::RightToLeft);
    pComplianceButton->setAttribute(Qt::WA_TransparentForMouseEvents);
    pComplianceButton->setFocusPolicy(Qt::NoFocus);
    //
    QList<QWidget*> widgetList = findChildren<QWidget*>();
    for(int i=0; i<widgetList.size(); i++) {
        widgetList.at(i)->setMaximumWidth(120);
    }
    QList<QLineEdit*> editList = findChildren<QLineEdit*>();
    for(int i=0; i<editList.size(); i++) {
        editList.at(i)->setAlignment(Qt::AlignRight);
    }
}


void
ChannelTab::InitLayout() {
    QVBoxLayout* pLayout  = new QVBoxLayout();
    QGridLayout* pLayout1 = new QGridLayout();
    QGridLayout* pLayout2 = new QGridLayout();
    QGridLayout* pLayout3 = new QGridLayout();

    QGroupBox* pSourceGroupBox = new QGroupBox(tr("Source"));
    // Source Ui Labels (pLayout1)
    pLayout1->addWidget(pSourceModeLabel,         0, 0, 1, 1, Qt::AlignCenter);
    pLayout1->addWidget(pSourceRangeLabel,        0, 1, 1, 2, Qt::AlignCenter);
    pLayout1->addWidget(pSourceValueLabel,        0, 3, 1, 1, Qt::AlignCenter);
    // Source Ui Elements
    pLayout1->addWidget(pSourceModeCombo,         1, 0, 1, 1);
    pLayout1->addWidget(pSourceRangeCombo,        1, 1, 1, 1);
    pLayout1->addWidget(pSourceRangeEdit,         1, 2, 1, 1);
    pLayout1->addWidget(pSourceValueEdit,         1, 3, 1, 1);
    // Sweep Ui Labels
    pLayout1->addWidget(pSourceStartLabel,        2, 0, 1, 1, Qt::AlignCenter);
    pLayout1->addWidget(pSourceStopLabel,         2, 1, 1, 1, Qt::AlignCenter);
    pLayout1->addWidget(pSourceSettlingTimeLabel, 2, 2, 1, 1, Qt::AlignCenter);
    pLayout1->addWidget(pSourceNpointsLabel,      2, 3, 1, 1, Qt::AlignCenter);
    // Sweep Ui Elements
    pLayout1->addWidget(pSourceStartEdit,         3, 0, 1, 1);
    pLayout1->addWidget(pSourceStopEdit,          3, 1, 1, 1);
    pLayout1->addWidget(pSourceSettlingTimeEdit,  3, 2, 1, 1);
    pLayout1->addWidget(pSourceNpointsEdit,       3, 3, 1, 1);
    pLayout1->addWidget(pOnTimeLabel,             4, 0, 1, 1, Qt::AlignCenter);
    pLayout1->addWidget(pOffTimeLabel,            4, 1, 1, 1, Qt::AlignCenter);
    pLayout1->addWidget(pBiasLabel,               4, 2, 1, 1, Qt::AlignCenter);
    pLayout1->addWidget(pOnTimeEdit,              5, 0, 1, 1);
    pLayout1->addWidget(pOffTimeEdit,             5, 1, 1, 1);
    pLayout1->addWidget(pBiasEdit,                5, 2, 1, 1);
    pSourceGroupBox->setLayout(pLayout1);

    QGroupBox* pMeasureGroupBox = new QGroupBox(tr("Measure"));
    // Measure Ui Labels (pLayout2)
    pLayout2->addWidget(pMeasureRangeLabel,  0, 1, 1, 2, Qt::AlignCenter);
    pLayout2->addWidget(pMeasureLimitLabel,  0, 3, 1, 1, Qt::AlignCenter);
    // Measure Ui Elements
    pLayout2->addWidget(pMeasureCurrent,     0, 0, 1, 1);
    pLayout2->addWidget(pMeasureVoltage,     1, 0, 1, 1);
    pLayout2->addWidget(pMeasureResistance,  2, 0, 1, 1);
    pLayout2->addWidget(pMeasurePower,       3, 0, 1, 1);
    pLayout2->addWidget(pMeasureRangeCombo,  1, 1, 1, 1);
    pLayout2->addWidget(pMeasureRangeEdit,   1, 2, 1, 1);
    pLayout2->addWidget(pMeasureLimitEdit,   1, 3, 1, 1);
    pLayout2->addWidget(pMeasureNPLCLabel,   4, 0, 1, 1, Qt::AlignRight);
    pLayout2->addWidget(pMeasureNPLCEdit,    4, 1, 1, 1);
    pMeasureGroupBox->setLayout(pLayout2);

    QGroupBox* pOtherGroupBox = new QGroupBox(tr(""));
    // Miscellaneous
    pLayout3->addWidget(pComplianceButton,   1, 0, 1, 1);
    pLayout3->addWidget(pOnOffLabel,         1, 2, 1, 1, Qt::AlignRight);
    pLayout3->addWidget(pOnOffButton,        1, 3, 1, 1);
    pOtherGroupBox->setLayout(pLayout3);

    // Layout
    pLayout->addSpacing(24);
    pLayout->addWidget(pSourceGroupBox);
    pLayout->addSpacing(24);
    pLayout->addWidget(pMeasureGroupBox);
    pLayout->addSpacing(24);
    pLayout->addWidget(pOtherGroupBox);
    setLayout(pLayout);
}


void
ChannelTab::UpdateSourceModeUi(K2602B_Channel::smuFunction mode) {
    switch (mode) {
        case K2602B_Channel::VOLTAGE : {
            pSourceStartLabel->hide();
            pSourceStopLabel->hide();
            pSourceSettlingTimeLabel->hide();
            pSourceNpointsLabel->hide();
            pSourceStartEdit->hide();
            pSourceStopEdit->hide();
            pSourceSettlingTimeEdit->hide();
            pSourceNpointsEdit->hide();
            pOnTimeLabel->hide();
            pOffTimeLabel->hide();
            pBiasLabel->hide();
            pOnTimeEdit->hide();
            pOffTimeEdit->hide();
            pBiasEdit->hide();
            break;
        }
    case K2602B_Channel::CURRENT : {
            pSourceStartLabel->hide();
            pSourceStopLabel->hide();
            pSourceSettlingTimeLabel->hide();
            pSourceNpointsLabel->hide();
            pSourceStartEdit->hide();
            pSourceStopEdit->hide();
            pSourceSettlingTimeEdit->hide();
            pSourceNpointsEdit->hide();
            pOnTimeLabel->hide();
            pOffTimeLabel->hide();
            pBiasLabel->hide();
            pOnTimeEdit->hide();
            pOffTimeEdit->hide();
            pBiasEdit->hide();
            break;
        }
    case K2602B_Channel::DC_SWEEP_V : {
            pSourceStartLabel->show();
            pSourceStopLabel->show();
            pSourceSettlingTimeLabel->show();
            pSourceNpointsLabel->show();
            pSourceStartEdit->show();
            pSourceStopEdit->show();
            pSourceSettlingTimeEdit->show();
            pSourceNpointsEdit->show();
            pOnTimeLabel->hide();
            pOffTimeLabel->hide();
            pBiasLabel->hide();
            pOnTimeEdit->hide();
            pOffTimeEdit->hide();
            pBiasEdit->hide();
            break;
        }
        case K2602B_Channel::DC_SWEEP_I: {
            pSourceStartLabel->show();
            pSourceStopLabel->show();
            pSourceSettlingTimeLabel->show();
            pSourceNpointsLabel->show();
            pSourceStartEdit->show();
            pSourceStopEdit->show();
            pSourceSettlingTimeEdit->show();
            pSourceNpointsEdit->show();
            pOnTimeLabel->hide();
            pOffTimeLabel->hide();
            pBiasLabel->hide();
            pOnTimeEdit->hide();
            pOffTimeEdit->hide();
            pBiasEdit->hide();
            break;
        }
        case K2602B_Channel::PLSD_SWEEP_V : {
            pSourceStartLabel->show();
            pSourceStopLabel->show();
            pSourceSettlingTimeLabel->show();
            pSourceNpointsLabel->show();
            pSourceStartEdit->show();
            pSourceStopEdit->show();
            pSourceSettlingTimeEdit->show();
            pSourceNpointsEdit->show();
            pOnTimeLabel->show();
            pOffTimeLabel->show();
            pBiasLabel->show();
            pOnTimeEdit->show();
            pOffTimeEdit->show();
            pBiasEdit->show();
            break;
        }
        case K2602B_Channel::PLSD_SWEEP_I : {
            pSourceStartLabel->show();
            pSourceStopLabel->show();
            pSourceSettlingTimeLabel->show();
            pSourceNpointsLabel->show();
            pSourceStartEdit->show();
            pSourceStopEdit->show();
            pSourceSettlingTimeEdit->show();
            pSourceNpointsEdit->show();
            pOnTimeLabel->show();
            pOffTimeLabel->show();
            pBiasLabel->show();
            pOnTimeEdit->show();
            pOffTimeEdit->show();
            pBiasEdit->show();
            break;
        }

    }

}


void
ChannelTab::saveSettings() {
}


void
ChannelTab::restoreSettings() {
}


void
ChannelTab::InitSignals() {
    connect(pSourceModeCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onSourceModeChangedUi(int)));
    connect(pSourceRangeCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onSourceRangeChangedUi(int)));
    connect(pMeasureRangeCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onMeasureRangeChangedUi(int)));

    connect(pOnOffButton, SIGNAL(stateChanged(int)),
            this, SLOT(onOnOffChangedUi(int)));

    connect(pSourceRangeEdit, SIGNAL(editingFinished()),
            this, SLOT(onSourceRangeEditingFinished()));
    connect(pSourceValueEdit, SIGNAL(editingFinished()),
            this, SLOT(onSourceValueEditingFinished()));
    connect(pMeasureRangeEdit, SIGNAL(editingFinished()),
            this, SLOT(onMeasureRangeEditingFinished()));
    connect(pMeasureLimitEdit, SIGNAL(editingFinished()),
            this, SLOT(onMeasureLimitEditingFinished()));

    connect(pMeasureNPLCEdit, SIGNAL(textChanged(QString)),
            this, SLOT(onNPLCEditTextChanged(QString)));
    connect(pMeasureNPLCEdit, SIGNAL(editingFinished()),
            this, SLOT(onNPLCEditingFinished()));
}


void
ChannelTab::onNPLCEditTextChanged(const QString &arg1) {
    double value = arg1.toDouble();
    if((value < 0.001) || (value > 25.0)) {
        pMeasureNPLCEdit->setStyleSheet(sErrorStyle);
    }
    else {
        pMeasureNPLCEdit->setStyleSheet(sNormalStyle);
    }
}


void
ChannelTab::onNPLCEditingFinished() {
    double dValue = pMeasureNPLCEdit->text().toDouble();
    pChannel->setNPLC(dValue);
    pMeasureNPLCEdit->setText(QString("%1").arg(pChannel->getNPLC()));
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName()
             << "NPLC"
             << dValue;
#endif
}


void
ChannelTab::onSourceModeChangedUi(int selectedItem) {
    bool bResult = false;
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName()
             << pSourceModeCombo->itemText(selectedItem);
#endif
    QString sValue = pSourceModeCombo->itemText(selectedItem);
    if(sValue == QString("Source V")) {
        bResult = pChannel->setSourceFunction(K2602B_Channel::VOLTAGE);
        UpdateSourceModeUi(K2602B_Channel::VOLTAGE);
    }
    else if(sValue == QString("Source I")) {
        bResult = pChannel->setSourceFunction(K2602B_Channel::CURRENT);
        UpdateSourceModeUi(K2602B_Channel::CURRENT);
    }
    else if(sValue == QString("Dc Sweep V")) {
        bResult = pChannel->setSourceFunction(K2602B_Channel::DC_SWEEP_V);
        UpdateSourceModeUi(K2602B_Channel::DC_SWEEP_V);
    }
    else if(sValue == QString("Dc Sweep I")) {
        bResult = pChannel->setSourceFunction(K2602B_Channel::DC_SWEEP_I);
        UpdateSourceModeUi(K2602B_Channel::DC_SWEEP_I);
    }
    else if(sValue == QString("Plsd Sweep V")) {
        bResult = pChannel->setSourceFunction(K2602B_Channel::PLSD_SWEEP_V);
        UpdateSourceModeUi(K2602B_Channel::PLSD_SWEEP_V);
    }
    else if(sValue == QString("Plsd Sweep I")) {
        bResult = pChannel->setSourceFunction(K2602B_Channel::PLSD_SWEEP_I);
        UpdateSourceModeUi(K2602B_Channel::PLSD_SWEEP_I);
    }

    (void)bResult;
}


void
ChannelTab::onMeasureRangeChangedUi(int selectedItem) {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName()
             << pMeasureRangeCombo->itemText(selectedItem);
#endif
    QString sValue = pMeasureRangeCombo->itemText(selectedItem);
    if(sValue == "AUTO") {
        pMeasureRangeEdit->setDisabled(true);
    }
    else { // MANUAL
        pMeasureRangeEdit->setEnabled(true);
        onMeasureRangeEditingFinished();
    }
}


void
ChannelTab::onSourceRangeChangedUi(int selectedItem) {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName()
             << pSourceRangeCombo->itemText(selectedItem);
#endif
    QString sValue = pSourceRangeCombo->itemText(selectedItem);
    if(sValue == "AUTO") {
        pSourceRangeEdit->setDisabled(true);
    }
    else { // MANUAL
        pSourceRangeEdit->setEnabled(true);
        onSourceRangeEditingFinished();
    }
}


void
ChannelTab::onOnOffChangedUi(int) {
    pChannel->setOnOff(pOnOffButton->isChecked());
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName()
             << (pOnOffButton->isChecked() ? "On" : "Off");
#endif
}


void
ChannelTab::setSourceMode_Ui(bool bSourceV) {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName();
#endif
    if(bSourceV) {
        pSourceModeCombo->setCurrentIndex(1);
    }
    else {
        pSourceModeCombo->setCurrentIndex(0);
    }
}


void
ChannelTab::setSourceValue_Ui(double dValue) {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName();
#endif
    pSourceValueEdit->setText(QString("%1").arg(dValue));
}


void
ChannelTab::setSourceRange_Ui(double dValue) {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName();
#endif
    pSourceRangeEdit->setText(QString("%1").arg(dValue));
}


void
ChannelTab::setMeasureRange_Ui(double dValue) {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName();
#endif
    pMeasureRangeEdit->setText(QString("%1").arg(dValue));
}


void
ChannelTab::setLimit_Ui(double dValue) {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName();
#endif
    pMeasureLimitEdit->setText(QString("%1").arg(dValue));
}


void
ChannelTab::onSourceValueEditingFinished() {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName();
#endif
    double dValue = pSourceValueEdit->text().toDouble();
    pChannel->setSourceValue(dValue);
    pSourceValueEdit->setText(QString("%1").arg(pChannel->getSourceValue()));
}


void
ChannelTab::onSourceRangeEditingFinished() {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName();
#endif
    double dValue = pSourceRangeEdit->text().toDouble();
    pChannel->setSourceRange(dValue);
    pSourceRangeEdit->setText(QString("%1").arg(pChannel->getSourceRange()));
}


void
ChannelTab::onMeasureRangeEditingFinished() {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName();
#endif
    double dValue = pMeasureRangeEdit->text().toDouble();
    pChannel->setMeasureRange(dValue);
    pMeasureRangeEdit->setText(QString("%1").arg(pChannel->getSourceRange()));
}


void
ChannelTab::onMeasureLimitEditingFinished() {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName();
#endif
    double dValue = pMeasureLimitEdit->text().toDouble();
    pChannel->setLimit(dValue);
    pMeasureLimitEdit->setText(QString("%1").arg(pChannel->getLimit()));
}


void
ChannelTab::setOnOff_Ui(bool bOn) {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName()
             << bOn;
#endif
    pOnOffButton->setChecked(bOn);
}


void
ChannelTab::setNPLC_Ui(double nplc) {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName()
             << nplc;
#endif
    pMeasureNPLCEdit->setText(QString("%1").arg(nplc));
}
