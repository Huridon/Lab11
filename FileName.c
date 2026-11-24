#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#define N 10
#define M 100
#define X_MIN 0.1
#define X_MAX 2.5

double FuncTask2(double x);
double CalcAvgPositive(double arr[], int size, double* sumPos, double* sumNeg, int* countPos, int* countNeg);
int SumAfterMinAbs(int arr[], int size, int* minAbsIdx);
int ClearInput();

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    setlocale(LC_NUMERIC, "C"); // разрешает ввод и вывод дробных чисел через точку

    // Task1
    printf("Задание 1\n\n");

    float A[N], A_orig[N];
    float temp, sum1 = 0.0f;
    int i, ok, inputError = 0;

    printf("Введите %d вещественных элементов массива A (через точку, например 8.44):\n", N);
    for (i = 0; i < N; i++)
    {
        printf("a[%d] = ", i + 1);
        ok = scanf("%f", &temp);
        ClearInput();

        if (ok != 1)
        {
            printf("Ошибка ввода элемента массива!\n");
            inputError = 1;
            break;
        }

        A_orig[i] = temp;
        A[i] = ceilf(temp);
        sum1 += A[i];
    }

    if (!inputError)
    {
        printf("\n| %6s | %17s | %14s |\n", "индекс", "исходное значение", "новое значение");
        printf("-----------------------------------------------\n");

        for (i = 0; i < N; i++)
        {
            printf("| %6d | %17.4f | %14.4f |\n", i, A_orig[i], A[i]);
        }

        printf("\nСреднее арифметическое преобразованного массива: %.4f\n", sum1 / N);
    }

    // Task2
    printf("\nЗадание 2\n\n");

    double B[M];
    double x, step, sumPos, sumNeg, avgPos;
    int countPos, countNeg;

    step = (X_MAX - X_MIN) / (M - 1);

    for (i = 0; i < M; i++)
    {
        x = X_MIN + i * step;
        B[i] = FuncTask2(x);
    }

    avgPos = CalcAvgPositive(B, M, &sumPos, &sumNeg, &countPos, &countNeg);

    printf("Имя массива: B | Сумма (+): %.4lf | Сумма (-): %.4lf | Кол-во (+): %d | Кол-во (-): %d | Среднее (+): %.4lf\n",
        sumPos, sumNeg, countPos, countNeg, avgPos);

    // Task3
    printf("\nЗадание 3\n\n");

    int n, minAbsIdx, sumAfter;
    int* C = NULL;

    printf("Введите количество элементов массива n: ");
    ok = scanf("%d", &n);
    ClearInput();

    if (ok != 1 || n <= 0)
    {
        printf("Ошибка ввода: n должно быть целым числом больше нуля\n");
    }
    else
    {
        C = (int*)malloc(n * sizeof(int));

        if (C == NULL)
        {
            printf("Ошибка выделения памяти!\n");
        }
        else
        {
            inputError = 0;
            printf("Введите %d целых чисел (положительных и отрицательных):\n", n);

            for (i = 0; i < n; i++)
            {
                printf("c[%d] = ", i + 1);
                ok = scanf("%d", &C[i]);
                ClearInput();

                if (ok != 1)
                {
                    printf("Ошибка ввода элемента массива!\n");
                    inputError = 1;
                    break;
                }
            }

            if (!inputError)
            {
                sumAfter = SumAfterMinAbs(C, n, &minAbsIdx);

                printf("\nМинимальный по модулю элемент: C[%d] = %d\n", minAbsIdx, C[minAbsIdx]);
                if (minAbsIdx == n - 1)
                {
                    printf("Минимальный по модулю элемент является последним, элементов после него нет (сумма = 0).\n");
                }
                else
                {
                    printf("Сумма элементов, расположенных после него: %d\n", sumAfter);
                }
            }

            free(C);
        }
    }

    return 0;
}

double FuncTask2(double x)
{
    return x * x + 2.0 * M_PI * cos(M_PI * x);
}

double CalcAvgPositive(double arr[], int size, double* sumPos, double* sumNeg, int* countPos, int* countNeg)
{
    int i;
    *sumPos = 0.0;
    *sumNeg = 0.0;
    *countPos = 0;
    *countNeg = 0;

    for (i = 0; i < size; i++)
    {
        if (arr[i] > 0)
        {
            *sumPos += arr[i];
            (*countPos)++;
        }
        else if (arr[i] < 0)
        {
            *sumNeg += arr[i];
            (*countNeg)++;
        }
    }

    if (*countPos > 0)
        return *sumPos / (*countPos);
    else
        return 0.0;
}

int SumAfterMinAbs(int arr[], int size, int* minAbsIdx)
{
    int i, sum = 0;
    *minAbsIdx = 0;

    for (i = 1; i < size; i++)
    {
        if (abs(arr[i]) < abs(arr[*minAbsIdx]))
        {
            *minAbsIdx = i;
        }
    }

    for (i = *minAbsIdx + 1; i < size; i++)
    {
        sum += arr[i];
    }

    return sum;
}

int ClearInput()
{
    int ch = getchar();

    while (ch != '\n' && ch != EOF)
        ch = getchar();

    return ch;
}
