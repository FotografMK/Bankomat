#include "interface.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

Interface::Interface(QWidget* parent) : QWidget(parent) {
    setupUI();
}

void Interface::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    cardNumberInput = new QLineEdit(this);
    pinInput = new QLineEdit(this);
    pinInput->setEchoMode(QLineEdit::Password);
    QPushButton* loginButton = new QPushButton("Login", this);
    statusLabel = new QLabel(this);

    mainLayout->addWidget(new QLabel("Card Number:", this));
    mainLayout->addWidget(cardNumberInput);
    mainLayout->addWidget(new QLabel("PIN:", this));
    mainLayout->addWidget(pinInput);
    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(statusLabel);

    connect(loginButton, &QPushButton::clicked, this, &Interface::onLoginClicked);

    // Nowe elementy interfejsu dla zalogowanych u¿ytkowników
    checkBalanceButton = new QPushButton("Check Balance", this);
    withdrawButton = new QPushButton("Withdraw", this);
    withdrawAmountInput = new QLineEdit(this);
    depositButton = new QPushButton("Deposit", this);
    depositAmountInput = new QLineEdit(this);
    changePinButton = new QPushButton("Change PIN", this);
    oldPinInput = new QLineEdit(this);
    oldPinInput->setEchoMode(QLineEdit::Password);
    newPinInput = new QLineEdit(this);
    newPinInput->setEchoMode(QLineEdit::Password);
    logoutButton = new QPushButton("Logout", this);

    mainLayout->addWidget(checkBalanceButton);
    mainLayout->addWidget(new QLabel("Withdraw Amount:", this));
    mainLayout->addWidget(withdrawAmountInput);
    mainLayout->addWidget(withdrawButton);
    mainLayout->addWidget(new QLabel("Deposit Amount:", this));
    mainLayout->addWidget(depositAmountInput);
    mainLayout->addWidget(depositButton);
    mainLayout->addWidget(new QLabel("Old PIN:", this));
    mainLayout->addWidget(oldPinInput);
    mainLayout->addWidget(new QLabel("New PIN:", this));
    mainLayout->addWidget(newPinInput);
    mainLayout->addWidget(changePinButton);
    mainLayout->addWidget(logoutButton);

    connect(checkBalanceButton, &QPushButton::clicked, this, &Interface::onCheckBalanceClicked);
    connect(withdrawButton, &QPushButton::clicked, this, &Interface::onWithdrawClicked);
    connect(depositButton, &QPushButton::clicked, this, &Interface::onDepositClicked);
    connect(changePinButton, &QPushButton::clicked, this, &Interface::onChangePinClicked);
    connect(logoutButton, &QPushButton::clicked, this, &Interface::onLogoutClicked);

    setLayout(mainLayout);

    // Pocz¹tkowo ukryj przyciski interfejsu dla zalogowanych u¿ytkowników
    checkBalanceButton->hide();
    withdrawButton->hide();
    withdrawAmountInput->hide();
    depositButton->hide();
    depositAmountInput->hide();
    changePinButton->hide();
    oldPinInput->hide();
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
    cardNumberInput->hide();
    pinInput->hide();

    checkBalanceButton->show();
    withdrawButton->show();
    withdrawAmountInput->show();
    depositButton->show();
    depositAmountInput->show();
    changePinButton->show();
    oldPinInput->show();
    newPinInput->show();
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

    cardNumberInput->show();
    pinInput->show();

    checkBalanceButton->hide();
    withdrawButton->hide();
    withdrawAmountInput->hide();
    depositButton->hide();
    depositAmountInput->hide();
    changePinButton->hide();
    oldPinInput->hide();
    newPinInput->hide();
    logoutButton->hide();
}
