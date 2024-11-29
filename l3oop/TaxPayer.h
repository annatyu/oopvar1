#pragma once

#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;
//comm

class TaxPayer {
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

};

// Перегрузка оператора "+="
double& operator+=(double& sum, const TaxPayer& taxpayer);

//class HomePropertyTaxPayer1 : public TaxPayer {
//private:
//    double propertyValue;  // Стоимость жилья
//    double deductionAmount; // Сумма вычета
//
//    // Максимально возможный вычет составляет 13% от стоимости жилья, но не более 13% от 2 млн руб.
//    const double MAX_DEDUCTION_LIMIT = 2000000.0; // 2 млн руб.
//    const double MAX_DEDUCTION_RATE = 0.13; // 13%
//
//public:
//    // Конструкторы
//    HomePropertyTaxPayer1(const char* inn, int year);
//
//    HomePropertyTaxPayer1(const char* inn, int year, double taxableIncome, double nonTaxableIncome, double propertyValue);
//
//    // Сеттер для стоимости жилья
//    void setPropertyValue(double newValue);
//
//    // Геттер для стоимости жилья
//    double getPropertyValue() const;
//
//    // Геттер для суммы вычета
//    double getDeductionAmount() const;
//    void displayInfo() const;
//
//
//private:
//    // Метод для расчета итогового вычета
//    void calculateDeduction();
//
//};




