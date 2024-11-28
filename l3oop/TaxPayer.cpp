﻿#include "TaxPayer.h"

// Реализация методов
void TaxPayer::updateTaxableAmount() {
    taxableAmount = taxableIncome * taxRate;
}

void TaxPayer::updateTotalIncome() {
    totalIncome = taxableIncome + nonTaxableIncome;
}

// Методы
//добавление налогооблагаемого дохода


//перегруженный конструктор


// Исходный конструктор

 TaxPayer::TaxPayer(const char* inn, int year)
    : taxableIncome(0),
    nonTaxableIncome(0),
    taxableAmount(0),
    totalIncome(0),
    taxRate(0.13) {
    setINN(inn);
    setYear(year);
}

 TaxPayer::TaxPayer(const char* inn, int year, double taxableIncome, double nonTaxableIncome)
    : taxableIncome(taxableIncome),
    nonTaxableIncome(nonTaxableIncome),
    taxableAmount(0),
    totalIncome(0),
    taxRate(0.13) {
    setINN(inn);
    setYear(year);
    updateTaxableAmount();
    updateTotalIncome();
}

inline void TaxPayer::addTaxedIncome(double netIncome) {
    if (netIncome <= 0) {
        throw invalid_argument("Net income must be positive.");
    }

    double grossIncome = netIncome / (1 - taxRate);
    double taxPaid = grossIncome - netIncome;

    taxableIncome += grossIncome;
    updateTaxableAmount();
    updateTotalIncome();

    cout << "Net income added: " << netIncome << endl;
    cout << "Gross income: " << grossIncome << endl;
    cout << "Tax paid: " << taxPaid << endl;
}

// Перегруженный метод для добавления дохода после вычета налога

 void TaxPayer::addTaxedIncomeNet(double netIncome) {
    if (netIncome <= 0) {
        throw invalid_argument("Net income must be positive.");
    }

    double grossIncome = netIncome / (1 - taxRate);
    double taxPaid = grossIncome - netIncome;

    taxableIncome += grossIncome;
    updateTaxableAmount();
    updateTotalIncome();

    cout << "Net income added: " << netIncome << endl;
    cout << "Calculated gross income: " << grossIncome << endl;
    cout << "Calculated tax paid: " << taxPaid << endl;
}

// Метод добавления статьи дохода

 void TaxPayer::addIncome(double amount, bool isTaxable) {
    if (amount <= 0) {
        throw invalid_argument("The income should be positive.");
    }

    if (isTaxable) {
        taxableIncome += amount;
    }
    else {
        nonTaxableIncome += amount;
    }

    updateTaxableAmount();
    updateTotalIncome();
}

// Метод вывода всех параметров на консоль

 void TaxPayer::displayInfo() const {
    cout << "INN " << getINN() << endl;
    cout << "YEAR " << getYear() << endl;
    cout << "NALOGOOBLAD_DOHOD " << getTaxableIncome() << endl;
    cout << "NENALOGOOBLAD_DOHOD " << getNonTaxableIncome() << endl;
    cout << "ITOG_SUMM_DOHOD_NALOGA " << getTaxableAmount() << endl;
    cout << "ITOG_SUM_DOHODA " << getTotalIncome() << endl;
    cout << "PERSENT_DOHOD_NALOGA " << getTaxRate() * 100 << "%" << endl;

}

// Геттеры

 const char* TaxPayer::getINN() const {
    return inn;
}

 int TaxPayer::getYear() const {
    return year;
}

 double TaxPayer::getTaxableIncome() const {
    return taxableIncome;
}

 double TaxPayer::getNonTaxableIncome() const {
    return nonTaxableIncome;
}

 double TaxPayer::getTaxableAmount() const {
    return taxableAmount;
}

 double TaxPayer::getTotalIncome() const {
    return totalIncome;
}

 double TaxPayer::getTaxRate() const {
    return taxRate;
}


// Сеттеры

 void TaxPayer::setINN(const char* newINN) {
    if (newINN == nullptr) {
        throw invalid_argument("The INN cannot be nullptr."); // Исключение, если указатель равен nullptr
    }

    if (strlen(newINN) != 10) { // Проверка длины ИНН
        throw invalid_argument("The INN must consist of 10 characters."); // Исключение, если длина не 10
    }

    inn = new char[strlen(newINN) + 1]; // Выделение памяти под ИНН
    strcpy_s(inn, strlen(newINN) + 1, newINN); // Копирование ИНН
}

void TaxPayer::setYear(int newYear) {
    if (newYear < 2000 || newYear > 2100) {
        throw invalid_argument("Invalid year value.");
    }
    year = newYear;
}

//перегрузка оператора >>
istream& operator>>(istream& in, TaxPayer& taxpayer) {
    double netIncome;
    cout << "Enter the net taxable income: ";
    in >> netIncome;
    taxpayer.addTaxedIncome(netIncome);
    return in;
}
double TaxPayer::operator>>(const double& amount) {
    addIncome(amount, true);
    return amount;
}
// перегрузка оператора +=
double& operator+=(double& sum, const TaxPayer& taxpayer) {
    sum += taxpayer.getTaxableAmount();
    return sum;
}

// Конструкторы

 HomePropertyTaxPayer::HomePropertyTaxPayer(const char* inn, int year)
    : TaxPayer(inn, year), propertyValue(0), deductionAmount(0) {}

 HomePropertyTaxPayer::HomePropertyTaxPayer(const char* inn, int year, double taxableIncome, double nonTaxableIncome, double propertyValue)
    : TaxPayer(inn, year, taxableIncome, nonTaxableIncome), propertyValue(propertyValue) {
    calculateDeduction();
}

// Сеттер для стоимости жилья

 void HomePropertyTaxPayer::setPropertyValue(double newValue) {
    propertyValue = newValue;
    calculateDeduction(); // Пересчитываем сумму вычета после изменения стоимости жилья
}

// Геттер для стоимости жилья

 double HomePropertyTaxPayer::getPropertyValue() const {
    return propertyValue;
}

// Геттер для суммы вычета

 double HomePropertyTaxPayer::getDeductionAmount() const {
    return deductionAmount;
}

 void HomePropertyTaxPayer::displayInfoHome() const {

    cout << "PropertyValue " << getPropertyValue() << endl;
    cout << "DeductionAmount " << getDeductionAmount() << endl;
}

// Метод для расчета доступного вычета

void HomePropertyTaxPayer::calculateDeduction() {
    // Максимально возможный вычет составляет 13% от стоимости жилья, но не более 13% от 2 млн руб.
    const double MAX_DEDUCTION_LIMIT = 2000000.0; // 2 млн руб.
    const double MAX_DEDUCTION_RATE = 0.13; // 13%

    double calculatedDeduction = std::min(propertyValue * MAX_DEDUCTION_RATE, MAX_DEDUCTION_LIMIT * MAX_DEDUCTION_RATE);
    deductionAmount = std::max(0.0, calculatedDeduction); // Убедимся, что вычет не отрицательный
}
