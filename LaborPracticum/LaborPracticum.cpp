#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <conio.h>
  


void KeyBoardToArray(double AR[100][100], unsigned Stolb, unsigned String)
{
    for (unsigned i = 0; i < Stolb; i++)
    {
        for (unsigned j = 0; j < String; j++)
        {
            printf_s("Введите через пробел [%u][%u] элемент: ", i+1, j+1);
            scanf_s("%lf", &AR[i][j]);
        }
    }
}

void ArrayDisplayShow(double AR[100][100], unsigned Stolb, unsigned String)
{
    for (unsigned i = 0; i < Stolb; i++)
    {
        for (unsigned j = 0; j < String; j++)
        {
            if (j == String - 1)
            {
                printf_s("%3.3lf\n", AR[i][j]);
            }
            else
            {
                printf_s("%3.3lf  ", AR[i][j]);
            }
        }
    }
}

int ArrayTextSave(double AR[100][100], unsigned Stolb, unsigned String, char na[100])
{
    FILE* file;

    file = fopen(na, "w+");

    if (file == 0)
    {
        return 404;
    }

    for (unsigned i = 0; i < Stolb; i++)
    {
        for (unsigned j = 0; j < String; j++)
        {
            if (j == String - 1)
            {
                fprintf_s(file, "%3.2fl\n", AR[i][j]);
            }
            else
            {
                fprintf_s(file, "%3.2fl  ", AR[i][j]);
            }
        }
    }

    fclose(file);

    return 20;
}

int ArrayFromKeyBoardFileTXT(double AR[100][100],unsigned stolb, unsigned str,char na[100])
{


    FILE* file;

    file = fopen(na, "r");

    if (file == 0)
    {
        return 404;
    }

    for (unsigned i = 0; i < stolb; i++)
    {
        for (unsigned j = 0; j < str; j++)
        {
            fscanf(file, "%lf", &AR[i][j]);
        }
    }
    fclose(file);
    return 1;
}

int SaveToBin(double arr[100][100], unsigned Stolb, unsigned String, char na[100])
{
    FILE* file;
    file = fopen(na, "wb");//Сделать ввод названия в ручную
    if (file == 0)
    {
        return 404;
    }
    for (int i = 0; i < Stolb; i++)
    {
        for (int j = 0; j < String; j++)
        {
            if (j == String - 1)
            {
                fwrite(&arr[i][j],1, sizeof(arr[i][j]), file);
            }
        }
    }
    fclose(file);
    return 12;
}

int ReadArrayFromBin(double arr[100][100], unsigned stolb, unsigned string, char na[100])
{
    FILE* file;
    file = fopen(na, "rb");
    if (file == 0)
    {
        return 404;
    }
    for (int i = 0; i < stolb; i++)
    {
        for (int j = 0; j < string; j++)
        {
            fread(&arr, 1, sizeof(arr[i][j]), file);
        }
    }
    fclose(file);
    return 11;
}
void RandFillArray(double ar[100][100], int stolb, int string)
{
    int Start;
    int End;
    printf_s("Введите диапазон для случайных чисел: \n");
    printf_s("От: ");
    scanf_s("%d", &Start);
    printf_s("До: ");
    scanf_s("%d", &End);
    for (int i = 0; i < stolb; i++)
    {
        for (int j = 0; j < string; j++)
        {
            ar[i][j] = rand() % (End - Start + 1) + Start;
        }
    }
}
void FileName(char name[])
{
    printf("Введите название файла: ");
    scanf("%s", name);
}
void FillByFromula(double AR[100][100], unsigned stolb, unsigned string)
{
    for (unsigned i = 0; i < stolb; i++)
    {
        for (unsigned j = 0; j < string; j++)
        {
            if (i > j)
            {
                AR[i][j] = cos(i) / sin(i);
            }
            if (i == j)
            {
                AR[i][j] = tan(i + j);
            }
            if (i < j)
            {
                AR[i][j] = cos(j) / sin(j);
            }
        }
    }
}
double SumFind(double AR[100][100], unsigned stolb, unsigned string,double sum)
{
    for (unsigned i = 0; i < stolb; i++)
    {
        for (unsigned j = 0; j < string; j++)
        {
            if (((i+1) * (j+1)) % 2 == 0)
            {
                sum += AR[i][j];
            }
        }
    }
    return sum;
}
int main()
{
    setlocale(LC_ALL, "Ru");// Русский язык

    srand(time(NULL));

    double arr[100][100];

    char fileName[100];

    int F = 0;

    int Choice;

    unsigned StolbSize;

    unsigned StringSize;

    int OutPutChoice;

    double sum = 0;

    double sm;
    

    do {
        printf_s("Что вы хотите сделать с массивом?\n");
        printf_s("Заполнить с клавиатуры - 1; Заполнить с клавиатуры с .txt файла - 2; Заполнить с клавиатуры с .bin файла - 3; Заполнить случайными числами - 4; Заполнить по формуле - 5\n");
        scanf_s("%d", &Choice);
        printf_s("Введите число столбцов массива: ");
        scanf_s("%d", &StolbSize);
        printf_s("Введите число строк массива: ");
        scanf_s("%d", &StringSize);
        switch (Choice)
        {
        case 1:
            KeyBoardToArray(arr,StolbSize, StringSize);
            sm = SumFind(arr, StolbSize, StringSize, sum);
            printf_s("Сумма элементов, произведения которых четное = %lf\n", sm);
            printf_s("Куда вы хотите вывести массив?\n");
            printf_s("| для вывода на ЭКРАН введите 1, для вывода в файл 2, для вывода в BIN файл 3 : | ");
            scanf_s("%d", &OutPutChoice);
            if (OutPutChoice == 1)
            {
                ArrayDisplayShow(arr, StolbSize, StringSize);
            }
            if (OutPutChoice == 2)
            {
                
                FileName(fileName);
                F = ArrayTextSave(arr, StolbSize, StringSize, fileName);

                if (F == 404)
                {
                    printf_s("Файл не найден!");
                }
            }
            if (OutPutChoice == 3)
            {
                
                FileName(fileName);
                F = SaveToBin(arr, StolbSize, StringSize, fileName);
            }
            break;
        case 2:
                        
            FileName(fileName);

            F = ArrayFromKeyBoardFileTXT(arr, StolbSize, StringSize, fileName);
            sm = SumFind(arr, StolbSize, StringSize, sum);
            printf_s("Сумма элементов, произведения которых четное = %lf\n", sm);
            printf_s("Куда вы хотите вывести массив?\n");

            printf_s("| для вывода на ЭКРАН введите 1, для вывода в файл 2, для вывода в BIN файл 3 : | ");

            scanf_s("%d", &OutPutChoice);
            if (OutPutChoice == 1)
            {
                ArrayDisplayShow(arr, StolbSize , StringSize);
            }
            if(OutPutChoice == 2)
            {
               
                FileName(fileName);
                F = ArrayTextSave(arr, StolbSize, StringSize, fileName);

                if (F == 404)
                {
                    printf_s("Файл не найден!");
                }
            }
            if (OutPutChoice == 3)
            {
                
                FileName(fileName);
                F = SaveToBin(arr, StolbSize, StringSize, fileName);

                if (F == 404)
                {
                    printf_s("Файл не найден!");
                }
            }

            break;
        case 3:
            FileName(fileName);
            ReadArrayFromBin(arr, StolbSize, StringSize, fileName);
            sm = SumFind(arr, StolbSize, StringSize, sum);
            printf_s("Сумма элементов, произведения которых четное = %lf\n", sm);
            printf_s("Куда вы хотите вывести массив?\n");
            printf_s("| для вывода на ЭКРАН введите 1, для вывода в файл 2, для вывода в BIN файл 3 : | ");
            scanf_s("%d", &OutPutChoice);
            if (OutPutChoice == 1)
            {
                ArrayDisplayShow(arr, StolbSize, StringSize);
            }
            if (OutPutChoice == 2)
            {
                FileName(fileName);
                F = ArrayTextSave(arr, StolbSize, StringSize, fileName);

                if (F == 404)
                {
                    printf_s("Файл не найден!");
                }
            }
            if (OutPutChoice == 3)
            {
                FileName(fileName);
                F = SaveToBin(arr, StolbSize, StringSize, fileName);

                if (F == 404)
                {
                    printf_s("Файл не найден!");
                }
            }
            break;
        case 4:
            RandFillArray(arr, StolbSize, StringSize);

            sm = SumFind(arr, StolbSize, StringSize, sum);

            printf_s("Сумма элементов, произведения которых четное = %lf\n", sm);

            printf_s("Куда вы хотите вывести массив?\n");

            printf_s("| для вывода на ЭКРАН введите 1, для вывода в файл 2, для вывода в BIN файл 3 : | ");

            scanf_s("%d", &OutPutChoice);
            if (OutPutChoice == 1)
            {
                ArrayDisplayShow(arr, StolbSize, StringSize);
            }
            if (OutPutChoice == 2)
            {
                FileName(fileName);
                F = ArrayTextSave(arr, StolbSize, StringSize, fileName);

                if (F == 404)
                {
                    printf_s("Файл не найден!");
                }
            }
            if (OutPutChoice == 3)
            {
                FileName(fileName);
                F = SaveToBin(arr, StolbSize, StringSize, fileName);

                if (F == 404)
                {
                    printf_s("Файл не найден!");
                }
            }

            break;
        case 5:
            FillByFromula(arr, StolbSize, StringSize);
            sm = SumFind(arr, StolbSize, StringSize, sum);

            printf_s("Сумма элементов, произведения которых четное = %lf\n", sm);

            printf_s("Куда вы хотите вывести массив?\n");

            printf_s("| для вывода на ЭКРАН введите 1, для вывода в файл 2, для вывода в BIN файл 3 : | ");

            scanf_s("%d", &OutPutChoice);

            if (OutPutChoice == 1)
            {
                ArrayDisplayShow(arr, StolbSize, StringSize);
            }
            if (OutPutChoice == 2)
            {
                FileName(fileName);
                F = ArrayTextSave(arr, StolbSize, StringSize, fileName);

                if (F == 404)
                {
                    printf_s("Файл не найден!");
                }
            }
            if (OutPutChoice == 3)
            {
                FileName(fileName);
                F = SaveToBin(arr, StolbSize, StringSize, fileName);

                if (F == 404)
                {
                    printf_s("Файл не найден!");
                }
            }

            break;

        default:

            printf_s("Пожалуйста, выберите одну из доступных операций!\n");

        }
        printf_s("Если хотите продолжить, выберите другую операцию, если нет - 0\n");

        scanf_s("%d", &Choice);

    } while (Choice != 0);



    return 0;
}

