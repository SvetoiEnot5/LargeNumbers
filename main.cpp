#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "header.h"

using namespace std;

void itobin(LONG_BINARY_NUMBER &numbBin, LONG_NUMBER &numb, int N) {
    LONG_NUMBER a;
    int oldsize = -1;
    a = numb;
    while (!((a.digArr[a.pointPlace - 1] == 0) && (a.digArr.size() == oldsize) && (a.pointPlace == 1))) {
        numbBin.binArr.push_back(a.digArr[a.pointPlace - 1] % 2);
        oldsize = a.digArr.size();
        a = longDiv(a, 2, 0);
    }
    numbBin.pointPlace = numbBin.binArr.size();
    cout << endl;
    cout << endl;

    for (int i = 0; i < N; i++) {
        numbBin.binArr.push_back(longMult(numb));
    }
}

class Empty_Enter {};
class file_open_error {};
class Unexpected_Symbol_Error {};
int main()
{
    setlocale(0, "");
    ifstream f1;
    ofstream f2;
    int N = 100;
    unsigned int start_time = clock();
    try {
        f1.open("C:\\laba.txt", ios::in);
        if (f1.fail()) throw file_open_error();
        if (f1.get() == EOF) throw Empty_Enter();
    }
    catch (file_open_error) {
        f2 << "file open error\n";
        exit(1);
    }
    catch (Empty_Enter) {
        f1.close();
        f2 << "File is empty\n";
        exit(1);
    }
    f1.seekg(0, ios::beg);

    // считывание чисел
    LONG_NUMBER first, second;

    string num;
    f1 >> num;
    {
        int i = 0;
        if (num[i] == '-') {
            first.isNegative = true;
            i++;
        }
        while ((i < num.length()) && (num[i] != ' ') && (num[i] != '\n') && (num[i] != '\0')) {
            if ((num[i] == ',') || (num[i] == '.')) {
                first.pointPlace = i;
                i++;
            };
            first.digArr.push_back(num[i] - 48);
            i++;
        }
        cout << "Изначальное первое число:\n";
        if (first.isNegative) cout << '-';
        for (int j = 0; j < first.digArr.size(); j++)
        {
            if (j == first.pointPlace) cout << ".";
            cout << first.digArr[j];
        }

        f1 >> num;
        i = 0;
        if (num[i] == '-') {
            second.isNegative = true;
            i++;
        }

        while ((i < num.length()) && (num[i] != ' ') && (num[i] != '\n') && (num[i] != '\0')) {
            if ((num[i] == ',') || (num[i] == '.')) {
                second.pointPlace = i - second.isNegative;
                i++;
            };
            second.digArr.push_back(num[i] - 48);
            i++;
        }
        cout << "\nИзначальное второе число:\n";
        if (second.isNegative) cout << '-';
        for (int j = 0; j < second.digArr.size(); j++)
        {
            if (j == second.pointPlace) cout << ".";
            cout << second.digArr[j];
        }
    }
    f1.close();


    // перевод в двоичную сс
    LONG_BINARY_NUMBER firstBin, secondBin;

    itobin(firstBin, first, N);
    cout << "Первое число в двоичной системе счисления:\n";
    for (int i = firstBin.pointPlace - 1; i >= 0; i--) {
        cout << firstBin.binArr[i];
    }
    cout << ".";
    for (int i = firstBin.pointPlace; i < firstBin.binArr.size(); i++) {
        cout << firstBin.binArr[i];
    }

    itobin(secondBin, second, N);
    cout << "Второе число в двоичной системе счисления:\n";
    for (int i = secondBin.pointPlace - 1; i >= 0; i--) {
        cout << secondBin.binArr[i];
    }
    cout << ".";
    for (int i = secondBin.pointPlace; i < secondBin.binArr.size(); i++) {
        cout << secondBin.binArr[i];
    }

    // операция побитового исключающее или
    LONG_BINARY_NUMBER answer;
    for (int i = firstBin.pointPlace - 1, j = secondBin.pointPlace - 1; ((i >= 0) && (j >= 0)); i--, j--)
    {
        answer.binArr.push_back(firstBin.binArr[i] ^ secondBin.binArr[j]);
    }
    answer.pointPlace = answer.binArr.size();
    for (int i = firstBin.pointPlace, j = secondBin.pointPlace; ((i < firstBin.binArr.size()) && (j < secondBin.binArr.size())); i++, j++) {
        answer.binArr.push_back(firstBin.binArr[i] ^ secondBin.binArr[j]);
    }
    cout << endl << endl;

    cout << "Результат побитового исключающее или в двоичной системе счисления:\n";
    for (int i = 0; i < answer.binArr.size(); i++) {
        if (answer.pointPlace == i) cout << ".";
        cout << answer.binArr[i];
    }
    // Приближённый перевод из двоичной в десятичную
    float sum = 0.0;
    for (int i = answer.pointPlace-1, j = 0; i >=0; i--, j++) {
        if(answer.binArr[i]) sum += pow(2,j);
    }
    for (int i = answer.pointPlace,j=-1; (i < answer.binArr.size())&&(j>-15); i++, j--) {
        if (answer.binArr[i]) sum += pow(2, j);
    }
    cout << "\n\nПриближённое число в десятичной системе счисления: " << sum<<endl<<endl;
    try {
        f2.open("C:\\res.txt", ios::out);
        if (f2.fail()) throw file_open_error();
    }
    catch (file_open_error) {
        f2 << "file 2 open error\n";
        exit(1);
    }
    for (int i = 0; i < answer.binArr.size();i++) {
        if (i == answer.pointPlace) f2 << ".";
        f2 << answer.binArr[i];
    }
    f2.close();
    cout << "Время работы программы: " << clock() - start_time << " мс\n\n";
}

