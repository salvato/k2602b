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

#include "k2602b.h"
#include <lxi.h>


k2602b::k2602b(QString sK2602B_Address, QObject *parent)
    : QObject{parent}
    , pComm(new CommChannel())
    , sAddress(sK2602B_Address)
    , bInitialized(false)
{
    pChannel[0] = new K2602B_Channel("a", pComm);
    pChannel[1] = new K2602B_Channel("b", pComm);
}


bool
k2602b::closeConnection() {
    if(!bInitialized)
        return true;
    return pComm->closeConnection();
}


bool
k2602b::Init() {
    // Connect the device
    if(pComm->connect(sAddress)== LXI_ERROR) {
        bInitialized = false;
        return bInitialized;
    }
    bInitialized = true;
    return bInitialized;
}


bool
k2602b::isInitialized() {
    return bInitialized;
}

