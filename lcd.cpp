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
    int m = 0;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            Cell* cell = new Cell(this, m, QColor(255, 255, 255, 0));

            cell->setMinimumSize(20, 30);
            cell->setMaximumSize(20, 30);
            cell->setGeometry(QRect(0, 0, 20, 30));
            //cell->mapToGlobal(cell->pos());


            cell->setStyleSheet("QLabel { background-color: #0099ff; color: #FFFFFF; font-size: 25px;}");
            cell->setAlignment(Qt::AlignCenter);

            layout->addWidget(cell, i, j);
            cells.push_back(cell);
            m++;
        }
    }

    qDebug()<<layout->itemAt(19)->geometry().x();

    this->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setGeometry(QRect(0, 0, cols * 20, rows * 30));
    layout->setSpacing(0);
}

void Lcd::mousePressEvent(QMouseEvent* event)
{
    QPoint position = event->pos();

    //layout->
    //80

    for(int i = 0; i < 80; i++)
    {
        /*
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
            }
            break;
        }
        */

        int m = 0;

        int span = 1;

        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                //if(position.x() >= layout->getItemPosition(m, &i, &j, &span, &span))
                //    qDebug()<<"elo";

               // m++;
            }
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
        case Qt::Key_Escape:
            editMode = false;
            break;
        }

        for(int i = 0 ; i < selectedNumbersOfCells.length(); i++)
        {
            if((selectedNumbersOfCells[i] + direction < cells.length()) && (selectedNumbersOfCells[i] + direction >= 0))
            {
                cells[selectedNumbersOfCells[i]]->clear();
                cells[selectedNumbersOfCells[i] + direction]->setText(selectedString.at(i));
                selectedNumbersOfCells[i] += direction;
            }
        }
    }
}

void Lcd::setSelectedCell(int m)
{
    selectedCell = m;

    int id = cells[selectedCell]->getId();

    if(id != -1)
    {
        for(int i = 0; i < cells.length(); i++)
        {
            int helpId = cells[i]->getId();

            if(id == helpId)
            {
                selectedString += cells[i]->text();
                selectedNumbersOfCells.push_back(i);
;               cells[i]->setStyleSheet("QLabel { background-color: #ff0000; font-size: 25px; }");
            }
        }

        editMode = true;
    }
}

void Lcd::setHoveredCell(int m)
{
    hoveredCell = m;
}


