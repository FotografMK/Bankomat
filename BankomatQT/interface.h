#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "atm.h"

class Interface : public QWidget {
    Q_OBJECT

public:
    Interface(QWidget* parent = nullptr);

private slots:
    void onLoginClicked();
    void onCheckBalanceClicked();
    void onWithdrawClicked();
    void onDepositClicked();
    void onChangePinClicked();
    void onLogoutClicked();

private:
    ATM atm;
    QLineEdit* cardNumberInput;
    QLineEdit* pinInput;
    QLabel* statusLabel;

    // Nowe elementy interfejsu dla zalogowanych u¿ytkowników
    QPushButton* checkBalanceButton;
    QPushButton* withdrawButton;
    QLineEdit* withdrawAmountInput;
    QPushButton* depositButton;
    QLineEdit* depositAmountInput;
    QPushButton* changePinButton;
    QLineEdit* oldPinInput;
    QLineEdit* newPinInput;
    QPushButton* logoutButton;

    void setupUI();
    void showMainMenu();
    void clearInputs();
};

#endif // INTERFACE_H
