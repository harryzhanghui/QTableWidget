/*
                            QTableWidget简介
    QTableWidget是QT对话框设计中常用的显示数据表格的控件。学习QTableWidget就要
首先看看QTableView控件（控件也是有”家世“的！就像研究人一样一样的），
因为QTableWidget继承于类QTableView。两者主要区别是QTableView可以使用自定义的数据模型来显示内容
（也就意味着使用时先要通过setModel来绑定数据源），而QTableWidget则只能使用标准的数据模型。
QTableWidget单元格数据是QTableWidgetItem对象来实现的（即就是不需要数据源，单元格内的信息需要逐个填充即可）。
这主要由于QTableView类中有setModel成员函数，而到了QTableWidget类中，该成员函数变成了私有。
使用QTableWidget就离不开QTableWidgetItem。QTableWidgetItem用来表示表格中的其中一个单元格，
整个表格都需要用逐个单元格对象QTableWidgetItem构建起来。
*/

#include "widget.h"
#include "ui_widget.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QHeaderView>
#include <QComboBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QTableWidget *tableWidget = new QTableWidget(10,5); // 构造了一个QTableWidget的对象，并且设置为10行，5列
    //也可用下面的方法构造QTableWidget对象
    //QTableWidget *tableWidget = new QTableWidget;
    //tableWidget->setRowCount(10);     //设置行数为10
    //tableWidget->setColumnCount(5);   //设置列数为5
    tableWidget->setWindowTitle("QTableWidget & Item");
    tableWidget->resize(350, 200);  //设置表格
    QStringList header;
    header<<"Month"<<"Description";
    tableWidget->setHorizontalHeaderLabels(header);
    tableWidget->setItem(0,0,new QTableWidgetItem("Jan"));
    tableWidget->setItem(1,0,new QTableWidgetItem("Feb"));
    tableWidget->setItem(2,0,new QTableWidgetItem("Mar"));

    tableWidget->setItem(0,1,new QTableWidgetItem(QIcon("images/IED.png"), "Jan's month"));
    tableWidget->setItem(1,1,new QTableWidgetItem(QIcon("images/IED.png"), "Feb's month"));
    tableWidget->setItem(2,1,new QTableWidgetItem(QIcon("images/IED.png"), "Mar's month"));

    //一. 对QTableWidget本身的效果实现
    //1. 将表格变为禁止编辑在默认情况下，表格里的字符是可以更改的，
    //比如双击一个单元格，就可以修改原来的内容，如果想禁止用户的这种操作，让这个表格对用户只读，可以这样：
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能对表格内容进行修改
    tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged);//任何时候都能对单元格修改
    tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);//双击单元格
    tableWidget->setEditTriggers(QAbstractItemView::SelectedClicked);//单击已选中的内容
    tableWidget->setEditTriggers(QAbstractItemView::EditKeyPressed);//按下任意键就能修改
    tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);//以上条件全包括


    //2. 设置表格为整行选择
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);//选中单个单元格
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//选中一行(整行选中)
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);//选中一列

    //3.单个选中和多个选中的设置：
    tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);//设置为可以选中多个目标
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);//不能选择
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //选中单个目标
    tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);//选中多个目标
    tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);//主要功能是正常情况下是单选，但按下Ctrl或Shift键后，可以多选
    tableWidget->setSelectionMode(QAbstractItemView::ContiguousSelection);//主要功能是正常情况下是单选，但按下Ctrl或Shift键后，可以多选

//      QAbstractItemView.ContiguousSelection
//      QAbstractItemView.ExtendedSelection
//      的区别不明显，主要功能是正常情况下是单选，但按下Ctrl或Shift键后，可以多选


//    5.表格表头的显示与隐藏(注意：需要 #include <QHeaderView>)
//     对于水平或垂直方法的表头，可以用以下方式进行 隐藏/显示 的设置：
     tableWidget->verticalHeader()->setVisible(false);   //隐藏列表头
     tableWidget->horizontalHeader()->setVisible(false); //隐藏行表头

//   6.对表头文字的字体、颜色进行设置(注意：需要 #include <QHeaderView>)
     QTableWidgetItem *columnHeaderItem0 = tableWidget->horizontalHeaderItem(0); //获得水平方向表头的Item对象
     columnHeaderItem0->setFont(QFont("Helvetica")); //设置字体
     columnHeaderItem0->setBackgroundColor(QColor(0,60,10)); //设置单元格背景颜色
     columnHeaderItem0->setTextColor(QColor(200,111,30)); //设置文字颜色

//   7.在单元格里加入控件：
      QComboBox *comBox = new QComboBox();
      comBox->addItem("Y");
      comBox->addItem("N");
      tableWidget->setCellWidget(0,2,comBox);

//   8.单元格中添加图片：
     tableWidget->setItem(1, 0, new QTableWidgetItem(QIcon(":/new/images/kingdemo.ico"),tr("")));

//   9设置单元格字体颜色、背景颜色和字体字符：
     QTableWidgetItem *item = new QTableWidgetItem("Apple");
     item->setBackgroundColor(QColor(0,60,10));
     item->setTextColor(QColor(200,111,100));
     item->setFont(QFont("Helvetica"));
     tableWidget->setItem(0,3,item);
     tableWidget->setFont(QFont("Helvetica"));//对所有的单元格都使用这种字体

//   10.设置单元格内文字的对齐方式
  /*
    水平对齐方式有：
    Qt.AlignLeft 0x0001 Aligns with the left edge.
    Qt.AlignRight 0x0002 Aligns with the right edge.
    Qt.AlignHCenter 0x0004 Centers horizontally in the available space.
    Qt.AlignJustify 0x0008 Justifies the text in the available space.
    垂直对齐方式：
    Qt.AlignTop 0x0020 Aligns with the top.
    Qt.AlignBottom 0x0040 Aligns with the bottom.
    Qt.AlignVCenter 0x0080 Centers vertically in the available space.
    如果两种都要设置，只要用 Qt.AlignHCenter |  Qt.AlignVCenter 的方式即可
 */


//   11.合并单元格：
     tableWidget->setSpan(0, 0, 3, 1);//  # 其参数为： 要改变单元格的1行数、2列数，要合并的3行数、4列数

//   12.设置单元格的大小

//   首先，可以指定某个行或者列的大小
      tableWidget->setColumnWidth(3,200);
      tableWidget->setRowHeight(3,60);

//   还可以将行和列的大小设为与内容相匹配
      tableWidget->resizeColumnsToContents();
      tableWidget->resizeRowsToContents();

//   13.获得单击单元格的内容

//     通过实现 itemClicked (QTableWidgetItem *) 信号的槽函数，就可以获得鼠标单击到的单元格指针，进而获得其中的文字信息
//   connect(tableWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(getItem(QTreeWidgetItem*,int)));
//    将itemClicked信号与函数getItem绑定

//   14.QTableWidget要调整表格行宽主要涉及以下函数
//     tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//使列完全填充并平分
//     tableWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);//行自适应宽度
     tableWidget->resizeColumnsToContents(); //根据内容调整列宽
     tableWidget->resizeColumnToContents(100);//根据内容自动调整给定列宽
//     tableWidget->horizontalHeader()->setResizeMode;//把给定列设置为给定模式
//     主要模式有Stretch和Fixed

//   15.添加表头内容：
//   方法一：
     QStringList header1;
     header1<<""<<tr("1")<<tr("2")<<tr("3")<<tr("4")<<tr("5");
//   方法二：
     tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("1")<<tr("2")<<tr("3")<<tr("4")<<tr("5"));

//   16.清除：
     tableWidget->clear();//清除所有可见数据（包括表头），行还在
     tableWidget->clearContents();//只清除表中数据，不清除表头内容
     tableWidget->setRowCount(0);//连行也清除掉
 /*
//   15.一些零碎的知识点代码：
     int row = tableWidget->rowCount();//获取表格中当前总行数
     tableWidget->setRowCount(row+1);//添加一行
     tableWidget->removeRow(row);//清除已有的行列
    int row1 = tableWidget->currentItem()->row();//当前选中行
     bool focus = tableWidget->isItemSelected(tableWidget->currentItem());//判断是否选中一行
     //QString proName = tableWidget->item(0, 0)->text();//获取某一格内容
     tableWidget->setShowGrid(true);//显示表格线
     tableWidget->verticalHeader()->setVisible(false);//隐藏左边垂直
     QHeaderView *headerView = tableWidget->horizontalHeader();
     //headerView->setMovable(false);//去除表头的移动
     headerView->resizeSection(0,284);//设置第一列宽
     headerView->resizeSection(1,127);//设置第二列宽
     //headerView->setResizeMode(QHeaderView::Fixed);//列表不能移动
     //headerView->setClickable(false);//不响应鼠标单击
     tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);//不能编辑
     tableWidget->setSelectionBehavior(QTableWidget::SelectRows);//一次选中一行
     tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//只能单选
//     QScrollBar *scrollBar = horizontalScrollBar();
//     scrollBar->hide();

     tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉水平滚动条
     tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);//垂直滚动条按项移动
     tableWidget->setAutoScroll(false);//去掉自动滚动


//     Qt5以上的版本，所以其中有一项“headerView->setClickable(false);//不响应鼠标单击”，
//     这个setClickable(false);函数已经被setSectionsClickable(false);所代替

//   17.排序：
     tableWidget->sortByColumn(0, Qt::AscendingOrder);//顾名思义，该函数意思是将某列按升序/降序的方式排列
    //////
    tableWidget->setColumnCount(4); //设置列数
    tableWidget->horizontalHeader()->setDefaultSectionSize(150);
//    tableWidget->horizontalHeader()->setClickable(false); //Qt5以下的版本设置表头不可点击（默认点击后进行排序）
    tableWidget->horizontalHeader()->setSectionsClickable(false);//Qt5以上的版本设置表头不可点击（默认点击后进行排序）

*/


    //设置表头内容
    QStringList header2;
    header2<<tr("name")<<tr("last modify time")<<tr("type")<<tr("size");
    tableWidget->setHorizontalHeaderLabels(header2);

    //设置表头字体加粗
    QFont font = tableWidget->horizontalHeader()->font();
    font.setBold(true);
    tableWidget->horizontalHeader()->setFont(font);
    tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
//    tableWidget->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    tableWidget->verticalHeader()->setDefaultSectionSize(10); //设置行高
    tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
    tableWidget->setShowGrid(false); //设置不显示格子线
    tableWidget->verticalHeader()->setVisible(false); //设置垂直头不可见
    tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  //可多选（Ctrl、Shift、  Ctrl+A都可以）
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    tableWidget->horizontalHeader()->resizeSection(0,150); //设置表头第一列的宽度为150
    tableWidget->horizontalHeader()->setFixedHeight(25); //设置表头的高度
    tableWidget->setStyleSheet("selection-background-color:lightblue;"); //设置选中背景色
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色


//    （1）创建一个新的表格控件
    QTableWidget *table=new QTableWidget();
//    （2）设置列数
    table->setColumnCount(3);//设置3列
//    注意：如果内容超过3列，则无法显示超过3列的内容，所以需要看情况重新设置列数
//    （3）设置行数
    table->setRowCount(5);//设置5行
//    注意：如果内容超过5行，则无法显示超过3行的内容，所以需要看情况重新设置行数
//    （4）设置表头内容
    QStringList header;  //QString类型的List容器
    header<<"学号"<<"姓名"<<"性别";//设置内容是学号、姓名、性别
    table->setHorizontalHeaderLabels(header);//设置表头内容
//    （5）设置表格文字内容
    QTableWidgetItem *name=new QTableWidgetItem();//创建一个Item
    name->setText("桃花庵");//设置内容
    table->setItem(0,1,name);//把这个Item加到第一行第二列中
//    （6）可设置表格单元显示QComBox、QSpinBox、QLable、QDateTimeEdit等
    QDateTimeEdit *dateTimeEdit= new QDateTimeEdit();  //创建一个QDateTimeEdit
     dateTimeEdit->setDateTime(QDateTime::currentDateTime());//设置为当前时间
     dateTimeEdit->setDisplayFormat("dd/M/yyyy");//设置显示格式
     dateTimeEdit->setCalendarPopup(true);//设置可以打开日历
     table->setCellWidget (1,2,dateTimeEdit);//加到第二行第三列中
//    （7）设置表头的字体属性
    QFont font ;//定义一个字体变量
    font.setBold(true);  //设置粗体
    table->horizontalHeader()->setFont(font);//把字体变量属性加进表头中
//    （8）设置表头的内容充满整个表格的宽度
    table->horizontalHeader()->setStretchLastSection(true); //设置表头充满表格的宽度
//    （9）设置表头的高度
    table->horizontalHeader()->setFixedHeight(25); //设置表头的高度为25
//    （10）设置表头的列宽
    table->horizontalHeader()->resizeSection(0,180); //设置表头第1列的宽度为180
//    （11）设置表格的行高
    table->verticalHeader()->setDefaultSectionSize(10); //设置行高为10
//    （12）消除表格控件的边框
    table->setFrameShape(QFrame::NoFrame); //设置无边框
//    （13）设置表格不显示格子线
    table->setShowGrid(false); //设置不显示格子线
//    （14）去除每一行的左边序号
    table->verticalHeader()->setVisible(false); //设置垂直头不可见,即左边序号不见
//    （15）设置选择行为时每次一行
    table->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次一行
//    （16）设置对行可进行多选
    table->setSelectionMode(QAbstractItemView::ExtendedSelection);  //可多选（Ctrl、Shift、Ctrl+A都可以）
//    （17）设置表格内容不能编辑
    table->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格内容不可编辑
//    （18）设置选中行的背景色
    table->setStyleSheet("selection-background-color:rgb(34, 170, 75);"); //设置选中行的背景色
//    （19）设置表头的背景色
    table->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头的背景色
//    （20）设置水平滚动条样式
    table->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:12px;}"
             "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
             "QScrollBar::handle:hover{background:gray;}"
             "QScrollBar::sub-line{background:transparent;}"
             "QScrollBar::add-line{background:transparent;}");

//    （21）设置垂直滚动条的样式
    table->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 12px;}"
             "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
             "QScrollBar::handle:hover{background:gray;}"
             "QScrollBar::sub-line{background:transparent;}"
             "QScrollBar::add-line{background:transparent;}");
}


Widget::~Widget()
{
    delete ui;
}
