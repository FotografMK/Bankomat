#ifndef ATM_H
#define ATM_H

#include <QString>
#include <QMap>
#include <QVector>

class ATM {
public:
    ATM();
    bool login(const QString& cardNumber, const QString& pin);
    double checkBalance() const;
    bool withdraw(double amount);
    void deposit(double amount);
    bool changePin(const QString& oldPin, const QString& newPin);
    QVector<QString> getTransactionHistory() const;
    void logout();
    bool isCardBlocked(const QString& cardNumber) const;
    void blockCard();
    void addCard(const QString& cardNumber, const QString& pin);

private:
    QMap<QString, QString> accounts;
    QMap<QString, double> balances;
    QMap<QString, QVector<QString>> transactionHistories;
    QMap<QString, int> pinAttempts;
    QString currentCard;
    bool isLoggedIn;
    void logTransaction(const QString& transaction);

    const int MAX_PIN_ATTEMPTS = 3;
};

#endif // ATM_H
