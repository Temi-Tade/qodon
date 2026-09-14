# qodon (qdn) 🧬

### A Command Line Genomics tool. Written in C

`qodon` (invoked as `qdn`) is an ultra-fast, lightweight command-line utility for quick genomic sequence manipulations. Written in pure C, it processes sequence arguments natively at bare-metal speeds, making it perfect for rapid testing, scripting, and pipeline integration.

## ✨ Features
* **Zero Overhead:** Built in standard C for maximum execution velocity.
* **Instant Evaluation:** Passes the genetic sequence directly as an argument.
* **Core Bio-Utilities:** Fast sequence transcription, complementing, and metric calculations.

## 🚀 Installation
You can install `qodon` directly or build from the source code.

### 1. Direct Install (Linux, x86_64)
Install precompiled binaries by running:
```bash
curl -L -o mrg https://github.com/Temi-Tade/qodon/releases/download/v0.1.0/qdn && chmod +x mrg && sudo mv mrg /usr/local/bin/
```

### 2. Build from source
Compile `qdn` natively using any modern C compiler (`gcc` or `clang` required):

```bash
# Clone the repository
git clone https://github.com/Temi-Tade/qodon
cd qodon

# Compile the binary with optimizations
gcc -O3 main.c -o qdn

# Move to your local bin to run it globally
sudo mv qdn /usr/local/bin/
```

## 🛠️ Usage & Flags

Run `qdn` by providing a operational flag followed by the target nucleotide sequence string:

```bash
qdn [flag] <SEQUENCE>
```

### Core Operations

| Flag | Operation | Description |
| :--- | :--- | :--- |
| `-c` | Complement | Generates the complementary DNA/RNA strand |
| `-t` | Transcribe | Transcribes DNA to RNA (converts `T` to `U`) |
| `-u` | Reverse Transcribe | Reverse transcribes RNA to DNA (converts `U` to `T`) |
| `-l` | Length | Computes the total length of the sequence |
| `-g` | GC-Content | Calculates the exact GC content percentage |

### 💻 Examples

**Get Complementary Strand:**
```bash
qdn -c ATGC
# Output: TACG
```

**Transcribe DNA to RNA:**
```bash
qdn -t GATTACA
# Output: GAUUACA
```

**Calculate GC Content:**
```bash
qdn -g CCGGTT
# Output: 66.67%
```

**Get Sequence Length:**
```bash
qdn -l ATGCATGC
# Output: 8bp
```

## 📄 License
This project is licensed under the MIT License - see the LICENSE file for details.
