#include <stdio.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>

void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
            hStdOut,
            (TCHAR) ' ',
            cellCount,
            homeCoords,
            &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
            hStdOut,
            csbi.wAttributes,
            cellCount,
            homeCoords,
            &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );
}

#else // !_WIN32
#include <unistd.h>
#include <term.h>

void ClearScreen()
{
  if (!cur_term)
  {
     int result;
     setupterm( NULL, STDOUT_FILENO, &result );
     if (result <= 0) return;
  }

   putp( tigetstr( "clear" ) );
}
#endif

int updateTime(struct tm *p);

void print(int mat[][5]);

void digit0();
void digit1();
void digit2();
void digit3();
void digit4();
void digit5();
void digit6();
void digit7();
void digit8();
void digit9();
void colon();
void clear();

void checkDigit(int num);

int tWidht = 0;

int main() {
    time_t cTime = time(NULL);
    unsigned short num;

    if (cTime == -1) {
        printf("Nem sikerult az idot lekerni");
        return 1;
    }

    struct tm *ptm = localtime(&cTime);

    if (ptm == NULL) {
        printf("Nem sikerult a lokalis ido beallitasa");
        return 1;
    }

    while(1) {

        if(ptm->tm_hour<10){
            checkDigit(0);
        }else if(ptm->tm_hour>9 && ptm->tm_hour<20){
            checkDigit(1);
        }else if(ptm->tm_hour>19&&ptm->tm_hour<25) {
            checkDigit(2);
        }
        checkDigit(ptm->tm_hour%10);
        colon();
        num = ptm->tm_min;
        while(num >= 10)
        {
            num = num / 10;
        }
        if(ptm->tm_min<10){
            num = 0;
        }
        checkDigit(num);
        checkDigit(ptm->tm_min%10);
        Sleep(2000);
        tWidht = 10;
        clear();
        Sleep(1000);
        tWidht = 10;
        colon();
        Sleep(2000);
        updateTime(ptm);
        tWidht = 0;
        ClearScreen();
    }
    return 0;
}

int updateTime(struct tm *p){
    time_t cTime = time(NULL);
    if (cTime == -1) {
        printf("Nem sikerult az idot lekerni");
        return 1;
    }
    p = localtime(&cTime);

    return 0;
}

void print(int mat[][5]){
    COORD coord;
    coord.X = tWidht;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 5; i++) {
        coord.Y = i;
        SetConsoleCursorPosition(hConsole, coord);
        for (int j = 0; j < 5; j++) {
            if (i % 2 == 0) {
                if (mat[i][j] == 1)
                    printf("-");
                else
                    printf(" ");
            }
            else {
                if (mat[i][j] == 1)
                    printf("|");
                else
                    printf(" ");
            }
        }
        printf("\n");

    }
    tWidht+=5;
}

void digit0()
{
    // In matrix 0 used for space
    // and 1 for either - or |
    int mat[5][5] = { { 0, 1, 1, 1, 0 },
                      { 1, 0, 0, 0, 1 },
                      { 0, 0, 0, 0, 0 },
                      { 1, 0, 0, 0, 1 },
                      { 0, 1, 1, 1, 0 } };
    print(mat);
}
void digit1()
{
    // In matrix 0 used for space
    // and 1 for either - or |
    int mat[5][5] = { { 0, 0, 0, 0, 0 },
                      { 0, 0, 1, 0, 0 },
                      { 0, 0, 0, 0, 0 },
                      { 0, 0, 1, 0, 0 },
                      { 0, 0, 0, 0, 0 } };
    print(mat);
}
void digit2()
{
    // In matrix 0 used for space
    // and 1 for either - or |
    int mat[5][5] = { { 0, 1, 1, 1, 0 },
                      { 0, 0, 0, 0, 1 },
                      { 0, 1, 1, 1, 0 },
                      { 1, 0, 0, 0, 0 },
                      { 0, 1, 1, 1, 0 } };
    print(mat);
}
void digit3()
{
    // In matrix 0 used for space
    // and 1 for either - or |
    int mat[5][5] = { { 0, 1, 1, 1, 0 },
                      { 0, 0, 0, 0, 1 },
                      { 0, 1, 1, 1, 0 },
                      { 0, 0, 0, 0, 1 },
                      { 0, 1, 1, 1, 0 } };
    print(mat);
}
void digit4()
{
    // In matrix 0 used for space
    // and 1 for either - or |
    int mat[5][5] = { { 0, 0, 0, 0, 0 },
                      { 1, 0, 0, 0, 1 },
                      { 0, 1, 1, 1, 0 },
                      { 0, 0, 0, 0, 1 },
                      { 0, 0, 0, 0, 0 } };
    print(mat);
}
void digit5()
{
    // In matrix 0 used for space
    // and 1 for either - or |
    int mat[5][5] = { { 0, 1, 1, 1, 0 },
                      { 1, 0, 0, 0, 0 },
                      { 0, 1, 1, 1, 0 },
                      { 0, 0, 0, 0, 1 },
                      { 0, 1, 1, 1, 0 } };
    print(mat);
}
void digit6()
{
    // In matrix 0 used for space
    // and 1 for either - or |
    int mat[5][5] = { { 0, 1, 1, 1, 0 },
                      { 1, 0, 0, 0, 0 },
                      { 0, 1, 1, 1, 0 },
                      { 1, 0, 0, 0, 1 },
                      { 0, 1, 1, 1, 0 } };
    print(mat);
}
void digit7()
{
    // In matrix 0 used for space
    // and 1 for either - or |
    int mat[5][5] = { { 0, 1, 1, 1, 0 },
                      { 0, 0, 0, 0, 1 },
                      { 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 1 },
                      { 0, 0, 0, 0, 0 } };
    print(mat);
}
void digit8()
{
    // In matrix 0 used for space
    // and 1 for either - or |
    int mat[5][5] = { { 0, 1, 1, 1, 0 },
                      { 1, 0, 0, 0, 1 },
                      { 0, 1, 1, 1, 0 },
                      { 1, 0, 0, 0, 1 },
                      { 0, 1, 1, 1, 0 } };
    print(mat);
}
void digit9()
{
    // In matrix 0 used for space
    // and 1 for either - or |
    int mat[5][5] = { { 0, 1, 1, 1, 0 },
                      { 1, 0, 0, 0, 1 },
                      { 0, 1, 1, 1, 0 },
                      { 0, 0, 0, 0, 1 },
                      { 0, 1, 1, 1, 0 } };
    print(mat);
}
void colon(){
    int mat[5][5] = { { 0, 1, 1, 1, 0 },
                      { 0, 1, 0, 1, 0 },
                      { 0, 1, 1, 1, 0 },
                      { 0, 1, 0, 1, 0 },
                      { 0, 1, 1, 1, 0 } };
    print(mat);
}
void clear(){
    int mat[5][5] = { { 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0 } };
    print(mat);
}

void checkDigit(int num)
{
    // for digit 0
    if (num == 0)
        digit0();

        // for digit 1
    else if (num == 1)
        digit1();

        // for digit 2
    else if (num == 2)
        digit2();

        // for digit 3
    else if (num == 3)
        digit3();

        // for digit 4
    else if (num == 4)
        digit4();

        // for digit 5
    else if (num == 5)
        digit5();

        // for digit 6
    else if (num == 6)
        digit6();

        // for digit 7
    else if (num == 7)
        digit7();

        // for digit 8
    else if (num == 8)
        digit8();

        // for digit 9
    else if (num == 9)
        digit9();
}