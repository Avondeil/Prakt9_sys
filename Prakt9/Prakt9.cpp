#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;



// 24 Разработать многопоточную программу для аппроксимации данных методом наименьших квадратов.
void Approximation(const vector<double>& x, const vector<double>& y, double& a, double& b) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, squarSumX = 0;

    // Вычисление сумм
    for (int i = 0; i < x.size(); ++i) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        squarSumX += x[i] * x[i];
    }
    a = (sum_xy - sum_x * sum_y / x.size()) / (squarSumX - sum_x * sum_x / x.size());
    b = (sum_y - a * sum_x) / x.size();
}

DWORD WINAPI Add(LPVOID nul)
{
    setlocale(LC_ALL, "ru");
    vector<double> x = { 1, 2, 3, 4, 5 }; 
    vector<double> y = { 2, 3, 4, 5, 6 }; 

    double a, b;
    Approximation(x, y, a, b);
    cout << "Исходные данные x: ";
    for (const auto x : x)
    {
        cout << x << " ";
    }
    cout << endl << "Исходные данные y: ";
    for (const auto y : y)
    {
        cout << y << " ";
    }
    cout << endl << "Результат: a = " << a << ", b = " << b << endl;

    return 0;
}

int main()
{
    HANDLE hThread;
    DWORD IDThread;
    hThread = CreateThread(NULL, 0, Add, NULL, 0, &IDThread);
    if (hThread == NULL)
    {
        return GetLastError();
    }
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    return 0;
}