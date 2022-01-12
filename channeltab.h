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

public:
    void setOnOff_Ui(bool bOn);
    void setSourceMode_Ui(bool bSourceV);
    void setSourceValue_Ui(double dValue);
    void setSourceRange_Ui(double dValue);
    void setMeasureRange_Ui(double dValue);
    void setLimit_Ui(double dValue);

protected:
    void saveSettings();
    void restoreSettings();
    void InitSignals();

signals:

public slots:
    void onSourceRangeEditingFinished();
    void onSourceValueEditingFinished();
    void onMeasureRangeEditingFinished();
    void onMeasureLimitEditingFinished();

    void onSourceRangeChangedUi(int selectedItem);
    void onSourceModeChangedUi(int selectedItem);
    void onMeasureModeChangedUi(int selectedItem);
    void onOnOffChangedUi(int);


private:
    K2602B_Channel* pChannel;

    QComboBox* pSourceMode;
    QLabel*    pSourceRangeLabel;
    QComboBox* pSourceRangeCombo;
    QLineEdit* pSourceRangeEdit;
    QLabel*    pSourceValueLabel;
    QLineEdit* pSourceValueEdit;

    QComboBox* pMeasureMode;
    QLabel*    pMeasureRangeLabel;
    QComboBox* pMeasureRangeCombo;
    QLineEdit* pMeasureRangeEdit;
    QLabel*    pMeasureLimitLabel;
    QLineEdit* pMeasureLimitEdit;

    QLabel*    pOnOffLabel;
    QCheckBox* pOnOffButton;

    QCheckBox* pComplianceButton;
};

