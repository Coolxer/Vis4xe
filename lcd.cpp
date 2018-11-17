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

Lcd::Lcd(unsigned short rows, unsigned short cols, QColor color, QWidget* widget, QVector <Cell*> cells) : QWidget(widget)
{
    this->rows = rows;
    this->cols = cols;
    this->color = color;

    this->widget = widget;

    this->cells = cells;

    setGeometry(QRect(145, 195, 505, 145));
    setStyleSheet("QWidget{ background-color:  #66c2ff; }");

    //initCells();

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

        int key = event->key();

        switch(key)
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
            cancelEditMode();
            break;
        case Qt::Key_Delete:
            qDebug()<<"you";
        }

        if(direction != 0)
        {
            int id = cells[selectedCell]->getId();

            if(direction != 1)
            {
                for(int i = 0; i < selectedNumbersOfCells.length(); i++)
                {
                    if((selectedNumbersOfCells[i] + direction < cells.length()) && (selectedNumbersOfCells[i] + direction >= 0))
                    {
                        cells[selectedNumbersOfCells[i]]->clear();
                        cells[selectedNumbersOfCells[i]]->setStyleSheet("QLabel { background-color: #0099ff; font-size: 25px; }");
                        cells[selectedNumbersOfCells[i]]->setId(-1);

                        selectedNumbersOfCells[i] += direction;

                        cells[selectedNumbersOfCells[i]]->setText(selectedString.at(i));
                        cells[selectedNumbersOfCells[i]]->setStyleSheet("QLabel { background-color: #ff0000; font-size: 25px; }");
                        cells[selectedNumbersOfCells[i]]->setId(id);
                    }
                }
            }
            else
            {
                cells[selectedNumbersOfCells[0]]->clear();
                cells[selectedNumbersOfCells[0]]->setStyleSheet("QLabel { background-color: #0099ff; font-size: 25px; }");
                cells[selectedNumbersOfCells[0]]->setId(-1);

                for(int i = 0, m = 0; i < selectedNumbersOfCells.length(); i++, m++)
                {
                    selectedNumbersOfCells[i] += 1; //direction;

                    cells[selectedNumbersOfCells[i]]->setText(selectedString.at(m));
                    cells[selectedNumbersOfCells[i]]->setStyleSheet("QLabel { background-color: #ff0000; font-size: 25px; }");
                    cells[selectedNumbersOfCells[i]]->setId(id);
                }
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
            //checks if the other cells have got the same id as the selected cell (same string)
            if(id == cells[i]->getId())
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

void Lcd::cancelEditMode()
{
    editMode = false;

    int id = cells[selectedCell]->getId();

    for(int i = 0; i < selectedNumbersOfCells.length(); i++)
        cells[selectedNumbersOfCells[i]]->setStyleSheet("QLabel { background-color: #0099ff; font-size: 25px; }");

    selectedString.clear();
    selectedNumbersOfCells.clear();
}


