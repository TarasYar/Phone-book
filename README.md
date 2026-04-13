# PhoneBook — C++ Console Application

A console-based contact manager with file persistence and event logging.

---

## Features

- Add contacts (first name, last name, phone number, tag, notes)
- Search contacts by any field
- View all contacts (sorted alphabetically by first and last name)
- Delete contacts
- Automatic saving to `phone_book.txt`
- Event logging to `log.txt`

---

## Project Structure

```
.
├── main.cpp          # Entry point
├── phonebook.h       # Phone_book class declaration
├── phonebook.cpp     # Phone_book class implementation
├── contact.h         # Contact struct
├── logger.h          # Logger class declaration
└── logger.cpp        # Logger class implementation
```

### File Descriptions

| File | Description |
|---|---|
| `contact.h` | `Contact` struct with fields: first name, last name, number, tag, notes |
| `phonebook.h / .cpp` | Core logic: menu, CRUD operations, file read/write |
| `logger.h / .cpp` | Logger class: writes timestamped events to `log.txt` |
| `main.cpp` | Creates a `Phone_book` object and starts the UI |

---

## Build

### Requirements

- C++17-compatible compiler (g++, clang++)

### Compile

```bash
g++ -std=c++17 main.cpp -o phonebook
```

### Run

```bash
./phonebook
```

---

## Usage

After launching, the main menu is displayed:

```
Select the operation you want to perform:
1 - add contact
2 - find contact
3 - show all contacts
4 - delete contact
5 - exit phonebook
Enter your choice:
```

### Adding a Contact

Fields are entered one by one: first name, last name, phone number (digits only, `+` is prepended automatically), tag, and notes. Empty values and commas are not allowed.

### Search

Search performs a case-insensitive exact match against one of the following fields: first name, last name, number, tag, or notes.

### Delete

All contacts are displayed with index numbers — enter the index of the contact you want to remove.

---

## Data Persistence

Contacts are stored in `phone_book.txt` in CSV format:

```
John,Doe,380671234567,friend,call on Friday
```

The file is created automatically on first run. All contacts are written to the file on exit.

---

## Logging

All actions are recorded in `log.txt` with a timestamp:

```
[Mon Apr 13 12:00:00 2026] INFO: The program is running
[Mon Apr 13 12:00:05 2026] INFO: Added one person John, Doe, 380671234567, friend, note
[Mon Apr 13 12:01:00 2026] INFO: The program has completed its work.
```

---

## Known Limitations

- Search finds only **exact matches**, not substrings
- `delete_contact` accesses the iterator after `erase` — undefined behavior
- `inline` in `.cpp` files has no effect for non-template functions
- `phonebook.h` includes `logger.cpp` directly — only the header `.h` should be included
