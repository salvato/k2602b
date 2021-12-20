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

#include "commchannel.h"
#include <QDebug>


CommChannel::CommChannel(QObject *parent)
    : QObject{parent}
    , timeout(3000)
    , bConnected(false)
{
}


int
CommChannel::connect(QString address) {
    errorCode = NO_ERROR;
    mySessionId = lxi_connect(address.toLocal8Bit().data(),
                              0,
                              NULL,
                              timeout,
                              VXI11);
    if(mySessionId != LXI_ERROR) {
        errorCode = NO_CONNECTION_ERROR;
        bConnected = true;
    }
    return mySessionId;
}


int
CommChannel::send(QString message) {
    errorCode = NO_ERROR;
    if(!bConnected) {
        errorCode = NO_CONNECTION_ERROR;
        return LXI_ERROR;
    }
    int result = lxi_send(mySessionId,
                          message.toLocal8Bit().data(),
                          message.length(),
                          timeout);
    if(result != message.length()) {
        errorCode = SEND_ERROR;
    }
    return result;
}


QByteArray
CommChannel::receive() {
    if(!bConnected) {
        errorCode = NO_CONNECTION_ERROR;
        return QByteArray();
    }
    char buf[1025];
    int result = lxi_receive(mySessionId, buf, sizeof(buf)-1, timeout);
    if(result == LXI_ERROR) {
        errorCode = RECEIVE_ERROR;
        return QByteArray();
    }
    buf[result] = 0;
    return QByteArray(buf);
}


int
CommChannel::closeConnection() {
    if(!bConnected)
        return LXI_ERROR;
    int result = lxi_disconnect(mySessionId);
    return result;
}


QByteArray
CommChannel::Query(QString sCommand) {
    int sent = send(sCommand);
    if(sent == LXI_ERROR)
        return QByteArray();
    QByteArray result =  receive();
//    qDebug() << __FILE__ << "Line:" <<__LINE__ << result;
    return result;
}


int
CommChannel::getError() {
    return errorCode;
}

