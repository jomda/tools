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
#ifndef SELL_H
#define SELL_H

#include <QtGui>
#include <QWidget>
#include <QDialog>
#include "FundDef.hpp"

class sell : public QDialog
{
    Q_OBJECT

public:
    sell(StStore info, QWidget *parent = 0);
	~sell();
	void getSellInfo(StStore& info);

private:
	QLineEdit* le_Date;
	QLineEdit* le_FundCode;
    QLineEdit* le_price;
    QLineEdit* le_quotient;
	QLineEdit* le_fare;
	QLineEdit* le_total;
	QPushButton* btn_sell;
	QPushButton* btn_accept;	
	QPushButton* btn_reject;
	QHBoxLayout* h_layout1;
    QHBoxLayout* h_layout2;
    QHBoxLayout* h_layout3;
    QHBoxLayout* h_layout4;
	QLabel* l_Date;
	QLabel* l_FundCode;
	QLabel* l_price;
	QLabel* l_quotient;
	QLabel* l_fare;
	QLabel* l_total;
	QVBoxLayout* v_layout;

	// 
	float quotient;
	char flag_sell;

private slots:
	void SlotAcceptCondition();
	void SlotSell();	

};

#endif // SELL_H
