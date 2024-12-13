#include "HomePropertyTaxPayer.h"

// Конструкторы

HomePropertyTaxPayer::HomePropertyTaxPayer(const char* inn, int year)
    : TaxPayer(inn, year), propertyValue(0), deductionAmount(0) {}

HomePropertyTaxPayer::HomePropertyTaxPayer(const char* inn, int year, double taxableIncome, double nonTaxableIncome, double propertyValue)
    : TaxPayer(inn, year, taxableIncome, nonTaxableIncome), propertyValue(propertyValue) {
    calculateDeduction();
}

// Сеттер для стоимости жилья

void HomePropertyTaxPayer::setPropertyValue(double newValue) {
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

double HomePropertyTaxPayer::getPropertyValue() const {
    return propertyValue;
}

// Геттер для суммы вычета

double HomePropertyTaxPayer::getDeductionAmount() const {
    return deductionAmount;
}

void HomePropertyTaxPayer::displayInfo() const {
    TaxPayer::displayInfo();
    cout << "PropertyValue " << getPropertyValue() << endl;
    cout << "DeductionAmount " << getDeductionAmount() << endl;
}

void HomePropertyTaxPayer::displayNonRefundableTax() const {
    // Логика для отображения налога, который не подлежит возврату
    cout << "Non-refundable tax for property " << getPropertyValue() << ": " << getTaxableAmount() << endl;
}

// Метод для расчета того, сколько вернется с налогов
void HomePropertyTaxPayer::calculateDeduction() {
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

