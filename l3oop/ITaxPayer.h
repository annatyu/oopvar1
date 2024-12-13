#pragma once
// Интерфейс для налогоплательщиков
class ITaxPayer
{
    // Интерфейс для налогоплательщиков
    public:
        virtual void displayNonRefundableTax() const = 0; // Чисто виртуальный метод
        virtual ~ITaxPayer() {} // Виртуальный деструктор

};

