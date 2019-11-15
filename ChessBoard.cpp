#include "ChessBoard.h"
#include "ui_ChessBoard.h"
#include <QPainter>
#include <QMouseEvent>

ChessBoard::ChessBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessBoard)
{

    //初始化32个象棋
    for(int i = 0; i <= 31; i++)
    {
        _ChessPieces[i].initialize(i);
    }

    _selectId = -1;  //IS? 选中棋子[-1:选棋子 || 非-1:走棋子]
    _bRedTrue = true;

    ui->setupUi(this);
}

ChessBoard::~ChessBoard()
{
    delete ui;
}



int ChessBoard::getStoneId(int row, int col)
{
    for(int i=0; i<32; ++i)
    {
        if(_ChessPieces[i]._row == row && _ChessPieces[i]._col == col && !isDead(i))
            return i;
    }
    return -1;
}

bool ChessBoard::isDead(int id)
{
    if(id == -1)return true;
    return _ChessPieces[id]._deal;
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
            if(getStoneId(row1, col) != -1) ++ret;
        }
    }
    else
    {
        int min = row1 < row2 ? row1 : row2;
        int max = row1 < row2 ? row2 : row1;
        for(int row = min+1; row<max; ++row)
        {
            if(getStoneId(row, col1) != -1) ++ret;
        }
    }

    return ret;

}


//绘画棋盘
void ChessBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    _offset = 60;  //距离界面的边距
    _d = 90; //间距为50px
    _r = _d/2;  //棋子半径为d/2


    //*******************绘画棋盘*******************
    //绘画10条横线
    for(int i = 0; i <= 9; i++)
    {
        painter.drawLine(QPoint(_offset, _offset+i*_d), QPoint(_offset+8*_d, _offset+i*_d));
    }


    //绘画9条竖线
    for(int i = 0; i <= 8; i++)
    {
        if(i==0 || i==8)
        {
            painter.drawLine(QPoint(_offset+i*_d, _offset), QPoint(_offset+i*_d, _offset+9*_d));
        }
        else
        {
            painter.drawLine(QPoint(_offset+i*_d, _offset), QPoint(_offset+i*_d, _offset+4*_d));
            painter.drawLine(QPoint(_offset+i*_d, _offset+5*_d), QPoint(_offset+i*_d, _offset+9*_d));
        }
    }

    //绘画4条斜线
    painter.drawLine(QPoint(_offset+3*_d, _offset), QPoint(_offset+5*_d, _offset+2*_d));
    painter.drawLine(QPoint(_offset+3*_d, _offset+2*_d), QPoint(_offset+5*_d, _offset));
    painter.drawLine(QPoint(_offset+3*_d, _offset+7*_d), QPoint(_offset+5*_d, _offset+9*_d));
    painter.drawLine(QPoint(_offset+3*_d, _offset+9*_d), QPoint(_offset+5*_d, _offset+7*_d));

    QRect rect1(_offset+_d,   _offset+4*_d, _d, _d);
    QRect rect2(_offset+2*_d, _offset+4*_d, _d, _d);
    QRect rect3(_offset+5*_d, _offset+4*_d, _d, _d);
    QRect rect4(_offset+6*_d, _offset+4*_d, _d, _d);
    painter.setFont(QFont("隶书", _r, 800));
    painter.drawText(rect1, "楚", QTextOption(Qt::AlignCenter));
    painter.drawText(rect2, "河", QTextOption(Qt::AlignCenter));
    painter.drawText(rect3, "汉", QTextOption(Qt::AlignCenter));
    painter.drawText(rect4, "界", QTextOption(Qt::AlignCenter));





    //*******************绘画棋子*******************
    for(int i = 0; i <= 31; i++)
    {
        drawStone(painter, i);
    }


}

//象棋的棋盘的坐标转换成界面坐标
QPoint ChessBoard::center(int row, int col)
{
    QPoint rePoint;
    //这里注意坐标的转换
    rePoint.rx() = col*_d+_offset;
    rePoint.ry() = row*_d+_offset;
    return rePoint;
}

//重载:坐标转换
QPoint ChessBoard::center(int id)
{
    return center(_ChessPieces[id]._row, _ChessPieces[id]._col);
}


//绘画单个具体的棋子
void ChessBoard::drawStone(QPainter &painter, int id)
{
    if(_ChessPieces[id]._deal)
        return;

    QPoint temp = center(id);
    QRect rect(temp.x()-_r, temp.y()-_r, _d, _d);

    if(_selectId == id)
        painter.setBrush(QBrush(QColor(64,64,196, 80)));
    else
        painter.setBrush(QBrush(QColor(64,64,196, 10)));

    painter.setPen(QColor(0, 0, 0));
    painter.drawEllipse(center(id), _r, _r);  //绘画圆形
    painter.setFont(QFont("华文行楷", _r, 700));

    if(id < 16)
    {
        painter.setPen(QColor(255, 0, 0));
    }
    else
    {
        painter.setPen(QColor(0, 0, 0));
    }

    painter.drawText(rect, _ChessPieces[id].getText(), QTextOption(Qt::AlignCenter));  //绘画圆形里面的汉字

}

//界面坐标转换成棋盘的行列值[获取鼠标点击的像素坐标，是位于棋盘的哪一个行列值]
bool ChessBoard::getRowCol(QPoint pt, int &row, int &col)
{
    for(row = 0; row <= 9; row++)
    {
        for(col = 0; col <= 8; col++)
        {
            QPoint temp = center(row, col);
            int x = temp.x()-pt.x();
            int y = temp.y()-pt.y();

            if(x*x+y*y < _r*_r)
                return true;
        }
    }
}


//鼠标点击事件
void ChessBoard::mousePressEvent(QMouseEvent *ev)
{
    QPoint pt = ev->pos();
    //将pt转化成棋盘的像行列值
    //判断这个行列值上面有没有棋子
    int row, col;

    //点击棋盘外面就不做处理
    if(!getRowCol(pt, row, col))
        return;

    _clickId = -1;
    int i;

    //判断是哪一个棋子被选中，根据ID（这里的局部i）来记录下来
    for(i = 0; i <= 31; i++)
    {
        if(_ChessPieces[i]._row == row && _ChessPieces[i]._col == col && _ChessPieces[i]._deal == false)
            break;
    }


    if(i < 32)
        _clickId = i;  //选中的棋子的ID


    if(_selectId == -1)//选中棋子
    {
        if(_clickId != -1)
        {
            if(_bRedTrue == _ChessPieces[_clickId]._red)
            {
                _selectId = _clickId;
            }

        }
    }
    else//走棋子
    {
        if(canMove(_selectId, _clickId, row, col ))
        {
            //_selectId为第一次点击选中的棋子，
            //_clickId为第二次点击||被杀的棋子ID，准备选中棋子下子的地方
            _ChessPieces[_selectId]._row = row;
            _ChessPieces[_selectId]._col = col;
            if(_clickId != -1)
                _ChessPieces[_clickId]._deal = true;

            _selectId = -1;
            _bRedTrue = !_bRedTrue;
        }

    }

    update();

}

//总的移动规则，选中准备下的棋子，被杀的棋子， 准备移动到的目的行列值
bool ChessBoard::canMove(int moveId, int killId, int row, int col)
{
    //1.确定是选择其它棋子还是走棋
    //2.是否需要使用到canMoveXXX()来做限制
    //3.罗列出所有情况，和需要的得到的结果值 ==>  然后进行中间的逻辑层判断※不要受到别人的代码框架的束缚※
        if(_ChessPieces[moveId]._red == _ChessPieces[killId]._red)  //选择其它棋子，返回false
        {
            if(killId == -1)  //其中有一个特殊情况，黑+_ChessPieces[-1]._red ==> 也需要判断能否
            {
                switch (_ChessPieces[moveId]._type)
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
                }

            }

            _selectId = killId;
            update();

            return false;
        }
        else  //选择其走棋，返回true
        {
            switch (_ChessPieces[moveId]._type)
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
            }
            return true;
        }




}

bool ChessBoard::canMoveJIANG(int moveId, int killId, int row, int col)
{
    if(_ChessPieces[moveId]._red) //红 将
    {
        if(row > 2 || col < 3 || col > 5) return false;
    }
    else  //黑 将
    {
        if(row < 7 || col < 3 || col > 5) return false;
    }

    int dr = _ChessPieces[moveId]._row - row;
    int dc = _ChessPieces[moveId]._col - col;
    int d = abs(dr)*10 + abs(dc);
    if(d == 1 || d == 10)
        return true;

    return false;
}

bool ChessBoard::canMoveSHI(int moveId, int killId, int row, int col)
{
    if(_ChessPieces[moveId]._red) //红 士
    {
        if(row > 2 || col < 3 || col > 5) return false;
    }
    else  //黑 士
    {
        if(row < 7 || col < 3 || col > 5) return false;
    }

    int dr = _ChessPieces[moveId]._row - row;
    int dc = _ChessPieces[moveId]._col - col;
    int d = abs(dr)*10 + abs(dc);
    if(d == 11)
        return true;

    return false;
}

bool ChessBoard::canMoveXIANG(int moveId, int killId, int row, int col)
{
    if(_ChessPieces[moveId]._red) //红
    {
        if(row > 4) return false;
    }
    else  //黑
    {
        if(row < 5) return false;
    }



    int dr = _ChessPieces[moveId]._row - row;
    int dc = _ChessPieces[moveId]._col - col;
    int d = abs(dr)*10 + abs(dc);

    int dr2 = (_ChessPieces[moveId]._row + row)/2;
    int dc2 = (_ChessPieces[moveId]._col + col)/2;

    //象眼被堵，就不能够调，就会有i属于0~31，返回false
    int i = 0;
    for(i = 0; i <= 31; i++)
    {
        if(_ChessPieces[i]._row == dr2 && _ChessPieces[i]._col == dc2 && _ChessPieces[i]._deal == false)
            break;
    }

    if(0 <= i && i <= 31)
        return false;


    if(d == 22)
        return true;

    return false;
}

bool ChessBoard::canMoveMA(int moveId, int killId, int row, int col)
{

    int dr = _ChessPieces[moveId]._row - row;
    int dc = _ChessPieces[moveId]._col - col;
    int d = abs(dr)*10 + abs(dc);

    int dr2 = (_ChessPieces[moveId]._row + row)/2;
    int dc2 = (_ChessPieces[moveId]._col + col)/2;


    //蹩脚马
    if(abs(dr) == 2 && abs(dc)==1)
    {
        int i = 0;
        if(row < _ChessPieces[moveId]._row )
        {
            for(i = 0; i <= 31; i++)
            {
                if(_ChessPieces[i]._row == (_ChessPieces[moveId]._row-1) && _ChessPieces[i]._col == _ChessPieces[moveId]._col && _ChessPieces[i]._deal == false)
                    break;
            }
        }
        else
        {
            for(i = 0; i <= 31; i++)
            {
                if(_ChessPieces[i]._row == (_ChessPieces[moveId]._row+1) && _ChessPieces[i]._col == _ChessPieces[moveId]._col && _ChessPieces[i]._deal == false)
                    break;
            }
        }

        if(0 <= i && i <= 31)
            return false;
    }


    if(abs(dr) == 1 && abs(dc)==2)
    {
        int i = 0;
        if(col < _ChessPieces[moveId]._col)
        {

            for(i = 0; i <= 31; i++)
            {
                if(_ChessPieces[i]._row == _ChessPieces[moveId]._row && _ChessPieces[i]._col == (_ChessPieces[moveId]._col-1) && _ChessPieces[i]._deal == false)
                    break;
            }
        }
        else
        {
            for(i = 0; i <= 31; i++)
            {
                if(_ChessPieces[i]._row == _ChessPieces[moveId]._row && _ChessPieces[i]._col == (_ChessPieces[moveId]._col+1) && _ChessPieces[i]._deal == false)
                    break;
            }
        }

        if(0 <= i && i <= 31)
            return false;

    }

    if(d == 12 || d == 21)
        return true;

    return false;
}

bool ChessBoard::canMoveCHE(int moveId, int killId, int row, int col)
{
    int ret = getStoneCountAtLine(_ChessPieces[moveId]._row, _ChessPieces[moveId]._col, row, col);
    if(ret == 0)
        return true;
    return false;
}

bool ChessBoard::canMovePAO(int moveId, int killId, int row, int col)
{
    int ret = getStoneCountAtLine(row, col, _ChessPieces[moveId]._row, _ChessPieces[moveId]._col);
    if(killId != -1)
    {
        if(ret == 1) return true;
    }
    else
    {
        if(ret == 0) return true;
    }
    return false;
}

bool ChessBoard::canMoveBING(int moveId, int killId, int row, int col)
{
    int dr = _ChessPieces[moveId]._row - row;
    int dc = _ChessPieces[moveId]._col - col;
    int d = abs(dr)*10 + abs(dc);
    if(d != 1 && d != 10) return false;


    if(_ChessPieces[moveId]._red) //红 兵
    {


        if(row <  _ChessPieces[moveId]._row) return false;
        if(_ChessPieces[moveId]._row == 3 || _ChessPieces[moveId]._row == 4)
        {
            if(col == _ChessPieces[moveId]._col && row == (_ChessPieces[moveId]._row+1))
                return true;
        }
        else
        {
            if((col == _ChessPieces[moveId]._col && row >= 5) || (row == _ChessPieces[moveId]._row && abs(col-_ChessPieces[moveId]._col)==1))
                    return true;
        }
        return false;
    }
    else  //黑 兵
    {
        if(row >  _ChessPieces[moveId]._row) return false;
        if(_ChessPieces[moveId]._row == 5 || _ChessPieces[moveId]._row == 6)
        {
            if(col == _ChessPieces[moveId]._col && row == (_ChessPieces[moveId]._row-1))
                return true;
        }
        else
        {
            if((col == _ChessPieces[moveId]._col && row <= 4) || (row == _ChessPieces[moveId]._row && abs(col-_ChessPieces[moveId]._col)==1))
                    return true;
        }
        return false;

    }

    return true;
}




