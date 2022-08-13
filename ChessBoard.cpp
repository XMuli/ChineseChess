/*
 * Copyright (C)  2019~2020  偕臧  All rights reserved.
 *
 * Author:  xmuli(偕臧) xmulitech@gmail.com
 *
 * GitHub:  https://github.com/XMuli
 * Blogs:   https://ifmet.cn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.
 */
#include "ChessBoard.h"
#include "ui_ChessBoard.h"

ChessBoard::ChessBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChessBoard)
{
    init();

    //计时器部分
    m_timer = new QTimer;  //初始化定时器
    m_timeRecord  = new QTime(0, 0, 0); //初始化时间
    m_bIsStart = false;  //初始为还未计时
    connect(m_timer,SIGNAL(timeout()),this,SLOT(updateTime()));

    m_pAbout = new AboutAuthor();

    this->setWindowIcon(QIcon(":/images/chess.svg"));
    ui->setupUi(this);
}

ChessBoard::~ChessBoard()
{
    delete ui;
}

void ChessBoard::init()
{
    for(int i = 0; i<32; i++)
        m_ChessPieces[i].init(i);

    m_ChessSteps.clear(); //重置步数
    m_nSelectID = -1;
    m_nCheckedID = -1;
    m_bIsTcpServer = true;
    m_bIsRed = true;
    m_bIsOver = false;
    m_bIsShowStep = true;
}

bool ChessBoard:: isRed(int id)
{
    return m_ChessPieces[id].m_bRed;
}


void ChessBoard:: killStone(int id)
{
    if(id== -1)
        return;
    m_ChessPieces[id].m_bDead= true;
}

void ChessBoard:: reliveStone(int id)
{
    if(id== -1)
        return;
    m_ChessPieces[id].m_bDead= false;
}

void ChessBoard:: moveStone(int moveid, int row, int col)
{
    m_ChessPieces[moveid].m_nRow= row;
    m_ChessPieces[moveid].m_nCol= col;

    m_bIsRed= !m_bIsRed;   //换边
}

bool ChessBoard::sameColor(int moveId,int killId)
{
    if(moveId== -1 || killId== -1)
        return false;

    return isRed(moveId)== isRed(killId);
}

bool ChessBoard::isDead(int id)
{
    if(id == -1)
        return true;

    return m_ChessPieces[id].m_bDead;
}

int ChessBoard::getStoneId(int row, int col)
{
    for(int i=0; i<32; ++i)
    {
        if(m_ChessPieces[i].m_nRow == row && m_ChessPieces[i].m_nCol == col && !isDead(i))
            return i;
    }

    return -1;
}

int ChessBoard::getStoneCountAtLine(int row1, int col1, int row2, int col2)
{
    int ret = 0;
    if(row1 != row2 && col1 != col2)
        return -1;
    if(row1 == row2 && col1 == col2)
        return -1;

    if(row1 == row2)
    {
        int min  = col1 < col2 ? col1 : col2;
        int max = col1 < col2 ? col2 : col1;
        for(int col = min+1; col<max; ++col)
        {
            if(getStoneId(row1, col) != -1)
                ++ret;
        }
    }
    else
    {
        int min = row1 < row2 ? row1 : row2;
        int max = row1 < row2 ? row2 : row1;
        for(int row = min+1; row<max; ++row)
        {
            if(getStoneId(row, col1) != -1)
                ++ret;
        }
    }

    return ret;
}

void ChessBoard::whoWin()  //谁胜谁负
{
    if(m_ChessPieces[4].m_bDead && !m_ChessPieces[20].m_bDead)
    {
        reset();
        winMessageBox("提示", "本局结束，红方胜利.");
    }

    if(!m_ChessPieces[4].m_bDead && m_ChessPieces[20].m_bDead)
    {
        reset();
        winMessageBox("提示", "本局结束，黑方胜利.");
    }
}
int ChessBoard:: relation(int row1,int col1,int row2,int col2)
{
    // 原坐标(row1,col1)与目标坐标(row2,col2)的关系
    // 使用原坐标与目标坐标的行相减的绝对值乘以10 加上原坐标与目标坐标的列相减的绝对值
    // 作为关系值
    // 关系值用于判断是否符合棋子移动规则
    return abs(row1-row2)*10+ abs(col1-col2);
}

//是否选中该枚棋子。pt为输入参数; row， col为输出参数
bool ChessBoard::isChecked(QPoint pt, int &row, int &col)
{
    for(row = 0; row <= 9; row++)
    {
        for(col = 0; col <= 8; col++)
        {
            QPoint temp = center(row, col);
            int x = temp.x()-pt.x();
            int y = temp.y()-pt.y();

            if(x*x+y*y < m_nR*m_nR)
                return true;
        }
    }

    return false;
}


//象棋的棋盘的坐标转换成界面坐标
QPoint ChessBoard::center(int row, int col)
{
    QPoint rePoint;
    //这里注意坐标的转换
    rePoint.ry() = row*m_nD+m_nOffSet;
    rePoint.rx() = col*m_nD+m_nOffSet;

    return rePoint;
}

//重载:坐标转换
QPoint ChessBoard::center(int id)
{
    return center(m_ChessPieces[id].m_nRow, m_ChessPieces[id].m_nCol);
}

void ChessBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int side = qMin(int((ui->centralwidget->width() - ui->verticalWidget->width()) / 0.9), ui->label->height());
    painter.scale(side / 960.0, side / 960.0);

        m_nOffSet = 60;  //距离界面的边距
        m_nD = 90;       //间距为50px
        m_nR = m_nD/2;   //棋子半径为d/2

        //*******************绘画棋盘*******************
        //绘画10条横线
        for(int i = 0; i <= 9; i++)
            painter.drawLine(QPoint(m_nOffSet, m_nOffSet+i*m_nD), QPoint(m_nOffSet+8*m_nD, m_nOffSet+i*m_nD));

        //绘画9条竖线
        for(int i = 0; i <= 8; i++)
        {
            if(i==0 || i==8)
            {
                painter.drawLine(QPoint(m_nOffSet+i*m_nD, m_nOffSet), QPoint(m_nOffSet+i*m_nD, m_nOffSet+9*m_nD));
            }
            else
            {
                painter.drawLine(QPoint(m_nOffSet+i*m_nD, m_nOffSet), QPoint(m_nOffSet+i*m_nD, m_nOffSet+4*m_nD));
                painter.drawLine(QPoint(m_nOffSet+i*m_nD, m_nOffSet+5*m_nD), QPoint(m_nOffSet+i*m_nD, m_nOffSet+9*m_nD));
            }
        }

        //绘画4条斜线
        painter.drawLine(QPoint(m_nOffSet+3*m_nD, m_nOffSet), QPoint(m_nOffSet+5*m_nD, m_nOffSet+2*m_nD));
        painter.drawLine(QPoint(m_nOffSet+3*m_nD, m_nOffSet+2*m_nD), QPoint(m_nOffSet+5*m_nD, m_nOffSet));
        painter.drawLine(QPoint(m_nOffSet+3*m_nD, m_nOffSet+7*m_nD), QPoint(m_nOffSet+5*m_nD, m_nOffSet+9*m_nD));
        painter.drawLine(QPoint(m_nOffSet+3*m_nD, m_nOffSet+9*m_nD), QPoint(m_nOffSet+5*m_nD, m_nOffSet+7*m_nD));

        QRect rect1(m_nOffSet+m_nD,   m_nOffSet+4*m_nD, m_nD, m_nD);
        QRect rect2(m_nOffSet+2*m_nD, m_nOffSet+4*m_nD, m_nD, m_nD);
        QRect rect3(m_nOffSet+5*m_nD, m_nOffSet+4*m_nD, m_nD, m_nD);
        QRect rect4(m_nOffSet+6*m_nD, m_nOffSet+4*m_nD, m_nD, m_nD);
        painter.setFont(QFont("FangSong", m_nR * 5 / 6, 800));
        painter.drawText(rect1, "楚", QTextOption(Qt::AlignCenter));
        painter.drawText(rect2, "河", QTextOption(Qt::AlignCenter));
        painter.drawText(rect3, "汉", QTextOption(Qt::AlignCenter));
        painter.drawText(rect4, "界", QTextOption(Qt::AlignCenter));

        //*******************绘画棋子*******************
        for(int i = 0; i < 32; i++)
            drawChessPieces(painter, i);
        //绘制上次移动棋子的起止位置
        if(m_bIsShowStep)
            drawLastStep(painter,m_ChessSteps);

        //绘制文本棋谱
        drawTextStep();
}

void ChessBoard::drawChessPieces(QPainter &painter, int id)   //绘画单个具体的棋子
{
    if(m_ChessPieces[id].m_bDead)
        return;

    QPoint temp = center(id);
    QRect rect(temp.x()-m_nR, temp.y()-m_nR, m_nD, m_nD);

    if(m_nSelectID == id)
        painter.setBrush(QBrush(QColor(64,64,196, 80)));
    else
        painter.setBrush(QBrush(QColor(64,64,196, 10)));

    painter.setPen(QColor(0, 0, 0));
    painter.drawEllipse(center(id), m_nR, m_nR);  //绘画圆形
    painter.setFont(QFont("FangSong", m_nR * 5 / 6, 2700));

    if(id < 16)
        painter.setPen(QColor(0, 0, 0));
    else
        painter.setPen(QColor(255, 0, 0));

    painter.drawText(rect, m_ChessPieces[id].getnName(m_ChessPieces[id].m_bRed), QTextOption(Qt::AlignCenter));  //绘画圆形里面的汉字
}

void ChessBoard:: drawLastStep(QPainter &painter,QVector<ChessStep*>& steps)
{
    if (this->m_ChessSteps.size() == 0) {
        return;
    }

    QPoint stepFrom = center(steps.last()->m_nRowFrom,steps.last()->m_nColFrom);
    QRect rectFrom(stepFrom.x()-m_nR, stepFrom.y()-m_nR, m_nD, m_nD);
    painter.setBrush(QColor(0,0,0,50));
    painter.setPen(Qt::black);
    painter.drawRect(rectFrom);

    QPoint stepTo = center(steps.last()->m_nRowTo,steps.last()->m_nnColTo);
    QRect rectTo(stepTo.x()-m_nR, stepTo.y()-m_nR, m_nD, m_nD);
    painter.setBrush(QColor(0,0,0,30));
    painter.setPen(Qt::black);
    painter.drawRect(rectTo);
}

void ChessBoard::drawTextStep()
{
    ui->labelTextStep->setText(textStepRecord);
}

// true 产生"对将" 情景了；false 无"对将"情况
bool ChessBoard::hongMenFeast()
{
    if (m_ChessPieces[4].m_bDead || m_ChessPieces[20].m_bDead)
        return false;

    int colBlack = m_ChessPieces[4].m_nCol;
    int colRed = m_ChessPieces[20].m_nCol;
    int rowBlack = m_ChessPieces[4].m_nRow;
    int rowRed = m_ChessPieces[20].m_nRow;

    bool bColEmpty = true;
    if (colBlack == colRed){
        for (int row = rowBlack + 1; row < rowRed ; ++row) {
            if (havePieces(row, colBlack))
                bColEmpty = false;  // 将之间有棋子；非此列为空
        }
    } else {
        bColEmpty = false;
    }

    return bColEmpty;
}

// 判断某格子是否有棋子在其上
bool ChessBoard::havePieces(int row, int col)
{
    for (auto pieces : m_ChessPieces) {
        if (pieces.m_bDead)
            continue;

        if (pieces.m_nRow == row && pieces.m_nCol == col)
            return true;
    }

    return false;
}

// 胜负已分，重置
void ChessBoard::reset()
{
    m_Chessvoice.voiceWin();
    m_bIsOver = true;
    //游戏结束 则计时停止 & 计时控制按钮不再可用 直到用户重新游戏
    if(m_bIsStart)
    {
        m_timer->stop();
        m_bIsStart = false;
    }

    ui->pushButton_start->setEnabled(false);
}

void ChessBoard::winMessageBox(QString title, QString msg)
{
    QMessageBox message(QMessageBox::Information, title, msg);
    message.setIconPixmap(QPixmap(":/images/win.jpg"));
    message.setFont(QFont("FangSong", 16, QFont::Bold));
    message.exec();
}

QPoint ChessBoard::getRealPoint(QPoint pt)
{
    int side = qMin(int((ui->centralwidget->width() - ui->verticalWidget->width()) / 0.9), ui->label->height());
    QPoint ret;

    ret.setX(pt.x() / double(side) * 960.0);
    ret.setY(pt.y() / double(side) * 960.0);

    return ret;
}

bool ChessBoard:: isGeneral()
{
    int generalId=20;   //当前回合方将军id
    if(!m_bIsRed)
        generalId=4;

    int row= m_ChessPieces[generalId].m_nRow;    //当前回合方的将军row
    int col= m_ChessPieces[generalId].m_nCol;    //当前回合方的将军col

    for(int i=0; i<32; ++i)
    {
        if(i>=16&& m_bIsRed)    //红方时采用黑子0-15 黑方时采用红子16-32
            break;

        if(canMove(i,generalId,row,col) && !m_ChessPieces[i].m_bDead)   //依次遍历存活子能否移动到指定坐标
        {
            return true;
        }
    }
    return false;
}

//鼠标按下事件
//void ChessBoard::mousePressEvent(QMouseEvent *ev)
//{
//    //只响应鼠标左键的单击操作 防止游戏结束重复弹框
//    if(ev->button() != Qt::LeftButton || ev->type() != QEvent::Type::MouseButtonPress)
//        return;

//    QPoint pt = ev->pos();
//    pt = getRealPoint(pt);
//    //将pt转化成棋盘的像行列值
//    //判断这个行列值上面有没有棋子
//    int row, col;

//    //点击棋盘外面就不做处理
//    if(!isChecked(pt, row, col))
//        return;

//    if(m_bIsOver)
//    {
//        QMessageBox message(QMessageBox::Information, "提示", "本局已结束，请重新开始.");
//        message.setIconPixmap(QPixmap(":/images/win.jpg"));
//        message.setFont(QFont("FangSong",16,QFont::Bold));
//        message.exec();
//        return;
//    }

//    //判断是哪一个棋子被选中，根据ID（这里的局部i）来记录下来
//    int i;
//    m_nCheckedID = -1;

//    for(i = 0; i <= 31; i++)
//    {
//        if(m_ChessPieces[i].m_nRow == row && m_ChessPieces[i].m_nCol == col && !m_ChessPieces[i].m_bDead)
//            break;
//    }

//    if(0<=i && i<32)
//        m_nCheckedID = i;  //选中的棋子的ID

//    bool newbIsRed = m_bIsRed;
//    clickPieces(m_nCheckedID, row, col);

//    // 刚执棋落子完成，出现对将
//    if (hongMenFeast() && m_nSelectID == -1 && newbIsRed != m_bIsRed)
//    {
//        winMessageBox("提示", "可将军，直接取胜");
//        // TODO: 可将军，直接提示直接取胜的音效
//    }

//    update();
//    whoWin();
//}

//void ChessBoard::clickPieces(int checkedID, int& row, int& col)
//{
//    m_nCheckedID = checkedID;

//    if(m_nSelectID == -1) //选中棋子
//    {
//       // whoPlay(m_nCheckedID);

//        if(m_nCheckedID != -1)
//        {
//            if(m_bIsRed == m_ChessPieces[m_nCheckedID].m_bRed)
//            {
//                m_nSelectID = m_nCheckedID;
//                m_Chessvoice.voiceSelect();   //选棋音效
//            }
//        }
//    }
//    else//走棋子
//    {
//        if(canMove(m_nSelectID, m_nCheckedID, row, col ))
//        {
//            //m_nSelectID为第一次点击选中的棋子，
//            //m_nCheckedID为第二次点击||被杀的棋子ID，准备选中棋子下子的地方
//            m_ChessPieces[m_nSelectID].m_nRow = row;
//            m_ChessPieces[m_nSelectID].m_nCol = col;
//            if(m_nCheckedID != -1)
//            {
//                m_ChessPieces[m_nCheckedID].m_bDead = true;
//                m_Chessvoice.voiceEat();  //吃子音效
//            }
//            m_Chessvoice.voiceMove(); //移动音效

//            m_nSelectID = -1;
//            m_bIsRed = !m_bIsRed;
//        }
//    }
//}


//总的移动规则，选中准备下的棋子，被杀的棋子， 准备移动到的目的行列值
//bool ChessBoard::canMove(int moveId, int killId, int row, int col)
//{
//    //1.确定是选择其它棋子还是走棋
//    //2.是否需要使用到canMoveXXX()来做限制
//    //3.罗列出所有情况，和需要的得到的结果值 ==>  然后进行中间的逻辑层判断※不要受到别人的代码框架的束缚※

//        if(isRed(moveId) == m_ChessPieces[killId].m_bRed)  //选择其它棋子，返回false
//        {
//            if(killId == -1)  //其中有一个特殊情况，黑+m_ChessPieces[-1].m_bRed ==> 也需要判断能否
//            {
//                switch (m_ChessPieces[moveId].m_emType)
//                {
//                case ChessPieces::JIANG:
//                    return canMoveJIANG(moveId, killId, row, col);
//                case ChessPieces::SHI:
//                    return canMoveSHI(moveId, killId, row, col);
//                case ChessPieces::XIANG:
//                    return canMoveXIANG(moveId, killId, row, col);
//                case ChessPieces::MA:
//                    return canMoveMA(moveId, killId, row, col);
//                case ChessPieces::CHE:
//                    return canMoveCHE(moveId, killId, row, col);
//                case ChessPieces::PAO:
//                    return canMovePAO(moveId, killId, row, col);
//                case ChessPieces::BING:
//                    return canMoveBING(moveId, killId, row, col);
//                }
//            }
//            m_nSelectID = killId;

//            return false;
//        }
//        else  //选择其走棋，返回true
//        {
//            switch (m_ChessPieces[moveId].m_emType)
//            {
//            case ChessPieces::JIANG:
//                return canMoveJIANG(moveId, killId, row, col);
//            case ChessPieces::SHI:
//                return canMoveSHI(moveId, killId, row, col);
//            case ChessPieces::XIANG:
//                return canMoveXIANG(moveId, killId, row, col);
//            case ChessPieces::MA:
//                return canMoveMA(moveId, killId, row, col);
//            case ChessPieces::CHE:
//                return canMoveCHE(moveId, killId, row, col);
//            case ChessPieces::PAO:
//                return canMovePAO(moveId, killId, row, col);
//            case ChessPieces::BING:
//                return canMoveBING(moveId, killId, row, col);
//            }

//            return true;

//        }
//}

//总的移动规则
bool ChessBoard::canMove(int moveId, int killId, int row, int col)
{
    //选棋id和吃棋id同色，则选择其它棋子并返回
    if(sameColor(moveId,killId))
    {
        //换选棋子
        m_nSelectID=killId;
        update();
        return false;
    }

    switch (m_ChessPieces[moveId].m_emType)
    {
    case ChessPieces::JIANG:
        return canMoveJIANG(moveId, killId, row, col);

    case ChessPieces::SHI:
        return canMoveSHI(moveId, killId, row, col);

    case ChessPieces::XIANG:
        return canMoveXIANG(moveId, killId, row, col);

    case ChessPieces::MA:
        return canMoveMA(moveId, killId, row, col);

    case ChessPieces::CHE:
        return canMoveCHE(moveId, killId, row, col);

    case ChessPieces::PAO:
        return canMovePAO(moveId, killId, row, col);

    case ChessPieces::BING:
        return canMoveBING(moveId, killId, row, col);

    default: break;
    }

    return true;
}

bool ChessBoard::canMoveJIANG(int moveId, int killId, int row, int col)
{
    //对将的情况
    if (killId != -1 && m_ChessPieces[killId].m_emType == m_ChessPieces->JIANG)
        return canMoveCHE(moveId, killId, row, col );

    if(isRed(moveId)) //红 将
    {
        if(row < 7 || col < 3 || col > 5) return false;
    }
    else  //黑 将
    {
        if(row > 2 || col < 3 || col > 5) return false;
    }

    int d=relation(m_ChessPieces[moveId].m_nRow, m_ChessPieces[moveId].m_nCol, row, col);
    if(d == 1 || d == 10)
        return true;

    return false;
}

bool ChessBoard::canMoveSHI(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    if(isRed(moveId)) //红 士
    {
        if(row < 7 || col < 3 || col > 5) return false;
    }
    else  //黑 士
    {
        if(row > 2 || col < 3 || col > 5) return false;
    }

    int d=relation(m_ChessPieces[moveId].m_nRow, m_ChessPieces[moveId].m_nCol, row, col);
    if(d == 11)
        return true;

    return false;
}

bool ChessBoard::canMoveXIANG(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    int d=relation(m_ChessPieces[moveId].m_nRow, m_ChessPieces[moveId].m_nCol, row, col);
    if(d!= 22)
        return false;

    int row_eye= (m_ChessPieces[moveId].m_nRow+ row)/ 2;
    int col_eye= (m_ChessPieces[moveId].m_nCol+ col)/ 2;

    //堵象眼
    if(getStoneId(row_eye,col_eye)!= -1)
        return false;

    //象不可过河
    if(isRed(moveId))   //红
    {
        if(row< 4)
            return false;
    }
    else    //黑
    {
        if(row> 5)
            return false;
    }

    return true;
}

bool ChessBoard::canMoveMA(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    int d=relation(m_ChessPieces[moveId].m_nRow, m_ChessPieces[moveId].m_nCol, row, col);
    if(d!=12 && d!=21)
        return false;

    //蹩马脚
    if(d==12)
    {
        if(getStoneId(m_ChessPieces[moveId].m_nRow, (m_ChessPieces[moveId].m_nCol+ col) /2) != -1)
            return false;
    }
    else
    {
        if(getStoneId((m_ChessPieces[moveId].m_nRow+ row) /2 ,m_ChessPieces[moveId].m_nCol) != -1)
            return false;
    }

    return true;
}

bool ChessBoard::canMoveCHE(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    int ret = getStoneCountAtLine(m_ChessPieces[moveId].m_nRow, m_ChessPieces[moveId].m_nCol, row, col);
    if(ret == 0)
        return true;

    return false;
}

bool ChessBoard::canMovePAO(int moveId, int killId, int row, int col)
{
    int ret = getStoneCountAtLine(row, col, m_ChessPieces[moveId].m_nRow, m_ChessPieces[moveId].m_nCol);
    if(killId != -1)
    {
        if(ret == 1)
            return true;
    }
    else
    {
        if(ret == 0)
            return true;
    }
    return false;
}

bool ChessBoard::canMoveBING(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    int d=relation(m_ChessPieces[moveId].m_nRow, m_ChessPieces[moveId].m_nCol, row, col);
    if(d!= 1 && d!= 10)
        return false;

    if(isRed(moveId))   //红
    {
        //兵卒不可后退
        if(row> m_ChessPieces[moveId].m_nRow)
            return false;

        //兵卒没过河不可横着走
        if(m_ChessPieces[moveId].m_nRow>= 5 && m_ChessPieces[moveId].m_nRow== row)
            return false;
    }
    else    //黑
    {
        if(row< m_ChessPieces[moveId].m_nRow)
            return false;
        if(m_ChessPieces[moveId].m_nRow<= 4 && m_ChessPieces[moveId].m_nRow== row)
            return false;
    }

    return true;
}

bool ChessBoard:: canSelect(int id)
{
    return m_bIsRed== m_ChessPieces[id].m_bRed;
}

void ChessBoard::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() != Qt::LeftButton || m_bIsOver== true) { // 排除鼠标右键点击 游戏已结束则直接返回
        return;
    }
    QPoint pt= ev->pos();  //获取当前鼠标位置坐标
    pt=getRealPoint(pt);    //转换至实际像素坐标
    click(pt);
}

void ChessBoard::click(QPoint pt)
{
    // 看有没有点中象棋
    // 将pt转化成象棋的行列值
    // 判断这个行列值上面有没有棋子
    int row, col;
    bool bClicked = isChecked(pt, row, col);
    if (!bClicked) {
        return;
    }

    int id = getStoneId(row, col);
    clickPieces(id, row, col);

}

void ChessBoard::clickPieces(int id, int row, int col)
{
    if (this->m_nSelectID == -1) { // 如果点中的棋子之前未被选中
        trySelectStone(id);
    }
    else {
        tryMoveStone(id, row, col);
    }
}

void ChessBoard::trySelectStone(int id)
{
    if (id == -1) {
        return;
    }

    if (!canSelect(id)) {
        return;
    }

    m_nSelectID = id;
    update();
    m_Chessvoice.voiceSelect();
}

void ChessBoard::tryMoveStone(int killid, int row, int col)
{
    if (killid != -1 && sameColor(killid, m_nSelectID)) {
        trySelectStone(killid);
        return;
    }

    bool ret = canMove(m_nSelectID, killid, row, col);
    if (ret) {
        doMoveStone(m_nSelectID, killid, row, col);
        m_nSelectID = -1;
        update();
    }
}

void ChessBoard::doMoveStone(int moveid, int killid, int row, int col)
{
    saveStep(moveid, killid, row, col, m_ChessSteps);

    killStone(killid);
    moveStone(moveid, row, col);
    whoWin();

    if(killid== -1)
        m_Chessvoice.voiceMove(); //移动音效
    else
        m_Chessvoice.voiceEat(); //吃子音效

    if(isGeneral())
        m_Chessvoice.voiceGeneral();    //将军音效
}

void ChessBoard::saveStep(int moveid, int killid, int row, int col, QVector<ChessStep*>& steps)
{
    ChessStep* step = new ChessStep;
    step->m_nColFrom = m_ChessPieces[moveid].m_nCol;
    step->m_nnColTo = col;
    step->m_nRowFrom = m_ChessPieces[moveid].m_nRow;
    step->m_nRowTo = row;
    step->m_nMoveID = moveid;
    step->m_nKillID = killid;

    steps.append(step);
    textStepRecord= textStep(moveid, row, col);
}

QString ChessBoard::textStep(int id, int row, int col)
{
    int rowFrom= m_ChessPieces[id].m_nRow;
    int rowTo= row;
    int colFrom= m_ChessPieces[id].m_nCol;
    int colTo= col;

    QString temp="";
    QString name=m_ChessPieces[id].getnName(m_ChessPieces[id].m_bRed);
    QString textCol= m_ChessPieces[id].getColText(colFrom);
    QString textRow= m_ChessPieces[id].getRowText(rowTo);
    temp.append(name).append(textCol).append(textRow);

    //兵炮车将
    if(m_ChessPieces[id].m_emType==6 || m_ChessPieces[id].m_emType==5 || m_ChessPieces[id].m_emType==4 || m_ChessPieces[id].m_emType==0)
    {
        //行相等
        if(rowFrom== rowTo)
        {
            temp.append(m_ChessPieces[id].getColText(colTo));
            return temp;
        }
        //移动的格数
        temp.append(m_ChessPieces[id].getMoveText(rowFrom, rowTo));
    }
    else    //马相士
    {
        //移动后所在列
        temp.append(m_ChessPieces[id].getColText(colTo));
    }
    return temp;

}

void ChessBoard::backOne()
{
    if (this->m_ChessSteps.size() == 0 || m_bIsOver) {
        return;
    }

    ChessStep* step = this->m_ChessSteps.last();
    m_ChessSteps.removeLast();
    back(step);

    update();
    delete step;
    m_Chessvoice.voiceBack();
}

void ChessBoard::back(ChessStep* step)
{
    reliveStone(step->m_nKillID);
    moveStone(step->m_nMoveID, step->m_nRowFrom, step->m_nColFrom);
}

void ChessBoard::back()
{
    backOne();
}

//刷新时间
void ChessBoard::updateTime()
{
    *m_timeRecord = m_timeRecord->addSecs(1);
    ui->lcdNumber->display(m_timeRecord->toString("hh:mm:ss"));

    if(m_bIsStart == false)
        ui->pushButton_start->setText("开始");
    else if(m_bIsStart == true)
        ui->pushButton_start->setText("暂停");
}

void ChessBoard::on_pushButton_start_clicked()
{
    if(!m_bIsStart) //尚未开始 开始计时
        {
            m_timer->start(1000);
            ui->pushButton_start->setText("暂停");
        }
        else //已经开始，暂停
        {
            m_timer->stop();
            ui->pushButton_start->setText("继续");
        }

        m_bIsStart = !m_bIsStart;
}

void ChessBoard::on_pushButton_reset_clicked()
{
    m_timer->stop();    //计时器停止
    m_timeRecord->setHMS(0,0,0); //时间设为0
    ui->lcdNumber->display(m_timeRecord->toString("hh:mm:ss")); //显示00:00:00
    m_bIsStart = false;
    ui->pushButton_start->setText("开始");
    ui->pushButton_start->setEnabled(true);
}

void ChessBoard::on_pushButton_about_clicked()
{
    m_pAbout->setWindowTitle("关于作者");
    m_pAbout->show();
}

void ChessBoard::on_pushButton_restart_clicked()
{
    init();
    on_pushButton_reset_clicked();
    update();
}

void ChessBoard::on_pushButton_back_clicked()
{
    back();
    update();
}

void ChessBoard::on_pushButton_showStep_clicked()
{
    m_bIsShowStep=!m_bIsShowStep;
    update();
}

void ChessBoard::on_pushButton_toMenu_clicked()
{
    emit this->toMenu();
}
