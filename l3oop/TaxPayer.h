#pragma once

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <vector>
using namespace std;
#include "ITaxPayer.h"

class TaxPayer:public ITaxPayer{
protected:
    double taxableAmount =0;
private:
    char* inn;
    int year;
    double taxableIncome;
    double nonTaxableIncome;
    double totalIncome;
    const double taxRate;

    void updateTaxableAmount();
    void updateTotalIncome();

public:
    // Исходный конструктор
    TaxPayer(const char* inn, int year);
    //перегруженный конструктор
    TaxPayer(const char* inn, int year, double taxableIncome, double nonTaxableIncome);
    // Деструктор
    ~TaxPayer();

    // Методы
    //добавление налогооблагаемого дохода
    void addTaxedIncome(double netIncome);

    // Перегруженный метод для добавления дохода после вычета налога
    void addTaxedIncomeNet(double netIncome);

    // Метод добавления статьи дохода
    void addIncome(double amount, bool isTaxable);

    // Метод вывода всех параметров на консоль
    void displayInfo() const;

    // Геттеры
    const char* getINN() const;

    int getYear() const;

    double getTaxableIncome() const;

    double getNonTaxableIncome() const;

    double getTaxableAmount() const;

    double getTotalIncome() const;

    double getTaxRate() const;

    // Сеттеры
    void setINN(const char* newINN);

    void setYear(int newYear);
    // Перегрузка оператора ">>"
    friend istream& operator>>(istream& in, TaxPayer& taxpayer);

    // Перегрузка оператора >> для добавления налогооблагаемого дохода
    double operator>>(const double& amount);

    void displayNonRefundableTax() const override;
};

// Перегрузка оператора "+="
double& operator+=(double& sum, const TaxPayer& taxpayer);




