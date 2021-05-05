#include <stdio.h>
#include <stdlib.h>

int count = 0;

//documnet must in utf-8
void read_sudoku(int *sudoku){

    FILE *fdata;
    fdata = fopen("sudoku.csv", "r");
    if (fdata == NULL){
        printf("file error\n");
        return 0;
    }

    int tmp;

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            tmp = fgetc(fdata) - 48;
            //printf("%d ", tmp);
            *((sudoku + i * 9) + j) = tmp;
            fgetc(fdata);
        }
    }
    fclose(fdata);
}

void print_sudoku(int *sudoku){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            printf("%d ", *((sudoku + i * 9) + j));
        }
        printf("\n");
    }
}

int check(int *sudoku, int row, int column, int num){

    //check number in same row
    for (int j = 0; j < 9; j++){
        if (*((sudoku + row * 9) + j) == num)
            return 0;
    }

    //check number in same column
    for (int i = 0; i < 9; i++){
        if (*((sudoku + i * 9) + column) == num)
            return 0;
    }

    //check number in same block
    for (int i = row / 3 * 3; i < (row / 3 + 1) * 3; i++){
        for (int j = column / 3 * 3; j < (column / 3 + 1) * 3; j++){
            if (*((sudoku + i * 9) + j) == num)
                return 0;
        }
    }

    return 1;

}

/*
*Find the only answer of sudoku
*sudoku: array of sudoku
*row, column: the index to fill in new number
*/
int solve_sudoku(int *sudoku, int row, int column){

    int done = 0;

    //change to next row after a row is filled
    if (column > 8){
        row++;
        column = 0;
    }

    //sudoku solved, tell upper recursion to finished the program
    if (row > 8){
        print_sudoku(sudoku);
        return 1;
    }

    if (*((sudoku + row * 9) + column) != 47){
        solve_sudoku(sudoku, row, column + 1);  //continue if the number is given
    } else{
        for (int i = 1; i < 10; i++){
            count++;
            //printf("row: %d, column: %d, i: %d, check: %d\n", row, column, i, check(sudoku, row, column, i));
            if (check(sudoku, row, column, i) == 1){
                *((sudoku + row * 9) + column) = i;
                //print_sudoku(sudoku);
                done = solve_sudoku(sudoku, row, column + 1); 
                if (done == 1){
                    return 1;  //sudoku solved, tell upper recursion to finished the program
                }
                *((sudoku + row * 9) + column) = 47;  //fresh sudoku' state for next trying
            }
        }
    }
}

int main(){

    int sudoku[9][9];
    read_sudoku(sudoku);
    print_sudoku(sudoku);
    printf("\n");
    solve_sudoku(sudoku, 0, 0);
    printf("===FINISH, TRY: %d===", count);
    return 0;
}