import os
import sys
import subprocess

def run(module=""):
    folder = os.walk(".")
    for addr, dirs, files in folder:
        for file in files:
            if "_test.py" in file and module in addr:
                subprocess.run(["python3", addr+"/"+file])
            
if __name__ == "__main__":
    run(sys.argv[1])
