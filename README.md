# 🐚 **Minishell**

[![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=flat-square)]()
[![Shell](https://img.shields.io/badge/Shell-Bash%20Inspired-lightgrey?style=flat-square)](https://en.wikipedia.org/wiki/Bash_(Unix_shell))

Welcome to **Minishell**, a 42 School project where we build a simple yet powerful custom shell. It's a miniature version of Bash, carefully crafted to handle common shell operations with elegance and efficiency.

---

## 🎨 **Features**

- **🔧 Command Execution**: Run binaries and built-in commands seamlessly.
- **🌐 Environment Variables**: Export, unset, and manipulate variables dynamically.
- **🔀 Pipelines (`|`)**: Chain commands using pipes.
- **📄 Input/Output Redirection**:
  - Redirect standard input (`<`) and output (`>`).
  - Append output to files (`>>`).
- **🧠 Custom Signals**: Gracefully handle `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`.
- **⚠️ Error Handling**: Informative error messages to guide users.
- **💡 Interactive Mode**: Fully functional prompt for real-time command execution.

---

## 🛠️ **Built-In Commands**

| Command   | Description                               |
|-----------|-------------------------------------------|
| `echo`    | Display a line of text                    |
| `cd`      | Change the current working directory      |
| `pwd`     | Print the current working directory       |
| `export`  | Set or export environment variables       |
| `unset`   | Unset environment variables               |
| `env`     | Display the current environment variables |
| `exit`    | Exit the shell with a status code         |

---

## 📁 **Directory Structure**

```plaintext
minishell/
├── include/           # Header files
├── src/               # Source code files
│   ├── execution/     # Command execution logic
│   ├── parsing/       # Input parsing logic
│   ├── builtins/      # Built-in command implementations
│   ├── signals/       # Signal handling
│   ├── utils/         # Helper functions
├── Makefile           # Build system
└── README.md          # Project documentation
```

---

## 🚀 **Getting Started**

### **Prerequisites**

- GCC Compiler
- GNU Make
- A UNIX-like operating system

### **Installation**

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/minishell.git
   cd minishell
   ```

2. **Compile the Project**

   ```bash
   make
   ```

### **Running Minishell**

Start the shell by executing:

```bash
./minishell
```

---

## 📖 **How It Works**

1. **Prompt Display**: Shows a custom prompt and waits for user input.
2. **Command Parsing**: Breaks down the input into commands and arguments.
3. **Execution Flow**:
   - **Built-In Commands**: Handled internally within the shell.
   - **External Commands**: Located using the `PATH` environment variable and executed using `execve`.
4. **Pipelines and Redirections**:
   - **Pipes**: Connects the output of one command to the input of another.
   - **Redirections**: Redirects input/output to files or other commands.
5. **Signal Handling**: Custom handlers for signals like `SIGINT` and `SIGQUIT` to ensure smooth operation.

---

## 🧪 **Testing the Shell**

Try out various commands to test the functionality:

- **Built-In Commands**:
  - `cd ~/folder`
  - `pwd`
  - `echo "Hello, World!"`
  - `export VAR=value`
  - `unset VAR`
  - `env`
  - `exit`
- **Pipelines**:
  - `ls -la | grep minishell`
  - `cat file.txt | sort | uniq`
- **Redirections**:
  - Input redirection: `sort < unsorted.txt`
  - Output redirection: `echo "Sample Text" > output.txt`
  - Append output: `echo "More Text" >> output.txt`

---

## 🌟 **Highlights**

- **User-Friendly Interface**: Clean and intuitive command-line interface.
- **Modular Codebase**: Easy to read, maintain, and extend.
- **Robust Error Handling**: Provides clear messages for invalid inputs or errors.
- **Compliance with Bash**: Mimics Bash behavior for a seamless user experience.

---

## 🤝 **Contributing**

Contributions are welcome! Here's how you can help:

1. **Fork the Repository**

   Click the "Fork" button at the top right corner of the repository page.

2. **Create a Feature Branch**

   ```bash
   git checkout -b feature/YourFeature
   ```

3. **Commit Your Changes**

   ```bash
   git commit -am 'Add YourFeature'
   ```

4. **Push to the Branch**

   ```bash
   git push origin feature/YourFeature
   ```

5. **Open a Pull Request**

   Submit your pull request, and we'll review it together!

---

## 📄 **License**

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

---

## 💬 **Contact**

- **Author**: Abdurahim Hudulov
- **Email**: [abul.hudul@gmail.com](mailto:abul.hudul@gmail.com)
- **GitHub**: [abdurahim-H](https://github.com/abdurahim-H)

---

## 🎉 **Acknowledgments**

- **42 School**: For the opportunity to learn and grow through this project.
- **Open-Source Community**: For the invaluable resources and support.
