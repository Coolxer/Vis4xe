#include "lcd.h"

Lcd::Lcd(unsigned short rows, unsigned short cols, QColor color, QWidget* widget) : QWidget (widget)
{

    this->rows = rows;
    this->cols = cols;
    this->color = color;

    this->widget = widget;

    /* *********** */

    //for not typing in all the time during tests and developing
    this->rows = 4;
    this->cols = 20;

    /* ************* */

    layout = new QGridLayout;

    setGeometry(QRect(150, 200, (20 * this->cols) + 63, (30 * this->rows) + 15));
    setStyleSheet("QWidget{ background-color:  #66c2ff; }");

    numberOfCells = rows * cols;

    initCells();

    //this->setMouseTracking(true);
    this->setFocusPolicy(Qt::ClickFocus);
}

Lcd::~Lcd()
{
    delete widget;
    delete layout;
}

void Lcd::initCells()
{
    /*
    unsigned short m = 0 ;

    for(unsigned short i = 0; i < rows; i++)
    {
        for(unsigned short j = 0; j < cols; j++)
        {
            cells.push_back(new Cell(widget, QColor(255, 255, 255, 0)));

            cells[m]->setGeometry(QRect(0, 0, 20, 30));
            cells[m]->setStyleSheet("QLabel { background-color: #0099ff; color: #FFFFFF; font-size: 25px; }");
            cells[m]->setAlignment(Qt::AlignCenter);

            cells[m]->move(150 + (25 * j), 200 + (i * 35));
            m++;
        }
    }
*/
    for(unsigned short i = 0; i < rows; i++)
    {
        for(unsigned short j = 0; j < cols; j++)
        {
            Cell* cell = new Cell(widget, QColor(255, 255, 255, 0));

            cell->setMinimumSize(20, 30);
            cell->setMaximumSize(20, 30);
            cell->setGeometry(QRect(0, 0, 20, 30));

            //mapps the coordinates of the cell to global numbers
            //cell->mapToGlobal(cell->pos());

            cell->setStyleSheet("QLabel { background-color: #0099ff; color: #FFFFFF; font-size: 25px;}");
            cell->setAlignment(Qt::AlignCenter);

            cells.push_back(cell);

            layout->addWidget(cell, i, j);
        }
    }

    qDebug()<<cells[19]->pos();

    for(int i = 0 ; i< 7; i++)
    {
        cells[i]->setId(1);
        cells[i]->setText("a");
    }

    this->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setGeometry(QRect(0, 0, cols * 20, rows * 30));
    layout->setSpacing(0);
}

void Lcd::mousePressEvent(QMouseEvent* event)
{
    QPoint position = event->pos();

    /*
    if(editMode != nullptr)
    {
        delete editMode;
        editMode = nullptr;
    }
    */

    for(int i = 0; i < 80; i++)
    {
        if(((position.x() >= cells[i]->x()) && (position.x() <= cells[i]->x() + cells[i]->width())) && ((position.y() >= cells[i]->y()) && (position.y() <= cells[i]->y() + cells[i]->height())))
        {
            int id = cells[i]->getId();

            if(id != -1)
            {
                for(int i = 0; i <80; i++)
                {
                    if(cells[i]->getId() == id)
                    {
                        currentString += cells[i]->text();
                        cellsNumbers.push_back(i);
                        cells[i]->setStyleSheet("QLabel{background-color: red;}");
                    }
                }

                editMode = true;

                //if(editMode == nullptr)
                //    editMode = new EditMode(this, string);
            }

            break;
        }
    }
}

void Lcd::keyPressEvent(QKeyEvent* event)
{
    if(editMode)
    {
        int direction = 0;

        switch(event->key())
        {
        case Qt::Key_Left:
            direction = -1;
            break;
        case Qt::Key_Up:
            direction = -20;
            break;
        case Qt::Key_Down:
            direction = 20;
            break;
        case Qt::Key_Right:
            direction = 1;
            break;
        }

        for(int i = 0 ; i < currentString.length(); i++)
        {
            if((cellsNumbers[i] + direction < cells.length()) && (cellsNumbers[i] + direction >= 0))
            {
                cells[cellsNumbers[i]]->clear();
                cells[cellsNumbers[i] + direction]->setText(currentString.at(i));
                cellsNumbers[i] += direction;
            }
        }
    }
}


