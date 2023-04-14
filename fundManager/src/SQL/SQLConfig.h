#ifndef _SQLCONFIG_HPP_
#define _SQLCONFIG_HPP_
/*****************************************************************************/
/*                                                                           */
/*    Copyright (C) -        Intelligent Equipment - All rights reserved     */
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
/*  2018-09-07 * Dajiang.Lu      * Creation of the file                      */
/*             *                 *                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Include Files                                                            */
/*                                                                           */
/*****************************************************************************/
#include <QtCore>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "FundDef.hpp"

typedef enum
{
	CMD_SQL_SC_REQUEST,
	CMD_SQL_SC_CHECK_SQL_FILES,
    CMD_SQL_SEND_AR_REQUEST,
    CMD_SQL_IETSP_CHECK_BATCH,
} eSQLCmd;


typedef struct
{
    quint8 fileType;
	quint32 date;
    quint32 start_sn;
    quint32 end_sn;
} StFilesRequireInfo;

typedef struct
{
    eSQLCmd cmd;
    union UnApiData
    {
        int test;
		StFilesRequireInfo filesRequireInfo;
    }SendData;
} StSQLApiCmd;

/*****************************************************************************/
/*                                                                           */
/*  Definitions                                                              */
/*                                                                           */
/*****************************************************************************/
#define NAME_DB               "./DB/fund.db"
#define NAME_TABLE_CONFIG     "appConfig"
#define NAME_TABLE_CODE       "code"
#define NAME_TABLE_STORE      "store"
#define NAME_TABLE_SELL       "sell"

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Class packed configuration file process functions                       */
/*                                                                           */
/* CAUTION!!!:                                                               */
/*   Only one single instance of this class is allowed to exist              */
/*                                                                           */
/*****************************************************************************/
class CSQLFund
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CSQLFund(QString sqlname);
        ~CSQLFund();

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
       
        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/        
		bool getSerNum(const QString tableName, int& serNum);
		bool getCodeInfo(QString code, QString& name);
		bool getAccoutInfo(QList<StCodeInfo>& info);
		bool updateSerNum(const QString tableName, int serNum);
		bool AddStore(const QString tableName, StStore storeInfo);
		bool AddSell(const QString tableName, StSellInfo info);
		bool getStoreInfo(const QString tableName, QString condition, QList<StStore>& storeList);
		bool deleteStoreInfo(const QString tableName, quint32 serNum);
		bool updateStoreInfo(const QString tableName, StStore storeInfo);
		bool updateStoreFlag(const QString tableName, quint32 id);
		bool getSellInfo(const QString tableName, QString condition, QList<StSellInfo>& sellList);

    private:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/ 
        QMutex accessMutex;
        QSqlDatabase database;
		
   
        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
		bool checkTableExist(QString tableName);
		bool getCountRows(QString tableName, quint32& count);

     protected:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
};


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


#endif //_SQLCONFIG_HPP_

