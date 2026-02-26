**HOSPITAL MANAGEMENT SYSTEM — Report**

**Overview:**
- **Description:** This repository contains a simple console-based hospital management program implemented in `hospital.c`. The program stores patient records in a binary file and provides basic CRUD-like operations via a menu.

**Features:**
- **Add Patient:** prompts for ID, name, age, disease and appends a record.
- **View Patients:** lists all stored patient records.
- **Search Patient:** lookup by patient ID.
- **Delete Patient:** remove a record by ID (uses a temporary file to rewrite data).

**Files:**
- **`hospital.c`**: main source implementing the menu and file operations.
- **`patients.dat`**: runtime-generated binary data file holding `struct Patient` records.
- **`temp.dat`**: temporary file used during delete operations.

**Data Layout (struct Patient):**
- **id**: `int`
- **name**: `char[50]`
- **age**: `int`
- **disease**: `char[50]`

**Build & Run (Windows / MinGW or similar):**
```
gcc hospital.c -o hospital.exe
.\\hospital.exe
```

**Runtime Notes:**
- Records are written/read using `fwrite`/`fread` in binary form; files are not portable between architectures with different endianness or struct packing.
- The program uses ANSI color escape codes which may not render correctly in the default Windows Console. Use a terminal that supports ANSI (Windows Terminal, PowerShell 7+, or enable VT processing).

**Usage Example:**
- Run the program, choose `1` to add a patient, `2` to view, `3` to search by ID, `4` to delete, `5` to exit.

**Limitations & Suggested Improvements:**
- No input validation (e.g., duplicate IDs, out-of-range ages) — validate and sanitize inputs.
- No update/edit record option — add an "Update Patient" feature.
- Concurrent access is not handled — consider file locking for multi-process safety.
- Use a text or CSV format (or a small DB) for easier inspection and portability.
- Improve portability by avoiding raw struct writes or by using fixed serialization.
- Add unique ID generation and confirm deletions before removing records.

**Sample Outputs:**

- Add Patient (example):
```
===== HOSPITAL MANAGEMENT SYSTEM =====
1. Add Patient
2. View Patients
3. Search Patient
4. Delete Patient
5. Exit
Enter your choice: 1

Enter Patient ID: 101
Enter Name: John Doe
Enter Age: 45
Enter Disease: Flu

✔ Patient record added successfully!
```

- View Patients (example):
```
========== Patient Records ==========
ID: 101
Name: John Doe
Age: 45
Disease: Flu
-------------------------------------
```

- Search Patient (found):
```
Enter Patient ID to search: 101

✔ Patient Found!
ID: 101
Name: John Doe
Age: 45
Disease: Flu
```

- Search Patient (not found):
```
Enter Patient ID to search: 999

✘ Patient not found!
```

- Delete Patient (example):
```
Enter Patient ID to delete: 101

✔ Patient record deleted successfully!
```

- Exit message:
```
Thank you! Exiting...
```

Created on: 2026-02-26
