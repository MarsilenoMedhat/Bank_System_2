# Bank System & Currency Exchange V2

A robust, console-based banking application developed in **C++**. This project demonstrates advanced Object-Oriented Programming (OOP) principles, clean architecture, and file-based data persistence.

It serves as a comprehensive simulation of a banking system backend, including user management, client transactions, and a fully functional currency exchange module.

## Key Features

### Currency Exchange System
- **Real-time Data:** Load currency data from `Currency.txt`.
- **List Currencies:** View all available currencies with their exchange rates (pegged to USD).
- **Update Rates:** Admin capability to modify exchange rates securely.
- **Currency Calculator:** Convert amounts between any two currencies.
- **Search:** Find currencies efficiently by Country Name or Currency Code.

### Core Banking Operations
- **Client Management:** Create, Read, Update, and Delete (CRUD) bank clients.
- **Transactions:** Deposit, Withdraw, and Transfer funds between accounts.
- **User Management:** System for managing bank staff/admins with specific permissions.
- **Security:** Secure login system with activity logging.

## Technical Implementation

The project is built using a **Modular Architecture**:

- **Language:** C++ (Standard 11/14+).
- **Paradigm:** Object-Oriented Programming (OOP).
- **Data Storage:** Flat-file database (using `.txt` files for persistence).
- **Key Concepts:**
  - **Inheritance & Polymorphism:** Abstract base classes for generic handling.
  - **Encapsulation:** Secure data access via Setters/Getters.
  - **STL:** Extensive use of `std::vector` for memory management.
  - **String Manipulation:** Custom library (`clsString`) for parsing data lines.
  - **Input Validation:** Robust handling of user inputs (`clsInputValidate`) to prevent crashes.

## Project Structure

- `Core/`: Business logic classes (e.g., `clsCurrency`, `clsBankClient`).
- `Screens/`: UI classes for menus (e.g., `clsCurrencyExchangeScreen`).
- `Lib/`: Helper libraries (`clsString`, `clsDate`, `clsUtil`).
- `Data/`: Text files storing the database (e.g., `Currency.txt`, `Clients.txt`).

## New Project Structure

The project has been reorganized into a modular hierarchy for better scalability and maintainability:

```text
Bank_System_2/
├── Core/                 # Business Logic & Data Models
│   ├── clsBankClient.h
│   ├── clsCurrency.h
│   └── clsUser.h
├── Lib/                  # Reusable Utility Libraries
│   ├── clsDate.h
│   ├── clsInputValidate.h
│   ├── clsString.h
│   └── clsScreen.h
├── Screens/              # User Interface Layers
│   ├── clsMainScreen.h
│   ├── Client/           # Client Management Screens
│   ├── Currencies/       # Currency Exchange Screens
│   └── User/             # User & Login Management Screens
├── Global.h              # System-wide global variables
└── Main.cpp              # Application Entry Point

Developed by Marsileno Medhat