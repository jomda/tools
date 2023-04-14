#ifndef _FUNDDEF_HPP_
#define _FUNDDEF_HPP_
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
/*  2011-06-14 * dajiang.lu      * Creation of the file                      */
/*             *                 *                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Include Files                                                            */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Definitions                                                              */
/*                                                                           */
/*****************************************************************************/
typedef struct
{
    quint32 serNum;
    QString date;
    quint32 fundCode;
    float price;
    float quotient;
    float fare;
    float total;
    char flag_sell;
} StStore;

typedef struct
{
    quint32 serNum;
    quint32 fundCode;
    QString date_buy;
    QString date_sell;
    float price_buy;
    float price_sell;
    float quotient;
    float fare_buy;
    float fare_sell;
    float total_buy;
    float total_sell;
} StSellInfo;

typedef struct
{
    quint32 fundCode;
    QString name;
    float quotient;
    float total;
} StCodeInfo;


/*****************************************************************************/
/*                                                                           */
/*  Variable Declarations                                                    */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Function Declarations                                                    */
/*                                                                           */
/*****************************************************************************/


#endif //_FUNDDEF_HPP_

