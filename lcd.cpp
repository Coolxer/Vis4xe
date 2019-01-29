#include "lcd.h"

Lcd::Lcd(unsigned short rows, unsigned short cols, QWidget* widget) : QWidget (widget)
{
    this->rows = rows;
    this->cols = cols;

    int width = (this->cols * 20) + (this->cols + 1) * 5;
    int height = (this->rows * 30) + (this->rows + 1) * 5;

    setGeometry(QRect((widget->width() - 160)/2 - width/2, widget->height()/2 - height/2, width, height));
    setStyleSheet("QWidget{ background-color:  #FFFFFF; }");

    initCells();

    //this->setMouseTracking(true);
    this->setFocusPolicy(Qt::ClickFocus);
}

void Lcd::initCells()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            Cell* cell = new Cell(this, numberOfCells);

            cell->setGeometry(QRect((25 * j) + 5, (i * 35) + 5, 20, 30));

            cells.push_back(cell);
            numberOfCells++;
        }
    }
}

void Lcd::organize()
{
    int m = 0;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cells[m]->setGeometry(QRect((25 * j) + 5, (i * 35) + 5, 20, 30));
            m++;
        }
    }

}

void Lcd::loadCellsFromFile(QVector <Cell*> cells)
{
    this->cells = cells;
    organize();
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
            direction = -cols;
            break;
        case Qt::Key_Down:
            direction = cols;
            break;
        case Qt::Key_Right:
            direction = 1;
            break;
        case Qt::Key_Escape:
            cancelChanges();
            break;
        case Qt::Key_Return:
            acceptChanges();
            break;
        case Qt::Key_Enter:
            acceptChanges();
            break;
        case Qt::Key_Delete:
            qDebug()<<"you";
            break;
        }

        if(direction != 0)
        {
            if(direction == 1)
            {
                int currentRow = (operationCells[0] / cols) + 1;

                if((operationCells[operationCells.length() - 1] < (cols * currentRow) -1))
                {
                    cells[operationCells[0]]->clear();
                    cells[operationCells[0]]->setStyleSheet("QLabel { background-color: #0099ff; font-size: 25px; }");
                    cells[operationCells[0]]->setId(-1);

                    for(int i = 0, m = 0; i < operationCells.length(); i++, m++)
                    {
                        operationCells[i] += direction;

                        cells[operationCells[i]]->setText(selectedString.at(m));
                        cells[operationCells[i]]->setStyleSheet("QLabel { background-color: #ff0000; font-size: 25px; }");
                        cells[operationCells[i]]->setId(currentId);
                    }
                }
            }
            else
            {
                int currentRow = (operationCells[0] / cols);

                bool allowToMove = false;

                if(direction == -1)
                {
                    if(operationCells[0] > currentRow * cols)
                        allowToMove = true;
                }
                else
                {
                    if(direction == cols && operationCells[0] + direction < rows*cols && currentRow < rows )
                        allowToMove = true;

                    else if (direction == -cols && operationCells[0] + direction >= 0  && currentRow > 0)
                        allowToMove = true;
                }

                if(allowToMove)
                {
                    for(int i = 0; i < operationCells.length(); i++)
                    {

                        cells[operationCells[i]]->clear();
                        cells[operationCells[i]]->setStyleSheet("QLabel { background-color: #0099ff; font-size: 25px; }");
                        cells[operationCells[i]]->setId(-1);

                        operationCells[i] += direction;

                        cells[operationCells[i]]->setText(selectedString.at(i));
                        cells[operationCells[i]]->setStyleSheet("QLabel { background-color: #ff0000; font-size: 25px; }");
                        cells[operationCells[i]]->setId(currentId);
                    }
                }
            }
        }
    }
}

void Lcd::setSelectedCell(int m)
{
    currentId = cells[m]->getId();

    if(currentId != -1)
    {
        selectedCell = m;

        for(int i = 0; i < numberOfCells; i++)
        {
            //checks if the other cells have got the same id as the selected cell (same string)
            if(cells[i]->getId() == currentId)
            {
                selectedString += cells[i]->text();
                operationCells.push_back(i);
                cells[i]->setStyleSheet("QLabel { background-color: #ff0000; font-size: 25px; }");
            }
        }

        selectedNumbersOfCells = operationCells;

        editMode = true;
    }
}

void Lcd::cancelChanges()
{
    for(int i = 0; i < selectedNumbersOfCells.length(); i++)
    {
        cells[operationCells[i]]->clear();
        cells[operationCells[i]]->setId(-1);

        cells[selectedNumbersOfCells[i]]->setText(selectedString.at(i));
        cells[selectedNumbersOfCells[i]]->setId(currentId);
    }
    exitEditMode();
}

void Lcd::acceptChanges()
{
    exitEditMode();
}

void Lcd::exitEditMode()
{
    editMode = false;
    selectedCell = -1;
    currentId = -1;

    for(int i = 0; i < selectedNumbersOfCells.length(); i++)
        cells[operationCells[i]]->setStyleSheet("QLabel{ background-color: #0099ff; font-size: 25px; }");

    selectedString.clear();
    selectedNumbersOfCells.clear();
    operationCells.clear();
}

void Lcd::unpin()
{
    //for(int i = 0; i <)


    exitEditMode();
}


