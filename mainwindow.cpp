#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDebug>
#include <QString>
#include <cmath>

#define TABLE_FILE "./digits.txt"
#define COUNT_NUMBERS 1000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // необходимо указывать путь к вашему требуемому файлу
    QFile file(TABLE_FILE);
    if(! file.open(QFile::ReadOnly | QIODevice::Text))
    {
        qDebug() << file.errorString();
    } else {
        // Создаём поток для извлечения данных из файла
        QTextStream in(&file);
        // Считываем данные до конца файла
        int num_len {0};
        while (!in.atEnd() || num_len <=COUNT_NUMBERS)
        {
            num_len++;
            // ... построчно
            QString line = in.readLine();
            line.replace(QString("   "), QString(" "));
            line.replace(QString("  "), QString(" "));

            // Добавляем в модель по строке с элементами

            // учитываем, что строка разделяется точкой с запятой на колонки
            int k {0};
            for (QString item : line.split(" "))
            {
                k++;
                if(k==1) continue;
                mas.push_back(item.toInt());
            }
        }
        file.close();
    }
//    for(int i = 0; i<40;i++)
//    {
//        qDebug() << mas[i]%10; //one digit
//        qDebug() << mas[i]%90+10; //two digit
//        qDebug() << mas[i]%900+100; //three digit
//    }



    QVector<int> mass;
    for(int i = 0; i<1000;i++)
    {
        mass.push_back(mas[i]%10); //three digit
    }

    int A = 3626;
    int C = 6603;
    int M = 31250;
    int X = 0;
    int nextNumber = (A * X + C) % M;

    for(int i = 0; i < 1000; i++)
    {
        nextNumber = std::fabs((A * nextNumber + C) % M); //Конгруэнтный метод
        mas_algo.push_back(nextNumber);
    }

//    for(int i = 0; i<40;i++)
//    {
//        qDebug() << mas_algo[i]%10; //one digit
//        qDebug() << mas_algo[i]%90+10; //two digit
//        qDebug() << mas_algo[i]%900+100; //three digit
//    }
    QVector<int> mass_algo;
    QVector<int> mass_algor = {0,2,1,6,3,5,8,4,1,8};
    for(int i = 0; i<1000;i++)
    {
        mass_algo.push_back(mas_algo[i]%90+10); //one digit
    }

    QVector<int> odd; // нечетный
    QVector<int> even; // четный
    for(int i=0; i<mass_algor.length(); i++)
    {
        if(i % 2)
        {
            even.push_back(mass_algor[i]);
        } else {
            odd.push_back(mass_algor[i]);
        }
    }
    long int sum_even {0};
    int count_even {0};
    long int sum_odd {0};
    int count_odd {0};
    for(int i=0; i<even.length(); i++)
    {
       sum_even += even[i];
       count_even++;
    }
    double diff_even = sum_even/count_even;
    for(int i=0; i<odd.length(); i++)
    {
       sum_odd += odd[i];
       count_odd++;
    }
    double diff_odd = sum_odd/count_odd;

    double result = diff_odd<diff_even ? diff_odd/diff_even : diff_even/diff_odd;

    qDebug() << result;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}

