# Qt C++ App: Build & Run Instructions (macOS & Windows)

## About
### IoT-Device Manager
The IoT-Device Manager is an educational project developed in C++ and Qt framework that illustrates the prototype for an manager platform for IoT devices in a personalized and user-friendly manner

## Prerequisites

### macOS
- Homebrew (https://brew.sh)
- Qt 5 (recommended: `qt@5`)
- Xcode Command Line Tools

### Windows
- Qt 5 (https://www.qt.io/download)
- MinGW or MSVC (comes with Qt installer)
- Git Bash or Command Prompt

---

## Setup

### macOS

1. **Install Qt 5 via Homebrew:**
   ```sh
   brew install qt@5
   ```

2. **Add Qt to your PATH (for this session):**
   ```sh
   export PATH="/opt/homebrew/opt/qt@5/bin:$PATH"
   ```

3. **Generate Makefile with qmake:**
   ```sh
   cd /path/to/your/project
   qmake .pro
   ```

4. **Build the app:**
   ```sh
   make
   ```

5. **Run the app:**
   ```sh
   ./myapp.app/Contents/MacOS/myapp
   ```
   or, if built as a plain executable:
   ```sh
   ./myapp
   ```

---

### Windows

1. **Install Qt 5 using the official installer.**
   - Choose MinGW or MSVC toolchain during installation.

2. **Open Qt Command Prompt (from Start Menu).**

3. **Navigate to your project folder:**
   ```bat
   cd C:\path\to\your\project
   ```

4. **Generate Makefile with qmake:**
   ```bat
   qmake .pro
   ```

5. **Build the app:**
   ```bat
   mingw32-make
   ```
   or (if using MSVC):
   ```bat
   nmake
   ```

6. **Run the app:**
   ```bat
   myapp.exe
   ```

---

## Notes

- The `.pro` file should list your source files and include `QT += widgets`.
- On macOS, you may need to allow the app to run via System Preferences > Security & Privacy.
- On Windows, ensure your Qt bin directory is in your PATH if you run the app outside Qt's command prompt.

---

## Troubleshooting

- If you get `'QApplication' file not found`, ensure you are using the correct `qmake` from Qt 5.
- If you see linker errors about duplicate `main`, only include one file with a `main()` function in your `.pro` file's `SOURCES`.
- For GUI issues, check that you added widgets to your layout.

---

## Example Run

After building, you should see a window with:
- A prompt that asks the user for their name
- A terminal-like section streaming `std::cout` output.
- "Greet the user" button (prints to terminal section).
- Various buttons that open dialog windows to communicate with hypothetical IoT devices
- "Click to end the program" button (closes the window and ends the program)