#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

// 24 Разработать многопоточную программу для аппроксимации данных методом наименьших квадратов.
void Approximation(const vector<double>& x, const vector<double>& y, double& a, double& b) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, squarSumX = 0;

    for (int i = 0; i < x.size(); ++i) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        squarSumX += x[i] * x[i];
    }
    b = (sum_xy - sum_x * sum_y / x.size()) / (squarSumX - sum_x * sum_x / x.size());
    a = (sum_y - b * sum_x) / x.size();
}

DWORD WINAPI Calculation(LPVOID vecPair)
{
    pair<vector<double>, vector<double>>* par = reinterpret_cast<pair<vector<double>, vector<double>>*>(vecPair);
    vector<double> x = par->first;
    vector<double> y = par->second;
    double a, b;
    Approximation(x, y, a, b);
    cout <<"a = " << a << " b = " << b << endl;

    return 0;
}

int main()
{
    setlocale(LC_ALL, "ru");
    vector<double> x_1 = { 1, 2, 3, 4, 5 };
    vector<double> y_1 = { 2, 3, 4, 5, 6 };

    vector<double> x_2 = { 1, 2, 3, 4, 5 };
    vector<double> y_2 = { 5, 15, 25, 45, 65 };

    pair<vector<double>, vector<double>> first(x_1, y_1);
    pair<vector<double>, vector<double>> second(x_2, y_2);
    HANDLE hThread1 = CreateThread(NULL, 0, Calculation, &first, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, Calculation, &second, 0, NULL);
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    CloseHandle(hThread1);
    CloseHandle(hThread2);

    return 0;
}
