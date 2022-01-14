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
#include <QString>
#include <QMutex>
#include <lxi.h>


class CommChannel : public QObject
{
    Q_OBJECT
public:
    explicit CommChannel(QObject *parent = nullptr);

public:
    int connect(QString address);
    int send(QString message);
    QByteArray receive();
    int closeConnection();
    QByteArray Query(QString sCommand);
    typedef enum error {
        NO_ERROR=0,
        NO_CONNECTION_ERROR,
        SEND_ERROR,
        RECEIVE_ERROR
    } errorCodes;
    int getError();

signals:

private:
    QMutex mutex;
    int mySessionId;
    int timeout;
    bool bConnected;
    int errorCode;
    char buf[1025];
};
