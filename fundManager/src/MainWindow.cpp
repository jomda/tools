#include "MainWindow.h"
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QtGlobal>

#include <QFileDialog>
#include "sell.h"

#define MAJOR_VERSION    1
#define MINOR_VERSION    0

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    pCSQLFund = new CSQLFund(NAME_DB);        
    widget = new QWidget();
    this->setCentralWidget(widget);
    setWindowTitle(tr("基金管理软件_V%1.%2").arg(MAJOR_VERSION).arg(MINOR_VERSION));
    InitUI();
}

MainWindow::~MainWindow()
{
    // deinitialise disk monitor
    if(pCSQLFund)
    {        
        delete pCSQLFund;
        pCSQLFund = NULL;
    }

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

    if(le_evaluate)
    {
        delete le_evaluate;
        le_evaluate = NULL;
    }

    if(le_targetRate)
    {
        delete le_targetRate;
        le_targetRate = NULL;
    }

    if(btn_add)
    {
        delete btn_add;
        btn_add = NULL;
    }

    if(btn_search)
    {
        delete btn_search;
        btn_search = NULL;
    }

    if(btn_store)
    {
        delete btn_store;
        btn_store = NULL;
    }

    if(btn_history)
    {
        delete btn_history;
        btn_history = NULL;
    }

    if(statusBar)
    {
        delete statusBar;
        statusBar = NULL;
    }

    if(standardItemModel)
    {
        delete standardItemModel;
        standardItemModel = NULL;
    }

    if(tv_file)
    {
        delete tv_file;
        tv_file = NULL;
    }   
}

void MainWindow::InitUI()
{
    //  购买添加
    QHBoxLayout* h_layout1 = new QHBoxLayout();
    QLabel* l_Date = new QLabel("成交时间:");
    le_Date = new QLineEdit();
    QString date = QDateTime::currentDateTime().toString("yyyyMMdd");
    le_Date->setText(date);
    QLabel* l_FundCode = new QLabel("基金代码:");
    le_FundCode = new QLineEdit();
    le_FundCode->setText("004746");
    QLabel* l_price = new QLabel("成交净值:");
    le_price = new QLineEdit();
    le_price->setText("1.0000");
    QLabel* l_quotient = new QLabel("成交份额:");
    le_quotient = new QLineEdit();
    le_quotient->setText("01.00");
    QLabel* l_fare = new QLabel("手续费:");
    le_fare = new QLineEdit();
    le_fare->setText("0.00");
    QLabel* l_total = new QLabel("成交金额:");
    le_total = new QLineEdit();
    le_total->setText("1.00");  
    btn_add = new QPushButton("新增");
    connect(btn_add, SIGNAL(clicked(bool)), this, SLOT(SlotAdd()));
    h_layout1->addWidget(l_Date);
    h_layout1->addWidget(le_Date);
    h_layout1->addWidget(l_FundCode);
    h_layout1->addWidget(le_FundCode);
    h_layout1->addWidget(l_price);
    h_layout1->addWidget(le_price);
    h_layout1->addWidget(l_quotient);
    h_layout1->addWidget(le_quotient);
    h_layout1->addWidget(l_fare);
    h_layout1->addWidget(le_fare);
    h_layout1->addWidget(l_total);
    h_layout1->addWidget(le_total);
    h_layout1->addWidget(btn_add);
    // 输入预估净值、目标收益率，搜索满足条件的库存
    QHBoxLayout* h_layout2 = new QHBoxLayout();
    QLabel* l_evaluate = new QLabel("预估净值:");
    le_evaluate = new QLineEdit();
    le_evaluate->setText("1.0000");
    QLabel* l_targetRate1 = new QLabel("目标收益率:");
    QLabel* l_targetRate2 = new QLabel("%");
    le_targetRate = new QLineEdit();
    le_targetRate->setText("1.00");
    
    QLabel* l_date_hold = new QLabel("最小持有天数:");
    le_date_hold = new QLineEdit();
    le_date_hold->setText("7");
    
    btn_search = new QPushButton("搜索");
    connect(btn_search, SIGNAL(clicked(bool)), this, SLOT(SlotSearch()));
    h_layout2->addWidget(l_evaluate);
    h_layout2->addWidget(le_evaluate);
    h_layout2->addWidget(l_targetRate1);
    h_layout2->addWidget(le_targetRate);
    h_layout2->addWidget(l_targetRate2);     
    h_layout2->addWidget(l_date_hold);
    h_layout2->addWidget(le_date_hold);
    h_layout2->addWidget(btn_search);
    
    // 查看库存、查看卖出历史记录
    btn_store = new QPushButton("库存");
    connect(btn_store, SIGNAL(clicked(bool)), this, SLOT(SlotStore()));
    connect(this, SIGNAL(getStoreAgain()), this, SLOT(SlotStore()));
    btn_history = new QPushButton("卖出记录");
    connect(btn_history, SIGNAL(clicked(bool)), this, SLOT(SlotHistory()));
    btn_account = new QPushButton("库存总计");
    connect(btn_account, SIGNAL(clicked(bool)), this, SLOT(SlotAccount()));
    h_layout2->addWidget(btn_store);
    h_layout2->addWidget(btn_history);
    h_layout2->addWidget(btn_account);

    tv_file = new QTableView();
    standardItemModel = new QStandardItemModel();
    QStringList labels = QObject::trUtf8("流水号, 成交时间, 基金代码, 成交净值, 成交份额, 手续费, 成交金额").simplified().split(",");
    standardItemModel->setHorizontalHeaderLabels(labels);
    tv_file->setModel(standardItemModel);

    tv_file->setContextMenuPolicy(Qt::CustomContextMenu);
    tv_file->setSelectionBehavior(QAbstractItemView::SelectRows);
//    tv_file->setSelectionMode(QAbstractItemView::MultiSelection);
    tv_file->setSelectionMode(QAbstractItemView::SingleSelection);
    tv_file->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tv_file->setFont(QFont("Helvetica"));

    tv_file->setStyleSheet("QTableView{  \
                                    background:rgb(255,255,255);  \
                                    gridline-color : rgb(0, 0, 0);  \
                                    selection-background-color:rgb(0,0,255);  \
                                       }");
    for(int i = 0; i < 30; i++)
        tv_file->setColumnWidth(i,100);
    
    tv_file->setShowGrid(true);

    connect(tv_file,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(SlotDoubleClickItem(QModelIndex)));

    QVBoxLayout* v_layout = new QVBoxLayout(widget);
    v_layout->addLayout(h_layout1);
    v_layout->addLayout(h_layout2);
    v_layout->addWidget(tv_file);
    
    QHBoxLayout* h_layout3 = new QHBoxLayout();
    h_layout3->addStretch();    
    v_layout->addLayout(h_layout3);
    statusBar = new QStatusBar();
    QHBoxLayout* h_layout_bottom = new QHBoxLayout();
    h_layout_bottom->addWidget(statusBar);
    v_layout->addLayout(h_layout_bottom);

    SlotAccount();
}

void MainWindow::UpdateStoreTable(bool bSearch, QList<StStore> storeList)
{
    standardItemModel->clear();
    QStringList labels;
    bool ok;
    
    if(bSearch)
    {
        labels = QObject::trUtf8("流水号, 成交时间, 基金代码, 成交净值, 成交份额, 手续费, 成交金额, 持有天数, 收益率").simplified().split(",");      
    }
    else{
        labels = QObject::trUtf8("流水号, 成交时间, 基金代码, 成交净值, 成交份额, 手续费, 成交金额, 持有天数").simplified().split(",");
    }
    standardItemModel->setHorizontalHeaderLabels(labels);
    tv_file->setModel(standardItemModel);    
    tv_file->setColumnWidth(1,100);
    
    for(int i = 0;i < storeList.size();i++)
    {    
        QString temp;
        QStandardItem* item1 = new QStandardItem(temp.setNum(storeList[i].serNum, 10));
        item1->setTextAlignment(Qt::AlignCenter);
        standardItemModel->setItem(i,0,item1);
        
        QStandardItem* item2 = new QStandardItem(storeList[i].date);
        item2->setTextAlignment(Qt::AlignCenter);
        standardItemModel->setItem(i,1,item2);
        
        temp.sprintf("%06x", storeList[i].fundCode);
        QStandardItem* item3 = new QStandardItem(temp);
        item3->setTextAlignment(Qt::AlignCenter);
        standardItemModel->setItem(i,2,item3);
        
        QStandardItem* item4 = new QStandardItem(temp.setNum(storeList[i].price));
        item4->setTextAlignment(Qt::AlignCenter);
        standardItemModel->setItem(i,3,item4);
        
        QStandardItem* item5 = new QStandardItem(temp.setNum(storeList[i].quotient));
        item5->setTextAlignment(Qt::AlignCenter);
        standardItemModel->setItem(i,4,item5);
        
        QStandardItem* item6 = new QStandardItem(temp.setNum(storeList[i].fare, 'f', 2));
        item6->setTextAlignment(Qt::AlignCenter);
        standardItemModel->setItem(i,5,item6);
        
        QStandardItem* item7 = new QStandardItem(temp.setNum(storeList[i].total, 'f', 2));
        item7->setTextAlignment(Qt::AlignCenter);
        standardItemModel->setItem(i,6,item7);
        
        // 持有天数
        QDate current_day = QDate::currentDate();
        QDate buy_day = QDate::fromString(storeList[i].date, "yyyyMMdd");
        int day_hold = buy_day.daysTo(current_day);
        QStandardItem* item8 = new QStandardItem(temp.setNum(day_hold, 10));
        item8->setTextAlignment(Qt::AlignCenter);
        standardItemModel->setItem(i,7,item8);

        if(bSearch)
        {            
            float price_target = le_evaluate->text().toFloat(&ok);
            float price_persent = ((price_target - storeList[i].price)/storeList[i].price)*100;
            QStandardItem* item9 = new QStandardItem(temp.setNum(price_persent, 'f', 3)+"%");
            item9->setTextAlignment(Qt::AlignCenter);
            standardItemModel->setItem(i,8,item9);
        }

        if(storeList[i].flag_sell) // �Ƿ�������
        {
            // ��ɫ
            setStoreModelColor(bSearch, i, 255, 255, 0);            
        }
        else
        {
            if((uint)qAbs(day_hold) >= le_date_hold->text().toUInt(&ok, 10))
            {
                // ��ɫ
                setStoreModelColor(bSearch, i, 255, 0, 0);
            }
            else
            {
                //��ɫ
                setStoreModelColor(bSearch, i, 0, 255, 0);
            }
        }
    }
    
    doubleClickType = TYPE_DOUBLE_CLICK_SELL;
}

void MainWindow::UpdateSellTable(QList<StSellInfo> sellList)
{
    standardItemModel->clear();
    QStringList labels = QObject::trUtf8("流水号, 基金代码, 买入时间, 卖出时间, 买入净值, 卖出净值, 交易份额, 买入手续费, 卖出手续费, 买入金额, 卖出金额").simplified().split(",");
    standardItemModel->setHorizontalHeaderLabels(labels);
    tv_file->setModel(standardItemModel);
    tv_file->setColumnWidth(1,100);
    
    for(int i = 0;i < sellList.size();i++)
    {    
        QString temp;
        QStandardItem* item1 = new QStandardItem(temp.setNum(sellList[i].serNum, 10));
        standardItemModel->setItem(i,0,item1);
        temp.sprintf("%06x", sellList[i].fundCode);
        QStandardItem* item2 = new QStandardItem(temp);
        standardItemModel->setItem(i,1,item2);        
        QStandardItem* item3 = new QStandardItem(sellList[i].date_buy);
        standardItemModel->setItem(i,2,item3);
        QStandardItem* item4 = new QStandardItem(sellList[i].date_sell);
        standardItemModel->setItem(i,3,item4);
        QStandardItem* item5 = new QStandardItem(temp.setNum(sellList[i].price_buy));
        standardItemModel->setItem(i,4,item5);
        QStandardItem* item6 = new QStandardItem(temp.setNum(sellList[i].price_sell));
        standardItemModel->setItem(i,5,item6);
        QStandardItem* item7 = new QStandardItem(temp.setNum(sellList[i].quotient));
        standardItemModel->setItem(i,6,item7);
        QStandardItem* item8 = new QStandardItem(temp.setNum(sellList[i].fare_buy, 'f', 2));
        standardItemModel->setItem(i,7,item8);
        QStandardItem* item9 = new QStandardItem(temp.setNum(sellList[i].fare_sell, 'f', 2));
        standardItemModel->setItem(i,8,item9);
        QStandardItem* item10 = new QStandardItem(temp.setNum(sellList[i].total_buy, 'f', 2));
        standardItemModel->setItem(i,9,item10);
        QStandardItem* item11 = new QStandardItem(temp.setNum(sellList[i].total_sell, 'f', 2));
        standardItemModel->setItem(i,10,item11);
    }

    doubleClickType = TYPE_DOUBLE_CLICK_SELL;
}

void MainWindow::UpdateAccountTable(QList<StCodeInfo> info)
{
    standardItemModel->clear();
    QStringList labels = QObject::trUtf8("代码, 名称, 份额, 金额, 平均单价").simplified().split(",");
    standardItemModel->setHorizontalHeaderLabels(labels);
    tv_file->setModel(standardItemModel);
    tv_file->setColumnWidth(1,200);
    
    for(int i = 0;i < info.size();i++)
    {    
        QString temp;
        temp.sprintf("%06x", info[i].fundCode);
        QStandardItem* item1 = new QStandardItem(temp);
        standardItemModel->setItem(i,0,item1);
        QStandardItem* item2 = new QStandardItem(info[i].name);
        standardItemModel->setItem(i,1,item2);
        QStandardItem* item3 = new QStandardItem(temp.setNum(info[i].quotient));
        standardItemModel->setItem(i,2,item3);
        QStandardItem* item4 = new QStandardItem(temp.setNum(info[i].total));
        standardItemModel->setItem(i,3,item4); 
		QStandardItem* item5 = new QStandardItem(temp.setNum(info[i].total/info[i].quotient));
        standardItemModel->setItem(i,4,item5);
    }

    doubleClickType = TYPE_DOUBLE_CLICK_SEARCH;
}

void MainWindow::SlotAdd()
{   
    statusBar->showMessage( "添加记录");

    bool bRet = false;
    if(pCSQLFund)
    {    
        bool ok;
        StStore addFundInfo;
        addFundInfo.date = le_Date->text();
        addFundInfo.fundCode = le_FundCode->text().toUInt(&ok, 16);
        addFundInfo.price = le_price->text().toFloat(&ok);
        addFundInfo.quotient = le_quotient->text().toFloat(&ok);
        addFundInfo.fare = le_fare->text().toFloat(&ok);
        addFundInfo.total = le_total->text().toFloat(&ok);
        
        bRet = pCSQLFund->AddStore(NAME_TABLE_STORE, addFundInfo);
    }

    QString disStr = "添加记录成功";
    if(!bRet)
    {
        disStr = "添加记录失败";
    }
    else
    {
        emit getStoreAgain();
    }
    statusBar->showMessage(disStr);    
}

void MainWindow::SlotSearch()
{
    bool bRet = false;
    bool ok;
    statusBar->showMessage("搜索库存中");

    QList<StStore> storeList;
    float price_target = 0;
    QString QFundCode = le_FundCode->text();
    quint32 fundCode = QFundCode.toUInt(&ok, 16);
    if(pCSQLFund)
    {        
        price_target = le_evaluate->text().toFloat(&ok)/(le_targetRate->text().toFloat(&ok)/100 + 1);
        QString condition = QString("where price <= %1 and fundCode = %2").arg(price_target).arg(fundCode);
        bRet = pCSQLFund->getStoreInfo(NAME_TABLE_STORE, condition, storeList);
    }

    QString disStr = QString("(代码: %1-目标净值:%2) ").arg(QFundCode).arg(price_target);
    if(!bRet)
    {
        disStr += "没有搜索到对应的记录";
        storeList.clear();
    }
    else
    {
        disStr += "搜索完成";        
    }
    UpdateStoreTable(true, storeList);
    statusBar->showMessage(disStr);
}

void MainWindow::SlotStore()
{
    bool bRet = false;
    statusBar->showMessage( "库存加载中");

    QList<StStore> storeList;
    if(pCSQLFund)
    {
        QString condition;
        condition.clear();
        bRet = pCSQLFund->getStoreInfo(NAME_TABLE_STORE, condition, storeList);
    }

    QString disStr = "库存加载完成";
    if(!bRet)
    {
        disStr = "库存记录获取失败";
    }
    else
    {
        UpdateStoreTable(false, storeList);
    }
    statusBar->showMessage(disStr);
}

void MainWindow::SlotAccount()
{
    bool bRet = false;
    statusBar->showMessage( "库存加载中");

    QList<StCodeInfo> info;
    if(pCSQLFund)
    {        
        bRet = pCSQLFund->getAccoutInfo(info);
    }

    QString disStr = "库存加载完成";
    if(!bRet)
    {
        disStr = "库存记录获取失败";
    }
    else
    {
        UpdateAccountTable(info);
    }
    statusBar->showMessage(disStr);
}

void MainWindow::SlotHistory()
{
    bool bRet = false;
    statusBar->showMessage( "卖出记录加载中");
    
    QList<StSellInfo> sellList;
    if(pCSQLFund)
    {
        QString condition;
        condition.clear();
        bRet = pCSQLFund->getSellInfo(NAME_TABLE_SELL, condition, sellList);
    }

    QString disStr = "卖出记录加载完成";
    if(!bRet)
    {
        disStr = "卖出记录记录获取失败";
    }
    else
    {
        UpdateSellTable(sellList);
    }
    statusBar->showMessage(disStr);
}


void MainWindow::SlotDoubleClickItem(QModelIndex modelIndex)
{
    //QStandardItem* item = standardItemModel->item(modelIndex.row(),1);
    bool ok;
    switch(doubleClickType)
    {
        case TYPE_DOUBLE_CLICK_SELL:
            if(1)
            {
                StStore info;
                info.serNum = standardItemModel->item(modelIndex.row(),0)->text().toUInt();
                info.date = standardItemModel->item(modelIndex.row(),1)->text();
                info.fundCode = standardItemModel->item(modelIndex.row(),2)->text().toUInt(&ok, 16);
                info.price = standardItemModel->item(modelIndex.row(),3)->text().toFloat();
                info.quotient = standardItemModel->item(modelIndex.row(),4)->text().toFloat();
                info.fare = standardItemModel->item(modelIndex.row(),5)->text().toFloat();
                info.total = standardItemModel->item(modelIndex.row(),6)->text().toFloat();
                Trade_sell(info);
            }      
            break;
            
        case TYPE_DOUBLE_CLICK_SEARCH:
            if(1)
            {
                quint32 fundCode = standardItemModel->item(modelIndex.row(),0)->text().toUInt(&ok, 16);
                Trade_search(fundCode);
                QString QFundCode;
                QFundCode.sprintf("%06x", fundCode);
                le_FundCode->setText(QFundCode);
            }
            break;
            
        default:
            break;
    }
}

void MainWindow::Trade_sell(StStore info)
{
    sell *sellDialog = new sell(info, this);
    if(sellDialog)
    {
        if(sellDialog->exec())
        {
            StStore getInfo;
            sellDialog->getSellInfo(getInfo);
            if(1 == getInfo.flag_sell)
            {
                if(pCSQLFund)
                {
                    pCSQLFund->updateStoreFlag(NAME_TABLE_STORE, info.serNum);
                }
            }
            else
            {
                if(getInfo.quotient == info.quotient)
                {
                    // ɾ��
                    if(pCSQLFund)
                    {
                        pCSQLFund->deleteStoreInfo(NAME_TABLE_STORE, info.serNum);
                        emit getStoreAgain();
                    }
                }
                else if(getInfo.quotient < info.quotient)
                {
                    StStore updateInfo;
                    updateInfo.serNum = info.serNum;
                    updateInfo.date = info.date;
                    updateInfo.fundCode = info.fundCode;
                    updateInfo.price = info.price;
                    updateInfo.quotient = info.quotient-getInfo.quotient;               
                    updateInfo.fare = (info.fare/info.quotient) * updateInfo.quotient;
                    updateInfo.total = (info.total/info.quotient) * updateInfo.quotient;                   
        
                    // ����
                    if(pCSQLFund)
                    {
                        pCSQLFund->updateStoreInfo(NAME_TABLE_STORE, updateInfo);
                        emit getStoreAgain();
                    }
                }
                else
                {
                    statusBar->showMessage( "无效交易，卖出份额超出当前份额");
                }

                // ���µ������ı���
                if(getInfo.quotient)
                {
                    if(pCSQLFund)
                    {
                        StSellInfo sellInfo;
                        //info.serNum;
                        sellInfo.fundCode = info.fundCode;
                        sellInfo.date_buy = info.date;
                        sellInfo.date_sell = getInfo.date;
                        sellInfo.price_buy = info.price;
                        sellInfo.price_sell = getInfo.price;
                        sellInfo.quotient = info.quotient;
                        sellInfo.fare_buy = info.fare;
                        sellInfo.fare_sell = getInfo.fare;
                        sellInfo.total_buy = info.total;
                        sellInfo.total_sell = getInfo.total;    
                        pCSQLFund->AddSell(NAME_TABLE_SELL, sellInfo);
                    }
                }
            }
        }        
        
        delete sellDialog;
        sellDialog = NULL;
    }
}

// ����ĳֻ����Ŀ��
void MainWindow::Trade_search(quint32 fundCode)
{
    bool bRet = false;
    statusBar->showMessage("搜索库存中");

    QString temp;
    temp.sprintf("%06x", fundCode);
    le_FundCode->setText(temp);
    QList<StStore> storeList;
    if(pCSQLFund)
    {
        QString condition = QString("where fundCode = %1 ORDER BY price DESC").arg(fundCode);
        bRet = pCSQLFund->getStoreInfo(NAME_TABLE_STORE, condition, storeList);
    }

    QString disStr;
    if(!bRet)
    {
        disStr += "没有搜索到对应的记录";
        storeList.clear();
    }
    else
    {
        disStr += "搜索完成";        
    }
    UpdateStoreTable(false, storeList);
    statusBar->showMessage(disStr);
}

void MainWindow::setStoreModelColor(bool bSearch, quint8 count, quint8 r, quint8 g, quint8 b)
{
    standardItemModel->item(count, 0)->setForeground(QBrush(QColor(r, g, b))); 
    standardItemModel->item(count, 1)->setForeground(QBrush(QColor(r, g, b)));
    standardItemModel->item(count, 2)->setForeground(QBrush(QColor(r, g, b))); 
    standardItemModel->item(count, 3)->setForeground(QBrush(QColor(r, g, b))); 
    standardItemModel->item(count, 4)->setForeground(QBrush(QColor(r, g, b))); 
    standardItemModel->item(count, 5)->setForeground(QBrush(QColor(r, g, b))); 
    standardItemModel->item(count, 6)->setForeground(QBrush(QColor(r, g, b)));
    standardItemModel->item(count, 7)->setForeground(QBrush(QColor(r, g, b))); 

    if(bSearch)
    {
        standardItemModel->item(count, 8)->setForeground(QBrush(QColor(r, g, b)));        
    }
}

