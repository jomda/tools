#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QListView>
#include <QPushButton>
#include <QProcess>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QUrlInfo>
#include <QTableView>
#include <QStatusBar>
#include <QWidget>
#include "SQLConfig.h"

typedef enum
{
    TYPE_DOUBLE_CLICK_SELL,
    TYPE_DOUBLE_CLICK_SEARCH,
} EDoubleClickType;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void InitUI();
	void UpdateStoreTable(bool bSearch, QList<StStore> storeList);
	void UpdateSellTable(QList<StSellInfo> sellList);
	void UpdateAccountTable(QList<StCodeInfo> info);

public slots:
	void SlotAdd();
	void SlotSearch();
	void SlotStore();
	void SlotHistory();
    void SlotDoubleClickItem(QModelIndex);
	void SlotAccount();

signals:
	void getStoreAgain();

private:
    QWidget* widget;
	CSQLFund* pCSQLFund;	
	QLineEdit* le_Date;
    QLineEdit* le_FundCode;
    QLineEdit* le_price;
    QLineEdit* le_quotient;
	QLineEdit* le_fare;
	QLineEdit* le_total;
	QLineEdit* le_evaluate;
	QLineEdit* le_targetRate;
	QLineEdit* le_date_hold;
    QPushButton* btn_add;
	QPushButton* btn_search;
	QPushButton* btn_store;
	QPushButton* btn_history;
	QPushButton* btn_account;

    QTableView* tv_file;

    QStatusBar* statusBar;

    QStandardItemModel *standardItemModel;//ÉùÃ÷model

	EDoubleClickType doubleClickType;

	void Trade_sell(StStore info);
	void Trade_search(quint32 fundCode);
	void setStoreModelColor(bool bSearch, quint8 count, quint8 r, quint8 g, quint8 b);
};

#endif // MAINWINDOW_H
