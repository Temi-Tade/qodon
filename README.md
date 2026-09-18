# qodon (qdn) 🧬

## A Command Line Genomics tool. Written in C

qodon (invoked as `qdn`) is an ultra-fast, lightweight command-line utility for quick genomic sequence manipulations. Written in pure C, it processes sequence arguments natively at bare-metal speeds, making it perfect for rapid testing, scripting, and pipeline integration. 

### ✨ Features

* **Zero Overhead:** Built in standard C for maximum execution velocity.
* **Dual-Mode Engine:** Run quick one-off commands from your terminal or drop into a stateful interactive shell context.
* **Instant Evaluation:** High-performance byte manipulation for zero-lag sequence transformations.
* **Core Bio-Utilities:** Fast sequence transcription, complementing, reversing, and metric calculations.

## 🚀 Installation

You can install `qodon` directly or build from the source code. 

### 1. Direct Install (Linux, x86_64)

Install precompiled binaries by running: 

```bash
curl -L -o qdn https://github.com/Temi-Tade/qodon/releases/download/v0.2.0/qdn && chmod +x qdn && sudo mv qdn /usr/local/bin/
```

### 2. Build from source

Compile `qdn` natively using any modern C compiler (`gcc` or `clang` required): 

```bash
# Clone the repository
git clone https://github.com/Temi-Tade/qodon.git
cd qodon

# Compile the binary with optimizations
gcc -O3 main.c -o qdn

# Move to your local bin to run it globally
sudo mv qdn /usr/local/bin/
```

## Usage

### 🐚 Mode 1: Interactive Context Shell

Launch `qdn` with the `-i` flag followed by a target sequence to open the interactive context shell. The sequence is loaded directly into the session's workspace memory, allowing you to run rapid back-to-back operations against that specific strand without retyping it. 

```bash
$ qdn -i ATGCATGC
Entering qodon shell...
Template sequence: ATGCATGC 
Length: 8bps 
GC content: 50.00%
qdn> len
8bps
qdn> cmp
ATGCATGC (Template strand)
||||||||
TACGTACG (Complementary strand)
qdn> gc
50.00%
qdn> rev
ATGCATGC (FWD)
CGTACGTA (REV)
qdn> exit
$
```

### Available Shell Commands

Inside the shell, execute operations directly on the initialized sequence: 

| Command | Action | Description |
| :--- | :--- | :--- |
| **cmp** | Complement | Generates the complementary DNA/RNA strand |
| **tr** | Transcribe | Transcribes DNA to RNA (converts T to U) |
| **rt** | Reverse Transcribe | Reverse transcribes RNA to DNA (converts U to T) |
| **rev** | Reverse | Reverses the sequence direction |
| **len** | Length | Computes the total length of the sequence |
| **gc** | GC-Content | Calculates the exact GC content percentage |
| **exit** | Exit | Closes the interactive shell session |

### 🛠️ Mode 2: Quick Terminal Flags

For quick one-offs or integration into larger bash scripts, pass an operational flag followed by your target nucleotide sequence string directly to your terminal: 

```bash
qdn [flag] <SEQUENCE>
```

### Core Flag Operations

| Flag | Shell Command | Action | Description |
| :--- | :--- | :--- | :--- |
| **-c** | cmp | Complement | Generates the complementary DNA/RNA strand |
| **-t** | tr | Transcribe | Transcribes DNA to RNA (converts T to U) |
| **-u** | rt | Reverse Transcribe | Reverse transcribes RNA to DNA (converts U to T) |
| **-l** | len | Length | Computes the total length of the sequence |
| **-g** | gc | GC-Content | Calculates the GC content percentage |
| **-i** |  | Shell Mode | Enter interactive shell |

### 💻 One-off Examples

**Get Complementary Strand:** 

```bash
qdn -c ATGC
# Output: TACG
```

**Transcribe DNA to RNA:** 

```bash
qdn -t GATTACA
# Output: CUAAUGU
```

**Reverse Transcribe RNA to DNA**
```bash
qdn -u UUAGC
# Output: AATCG
```

**Calculate GC Content:** 

```bash
qdn -g CCGGTT
# Output: 66.67%
```

**Get Sequence Length:** 

```bash
qdn -l ATGCATGC
# Output: 8bps
```

### 📄 License

This project is licensed under the MIT License - see the `LICENSE` file for details.