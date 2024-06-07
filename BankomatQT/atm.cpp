#include "atm.h"
#include <QDateTime>

ATM::ATM() : isLoggedIn(false) {
    // Dodanie przyk³adowej karty i PIN
    addCard("1234567890123456", "1234");
}

bool ATM::login(const QString& cardNumber, const QString& pin) {
    if (accounts.contains(cardNumber) && accounts[cardNumber] == pin) {
        currentCard = cardNumber;
        isLoggedIn = true;
        pinAttempts[cardNumber] = 0;
        return true;
    }
    else {
        pinAttempts[cardNumber]++;
        if (pinAttempts[cardNumber] >= MAX_PIN_ATTEMPTS) {
            blockCard();
        }
        return false;
    }
}

double ATM::checkBalance() const {
    if (isLoggedIn) {
        return balances[currentCard];
    }
    return 0.0;
}

bool ATM::withdraw(double amount) {
    if (isLoggedIn && balances[currentCard] >= amount) {
        balances[currentCard] -= amount;
        logTransaction("Withdraw: " + QString::number(amount));
        return true;
    }
    return false;
}

void ATM::deposit(double amount) {
    if (isLoggedIn) {
        balances[currentCard] += amount;
        logTransaction("Deposit: " + QString::number(amount));
    }
}

bool ATM::changePin(const QString& oldPin, const QString& newPin) {
    if (isLoggedIn && accounts[currentCard] == oldPin) {
        accounts[currentCard] = newPin;
        return true;
    }
    return false;
}

QVector<QString> ATM::getTransactionHistory() const {
    if (isLoggedIn) {
        return transactionHistories[currentCard];
    }
    return {};
}

void ATM::logout() {
    isLoggedIn = false;
    currentCard = "";
}

bool ATM::isCardBlocked(const QString& cardNumber) const {
    return pinAttempts.contains(cardNumber) && pinAttempts[cardNumber] >= MAX_PIN_ATTEMPTS;
}

void ATM::blockCard() {
    pinAttempts[currentCard] = MAX_PIN_ATTEMPTS;
}

void ATM::addCard(const QString& cardNumber, const QString& pin) {
    accounts[cardNumber] = pin;
    balances[cardNumber] = 0.0;
    transactionHistories[cardNumber] = {};
    pinAttempts[cardNumber] = 0;
}

void ATM::logTransaction(const QString& transaction) {
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    transactionHistories[currentCard].append(timestamp + " - " + transaction);
}
