#include "adminwidgetdemo.h"
#include "ui_adminwidgetdemo.h"

AdminWidgetDemo::AdminWidgetDemo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminWidgetDemo)
{
    ui->setupUi(this);


    this->setWindowTitle("查看用户");
    this->setWindowFlags(~windowFlags() & Qt::WindowMaximized & Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_DeleteOnClose,true);//设置当单击关闭按钮时，释放创建的窗口的内存空间

    nullFont.setPixelSize(16);
    initTableWidget();
}

AdminWidgetDemo::~AdminWidgetDemo()
{
    delete ui;

    deleteButtons();
    if(ui->tableWidget!=NULL)
    {
        delete ui->tableWidget;
        ui->tableWidget=nullptr;
    }
}

void AdminWidgetDemo::initTableWidget()
{
    ui->tableWidget->setColumnCount(COLUMN_COUNT);
    ui->tableWidget->setHorizontalHeaderLabels(strs);

    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    font.setBold(true);
    font.setPixelSize(16);
    ui->tableWidget->horizontalHeader()->setFont(font);

    /*设置每列表头宽*/
    for(int i = 0; i < ui->tableWidget->columnCount(); i++)
    {
        ui->tableWidget->setColumnWidth(i,200);
    }

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
}

void AdminWidgetDemo::DisplayUserInfo(QList<QString> userName, QList<QString> userPassword)
{
    ui->tableWidget->clearContents();
    if(!btnVec.isEmpty())
    {
        btnVec.clear();
    }

    int rowsNa = userName.size();
    int rowsPwd=userPassword.size();
    if(rowsNa!=rowsPwd)//如果用户数量和密码数量不相等，则退出循环调用
    {
        return;
    }
    ui->tableWidget->setRowCount(rowsNa);

    for(int i = 0; i < rowsNa; i++)
    {
        /*设置用户名*/
        QTableWidgetItem *nameItem = new QTableWidgetItem(tr("%1").arg(userName.at(i)));
        nameItem->setFlags(nameItem->flags() & (~Qt::ItemIsEditable));//第一列不可编辑
        nameItem->setFont(nullFont);
        nameItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 0, nameItem);

        /*设置密码*/
        QTableWidgetItem *pwdItem = new QTableWidgetItem(tr("%1").arg(userPassword.at(i)));
        pwdItem->setTextAlignment(Qt::AlignCenter);
        pwdItem->setFont(nullFont);
        ui->tableWidget->setItem(i, 1, pwdItem);

        /*添加删除按钮*/
        QPushButton* btnDel=new QPushButton("删除");
        btnDel->setFont(nullFont);
        btnDel->setObjectName(QString::number(i));
        ui->tableWidget->setCellWidget(i,2,btnDel);
        btnVec.push_back(btnDel);

        /*修改*/
        QPushButton* btnUpdate=new QPushButton("修改");
        btnUpdate->setFont(nullFont);
        ui->tableWidget->setCellWidget(i,3,btnUpdate);
        btnVec.push_back(btnUpdate);

        connect(btnDel, &QPushButton::clicked, this, &AdminWidgetDemo::BtnDel_clicked);
        connect(btnUpdate, &QPushButton::clicked, this, &AdminWidgetDemo::BtnUpdate_clicked);
    }
}

void AdminWidgetDemo::deleteButtons()
{

    //释放table_user表格中动态申请的QPushButton
    int len=btnVec.length();
    for(int i=0;i<len;i++)
    {
        QPushButton* btnPtr=btnVec.at(i);
        if(btnPtr!=nullptr)
        {
            delete btnPtr;
            btnPtr=nullptr;
        }
    }
}

void AdminWidgetDemo::displayBtnVec()
{

    int len=btnVec.size();
    for(int i=0;i<len;i++)
    {
        QPushButton* btnPtr=btnVec.at(i);
        if(btnPtr!=nullptr)
        {
            qDebug()<<btnPtr;
        }
    }
}

void AdminWidgetDemo::showTableData()
{

    QString name;
    QString pwd;
    int permission;
    qDebug()<<"测试表格中的数据是否正确?";
    int row=ui->tableWidget->rowCount();
    for(int i=0;i<row;i++)
    {
        name=ui->tableWidget->item(i,0)->text();
        pwd=ui->tableWidget->item(i,1)->text();
        permission=ui->tableWidget->item(i,2)->text().toUInt();
        qDebug()<<name<<pwd<<permission;
    }
}
void AdminWidgetDemo::BtnDel_clicked()
{
    QPushButton* obj=qobject_cast<QPushButton*>(sender());
    int x=obj->frameGeometry().x();
    int y=obj->frameGeometry().y();

    QModelIndex index=ui->tableWidget->indexAt(QPoint(x,y));

    int row=index.row();
    int column=index.column();
    qDebug()<<"BtnDel_clicked()11"<<row<<column;
    QString name;
    QString password;
    name=ui->tableWidget->item(row,0)->text();
    password=ui->tableWidget->item(row,1)->text();
    qDebug()<<"BtnDel_clicked()11"<<row<<column<<name<<password;
    if(QMessageBox::question(this,"确认删除","是否真的删除",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        emit SendDeleteUserInfo(name,password);//删除信号
        qDebug()<<"success";
        ui->tableWidget->removeRow(row);
    }
}

void AdminWidgetDemo::BtnUpdate_clicked()
{
    QPushButton* obj=qobject_cast<QPushButton*>(sender());
    int x=obj->frameGeometry().x();
    int y=obj->frameGeometry().y();

    QModelIndex index=ui->tableWidget->indexAt(QPoint(x,y));

    int row=index.row();

    QString name;
    QString password;
    name=ui->tableWidget->item(row,0)->text();
    password=ui->tableWidget->item(row,1)->text();

    if(QMessageBox::question(this,"确认修改","是否真的修改？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        emit SendModifyUserInfo(name,password);//发送修改信号
        qDebug()<<"success";
    }
}

void AdminWidgetDemo::close()
{
    deleteButtons();
    ui->tableWidget->clearContents();
}

