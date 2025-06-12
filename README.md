# projeto_final_ED

Projeto final da A2 da disciplina de Estrutura de Dados.

## Entrega 2

- Implementação de funções para **AVL**, incluindo arquivos `.h`, `.cpp`, testes unitários e `main` (interface de linha de comando - CLI).
- Inclusão de **estatísticas** na CLI e testes para **BST**.

---

## 📦 Compilação e Execução

### ✅ Testes Unitários

**Compilar:**
```bash
g++ test_avl.cpp avl.cpp data.cpp tree_utils.cpp -o avl
g++ test_bst.cpp bst.cpp data.cpp tree_utils.cpp -o bst
```

**Executar:**
```bash
./avl
./bst
```

---

### ✅ CLI com Dados

**Compilar:**
```bash
g++ main_avl.cpp avl.cpp data.cpp tree_utils.cpp -o avl
g++ main_bst.cpp bst.cpp data.cpp tree_utils.cpp -o bst
```

**Executar:**
```bash
./avl <search|stats> <numero_de_docs> <diretorio_dados>
./bst <search|stats> <numero_de_docs> <diretorio_dados>
```

---

## 📁 Estrutura Esperada

- `avl.h`, `avl.cpp`
- `bst.h`, `bst.cpp`
- `data.cpp`
- `tree_utils.cpp`
- `main_avl.cpp`, `main_bst.cpp`
- `test_avl.cpp`, `test_bst.cpp`

---

## 🛠️ Observações

- Certifique-se de que o diretório com dados contém os arquivos a serem lidos pelas árvores.
- Os modos `search` e `stats` determinam a operação realizada via CLI.
