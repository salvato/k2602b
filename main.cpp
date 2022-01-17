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

#include "K2602bWindow.h"
#include <lxi.h>
#include <QApplication>
#include <QDebug>


QStringList connectedDevices;
QStringList addresses;


void
broadcast(const char *address, const char *interface) {
    Q_UNUSED(address)
    Q_UNUSED(interface)
#ifndef QT_NO_DEBUG
    qDebug() << QString("Broadcasting on interface %1 at Address: %2")
                .arg(interface, address);
#endif
}


void
device(const char *address, const char *id) {
#ifndef QT_NO_DEBUG
    qDebug() << QString(" Found %1 on address %2")
                .arg(id, address);
#endif
    connectedDevices.append(id);
    addresses.append(address);
}


int
main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationDomain("Gabriele.Salvato");
    QCoreApplication::setOrganizationName("Gabriele.Salvato");
    QCoreApplication::setApplicationName("K2602B");
    QCoreApplication::setApplicationVersion("0.0.1");

    lxi_info_t info;

    lxi_init(); // Initialize LXI library

    // Set up search information callbacks
    info.broadcast = &broadcast;
    info.device    = &device;

#ifndef QT_NO_DEBUG
    qDebug() << "Searching for LXI devices - please wait...";
#endif
    QString sK2602Baddress = QString();

    // Search for LXI devices, 1 second timeout
    lxi_discover(&info, 1000, DISCOVER_VXI11);
    bool bFound = false;
    for(int i=0; i<connectedDevices.size(); i++) {
#ifndef QT_NO_DEBUG
        qDebug() << connectedDevices.at(i);
#endif
        if(connectedDevices.at(i).contains("2602B")) {
            sK2602Baddress = addresses.at(i);
            bFound = true;
            break;
        }
    }
    if(!bFound)
        exit(EXIT_FAILURE);

    K2602BWindow* pK2602B;
    pK2602B = new K2602BWindow(sK2602Baddress);

    pK2602B->show();

    return a.exec();
}
