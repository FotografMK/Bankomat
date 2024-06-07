#include "interface.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

Interface::Interface(QWidget* parent) : QWidget(parent) {
    setupUI();
    resize(300, 200);
}

void Interface::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Elementy logowania
    cardNumberLabel = new QLabel("Card Number:", this);
    cardNumberInput = new QLineEdit(this);
    pinLabel = new QLabel("PIN:", this);
    pinInput = new QLineEdit(this);
    pinInput->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Login", this);
    statusLabel = new QLabel(this);

    mainLayout->addWidget(cardNumberLabel);
    mainLayout->addWidget(cardNumberInput);
    mainLayout->addWidget(pinLabel);
    mainLayout->addWidget(pinInput);
    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(statusLabel);

    connect(loginButton, &QPushButton::clicked, this, &Interface::onLoginClicked);

    // Nowe elementy interfejsu dla zalogowanych u¿ytkowników
    checkBalanceButton = new QPushButton("Check Balance", this);
    withdrawButton = new QPushButton("Withdraw", this);
    withdrawAmountInput = new QLineEdit(this);
    withdrawAmountLabel = new QLabel("Withdraw Amount:", this);  // Przypisanie wskaŸnika
    depositButton = new QPushButton("Deposit", this);
    depositAmountInput = new QLineEdit(this);
    depositAmountLabel = new QLabel("Deposit Amount:", this);    // Przypisanie wskaŸnika
    changePinButton = new QPushButton("Change PIN", this);
    oldPinInput = new QLineEdit(this);
    oldPinInput->setEchoMode(QLineEdit::Password);
    oldPinLabel = new QLabel("Old PIN:", this);  // Przypisanie wskaŸnika
    newPinInput = new QLineEdit(this);
    newPinInput->setEchoMode(QLineEdit::Password);
    newPinLabel = new QLabel("New PIN:", this);  // Przypisanie wskaŸnika
    logoutButton = new QPushButton("Logout", this);

    mainLayout->addWidget(checkBalanceButton);
    mainLayout->addWidget(withdrawAmountLabel);
    mainLayout->addWidget(withdrawAmountInput);
    mainLayout->addWidget(withdrawButton);
    mainLayout->addWidget(depositAmountLabel);
    mainLayout->addWidget(depositAmountInput);
    mainLayout->addWidget(depositButton);
    mainLayout->addWidget(oldPinLabel);
    mainLayout->addWidget(oldPinInput);
    mainLayout->addWidget(newPinLabel);
    mainLayout->addWidget(newPinInput);
    mainLayout->addWidget(changePinButton);
    mainLayout->addWidget(logoutButton);

    connect(checkBalanceButton, &QPushButton::clicked, this, &Interface::onCheckBalanceClicked);
    connect(withdrawButton, &QPushButton::clicked, this, &Interface::onWithdrawClicked);
    connect(depositButton, &QPushButton::clicked, this, &Interface::onDepositClicked);
    connect(changePinButton, &QPushButton::clicked, this, &Interface::onChangePinClicked);
    connect(logoutButton, &QPushButton::clicked, this, &Interface::onLogoutClicked);

    setLayout(mainLayout);

    // Pocz¹tkowo ukryj przyciski i etykiety interfejsu dla zalogowanych u¿ytkowników
    checkBalanceButton->hide();
    withdrawButton->hide();
    withdrawAmountLabel->hide();
    withdrawAmountInput->hide();
    depositButton->hide();
    depositAmountLabel->hide();
    depositAmountInput->hide();
    changePinButton->hide();
    oldPinLabel->hide();
    oldPinInput->hide();
    newPinLabel->hide();
    newPinInput->hide();
    logoutButton->hide();
}

void Interface::onLoginClicked() {
    QString cardNumber = cardNumberInput->text();
    QString pin = pinInput->text();
    if (atm.login(cardNumber, pin)) {
        statusLabel->setText("Login successful!");
        showMainMenu();
    }
    else {
        statusLabel->setText("Login failed!");
    }
}

void Interface::showMainMenu() {
    // Ukryj elementy logowania
    cardNumberLabel->hide();
    cardNumberInput->hide();
    pinLabel->hide();
    pinInput->hide();
    loginButton->hide();

    // Poka¿ elementy g³ównego menu
    checkBalanceButton->show();
    withdrawButton->show();
    withdrawAmountInput->show();
    withdrawAmountLabel->show();
    depositButton->show();
    depositAmountInput->show();
    depositAmountLabel->show();
    changePinButton->show();
    oldPinInput->show();
    oldPinLabel->show();
    newPinInput->show();
    newPinLabel->show();
    logoutButton->show();
}

void Interface::clearInputs() {
    cardNumberInput->clear();
    pinInput->clear();
    statusLabel->clear();
}

void Interface::onCheckBalanceClicked() {
    double balance = atm.checkBalance();
    statusLabel->setText("Current balance: " + QString::number(balance));
}

void Interface::onWithdrawClicked() {
    double amount = withdrawAmountInput->text().toDouble();
    if (atm.withdraw(amount)) {
        statusLabel->setText("Withdraw successful!");
    }
    else {
        statusLabel->setText("Insufficient funds!");
    }
}

void Interface::onDepositClicked() {
    double amount = depositAmountInput->text().toDouble();
    atm.deposit(amount);
    statusLabel->setText("Deposit successful!");
}

void Interface::onChangePinClicked() {
    QString oldPin = oldPinInput->text();
    QString newPin = newPinInput->text();
    if (atm.changePin(oldPin, newPin)) {
        statusLabel->setText("PIN change successful!");
    }
    else {
        statusLabel->setText("PIN change failed!");
    }
}

void Interface::onLogoutClicked() {
    atm.logout();
    clearInputs();
    statusLabel->setText("Logged out.");

    // Ukryj elementy g³ównego menu
    checkBalanceButton->hide();
    withdrawButton->hide();
    withdrawAmountInput->hide();
    withdrawAmountLabel->hide();
    depositButton->hide();
    depositAmountInput->hide();
    depositAmountLabel->hide();
    changePinButton->hide();
    oldPinInput->hide();
    oldPinLabel->hide();
    newPinInput->hide();
    newPinLabel->hide();
    logoutButton->hide();

    // Poka¿ elementy logowania
    cardNumberLabel->show();
    cardNumberInput->show();
    pinLabel->show();
    pinInput->show();
    // Pokaz przycisk logowania
    loginButton->show();
    // Ustaw rozmiar okna na wyjœciowy, mniejszy rozmiar
    resize(300, 200);
}
