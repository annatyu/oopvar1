#pragma once
#include "TaxPayer.h"
class HomePropertyTaxPayer :
    public TaxPayer
{
    private:
        double propertyValue;  // Стоимость жилья
        double deductionAmount; // Сумма вычета

        // Максимально возможный вычет составляет 13% от стоимости жилья, но не более 13% от 2 млн руб.
        const double MAX_DEDUCTION_LIMIT = 2000000.0; // 2 млн руб.
        const double MAX_DEDUCTION_RATE = 0.13; // 13%

    public:
        // Конструкторы
        HomePropertyTaxPayer(const char* inn, int year);

        HomePropertyTaxPayer(const char* inn, int year, double taxableIncome, double nonTaxableIncome, double propertyValue);

        // Сеттер для стоимости жилья
        void setPropertyValue(double newValue);

        // Геттер для стоимости жилья
        double getPropertyValue() const;

        // Геттер для суммы вычета
        double getDeductionAmount() const;
        void displayInfo() const;


    private:
        // Метод для расчета итогового вычета
        void calculateDeduction();

    };

