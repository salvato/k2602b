/*
MIT License

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
#include <QTabWidget>
#include <QStatusBar>
#include <QVBoxLayout>

#include "k2602b.h"
#include "channeltab.h"

class K2602BWindow : public QWidget
{
    Q_OBJECT

public:
    K2602BWindow(QString sK2602B_Address, QWidget *parent=nullptr);
    ~K2602BWindow();

protected:
    void closeEvent(QCloseEvent*) Q_DECL_OVERRIDE;
    void saveSettings();
    void restoreSettings();
    void initLayout();
    void initMessages();
    void updateUi();

private:
    QString sAddress;
    k2602b*      pK2602B;
    QTabWidget*  pTabWidget;
    ChannelTab*  pChannelTab[2];
    QStatusBar*  pStatusBar;
    QVBoxLayout* pMainLayout;
};
