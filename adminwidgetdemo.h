#ifndef ADMINWIDGETDEMO_H
#define ADMINWIDGETDEMO_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QList>
#include <QVector>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

#define COLUMN_COUNT 4  //列数

QT_BEGIN_NAMESPACE
namespace Ui { class AdminWidgetDemo; }
QT_END_NAMESPACE

class AdminWidgetDemo : public QWidget
{
    Q_OBJECT

public:
    AdminWidgetDemo(QWidget *parent = nullptr);
    ~AdminWidgetDemo();

    /**
     * @brief initTableWidget   初始化树控件
     */
    void initTableWidget();

    /**
     * @brief DisplayUserInfo   在tablewidget上显示用户信息
     * @param userName
     * @param userPassword
     */
    void DisplayUserInfo(QList<QString> userName,QList<QString> userPassword);

    /**
     * @brief deleteButtons     删除按钮
     */
    void deleteButtons();

    /**
     * @brief displayBtnVec     展示按钮
     */
    void displayBtnVec();

    /**
     * @brief showTableData     展示数据
     */
    void showTableData();

signals:
    /**
     * @brief SendDeleteUserInfo    发送删除信号
     * @param userName
     * @param userPassword
     */
    void  SendDeleteUserInfo(QString userName,QString userPassword);

    /**
     * @brief SendModifyUserInfo    发送修改信号，带2个参数
     * @param userName
     * @param userPassword
     */
    void  SendModifyUserInfo(QString userName,QString userPassword);

public slots:
    /**
     * @brief BtnDel_clicked    点击删除按钮
     */
    void BtnDel_clicked();

    /**
     * @brief BtnUpdate_clicked 点击修改按钮
     */
    void BtnUpdate_clicked();

    /**
    * @brief close
    */
    void close();

private:
    Ui::AdminWidgetDemo *ui;

    QStringList strs = {"用户名","密码","删除","更新"};
    QFont nullFont;
    QVector<QTableWidgetItem*> listTem;
    QVector<QPushButton*>  btnVec;  //定义这个按钮指针容器的目的是为了方便一次性释放按钮内存
};
#endif // ADMINWIDGETDEMO_H
