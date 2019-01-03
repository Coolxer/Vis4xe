#include "lcd.h"

Lcd::Lcd(unsigned short rows, unsigned short cols, QColor color, QWidget* widget) : QWidget (widget)
{
    this->rows = rows;
    this->cols = cols;
    this->color = color;

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
            Cell* cell = new Cell(this, numberOfCells, this->color);

            cell->setGeometry(QRect((25 * j) + 5, (i * 35) + 5, 20, 30));

            //cell->setStyleSheet("QLabel { color: #FFFFFF; font-size: 25px;}");

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
            direction = -rows;
            break;
        case Qt::Key_Down:
            direction = rows;
            break;
        case Qt::Key_Right:
            direction = 1;
            break;
        case Qt::Key_Escape:
            cancelChanges();
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
            int id = cells[selectedCell]->getId();

            if(direction != 1)
            {
                for(int i = 0; i < operationCells.length(); i++)
                {
                    if((operationCells[i] + direction < cells.length()) && (operationCells[i] + direction >= 0))
                    {
                        cells[operationCells[i]]->clear();
                        cells[operationCells[i]]->setStyleSheet("QLabel { background-color: #0099ff; font-size: 25px; }");
                        cells[operationCells[i]]->setId(-1);

                        operationCells[i] += direction;

                        cells[operationCells[i]]->setText(selectedString.at(i));
                        cells[operationCells[i]]->setStyleSheet("QLabel { background-color: #ff0000; font-size: 25px; }");
                        cells[operationCells[i]]->setId(id);
                    }
                }
            }
            else
            {
                cells[operationCells[0]]->clear();
                cells[operationCells[0]]->setStyleSheet("QLabel { background-color: #0099ff; font-size: 25px; }");
                cells[operationCells[0]]->setId(-1);

                for(int i = 0, m = 0; i < operationCells.length(); i++, m++)
                {
                    operationCells[i] += 1; //direction;

                    cells[operationCells[i]]->setText(selectedString.at(m));
                    cells[operationCells[i]]->setStyleSheet("QLabel { background-color: #ff0000; font-size: 25px; }");
                    cells[operationCells[i]]->setId(id);
                }
            }
        }
    }
}

void Lcd::setSelectedCell(int m)
{   
    int id = cells[m]->getId();

    if(id != -1)
    {
        selectedCell = m;

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

        operationCells = selectedNumbersOfCells;
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
        cells[selectedNumbersOfCells[i]]->setId(cells[selectedCell]->getId());
    }

    cancelEditMode();
}

void Lcd::acceptChanges()
{
    cancelEditMode();
}

void Lcd::cancelEditMode()
{
    editMode = false;

    for(int i = 0; i < selectedNumbersOfCells.length(); i++)
    {
        QString styles = "QLabel{ background-color: %1; font-size: 25px; }";
        cells[selectedNumbersOfCells[i]]->setStyleSheet(styles.arg(color.name()));
    }

    selectedString.clear();
    selectedNumbersOfCells.clear();
    operationCells.clear();
}


