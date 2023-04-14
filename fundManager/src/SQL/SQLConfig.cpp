#include "SQLConfig.h"
 #include <QSqlRecord>

#define SQL_USER_NAME             "avant"
#define SQL_PASSWORD              "ludajiang123456"

/*****************************************************************************/
/*                                                                           */
/*  Function Implementations                                                 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Constructor                                                             */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
CSQLFund::CSQLFund(QString sqlname)
{
    // 建立数据库
    if (QSqlDatabase::contains("qt_sql_fund_connection"))
    {
        database = QSqlDatabase::database("qt_sql_fund_connection");
    }
    else
    {        
        database = QSqlDatabase::addDatabase("QSQLITE", "qt_sql_fund_connection");
        database.setDatabaseName(sqlname);
        database.setUserName(SQL_USER_NAME);
        database.setPassword(SQL_PASSWORD);

        if (!database.open(SQL_USER_NAME, SQL_PASSWORD))
        {
            printf("Error: Failed to connect database.(%d)\n",database.lastError().number());
        }
        else
        {   
            // 判断,不存在则创建配置表          
            if(!checkTableExist(NAME_TABLE_CONFIG))
            {   
                QSqlQuery sql_query = QSqlQuery(database);
                QString create_sql;
                create_sql.sprintf("create table %s (" \
                                   "id int primary key    NOT NULL," \
                                   "serNum   int          NOT NULL);",
                                   NAME_TABLE_CONFIG);
                sql_query.prepare(create_sql);
                if(!sql_query.exec())
                {
                    printf("Error: Fail to create table.(%d)\n",sql_query.lastError().number());
                }
                else
                {
                    printf("Table created!\n");
                    QString insert_sql;
                    insert_sql.sprintf("INSERT INTO %s(id, serNum) " \
                               "VALUES (%d, %d);", NAME_TABLE_CONFIG, 1, 1);
            
                    if(!sql_query.exec(insert_sql))
                    {
                        printf("Error: Failed to update database.(%d)\n",sql_query.lastError().number());
                    }
                    else
                    {
                        //插入数据
                        printf("insert success\n");
                    }            
                }
            }

            // 判断,不存在则创建代码表            
            if(!checkTableExist(NAME_TABLE_CODE))
            {   
                QSqlQuery sql_query = QSqlQuery(database);
                QString create_sql;
                create_sql.sprintf("create table %s (" \
                                   "id int primary key    NOT NULL," \
                                   "fundCode text         NOT NULL," \
                                   "date     text         NOT NULL);",
                                   NAME_TABLE_CODE);

                //printf("%s\n", qPrintable(create_sql));
                sql_query.prepare(create_sql);
                if(!sql_query.exec())
                {
                    printf("Error: Fail to create table.(%d)\n",sql_query.lastError().number());
                }
                else
                {
                    printf("Table created!\n");
                }
            }            
        
            // 判断,不存在则创建买入库存表            
            if(!checkTableExist(NAME_TABLE_STORE))
            {   
                QSqlQuery sql_query = QSqlQuery(database);
                QString create_sql;
                create_sql.sprintf("create table %s (" \
                                   "id int primary key    NOT NULL," \
                                   "date     text         NOT NULL," \
                                   "fundCode integer      NOT NULL," \
                                   "price    float        NOT NULL,"  \
                                   "quotient float        NOT NULL," \
                                   "fare     float        NOT NULL," \
                                   "total    float        NOT NULL," \
                                   "flag_sell    CHAR);",
                                   NAME_TABLE_STORE);

                //printf("%s\n", qPrintable(create_sql));
                sql_query.prepare(create_sql);
                if(!sql_query.exec())
                {
                    printf("Error: Fail to create table.(%d)\n",sql_query.lastError().number());
                }
                else
                {
                    printf("Table created!\n");
                }
            }

            // 判断,不存在则创建买入库存表
            if(!checkTableExist(NAME_TABLE_SELL))
            {   
                QSqlQuery sql_query = QSqlQuery(database);
                QString create_sql;
                create_sql.sprintf("create table %s (" \
                                   "id int primary key    NOT NULL," \
                                   "fundCode      integer      NOT NULL," \
                                   "date_buy      text         NOT NULL," \
                                   "date_sell     text         NOT NULL," \
                                   "price_buy     float        NOT NULL,"  \
                                   "price_sell    float        NOT NULL,"  \
                                   "quotient      float        NOT NULL," \
                                   "fare_buy      float        NOT NULL," \
                                   "fare_sell     float        NOT NULL," \
                                   "total_buy     float        NOT NULL," \
                                   "total_sell    float        NOT NULL);",
                                   NAME_TABLE_SELL);

                //printf("%s\n", qPrintable(create_sql));
                sql_query.prepare(create_sql);
                if(!sql_query.exec())
                {
                    printf("Error: Fail to create table.(%d)\n",sql_query.lastError().number());
                }
                else
                {
                    printf("Table created!\n");
                }
            }
        }
    }
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Destructor                                                              */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
CSQLFund::~CSQLFund()
{
    database.close();
}

bool CSQLFund::getCountRows(QString tableName, quint32& count)
{
    bool bRet = false;
    QSqlQuery query(database);
    QString str_sql = QString("select count(*) from %1;").arg(tableName);
    query.exec(str_sql);
    if(query.next())
    {
        count = query.value(0).toInt();        
    }
    return bRet;
}

// 判断表是否存在
bool CSQLFund::checkTableExist(QString tableName)
{
    bool bRet = false;
    QSqlQuery query(database);
    QString str_sql = QString("select count(*) from sqlite_master where type='table' and name='%1';").arg(tableName);
    query.exec(str_sql);
    if(query.next())
    {
        if(query.value(0).toInt()==0)
        {
            printf("table does not exist\n");
        }
        else
        {
            printf("table exists\n");
            bRet = true;
        }
    }
    return bRet;
}

bool CSQLFund::AddStore(const QString tableName, StStore storeInfo)
{
    int serNum = 0;
    bool bRet = getSerNum(NAME_TABLE_CONFIG, serNum);

    accessMutex.lock();
    if (!database.open(SQL_USER_NAME, SQL_PASSWORD))
    {
        printf("Error: Failed to connect database.(%d)\n",database.lastError().number());
    }
    else
    {
        if(checkTableExist(tableName))
        {                        
            if(bRet)
            {       
                QSqlQuery sql_query = QSqlQuery(database);
                QString insert_sql;
                insert_sql.sprintf("INSERT INTO %s (id, date, fundCode, price, quotient, fare, total) " \
                                   "VALUES (%d, %s, %d, %f, %f, %f, %f);", qPrintable(tableName), serNum, qPrintable(storeInfo.date),
                                   storeInfo.fundCode, storeInfo.price, storeInfo.quotient, storeInfo.fare, storeInfo.total);

                printf("%s\n", qPrintable(insert_sql));
                
                if(!sql_query.exec(insert_sql))
                {
                    printf("Error: Failed to update database.(%d)\n",sql_query.lastError().number());
                }
                else
                {
                    //插入数据
                    printf("insert success\n");
                    bRet = true;                    
                }
            }
        }
    }
    accessMutex.unlock();

    if(bRet)
    {
        serNum++;
        updateSerNum(NAME_TABLE_CONFIG, serNum);
    }

    return bRet;
}

bool CSQLFund::AddSell(const QString tableName, StSellInfo info)
{    
    bool bRet = false;
    accessMutex.lock();
    if (!database.open(SQL_USER_NAME, SQL_PASSWORD))
    {
        printf("Error: Failed to connect database.(%d)\n",database.lastError().number());
    }
    else
    {
        if(checkTableExist(tableName))
        { 
            quint32 serNum = 0;
            getCountRows(tableName, serNum);
            serNum++;
        
            QSqlQuery sql_query = QSqlQuery(database);
            QString insert_sql;
            insert_sql.sprintf("INSERT INTO %s (id, fundCode, date_buy, date_sell, price_buy, price_sell, " \
                               "quotient, fare_buy, fare_sell, total_buy, total_sell) " \
                               "VALUES (%d, %d, %s, %s, %f, %f, %f, %f, %f, %f, %f);", 
                               qPrintable(tableName), serNum, info.fundCode,
                               qPrintable(info.date_buy), qPrintable(info.date_sell),
                               info.price_buy, info.price_sell, info.quotient,
                               info.fare_buy, info.fare_sell,
                               info.total_buy, info.total_sell);

            printf("%s\n", qPrintable(insert_sql));
            
            if(!sql_query.exec(insert_sql))
            {
                printf("Error: Failed to update database.(%d)\n",sql_query.lastError().number());
            }
            else
            {
                //插入数据
                printf("insert success\n");
                bRet = true;                    
            }
        }
    }

    accessMutex.unlock();
    
    return bRet;
}

bool CSQLFund::getSerNum(const QString tableName, int& serNum)
{
    bool bRet = false;
    accessMutex.lock();
    if (!database.open(SQL_USER_NAME, SQL_PASSWORD))
    {
        printf("Error: Failed to connect database.(%d)\n",database.lastError().number());
    }
    else
    {
        if(checkTableExist(tableName))
        {            
            // do something
            QSqlQuery sql_query = QSqlQuery(database);
            QString select_sql = QString("select serNum from %1 where id=%2;").arg(tableName).arg("1");
            //printf("select_sql=%s\n", qPrintable(select_sql));
            if(!sql_query.exec(select_sql))
            {
                printf("Error: Fail to select valure.(%d)\n",sql_query.lastError().number());
            }
            else
            {
                while(sql_query.next())
                {
                    serNum = sql_query.value(0).toInt();
                    bRet = true;
                }            
            }
        }
    }
    accessMutex.unlock();

    return bRet;
}

bool CSQLFund::getCodeInfo(QString code, QString& name)
{
    bool bRet = false;
    
    if (!database.open(SQL_USER_NAME, SQL_PASSWORD))
    {
        printf("Error: Failed to connect database.(%d)\n",database.lastError().number());
    }
    else
    {
        if(checkTableExist(NAME_TABLE_CODE))
        {            
            // do something
            QSqlQuery sql_query = QSqlQuery(database);
            QString select_sql = QString("select name from %1 where fundCode='%2';").arg(NAME_TABLE_CODE).arg(code);
            //printf("select_sql=%s\n", qPrintable(select_sql));
            if(!sql_query.exec(select_sql))
            {
                printf("Error: Fail to select valure.(%d)\n",sql_query.lastError().number());
            }
            else
            {
                while(sql_query.next())
                {
                    name = sql_query.value(0).toString();
                    bRet = true;
                }            
            }
        }
    }    

    return bRet;
}

bool CSQLFund::updateSerNum(const QString tableName, int serNum)
{
    bool bRet = false;

    accessMutex.lock();
    if (!database.open(SQL_USER_NAME, SQL_PASSWORD))
    {
        printf("Error: Failed to connect database.(%d)\n",database.lastError().number());
    }
    else
    {
        if(checkTableExist(tableName))
        {            
            QSqlQuery sql_query = QSqlQuery(database);
            QString select_sql = QString("update %1 set serNum = %2 where id=1;").arg(tableName).arg(serNum);
            //printf("%s",qPrintable(dirPath))

            if(!sql_query.exec(select_sql))
            {
                printf("Error: Failed to update database.(%d)\n",sql_query.lastError().number());
            }
            else
            {
                printf("updateSerNum() success\n");
                bRet = true;
            }
        }
    }
    accessMutex.unlock();

    return bRet;
}

bool CSQLFund::getAccoutInfo(QList<StCodeInfo>& info)
{
    bool bRet = false;
    accessMutex.lock(); 
    if (!database.open(SQL_USER_NAME, SQL_PASSWORD))
    {
        printf("Error: Failed to connect database.(%d)\n",database.lastError().number());
    }
    else
    {
        QString select_sql = QString("select * from %1;").arg(NAME_TABLE_STORE);
        //printf("%s\n",qPrintable(select_sql));
        QSqlQuery sql_query(select_sql, database);
        QSqlRecord rec = sql_query.record();
        
        quint32 tempFundCode;
        bool bFound = false;
        StCodeInfo codeInfo;        
        while(sql_query.next())
        {
            bFound = false;
            tempFundCode = sql_query.value(2).toUInt();
            for(int i = 0; i < info.size(); i++)
            {
                codeInfo = info.at(i);
                if(codeInfo.fundCode == tempFundCode)
                {
                    codeInfo.quotient += sql_query.value(4).toFloat();
                    codeInfo.total += sql_query.value(6).toFloat();
                    info.replace(i, codeInfo);
                    bFound = true;
                    break;
                }                
            }

            if(!bFound)
            {
                codeInfo.fundCode = tempFundCode;
                codeInfo.quotient = sql_query.value(4).toFloat();
                codeInfo.total = sql_query.value(6).toFloat();
                // 获得名字
                QString code;
                code.setNum(codeInfo.fundCode, 16);
                getCodeInfo(code, codeInfo.name);
                info.append(codeInfo);
                bRet = true;                
            }
        }     
    }
    accessMutex.unlock();

    return bRet;
}

bool CSQLFund::getStoreInfo(const QString tableName, QString condition, QList<StStore>& storeList)
{
    bool bRet = false;
    accessMutex.lock(); 
    if (!database.open(SQL_USER_NAME, SQL_PASSWORD))
    {
        printf("Error: Failed to connect database.(%d)\n",database.lastError().number());
    }
    else
    {
        QString select_sql = QString("select * from %1 %2;").arg(tableName).arg(condition);
        //printf("%s\n",qPrintable(select_sql));
        QSqlQuery sql_query(select_sql, database);
        QSqlRecord rec = sql_query.record();

        StStore storeInfo;
        while(sql_query.next())
        {
            storeInfo.serNum = sql_query.value(0).toUInt();
            storeInfo.date = sql_query.value(1).toString();
            storeInfo.fundCode = sql_query.value(2).toUInt();
            storeInfo.price = sql_query.value(3).toFloat();
            storeInfo.quotient = sql_query.value(4).toFloat();
            storeInfo.fare = sql_query.value(5).toFloat();
            storeInfo.total = sql_query.value(6).toFloat();
            storeInfo.flag_sell = sql_query.value(7).toFloat();
            storeList.append(storeInfo);
            bRet = true;
        }
    }
    accessMutex.unlock();

    return bRet;
}

bool CSQLFund::getSellInfo(const QString tableName, QString condition, QList<StSellInfo>& sellList)
{
    bool bRet = false;
    accessMutex.lock(); 
    if (!database.open(SQL_USER_NAME, SQL_PASSWORD))
    {
        printf("Error: Failed to connect database.(%d)\n",database.lastError().number());
    }
    else
    {
        QString select_sql = QString("select * from %1 %2;").arg(tableName).arg(condition);
        //printf("%s\n",qPrintable(select_sql));
        QSqlQuery sql_query(select_sql, database);
        QSqlRecord rec = sql_query.record();

        StSellInfo info;
        while(sql_query.next())
        {
            info.serNum = sql_query.value(0).toUInt();
            info.fundCode = sql_query.value(1).toUInt();
            info.date_buy = sql_query.value(2).toString();
            info.date_sell = sql_query.value(3).toString();
            info.price_buy = sql_query.value(4).toFloat(); 
            info.price_sell = sql_query.value(5).toFloat();
            info.quotient = sql_query.value(6).toFloat();            
            info.fare_buy = sql_query.value(7).toFloat();
            info.fare_sell = sql_query.value(8).toFloat();
            info.total_buy = sql_query.value(9).toFloat();
            info.total_sell = sql_query.value(10).toFloat();
            
            sellList.append(info);
            bRet = true;
        }
    }
    accessMutex.unlock();

    return bRet;
}

bool CSQLFund::updateStoreFlag(const QString tableName, quint32 id)
{
    bool bRet = false;

    accessMutex.lock();
    if (!database.open(SQL_USER_NAME, SQL_PASSWORD))
    {
        printf("Error: Failed to connect database.(%d)\n",database.lastError().number());
    }
    else
    {
        if(checkTableExist(tableName))
        {            
            QSqlQuery sql_query = QSqlQuery(database);
            QString select_sql = QString("update %1 set flag_sell = %2 where id=%5;").arg(tableName)
                                         .arg(1).arg(id);                                         

            if(!sql_query.exec(select_sql))
            {
                printf("Error: Failed to update database.(%d)\n",sql_query.lastError().number());
            }
            else
            {
                printf("updateStoreInfo() success\n");
                bRet = true;
            }
        }
    }
    accessMutex.unlock();

    return bRet;
}

bool CSQLFund::updateStoreInfo(const QString tableName, StStore storeInfo)
{
    bool bRet = false;

    accessMutex.lock();
    if (!database.open(SQL_USER_NAME, SQL_PASSWORD))
    {
        printf("Error: Failed to connect database.(%d)\n",database.lastError().number());
    }
    else
    {
        if(checkTableExist(tableName))
        {            
            QSqlQuery sql_query = QSqlQuery(database);
            QString select_sql = QString("update %1 set quotient = %2, " \
                                         "fare = %3, total = %4 where id=%5;").arg(tableName)
                                         .arg(storeInfo.quotient).arg(storeInfo.fare)
                                         .arg(storeInfo.total).arg(storeInfo.serNum);                                         

            if(!sql_query.exec(select_sql))
            {
                printf("Error: Failed to update database.(%d)\n",sql_query.lastError().number());
            }
            else
            {
                printf("updateStoreInfo() success\n");
                bRet = true;
            }
        }
    }
    accessMutex.unlock();

    return bRet;
}

bool CSQLFund::deleteStoreInfo(const QString tableName, quint32 serNum)
{
    bool bRet = false;

    accessMutex.lock();
    if (!database.open(SQL_USER_NAME, SQL_PASSWORD))
    {
        printf("Error: Failed to connect database.(%d)\n",database.lastError().number());
    }
    else
    {
        if(checkTableExist(tableName))
        {            
            QSqlQuery sql_query = QSqlQuery(database);
            QString select_sql = QString("delete from %1 where id=%2;").arg(tableName).arg(serNum);

            if(!sql_query.exec(select_sql))
            {
                printf("Error: Failed to delete database.(%d)\n",sql_query.lastError().number());
            }
            else
            {
                printf("deleteStoreInfo() success\n");
                bRet = true;
            }
        }
    }
    accessMutex.unlock();

    return bRet;
}

