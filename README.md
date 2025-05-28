# 🧬 Game of Life (GoL)

A C implementation of Conway's Game of Life with multiple analytical and generative tasks — including change tracking, rule comparison, Hamiltonian path analysis, and a bonus state reversal feature.

## 📌 Description

This project processes cellular automata patterns using both classic and modified Game of Life rules. It supports a wide range of tasks, from basic simulation to graph-theoretical analysis, with file-based input/output for easy testing and automation.

## 🚀 Features

The program supports five tasks:

### 1️⃣ Basic Simulation  
Prints all generations up to the given one using **standard Game of Life rules**.

### 2️⃣ Cellular Change Tracking  
For each generation, prints the coordinates of cells that changed their state (`X` ↔ `+`).

### 3️⃣ Rule Comparison  
Generates two versions of each generation:
- **Standard rules**
- **Custom rule**: A dead cell with **exactly 2 living neighbors** becomes alive

### 4️⃣ Hamiltonian Path Analysis  
For each configuration in Task 3:
- Computes the **largest connected component** that can be represented as a **Hamiltonian path**
- If a valid path exists, prints the **most optimal** one based on:
  1. Minimal start row
  2. Minimal end column

### 5️⃣ ♻️ Bonus: State Reversal  
Based on the output of Task 2:
- Reverts the matrix configuration **back to the initial state** by undoing the cell state changes across generations.

---

## ⚙️ Usage

### 🔧 Build
```bash
make build gol.c
```

### ▶️ Run
```bash
./a.out <input_file> <output_file>
```

- `<input_file>`: Must contain the task number, matrix dimensions, generation count, and matrix configuration
- `<output_file>`: Output of the task will be written here

### 📄 Input Format

```
<task_number>
<rows> <cols> 
<generation_count>
<initial matrix using '+' for dead and 'X' for alive>
```

#### ✅ Example `input.txt`:
```
2
3 3 
2
+ X +
X + X
+ + X
```

#### 🖨️ Output (`output.txt`) for Task 2 should look like:
```

1 0 1 1 0 1 1 2 2
2 0 0 0 2 2 1
```

---

## 📦 Custom Libraries

This project uses custom-built data structures for modularity and clarity:

| Library            | Description                                 | Used in Tasks     |
|--------------------|---------------------------------------------|-------------------|
| `celula.c/h`       | Cell representation and rule utilities      | All               |
| `lista.c/h`        | Linked list for storing cell changes        | 2, 3, 4, 5        |
| `stiva.c/h`        | Stack for managing reversible operations    | 2, 5              |
| `arbore_binar.c/h` | Binary tree for rule comparison             | 3, 4              |

---

## 🧠 Notes

- The program is **file-based** — perfect for grading scripts, large test sets, and reproducibility.
- Task 4 includes a Hamiltonian path check per component using a custom DFS-based algorithm with specific tiebreaker rules.

---

## 📄 License

This project is licensed under the MIT License.  
See the [LICENSE](LICENSE) file for full details.
