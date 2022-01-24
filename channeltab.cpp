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
    : QWidget(parent)
    , pChannel(pCh)
{
    CreateUiElements();
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
    pSourceModeLabel   = new QLabel("Source Mode");
    pSourceRangeLabel  = new QLabel("Source Range");
    pSourceValueLabel  = new QLabel("Source Value");

    pSourceStartLabel        = new QLabel("Sweep Start");
    pSourceStopLabel         = new QLabel("Sweep Stop");
    pSourceSettlingTimeLabel = new QLabel("Settling Time [s]");
    pSourceNpointsLabel      = new QLabel("Sweep Points");

    pMeasureModeLabel  = new QLabel("Measure Mode");
    pMeasureRangeLabel = new QLabel("Measure Range");
    pMeasureLimitLabel = new QLabel("Measure Limit");
    pMeasureNPLCLabel  = new QLabel("NPLC");
    pOnOffLabel        = new QLabel("Output");
    // ComboBoxes
    pSourceModeCombo   = new QComboBox();
    pSourceRangeCombo  = new QComboBox();
    pMeasureModeCombo  = new QComboBox();
    pMeasureRangeCombo = new QComboBox();
    // LineEdits
    pSourceRangeEdit        = new QLineEdit("0.0");
    pSourceValueEdit        = new QLineEdit("0.0");
    pSourceStartEdit        = new QLineEdit("0.0");
    pSourceStopEdit         = new QLineEdit("1.0e-6");
    pSourceSettlingTimeEdit = new QLineEdit("0.1");
    pSourceNpointsEdit      = new QLineEdit("11");
    pMeasureRangeEdit       = new QLineEdit("0.0");
    pMeasureLimitEdit       = new QLineEdit("0.0");
    pMeasureNPLCEdit        = new QLineEdit("0");
    // CheckBoxes
    pComplianceButton  = new QCheckBox("Compliance");
    pOnOffButton       = new QCheckBox("On/Off");
    // ComboBoxes Initialization
    pSourceModeCombo->addItems(QStringList(QList<QString>{
                                               "Source V",
                                               "Source I",
                                               "Dc Sweep V",
                                               "Dc Sweep I",
                                               "Plsd Sweep V",
                                               "Plsd Sweep I"}));
    pSourceRangeCombo->addItems(QStringList(QList<QString>{
                                                "AUTO",
                                                "MANUAL"}));
    pMeasureModeCombo->addItems(QStringList(QList<QString>{
                                                "Measure I",
                                                "Measure V"}));
    pMeasureRangeCombo->addItems(QStringList(QList<QString>{
                                                 "AUTO",
                                                 "MANUAL"}));
    // Ui Elements Attributes
    pComplianceButton->setLayoutDirection(Qt::RightToLeft);
    pComplianceButton->setAttribute(Qt::WA_TransparentForMouseEvents);
    pComplianceButton->setFocusPolicy(Qt::NoFocus);
    //
    pSourceRangeEdit->setAlignment(Qt::AlignRight);
    pSourceValueEdit->setAlignment(Qt::AlignRight);
    pSourceStartEdit->setAlignment(Qt::AlignRight);
    pSourceStopEdit->setAlignment(Qt::AlignRight);
    pSourceSettlingTimeEdit->setAlignment(Qt::AlignRight);
    pSourceNpointsEdit->setAlignment(Qt::AlignRight);
    pMeasureRangeEdit->setAlignment(Qt::AlignRight);
    pMeasureLimitEdit->setAlignment(Qt::AlignRight);
    pMeasureNPLCEdit->setAlignment(Qt::AlignRight);
    //
    pSourceModeLabel->setMaximumWidth(120);
    pSourceRangeLabel->setMaximumWidth(120);
    pSourceValueLabel->setMaximumWidth(120);
    pSourceStartLabel->setMaximumWidth(120);
    pSourceStopLabel->setMaximumWidth(120);
    pSourceSettlingTimeEdit->setMaximumWidth(120);
    pSourceNpointsEdit->setMaximumWidth(120);
    pSourceModeCombo->setMaximumWidth(120);
    pSourceRangeCombo->setMaximumWidth(120);
    pSourceRangeEdit->setMaximumWidth(120);
    pSourceStartEdit->setMaximumWidth(120);
    pSourceStopEdit->setMaximumWidth(120);
    pSourceSettlingTimeLabel->setMaximumWidth(120);
    pSourceValueEdit->setMaximumWidth(120);
    //
    pMeasureNPLCLabel->setMaximumWidth(120);
    pMeasureNPLCEdit->setMaximumWidth(120);
    pMeasureModeCombo->setMaximumWidth(120);
    pMeasureRangeCombo->setMaximumWidth(120);
    pMeasureRangeEdit->setMaximumWidth(120);
    pMeasureLimitEdit->setMaximumWidth(120);
}


void
ChannelTab::InitLayout() {
    QVBoxLayout* pLayout  = new QVBoxLayout();
    QGridLayout* pLayout1 = new QGridLayout();
    QGridLayout* pLayout2 = new QGridLayout();
    QGridLayout* pLayout3 = new QGridLayout();
    // Source Ui Labels (pLayout1)
    pLayout1->addWidget(pSourceModeLabel,    0, 0, 1, 1, Qt::AlignCenter);
    pLayout1->addWidget(pSourceRangeLabel,   0, 1, 1, 2, Qt::AlignCenter);
    pLayout1->addWidget(pSourceValueLabel,   0, 3, 1, 1, Qt::AlignCenter);
    // Source Ui Elements
    pLayout1->addWidget(pSourceModeCombo,    1, 0, 1, 1);
    pLayout1->addWidget(pSourceRangeCombo,   1, 1, 1, 1);
    pLayout1->addWidget(pSourceRangeEdit,    1, 2, 1, 1);
    pLayout1->addWidget(pSourceValueEdit,    1, 3, 1, 1);
    // Sweep Ui Labels
    pLayout1->addWidget(pSourceStartLabel,        2, 0, 1, 1, Qt::AlignCenter);
    pLayout1->addWidget(pSourceStopLabel,         2, 1, 1, 1, Qt::AlignCenter);
    pLayout1->addWidget(pSourceSettlingTimeLabel, 2, 2, 1, 1, Qt::AlignCenter);
    pLayout1->addWidget(pSourceNpointsLabel,      2, 3, 1, 1, Qt::AlignCenter);
    // Sweep Ui Elements
    pLayout1->addWidget(pSourceStartEdit,        3, 0, 1, 1);
    pLayout1->addWidget(pSourceStopEdit,         3, 1, 1, 1);
    pLayout1->addWidget(pSourceSettlingTimeEdit, 3, 2, 1, 1);
    pLayout1->addWidget(pSourceNpointsEdit,      3, 3, 1, 1);

//    pSourceStartLabel->hide();
//    pSourceStopLabel->hide();
//    pSourceNpointsLabel->hide();
//    pSourceStartEdit->hide();
//    pSourceStopEdit->hide();
//    pSourceSettlingTimeEdit->hide();
//    pSourceNpointsEdit->hide();

    // Measure Headers (pLayout2)
    pLayout2->addWidget(pMeasureModeLabel,   0, 0, 1, 1, Qt::AlignCenter);
    pLayout2->addWidget(pMeasureRangeLabel,  0, 1, 1, 2, Qt::AlignCenter);
    pLayout2->addWidget(pMeasureLimitLabel,  0, 3, 1, 1, Qt::AlignCenter);
    // Measure Ui Elements
    pLayout2->addWidget(pMeasureModeCombo,   1, 0, 1, 1);
    pLayout2->addWidget(pMeasureRangeCombo,  1, 1, 1, 1);
    pLayout2->addWidget(pMeasureRangeEdit,   1, 2, 1, 1);
    pLayout2->addWidget(pMeasureLimitEdit,   1, 3, 1, 1);
    pLayout3->addWidget(pMeasureNPLCLabel,   0, 0, 1, 1, Qt::AlignRight);
    pLayout3->addWidget(pMeasureNPLCEdit,    0, 1, 1, 1);
    // Miscellaneous
    pLayout3->addWidget(pComplianceButton,   1, 0, 1, 1);
    pLayout3->addWidget(pOnOffLabel,         1, 2, 1, 1, Qt::AlignRight);
    pLayout3->addWidget(pOnOffButton,        1, 3, 1, 1);
    // Styles
    sNormalStyle = pMeasureNPLCEdit->styleSheet();
    sErrorStyle  = "QLineEdit { ";
    sErrorStyle += "color: rgb(255, 255, 255);";
    sErrorStyle += "background: rgb(255, 0, 0);";
    sErrorStyle += "selection-background-color: rgb(128, 128, 255);";
    sErrorStyle += "}";
    // Layout
    pLayout->addSpacing(24);
    pLayout->addLayout(pLayout1);
    pLayout->addSpacing(24);
    pLayout->addLayout(pLayout2);
    pLayout->addSpacing(24);
    pLayout->addLayout(pLayout3);
    setLayout(pLayout);
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
    connect(pMeasureModeCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onMeasureModeChangedUi(int)));
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
        pMeasureModeCombo->setCurrentText("Measure I");
    }
    else if(sValue == QString("Source I")) {
        bResult = pChannel->setSourceFunction(K2602B_Channel::CURRENT);
        pMeasureModeCombo->setCurrentText("Measure V");
    }
    else if(sValue == QString("Dc Sweep V")) {
        bResult = pChannel->setSourceFunction(K2602B_Channel::DC_SWEEP_V);
        pMeasureModeCombo->setCurrentText("Measure I");
    }
    else if(sValue == QString("Dc Sweep I")) {
        bResult = pChannel->setSourceFunction(K2602B_Channel::DC_SWEEP_I);
        pMeasureModeCombo->setCurrentText("Measure V");
    }
    else if(sValue == QString("Pulsed Swp V")) {
        bResult = pChannel->setSourceFunction(K2602B_Channel::PLSD_SWEEP_V);
        pMeasureModeCombo->setCurrentText("Measure I");
    }
    else if(sValue == QString("Pulsed Swp I")) {
        bResult = pChannel->setSourceFunction(K2602B_Channel::PLSD_SWEEP_I);
        pMeasureModeCombo->setCurrentText("Measure V");
    }

    (void)bResult;
}


void
ChannelTab::onMeasureModeChangedUi(int selectedItem) {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << pChannel->getName()
             << pMeasureModeCombo->itemText(selectedItem);
#endif
    QString sValue = pMeasureModeCombo->itemText(selectedItem);
    bool bResult;
    if(sValue.contains("I")) {
        bResult = pChannel->setSourceFunction(K2602B_Channel::VOLTAGE);
    }
    else { // Measure
        bResult = pChannel->setSourceFunction(K2602B_Channel::CURRENT);
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
        pMeasureModeCombo->setCurrentIndex(0);
        pSourceModeCombo->setCurrentIndex(1);
    }
    else {
        pMeasureModeCombo->setCurrentIndex(1);
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
