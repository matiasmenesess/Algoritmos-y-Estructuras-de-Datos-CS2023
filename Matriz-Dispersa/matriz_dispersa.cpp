#include <iostream>
using namespace std;

struct Cell {
    int row, col, value;
    Cell* nextRow;
    Cell* nextCol;
    Cell(int r, int c, int v) : row(r), col(c), value(v), nextRow(nullptr), nextCol(nullptr) {}
};

struct Header {
    int index;
    Cell* next;
    Header* nextHeader;
    Header(int i) : index(i), next(nullptr), nextHeader(nullptr) {}
};

class SparseMatrix {
private:
    Header* rowHead;
    Header* colHead;
    int rows, cols;

    Header* getOrCreateRowHeader(int row) {
        Header* prev = nullptr;
        Header* curr = rowHead;
        while (curr && curr->index < row) {
            prev = curr;
            curr = curr->nextHeader;
        }
        if (!curr || curr->index != row) {
            Header* newHeader = new Header(row);
            if (prev) {
                prev->nextHeader = newHeader;
            } else {
                rowHead = newHeader;
            }
            newHeader->nextHeader = curr;
            return newHeader;
        }
        return curr;
    }

    Header* getOrCreateColHeader(int col) {
        Header* prev = nullptr;
        Header* curr = colHead;
        while (curr && curr->index < col) {
            prev = curr;
            curr = curr->nextHeader;
        }
        if (!curr || curr->index != col) {
            Header* newHeader = new Header(col);
            if (prev) {
                prev->nextHeader = newHeader;
            } else {
                colHead = newHeader;
            }
            newHeader->nextHeader = curr;
            return newHeader;
        }
        return curr;
    }

public:
    SparseMatrix(int r, int c) : rowHead(nullptr), colHead(nullptr), rows(r), cols(c) {}

    void insert(int row, int col, int value) {
        if (row < 0 || row >= rows || col < 0 || col >= cols || value == 0) return;

        Header* rowHeader = getOrCreateRowHeader(row);
        Header* colHeader = getOrCreateColHeader(col);
        Cell* newCell = new Cell(row, col, value);

        // Insertar en la fila
        Cell* rowPrev = nullptr;
        Cell* rowCurr = rowHeader->next;
        while (rowCurr && rowCurr->col < col) {
            rowPrev = rowCurr;
            rowCurr = rowCurr->nextRow;
        }
        if (rowPrev) {
            rowPrev->nextRow = newCell;
        } else {
            rowHeader->next = newCell;
        }
        newCell->nextRow = rowCurr;

        // Insertar en la columna
        Cell* colPrev = nullptr;
        Cell* colCurr = colHeader->next;
        while (colCurr && colCurr->row < row) {
            colPrev = colCurr;
            colCurr = colCurr->nextCol;
        }
        if (colPrev) {
            colPrev->nextCol = newCell;
        } else {
            colHeader->next = newCell;
        }
        newCell->nextCol = colCurr;
    }

    void display() {
        for (int i = 0; i < rows; ++i) {
            Header* rowHeader = getOrCreateRowHeader(i);
            Cell* cell = rowHeader->next;
            for (int j = 0; j < cols; ++j) {
                if (cell && cell->col == j) {
                    cout << cell->value << " ";
                    cell = cell->nextRow;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }

    SparseMatrix* add(SparseMatrix* other) {
        SparseMatrix* result = new SparseMatrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            Header* rowHeader1 = getOrCreateRowHeader(i);
            Header* rowHeader2 = other->getOrCreateRowHeader(i);
            Cell* cell1 = rowHeader1->next;
            Cell* cell2 = rowHeader2->next;

            while (cell1 || cell2) {
                if (cell1 && (!cell2 || cell1->col < cell2->col)) {
                    result->insert(cell1->row, cell1->col, cell1->value);
                    cell1 = cell1->nextRow;
                } else if (cell2 && (!cell1 || cell2->col < cell1->col)) {
                    result->insert(cell2->row, cell2->col, cell2->value);
                    cell2 = cell2->nextRow;
                } else {
                    result->insert(cell1->row, cell1->col, cell1->value + cell2->value);
                    cell1 = cell1->nextRow;
                    cell2 = cell2->nextRow;
                }
            }
        }
        return result;
    }

    SparseMatrix* subtract(SparseMatrix* other) {
        SparseMatrix* result = new SparseMatrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            Header* rowHeader1 = getOrCreateRowHeader(i);
            Header* rowHeader2 = other->getOrCreateRowHeader(i);
            Cell* cell1 = rowHeader1->next;
            Cell* cell2 = rowHeader2->next;

            while (cell1 || cell2) {
                if (cell1 && (!cell2 || cell1->col < cell2->col)) {
                    result->insert(cell1->row, cell1->col, cell1->value);
                    cell1 = cell1->nextRow;
                } else if (cell2 && (!cell1 || cell2->col < cell1->col)) {
                    result->insert(cell2->row, cell2->col, -cell2->value);
                    cell2 = cell2->nextRow;
                } else {
                    result->insert(cell1->row, cell1->col, cell1->value - cell2->value);
                    cell1 = cell1->nextRow;
                    cell2 = cell2->nextRow;
                }
            }
        }
        return result;
    }

    SparseMatrix* multiply(SparseMatrix* other) {
        if (cols != other->rows) {
            throw invalid_argument("Dimensiones incompatibles para la multiplicación");
        }
        SparseMatrix* result = new SparseMatrix(rows, other->cols);
        for (Header* rowHeader = rowHead; rowHeader; rowHeader = rowHeader->nextHeader) {
            for (Cell* cell1 = rowHeader->next; cell1; cell1 = cell1->nextRow) {
                Header* colHeader = other->getOrCreateColHeader(cell1->col);
                for (Cell* cell2 = colHeader->next; cell2; cell2 = cell2->nextCol) {
                    int value = cell1->value * cell2->value;
                    result->insert(cell1->row, cell2->col, result->getValue(cell1->row, cell2->col) + value);
                }
            }
        }
        return result;
    }

    int getValue(int row, int col) {
        Header* rowHeader = getOrCreateRowHeader(row);
        Cell* cell = rowHeader->next;
        while (cell) {
            if (cell->col == col) return cell->value;
            cell = cell->nextRow;
        }
        return 0;
    }

    SparseMatrix* transpose() {
        SparseMatrix* result = new SparseMatrix(cols, rows);
        for (Header* rowCurr = rowHead; rowCurr; rowCurr = rowCurr->nextHeader) {
            for (Cell* cell = rowCurr->next; cell; cell = cell->nextRow) {
                result->insert(cell->col, cell->row, cell->value);
            }
        }
        return result;
    }

    ~SparseMatrix() {
        Header* rowCurr = rowHead;
        while (rowCurr) {
            Cell* cellCurr = rowCurr->next;
            while (cellCurr) {
                Cell* toDelete = cellCurr;
                cellCurr = cellCurr->nextRow;
                delete toDelete;
            }
            Header* toDelete = rowCurr;
            rowCurr = rowCurr->nextHeader;
            delete toDelete;
        }
    }
};

int main() {
    SparseMatrix sm1(5, 5);
    sm1.insert(1, 1, 10);
    sm1.insert(2, 3, 20);
    sm1.insert(4, 0, 30);

    SparseMatrix sm2(5, 5);
    sm2.insert(1, 1, 5);
    sm2.insert(2, 3, 15);
    sm2.insert(4, 1, 25);

    cout << "Matriz 1:" << endl;
    sm1.display();

    cout << "Matriz 2:" << endl;
    sm2.display();

    SparseMatrix* sum = sm1.add(&sm2);
    cout << "Suma de Matrices:" << endl;
    sum->display();

    SparseMatrix* diff = sm1.subtract(&sm2);
    cout << "Resta de Matrices:" << endl;
    diff->display();

    SparseMatrix* transposed = sm1.transpose();
    cout << "Transpuesta de Matriz 1:" << endl;
    transposed->display();



    return 0;
}
