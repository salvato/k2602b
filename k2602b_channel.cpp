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


#define SOURCE_V true
#define SOURCE_I false


K2602B_Channel::K2602B_Channel(QString name,
                               CommChannel* pCommunicationChannel,
                               QObject* parent)
    : QObject{parent}
    , sName(name)
    , pComm(pCommunicationChannel)
{
}


bool
K2602B_Channel::setOnOff(bool bOn) {
    qDebug() << __FILE__ << "Line:" << __LINE__ << __FUNCTION__ << "Channel" << sName << bOn;
    QString sCommand;
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
    qDebug() << __FILE__ << "Line:" << __LINE__ << __FUNCTION__ << "Channel" << sName;
    QString sCommand;
    if(function == CURRENT)
        sCommand = QString("smu%1.source.func = smu%2.OUTPUT_DCAMPS").arg(sName, sName);
    else
        sCommand = QString("smu%1.source.func = smu%2.OUTPUT_DCVOLTS").arg(sName, sName);
    return pComm->send(sCommand) != LXI_ERROR;
}


bool
K2602B_Channel::setSourceValue(double dValue) {
    QString sCommand, sSource;
    if(getSourceFunction() == SOURCE_V)
        sSource = "v";
    else
        sSource = "i";
    sCommand = QString("smu%1.source.level%2 = %3").arg(sName,sSource).arg(dValue);
    qDebug() << __FILE__ << "Line:" << __LINE__ << __FUNCTION__ << "Channel" << sName << dValue;
    return pComm->send(sCommand) != LXI_ERROR;
}


// Set the maximum expected voltage or current to be sourced
bool
K2602B_Channel::setSourceRange(double dValue) {
    QString sCommand, sSource;
    if(getSourceFunction() == SOURCE_V)
        sSource = "v";
    else
        sSource = "i";
    sCommand = QString("smu%1.source.range%2 = %3").arg(sName,sSource).arg(dValue);
    qDebug() << __FILE__ << "Line:" << __LINE__ << __FUNCTION__ << "Channel" << sName << dValue;
    return pComm->send(sCommand) != LXI_ERROR;
}


bool
K2602B_Channel::setMeasureRange(double dValue) {
    QString sCommand, sSource;
    if(getSourceFunction() == SOURCE_V)
        sSource = "v";
    else // SOURCE_I
        sSource = "i";
    sCommand = QString("smu%1.measure.range%2 = %3").arg(sName,sSource).arg(dValue);
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << dValue;
    return pComm->send(sCommand) != LXI_ERROR;
}


bool
K2602B_Channel:: setLimit(double dValue) {
    QString sCommand, sLimit;
    if(getSourceFunction() == SOURCE_V)
        sLimit = "i";
    else // SOURCE_I
        sLimit = "v";
    sCommand = QString("smu%1.source.limit%2 = %3").arg(sName, sLimit).arg(dValue);
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << dValue;
    return pComm->send(sCommand) != LXI_ERROR;
}



QString
K2602B_Channel::getName() {
    return sName;
}


bool
K2602B_Channel::getOnOff() {
    bool bOk;
    sCommand = QString("print(smu%1.source.output)").arg(sName);
    double result = pComm->Query(sCommand).toDouble(&bOk);
    qDebug() << __FILE__ << "Line:" << __LINE__ << __FUNCTION__ << "Channel" << sName << result;
    return result > 0.0;
}


bool
K2602B_Channel::getSourceFunction() {
    bool bOk;
    sCommand = QString("print(smu%1.source.func)").arg(sName);
    double result = pComm->Query(sCommand).toDouble(&bOk);
    qDebug() << __FILE__ << "Line:" << __LINE__ << __FUNCTION__ << "Channel" << sName << result;
    return result > 0.0;
}


double
K2602B_Channel::getSourceValue() {
    bool bOk;
    QString sCommand, sSource;
    if(getSourceFunction() == SOURCE_V)
        sSource = "v";
    else
        sSource = "i";
    sCommand = QString("print(smu%1.source.level%2)").arg(sName, sSource);
    double result = pComm->Query(sCommand).toDouble(&bOk);
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << result;
    return result;
}


// Get the maximum expected voltage or current to be sourced
double
K2602B_Channel::getSourceRange() {
    bool bOk;
    QString sCommand, sSource;
    if(getSourceFunction() == SOURCE_V)
        sSource = "v";
    else
        sSource = "i";
    sCommand = QString("print(smu%1.source.range%2)").arg(sName, sSource);
    double result = pComm->Query(sCommand).toDouble(&bOk);
    qDebug() << __FILE__ << "Line:" << __LINE__ << __FUNCTION__ << "Channel" << sName << result;
    return result;
}


double
K2602B_Channel::getMeasureRange() {
    bool bOk;
    QString sCommand, sMeasure;
    if(getSourceFunction() == SOURCE_V)
        sMeasure = "i";
    else
        sMeasure = "v";
    sCommand = QString("print(smu%1.measure.range%2)").arg(sName, sMeasure);
    double result = pComm->Query(sCommand).toDouble(&bOk);
    qDebug() << __FILE__ << "Line:" << __LINE__ << __FUNCTION__ << "Channel" << sName << result;
    return result;
}


double
K2602B_Channel::getLimit() {
    bool bOk;
    QString sCommand, sLimit;
    if(getSourceFunction() == SOURCE_V)
        sLimit = "i";
    else
        sLimit = "v";
    sCommand = QString("print(smu%1.source.limit%2)").arg(sName, sLimit);
    double result = pComm->Query(sCommand).toDouble(&bOk);
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << result;
    return result;
}


bool
K2602B_Channel::getCompliance() {
    QString sCommand;
    sCommand = QString("print(smu%1.source.compliance)").arg(sName);
    bool result = pComm->Query(sCommand) == "true";
    qDebug() << __FILE__
             << "Line:"
             << __LINE__
             << __FUNCTION__
             << "Channel"
             << sName
             << result;
    return result;
}
