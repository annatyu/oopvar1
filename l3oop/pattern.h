#pragma once
#include "TaxPayer.h"
#include <iomanip> // Для форматирования вывода

// Template for working with taxes
template <typename T, int TaxRate>
class TaxCalculator {
public:
    static double calculateTax(T amount) {
        return static_cast<double>(amount) * (TaxRate / 100.0); // Расчет налога
    }

    static double calculateTotal(T amount) {
        return static_cast<double>(amount) + calculateTax(amount); // Общая сумма
    }
};