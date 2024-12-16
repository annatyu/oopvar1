#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;
#include "TaxPayer.h"
#include "HomePropertyTaxPayer.h"
#include "ITaxPayer.h"
#include "pattern.h"

int main() {
    try{
        // Пример суммы без копеек (в рублях)
        double amountWithoutCents = 1500.00; // 1500 рублей

        // Пример суммы с копейками
        double amountWithCents = 1500.75; // 1500.75 рублей (или 150075 копеек)

        // Вычисление налога на сумму без копеек при 15% налоге
        double taxRate = 15;
        double taxWithoutCents = TaxCalculator<double, 15>::calculateTax(amountWithoutCents);
        double totalWithoutCents = TaxCalculator<double, 15>::calculateTotal(amountWithoutCents);

        // Вывод результатов
        std::cout << "The amount without cents: " << std::fixed << std::setprecision(2)
            << amountWithoutCents << " rubles\n";
        std::cout << " (Tax 15%): " << taxWithoutCents << " rubles\n";
        std::cout << "Total amount with tax: " << totalWithoutCents << " rubles\n\n";

        // Вычисление налога на сумму с копейками при 15% налоге
        double taxWithCents = TaxCalculator<double, 15>::calculateTax(amountWithCents);
        double totalWithCents = TaxCalculator<double, 15>::calculateTotal(amountWithCents);

        // Вывод результатов
        std::cout << "The amount with cents: " << std::fixed << std::setprecision(2)
            << amountWithCents << " rubles\n";
        std::cout << "Tax (15%): " << taxWithCents << " rubles\n";
        std::cout << "Total amount with tax: " << totalWithCents << " rubles\n";
        std::cout << endl;

        // Создание массива указателей на ITaxPayer
        vector<ITaxPayer*> taxPayers;
        // Создание налогоплательщика с использованием базового конструктора
        TaxPayer taxpayer1("1234567890", 2023);
        taxpayer1.addIncome(50000, true); // Добавление налогооблагаемого дохода
        taxpayer1.addIncome(10000, false); // Добавление неналогооблагаемого дохода
        taxpayer1.addTaxedIncome(10000);
        taxpayer1.addTaxedIncomeNet(8700);
        cout << "--- Taxpayer 1 Information ---" << endl;
        taxpayer1.displayInfo();
         
        // Создание налогоплательщика с использованием перегруженного конструктора
        TaxPayer taxpayer2("0987654321", 2023, 100000, 15000);
        cout << "\n--- Taxpayer 2 Information ---" << endl;
        taxpayer2.addTaxedIncome(8889);
        taxpayer2.addTaxedIncomeNet(1234);
        taxpayer2.displayInfo();

        taxpayer2 >> 2;

        // Ввод через оператор ">>"
        cout << "\nAdding net taxable income for taxpayer1 using '>>' operator:" << endl;
        cin >> taxpayer1;
        cout << "\n--- Updated Taxpayer 1 Information ---" << endl;
        taxpayer1.displayInfo();

        // Суммирование общего налога
        double totalTax = 0;
        (totalTax += taxpayer1) += taxpayer2;
        totalTax += taxpayer2;
        cout << "Creating HomePropertyTaxPayer..." << endl;
        cout << "\nTotal tax from all taxpayers: " << totalTax << endl;

        // Создание налогоплательщика для налогов на имущество
        HomePropertyTaxPayer propertyTaxPayer("1234567890", 2023, 120000, 15000, 2500000);
        cout << "\n--- Home Property Tax Payer Information ---" << endl;
        propertyTaxPayer.displayInfo();

        // Установка новой стоимости имущества
        propertyTaxPayer.setPropertyValue(3000000);
        cout << "\n--- Updated Home Property Tax Payer Information ---" << endl;
        propertyTaxPayer.displayInfo();

        // Добавление объектов в массив
        taxPayers.push_back(&taxpayer1);
        taxPayers.push_back(&propertyTaxPayer);

        // Вывод налогов, которые не подлежат возврату
        for (const auto& taxpayer : taxPayers) {
            taxpayer->displayNonRefundableTax();
        }
    }
    catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "An unexpected error occurred: " << e.what() << endl;
    }

    return 0;
}



