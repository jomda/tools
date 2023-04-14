/*****************************************************************************/
/*                                                                           */
/*    Copyright (C) - LEGATE Intelligent Equipment - All rights reserved     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*  Except if expressly provided in a dedicated License Agreement, you are   */
/*  not authorized to:                                                       */
/*                                                                           */
/*  1. Use, copy, modify or transfer this software component, module or      */
/*  product, including any accompanying electronic or paper documentation    */
/*  (together, the "Software").                                              */
/*                                                                           */
/*  2. Remove any product identification, copyright, proprietary notices or  */
/*  labels from the Software.                                                */
/*                                                                           */
/*  3. Modify, reverse engineer, decompile, disassemble or otherwise attempt */
/*  to reconstruct or discover the source code, or any parts of it, from the */
/*  binaries of the Software.                                                */
/*                                                                           */
/*  4. Create derivative works based on the Software (e.g. incorporating the */
/*  Software in another software or commercial product or service without a  */
/*  proper license).                                                         */
/*                                                                           */
/*  By installing or using the "Software", you confirm your acceptance of the*/
/*  hereabove terms and conditions.                                          */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*  History:                                                                 */
/*****************************************************************************/
/*  Date       * Author          * Changes                                   */
/*****************************************************************************/
/*  2012-06-06 * Dajiang.lu      * Creation of the file                      */
/*             *                 *                                           */
/*****************************************************************************/
#include "sell.h"

sell::sell(StStore info, QWidget *parent)
     :QDialog(parent)
{    
    QString temp;

    quotient = info.quotient;
    h_layout1 = new QHBoxLayout();
    h_layout2 = new QHBoxLayout();
    h_layout3 = new QHBoxLayout();
    h_layout4 = new QHBoxLayout();
    l_Date = new QLabel("成交时间:");
    le_Date = new QLineEdit();
    QString date = QDate::currentDate().toString("yyyyMMdd");
    le_Date->setText(date);
    l_FundCode = new QLabel("基金代码:");
    le_FundCode = new QLineEdit();
    le_FundCode->setEnabled(false);
    temp.sprintf("%06x", info.fundCode);
    le_FundCode->setText(temp);
    l_price = new QLabel("成交净值:");
    le_price = new QLineEdit();
    temp.setNum(info.price);
    le_price->setText(temp);
    l_quotient = new QLabel("成交份额:");
    le_quotient = new QLineEdit();
    temp.setNum(info.quotient);
    le_quotient->setText(temp);
    l_fare = new QLabel("  手续费:");
    le_fare = new QLineEdit();
    temp.setNum(info.fare);
    le_fare->setText(temp);
    l_total = new QLabel("成交金额:");
    le_total = new QLineEdit();
    temp.setNum(info.total);
    le_total->setText(temp);      

    btn_sell = new QPushButton("卖出"); 
    btn_accept = new QPushButton("确认");
    btn_reject = new QPushButton("取消");
    connect(btn_sell,SIGNAL(clicked(bool)), this, SLOT(SlotSell()));
    connect(btn_accept,SIGNAL(clicked(bool)), this, SLOT(SlotAcceptCondition()));
    connect(btn_reject,SIGNAL(clicked(bool)), this, SLOT(reject()));
    
    h_layout1->addWidget(l_Date);
    h_layout1->addWidget(le_Date);
    h_layout1->addWidget(l_FundCode);
    h_layout1->addWidget(le_FundCode);
    h_layout2->addWidget(l_price);
    h_layout2->addWidget(le_price);
    h_layout2->addWidget(l_quotient);
    h_layout2->addWidget(le_quotient);
    h_layout3->addWidget(l_fare);
    h_layout3->addWidget(le_fare);
    h_layout3->addWidget(l_total);
    h_layout3->addWidget(le_total);
    h_layout4->addWidget(btn_sell);
    h_layout4->addWidget(btn_accept);
    h_layout4->addWidget(btn_reject);
   
    v_layout = new QVBoxLayout(this);
    v_layout->addLayout(h_layout1);
    v_layout->addLayout(h_layout2);
    v_layout->addLayout(h_layout3);
    v_layout->addLayout(h_layout4);
}

void sell::SlotSell()
{
    flag_sell = 1;
    accept();
}

void sell::SlotAcceptCondition()
{
    bool ok;
    if(quotient >= le_quotient->text().toFloat(&ok))
    {
        flag_sell = 0;
        accept();
    }
    else
    {
        QString temp = QString("最大份额:%1").arg(quotient);
        le_quotient->setText(temp);
    }
}

void sell::getSellInfo(StStore& info)
{
    bool ok;
    info.date = le_Date->text();
    info.fundCode = le_FundCode->text().toUInt(&ok, 16);
    info.price = le_price->text().toFloat(&ok);
    info.quotient = le_quotient->text().toFloat(&ok);
    info.fare = le_fare->text().toFloat(&ok);
    info.total = le_total->text().toFloat(&ok);
    info.flag_sell = flag_sell;
}        

sell::~sell()
{    
    if(le_Date)
    {        
        delete le_Date;
        le_Date = NULL;
    }

    if(le_FundCode)
    {
        delete le_FundCode;
        le_FundCode = NULL;
    }

    if(le_price)
    {
        delete le_price;
        le_price = NULL;
    }
    
    if(le_price)
    {
        delete le_price;
        le_price = NULL;
    }
    
    if(le_quotient)
    {
        delete le_quotient;
        le_quotient = NULL;
    }

    if(le_fare)
    {
        delete le_fare;
        le_fare = NULL;
    }
    
    if(le_total)
    {
        delete le_total;
        le_total = NULL;
    }
    
    if(btn_accept)
    {
        delete btn_accept;
        btn_accept = NULL;
    }
    
    if(btn_reject)
    {
        delete btn_reject;
        btn_reject = NULL;
    }    

    if(l_Date)
    {
        delete l_Date;
        l_Date = NULL;
    }

    if(l_FundCode)
    {
        delete l_FundCode;
        l_FundCode = NULL;
    }

    if(l_price)
    {
        delete l_price;
        l_price = NULL;
    }

    if(l_quotient)
    {
        delete l_quotient;
        l_quotient = NULL;
    }

    if(l_fare)
    {
        delete l_fare;
        l_fare = NULL;
    }

    if(l_total)
    {
        delete l_total;
        l_total = NULL;
    }
    
    if(h_layout1)
    {
        delete h_layout1;
        h_layout1 = NULL;
    }

    if(h_layout2)
    {
        delete h_layout2;
        h_layout2 = NULL;
    }

    if(h_layout3)
    {
        delete h_layout3;
        h_layout3 = NULL;
    }

    if(h_layout4)
    {
        delete h_layout4;
        h_layout4 = NULL;
    }

    if(v_layout)
    {
        delete v_layout;
        v_layout = NULL;
    }
}

