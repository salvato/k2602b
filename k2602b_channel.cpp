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

#include "k2602b_channel.h"
#include <QDebug>


K2602B_Channel::K2602B_Channel(QString name,
                               CommChannel* pCommunicationChannel,
                               QObject* parent)
    : QObject{parent}
    , sName(name)
    , pComm(pCommunicationChannel)
{
}


bool
K2602B_Channel::reset() {
    sCommand = QString("smu%1.reset()").arg(sName);
    return pComm->send(sCommand) != LXI_ERROR;
}


bool
K2602B_Channel::setNPLC(double nplc) {
    if((nplc > 25.0) || (nplc < 0.001))
        return false;
    sCommand = QString("smu%1.measure.nplc = %2").arg(sName).arg(nplc);
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << nplc;
#endif
    return pComm->send(sCommand) != LXI_ERROR;
}


bool
K2602B_Channel::setOnOff(bool bOn) {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << bOn;
#endif
    if(bOn) {
        sCommand = QString("smu%1.source.output = smu%2.%3")
                   .arg(sName, sName, "OUTPUT_ON");
    }
    else {
        sCommand = QString("smu%1.source.output = smu%2.%3")
                   .arg(sName, sName, "OUTPUT_OFF");
    }
    return pComm->send(sCommand) != LXI_ERROR;
}


bool
K2602B_Channel::setSourceFunction(smuFunction function) {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName;
#endif
    sCommand = QString();
    if(function == VOLTAGE) {
        sCommand = QString("smu%1.source.func = smu%1.OUTPUT_DCVOLTS")
                .arg(sName);
    }
    else if(function == CURRENT) {
        sCommand = QString("smu%1.source.func = smu%1.OUTPUT_DCAMPS")
                .arg(sName);
    }
    else if(function == DC_SWEEP_V) {
//        sCommand = QString("smu%1.trigger.source.linearv(0.0, 1.0, 11)")
//                .arg(sName);
//        pComm->send(sCommand);
//        sCommand = QString("smu%1.trigger.source.action=smu%1.ENABLE")
//                .arg(sName);
//        pComm->send(sCommand);
//        sCommand = QString("smu%1.trigger.initiate()")
//                .arg(sName);
}
    else if(function == DC_SWEEP_I) {
        ;
    }
    else if(function == PLSD_SWEEP_V) {
        ;
    }
    else if(function == PLSD_SWEEP_I) {
        ;
    }
    return pComm->send(sCommand) != LXI_ERROR;
}


bool
K2602B_Channel::setAutoZero(smuAutoZero autoZero) {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << autoZero;
#endif
    if(autoZero == OFF) {
        sCommand = QString("smu%1.measure.autozero = smu%1.AUTOZERO_OFF")
                   .arg(sName);
    }
    else if(autoZero == ONCE) {
        sCommand = QString("smu%1.measure.autozero = smu%1.AUTOZERO_ONCE")
                   .arg(sName);
    }
    else if(autoZero == AUTO) {
        sCommand = QString("smu%1.measure.autozero = smu%1.AUTOZERO_AUTO")
                   .arg(sName);
    }
    return pComm->send(sCommand) != LXI_ERROR;
}


bool
K2602B_Channel::setSourceValue(double dValue) {
    QString sSource;
    if(isSourceV())
        sSource = "v";
    else
        sSource = "i";
    sCommand = QString("smu%1.source.level%2 = %3").arg(sName,sSource).arg(dValue);
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << dValue;
#endif
    return pComm->send(sCommand) != LXI_ERROR;
}


bool
K2602B_Channel::setSourceAutoRange(bool bAuto) {
    QString sMeasure;
    if(isSourceV())
        sMeasure = "v";
    else // SOURCE_I
        sMeasure = "i";

    if(bAuto) {
        sCommand = QString("smu%1.source.autorange%2 = smu%1.AUTORANGE_ON")
                   .arg(sName, sMeasure);
    }
    else {
        sCommand = QString("smu%1.source.autorange%2 = smu%1.AUTORANGE_OFF")
                   .arg(sName, sMeasure);
    }
    return pComm->send(sCommand) != LXI_ERROR;
}


// Set the maximum expected voltage or current to be sourced
bool
K2602B_Channel::setSourceRange(double dValue) {
    QString sSource;
    if(isSourceV())
        sSource = "v";
    else
        sSource = "i";
    sCommand = QString("smu%1.source.range%2 = %3").arg(sName,sSource).arg(dValue);
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << dValue;
#endif
    return pComm->send(sCommand) != LXI_ERROR;
}


bool
K2602B_Channel::setMeasureAutoRange(bool bAuto) {
    QString sMeasure;
    if(isSourceV())
        sMeasure = "i";
    else // SOURCE_I
        sMeasure = "v";

    if(bAuto) {
        sCommand = QString("smu%1.measure.autorange%2 = smu%1.AUTORANGE_ON")
                   .arg(sName, sMeasure);
    }
    else {
        sCommand = QString("smu%1.measure.autorange%2 = smu%1.AUTORANGE_OFF")
                   .arg(sName, sMeasure);
    }
    return pComm->send(sCommand) != LXI_ERROR;
}


bool
K2602B_Channel::setMeasureRange(double dValue) {
    QString sSource;
    if(isSourceV())
        sSource = "v";
    else // SOURCE_I
        sSource = "i";
    sCommand = QString("smu%1.measure.range%2 = %3").arg(sName,sSource).arg(dValue);
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << dValue;
#endif
    return pComm->send(sCommand) != LXI_ERROR;
}


bool
K2602B_Channel:: setLimit(double dValue) {
    QString sLimit;
    if(isSourceV())
        sLimit = "i";
    else // SOURCE_I
        sLimit = "v";
    sCommand = QString("smu%1.source.limit%2 = %3").arg(sName, sLimit).arg(dValue);
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << dValue;
#endif
    return pComm->send(sCommand) != LXI_ERROR;
}


bool
K2602B_Channel::setSenseLocal(bool bSenseLocal) {
    if(bSenseLocal) {
        sCommand = QString("smu%1.sense = smu%1.SENSE_LOCAL").arg(sName);
    }
    else {
        sCommand = QString("smu%1.sense = smu%1.SENSE_REMOTE").arg(sName);
    }
    return pComm->send(sCommand) != LXI_ERROR;
}


QString
K2602B_Channel::getName() {
    return sName;
}


bool
K2602B_Channel::isOn() {
    bool bOk;
    sCommand = QString("print(smu%1.source.output)").arg(sName);
    double result = pComm->Query(sCommand).toDouble(&bOk);
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << result;
#endif
    return result > 0.0;
}


bool
K2602B_Channel::isSourceV() {
    bool bOk;
    sCommand = QString("print(smu%1.source.func)").arg(sName);
    double result = pComm->Query(sCommand).toDouble(&bOk);
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << result;
#endif
    return result > 0.0;
}


double
K2602B_Channel::getNPLC() {
    bool bOk;
    sCommand = QString("print(smu%1.measure.nplc)").arg(sName);
    double result = pComm->Query(sCommand).toDouble(&bOk);
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << result;
#endif
    return result;
}


double
K2602B_Channel::getSourceValue() {
    bool bOk;
    QString sSource;
    if(isSourceV())
        sSource = "v";
    else
        sSource = "i";
    sCommand = QString("print(smu%1.source.level%2)").arg(sName, sSource);
    double result = pComm->Query(sCommand).toDouble(&bOk);
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << result;
#endif
    return result;
}


// Get the maximum expected voltage or current to be sourced
double
K2602B_Channel::getSourceRange() {
    bool bOk;
    QString sSource;
    if(isSourceV())
        sSource = "v";
    else
        sSource = "i";
    sCommand = QString("print(smu%1.source.range%2)").arg(sName, sSource);
    double result = pComm->Query(sCommand).toDouble(&bOk);
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << result;
#endif
    return result;
}


double
K2602B_Channel::getMeasureRange() {
    bool bOk;
    QString sMeasure;
    if(isSourceV())
        sMeasure = "i";
    else
        sMeasure = "v";
    sCommand = QString("print(smu%1.measure.range%2)").arg(sName, sMeasure);
    double result = pComm->Query(sCommand).toDouble(&bOk);
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << result;
#endif
    return result;
}


double
K2602B_Channel::getLimit() {
    bool bOk;
    QString sLimit;
    if(isSourceV())
        sLimit = "i";
    else
        sLimit = "v";
    sCommand = QString("print(smu%1.source.limit%2)").arg(sName, sLimit);
    double result = pComm->Query(sCommand).toDouble(&bOk);
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << result;
#endif
    return result;
}


bool
K2602B_Channel::getCompliance() {
    sCommand = QString("print(smu%1.source.compliance)").arg(sName);
    bool result = pComm->Query(sCommand) == "true";
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << result;
#endif
    return result;
}


double
K2602B_Channel::getSingleMeasure() {
    bool bOk;
    QString sRead;
    if(isSourceV())
        sRead = "i";
    else
        sRead = "v";
    sCommand = QString("print(smu%1.measure.%2())").arg(sName, sRead);
    double result = pComm->Query(sCommand).toDouble(&bOk);
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << result;
#endif
    return result;
}


bool
K2602B_Channel::abort() {
#ifndef QT_NO_DEBUG
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName;
#endif
    sCommand = QString("smu%1.abort()").arg(sName);
    return pComm->send(sCommand) != LXI_ERROR;
}
