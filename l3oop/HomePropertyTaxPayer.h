#pragma once
#include "TaxPayer.h"
template <typename T>
class HomePropertyTaxPayer :
    public TaxPayer
{
    private:
        T propertyValue;  // Стоимость жилья
        T deductionAmount; // Сумма вычета

        // Максимально возможный вычет составляет 13% от стоимости жилья, но не более 13% от 2 млн руб.
        const T MAX_DEDUCTION_LIMIT = static_cast<T>(2000000.0); // 2 млн руб.
        const T MAX_DEDUCTION_RATE = static_cast<T>(0.13); // 13%

    public:
        // Конструкторы
        HomePropertyTaxPayer(const char* inn, int year);

        HomePropertyTaxPayer(const char* inn, int year, T taxableIncome, T nonTaxableIncome, T propertyValue);

        // Сеттер для стоимости жилья
        void setPropertyValue(T newValue);

        // Геттер для стоимости жилья
        T getPropertyValue() const;

        // Геттер для суммы вычета
        T getDeductionAmount() const;
        //зашаблонировать сумму вычера и стоимость жилья, чтобы не только дабл было но и инт, применить универсальные параметры в шаблоне

        void displayInfo() const;
        void displayNonRefundableTax() const override;

    private:
        // Метод для расчета итогового вычета
        void calculateDeduction();

    };

// Конструкторы
template <typename T>
HomePropertyTaxPayer <T> ::HomePropertyTaxPayer(const char* inn, int year)
    : TaxPayer(inn, year), propertyValue(0), deductionAmount(0) {}

template <typename T>
HomePropertyTaxPayer <T>::HomePropertyTaxPayer(const char* inn, int year, T taxableIncome, T nonTaxableIncome, T propertyValue)
    : TaxPayer(inn, year, taxableIncome, nonTaxableIncome), propertyValue(propertyValue) {
    calculateDeduction();
}



// Сеттер для стоимости жилья
template <typename T>
void HomePropertyTaxPayer<T>::setPropertyValue(T newValue) {
    try {
        if (newValue < 0) {
            throw invalid_argument("Property value must be ne negative."); // Проверка на неотрицательность
        }
        propertyValue = newValue;
        calculateDeduction(); // Пересчитываем сумму вычета после изменения стоимости жилья
    }
    catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "An unexpected error occurred: " << e.what() << endl;
    }
}


// Геттер для стоимости жилья

template <typename T>
T HomePropertyTaxPayer<T>::getPropertyValue() const {
    return propertyValue;
}

// Геттер для суммы вычета

template <typename T>
T HomePropertyTaxPayer<T>::getDeductionAmount() const {
    return deductionAmount;
}

template <typename T>
void HomePropertyTaxPayer<T>::displayInfo() const {
    TaxPayer::displayInfo();
    cout << "PropertyValue " << getPropertyValue() << endl;
    cout << "DeductionAmount " << getDeductionAmount() << endl;
}

template <typename T>
void HomePropertyTaxPayer<T>::displayNonRefundableTax() const {
    // Логика для отображения налога, который не подлежит возврату
    cout << "Non-refundable tax for property " << getPropertyValue() << ": " << getTaxableAmount() << endl;
}

// Метод для расчета того, сколько вернется с налогов
template <typename T>
void HomePropertyTaxPayer<T>::calculateDeduction() {
    double calculatedDeduction = std::min(propertyValue * MAX_DEDUCTION_RATE, MAX_DEDUCTION_LIMIT * MAX_DEDUCTION_RATE);

    double taxableAmount = TaxPayer::taxableAmount;
    if (taxableAmount < calculatedDeduction)
    {
        deductionAmount = taxableAmount;
    }
    else {
        deductionAmount = calculatedDeduction;
    }
}


