#include <iostream>
using namespace std;

#define DIMENSION 9
#define NCELLS (DIMENSION * DIMENSION)
#define MAXCANDIDATES (DIMENSION + 1)

struct Point {
    int x, y;
};

struct BoardType {
    int m[DIMENSION + 1][DIMENSION + 1]; // Содержимое доски
    int freecount;                       // Количество пустых клеток
    Point move[NCELLS + 1];              // Ходы
};

bool finished = false;
long long steps = 0; // Счётчик шагов

// выбирает следующую клетку для заполнения
void next_square(Point* p, BoardType* board) {
    // Заглушка: просто ставим -1, -1 (нет хода)
    p->x = -1;
    p->y = -1;
}

// определяет, какие цифры можно поставить в клетку
void possible_values(Point p, BoardType* board, bool possible[]) {
    for (int i = 1; i <= DIMENSION; i++) possible[i] = true; // Заглушка: разрешено всё
}

// заполняет клетку
void fill_square(Point p, int value, BoardType* board) {
    board->m[p.x][p.y] = value;
    board->freecount--;
}

// освобождает клетку
void free_square(Point p, BoardType* board) {
    board->m[p.x][p.y] = 0;
    board->freecount++;
}

// вывод доски
void print_board(BoardType* board) {
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++)
            cout << board->m[i][j] << " ";
        cout << endl;
    }
}

// построение списка возможных кандидатов
void construct_candidates(int a[], int k, BoardType* board, int c[]) {
    bool possible[DIMENSION + 1];

    next_square(&(board->move[k]), board); // выбираем следующую клетку

    int nc = 0;

    if (board->move[k].x < 0 || board->move[k].y < 0) {
        return; // нет допустимых ходов
    }

    possible_values(board->move[k], board, possible);

    for (int i = 1; i <= DIMENSION; i++) {
        if (possible[i]) {
            c[nc] = i;
            nc++;
        }
    }
}

void make_move(int a[], int k, BoardType* board) {
    fill_square(board->move[k], a[k], board);
}

void unmake_move(int a[], int k, BoardType* board) {
    free_square(board->move[k], board);
}

bool is_a_solution(int a[], int k, BoardType* board) {
    steps++;
    return (board->freecount == 0);
}

void process_solution(int a[], int k, BoardType* board) {
    finished = true;
    cout << "Решение найдено:\n";
    print_board(board);
}

int main() {
    BoardType board{};
    board.freecount = DIMENSION * DIMENSION; // по умолчанию доска пустая

    print_board(&board);
    return 0;
}
