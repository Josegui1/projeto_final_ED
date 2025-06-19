import subprocess
import matplotlib.pyplot as plt
import re

executables = {
    "AVL": "./avl",
    "BST": "./bst",
    "RBT": "./rbt"
}

directory = "data"  # your folder with documents
doc_counts = list(range(100, 200, 400))  # run for 5, 10, ..., 50 documents

results = {name: [] for name in executables}  # Store results for each tree

# Run tests
for n_docs in doc_counts:
    for name, exe in executables.items():
        print(f"Running {name} with {n_docs} documents...")
        try:
            output = subprocess.check_output(
                [exe, "stats", str(n_docs), directory],
                stderr=subprocess.STDOUT,
                universal_newlines=True
            )
            # Parse the stats output
            comparisons = re.search(r"Comparacoes totais: (\d+)", output)
            total_time = re.search(r"Tempo total de busca: ([\d.]+)", output)
            max_depth = re.search(r"Altura do maior galho: (\d+)", output)

            results[name].append({
                "docs": n_docs,
                "comparisons": int(comparisons.group(1)) if comparisons else 0,
                "time": float(total_time.group(1)) if total_time else 0.0,
                "depth": int(max_depth.group(1)) if max_depth else 0
            })
        except subprocess.CalledProcessError as e:
            print(f"Error running {exe}:")
            print(e.output)

# Plotting
for metric in ["comparisons", "time", "depth"]:
    plt.figure()
    for name in executables:
        y = [r[metric] for r in results[name]]
        plt.plot(doc_counts, y, label=name)
    plt.xlabel("Number of documents")
    plt.ylabel(metric.capitalize())
    plt.title(f"{metric.capitalize()} vs Number of Documents")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"{metric}_plot.png")
    plt.show()
