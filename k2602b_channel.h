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

#include <QObject>
#include "commchannel.h"

class K2602B_Channel : public QObject
{
    Q_OBJECT
public:
    explicit K2602B_Channel(QString name, CommChannel* pCommunicationChannel, QObject *parent=nullptr);

public:
    typedef enum smuFunction {
        VOLTAGE = 0,
        CURRENT,
        DC_SWEEP_V,
        DC_SWEEP_I,
        PLSD_SWEEP_I,
        PLSD_SWEEP_V
    } outputFunction;
    typedef enum smuAutoZero {
        OFF = 0,
        ONCE,
        AUTO
    } autoZero;
    QString getName();
    bool reset();
    bool setOnOff(bool bOn);
    bool setNPLC(double nplc);
    bool setSourceFunction(smuFunction function);
    bool setAutoZero(smuAutoZero autoZero);
    bool setSourceValue(double dValue);
    bool setSourceRange(double dValue);
    bool setSourceAutoRange(bool bAuto);
    bool setMeasureRange(double dValue);
    bool setMeasureAutoRange(bool bAuto);
    bool setLimit(double dValue);
    bool setSenseLocal(bool bSenseLocal);

    bool   isOn();
    double getNPLC();
    bool   isSourceV();
    double getSourceValue();
    double getSourceRange();
    double getMeasureRange();
    double getLimit();
    bool   getCompliance();
    double getSingleMeasure();

    bool   abort();

signals:

private:
    QString sName;
    QString sCommand;
    CommChannel* pComm;
};

