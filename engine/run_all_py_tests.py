import os
import subprocess

folder = os.walk(".")
for addr, dirs, files in folder:
    for file in files:
        if "_test.py" in file:
            subprocess.run(["python3", addr+"/"+file])
