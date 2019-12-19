import os
import sys
import subprocess
import json

def run(module=""):
    folder = os.walk(".")
    short_results = []
    for addr, dirs, files in folder:
        for file in files:
            if "_test.py" in file and module in addr:
                res = file + ": "
                res += "OK" if subprocess.run(["python3", addr+"/"+file]).returncode == 0 else "Failed"
                short_results.append(res)
    
    
    print("-------Short results-------")
    for res in short_results:
        print(res)
        

if __name__ == "__main__":
    run(sys.argv[1])
