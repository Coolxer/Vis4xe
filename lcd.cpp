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

    setGeometry(QRect(145, 195, 505, 145));
    setStyleSheet("QWidget{ background-color:  #66c2ff; }");

    initCells();

    //this->setMouseTracking(true);
    this->setFocusPolicy(Qt::ClickFocus);
}

Lcd::~Lcd()
{
    delete widget;
}

void Lcd::initCells()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            Cell* cell = new Cell(this, numberOfCells, QColor(255, 255, 255, 0));

            cell->setMinimumSize(20, 30);
            cell->setMaximumSize(20, 30);
            cell->setGeometry(QRect((25 * j) + 5, (i * 35) + 5, 20, 30));

            cell->setStyleSheet("QLabel { background-color: #0099ff; color: #FFFFFF; font-size: 25px;}");
            cell->setAlignment(Qt::AlignCenter);

            cells.push_back(cell);
            numberOfCells++;
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
        for(int i = 0; i < numberOfCells; i++)
        {
            int helpId = cells[i]->getId();

            if(id == helpId)
            {
                selectedString += cells[i]->text();
                selectedNumbersOfCells.push_back(i);
                cells[i]->setStyleSheet("QLabel { background-color: #ff0000; font-size: 25px; }");
            }
        }

        editMode = true;
    }
}

void Lcd::setHoveredCell(int m)
{
    hoveredCell = m;
}


