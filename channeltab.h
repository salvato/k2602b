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

#pragma once

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>

#include "channeltab.h"
#include "k2602b_channel.h"

class ChannelTab : public QWidget
{
    Q_OBJECT
public:
    explicit ChannelTab(K2602B_Channel* pCh, QWidget *parent = nullptr);
    typedef enum {
        Source_V=0,
        Source_I,
        DcSweep_V,
        DcSweep_I,
        PulsedSweep_V,
        PulsedSweep_I
    } sourceMode;

public:
    void setOnOff_Ui(bool bOn);
    void setSourceMode_Ui(bool bSourceV);
    void setSourceValue_Ui(double dValue);
    void setSourceRange_Ui(double dValue);
    void setMeasureRange_Ui(double dValue);
    void setLimit_Ui(double dValue);
    void setNPLC_Ui(double nplc);

protected:
    void closeEvent(QCloseEvent*event) Q_DECL_OVERRIDE;
    void saveSettings();
    void restoreSettings();
    void InitLayout();
    void InitSignals();
    void CreateUiElements();
    void UpdateUi(sourceMode mode);

signals:

public slots:
    void onSourceRangeEditingFinished();
    void onSourceValueEditingFinished();
    void onMeasureRangeEditingFinished();
    void onMeasureLimitEditingFinished();
    void onNPLCEditTextChanged(const QString &arg1);
    void onNPLCEditingFinished();

    void onSourceRangeChangedUi(int selectedItem);
    void onSourceModeChangedUi(int selectedItem);
    void onMeasureRangeChangedUi(int selectedItem);
    void onOnOffChangedUi(int);

public:

private:
    // QLineEdit styles
    QString sNormalStyle;
    QString sErrorStyle;

    K2602B_Channel* pChannel;

    QLabel*    pSourceModeLabel;
    QLabel*    pSourceRangeLabel;
    QLabel*    pSourceValueLabel;

    QComboBox* pSourceModeCombo;
    QComboBox* pSourceRangeCombo;
    QLineEdit* pSourceRangeEdit;
    QLineEdit* pSourceValueEdit;

    QLabel*    pSourceStartLabel;
    QLabel*    pSourceStopLabel;
    QLabel*    pSourceSettlingTimeLabel;
    QLabel*    pSourceNpointsLabel;
    QLabel*    pOnTimeLabel;
    QLabel*    pOffTimeLabel;
    QLabel*    pBiasLabel;

    QLineEdit*    pSourceStartEdit;
    QLineEdit*    pSourceStopEdit;
    QLineEdit*    pSourceSettlingTimeEdit;
    QLineEdit*    pSourceNpointsEdit;
    QLineEdit*    pOnTimeEdit;
    QLineEdit*    pOffTimeEdit;
    QLineEdit*    pBiasEdit;

    QLabel*    pMeasureRangeLabel;
    QLabel*    pMeasureLimitLabel;

    QCheckBox* pMeasureCurrent;
    QCheckBox* pMeasureVoltage;
    QCheckBox* pMeasureResistance;
    QCheckBox* pMeasurePower;
    QComboBox* pMeasureRangeCombo;
    QLineEdit* pMeasureRangeEdit;
    QLineEdit* pMeasureLimitEdit;

    QLabel*    pMeasureNPLCLabel;
    QLineEdit* pMeasureNPLCEdit;

    QLabel*    pOnOffLabel;
    QCheckBox* pOnOffButton;

    QCheckBox* pComplianceButton;
};

