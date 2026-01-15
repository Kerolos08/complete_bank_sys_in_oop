# Bank Management System - C++ OOP

A complete console-based banking system built with C++ as part of **Course 11** from the [Programming Advices](https://programmingadvices.com) Fundamentals Roadmap.

## 📚 About

This educational project demonstrates Object-Oriented Programming concepts in C++ including inheritance, encapsulation, file handling, and user authentication systems.

## ✨ Features

### 🔐 User System
- Secure login with password encryption
- Role-based permissions (8 permission levels)
- Login history tracking
- Multi-user support

### 👥 Client Management
- Add, update, delete, and find clients
- List all clients
- Account balance tracking

### 💰 Banking Transactions
- Deposit money
- Withdraw money
- Transfer between accounts
- View total bank balance
- Complete transfer log with timestamps

### 💱 Currency Exchange
- 190+ world currencies supported
- Currency converter/calculator
- Update exchange rates
- Find currency by code or country

### 📊 Reports
- Login register (tracks all user sessions)
- Transfer log (complete audit trail)
- Balance reports with text conversion

## 🛠️ Technologies

- **Language:** C++17
- **Paradigm:** Object-Oriented Programming
- **Storage:** Text file-based persistence
- **Platform:** Cross-platform (Windows, Linux, macOS)

## 📦 Installation

```bash
# Clone the repository
git clone https://github.com/Kerolos08/complete_bank_sys_in_oop
cd complete_bank_sys_in_oop

# Compile
make

# Run
./BankSystem
```


## 📁 Project Structure

```
src/
├── ConsoleApp.cpp              # Main entry point
├── Core/                       # Base classes (Person, Client, User)
├── Screens/                    # UI screens for all features
├── Utils/                      # Helper classes (Date, String, Validation)
└── Global.h                    # Active user session

data/
├── Clients.txt                 # Client accounts
├── Users.txt                   # System users
├── Currencies.txt              # Currency data
├── LoginRegister.txt           # Login history
└── TransferLog.txt             # Transfer audit trail
```

## 🎯 Key OOP Concepts

- **Inheritance:** `clsPerson` → `clsBankClient`, `clsUser`
- **Encapsulation:** Private data with getters/setters
- **Polymorphism:** Virtual functions and method overloading
- **File I/O:** Custom text file format with `#//#` delimiter
- **Security:** Password encryption and permission checks

## 💡 Learning Outcomes

This project helped me learn:
- Advanced C++ OOP design patterns
- File-based data persistence
- User authentication and authorization
- Cross-platform C++ development
- Input validation and error handling
- Code organization and structure

## ⚠️ Educational Note

This is an educational project with simplified security:
- Basic password encryption (character shift)
- Plain text file storage
- For production use, implement proper hashing (bcrypt) and database storage (SQL)

## 📝 Course Information

**Course 11 - OOP as It Should Be (Applications)**  
Part of Programming Advices Fundamentals Roadmap  
Instructor: Mohammed Abu-Hadhoud  
Website: [programmingadvices.com](https://programmingadvices.com)

## 📄 License

MIT License - Free to use for learning

## 👨‍💻 Author

Created by [@Kerolos08](https://github.com/Kerolos08) as part of the Programming Advices course

---
