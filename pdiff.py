import sys
import subprocess
from rapidfuzz.distance import Levenshtein


def percentage(s1: str, s2: str) -> float:
    diff = Levenshtein.distance(s1, s2)
    return 100 * diff / len(s1)

if __name__ == "__main__":
    file_path = sys.argv[-1]
    file_a = subprocess.check_output(f"git show HEAD:./{file_path} | cat", shell=True)
    file_b = subprocess.check_output(f"cat {file_path}", shell=True)

    print(f"diff: {percentage(file_a.decode(), file_b.decode()):.2f}%")
