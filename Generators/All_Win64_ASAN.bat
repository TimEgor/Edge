@echo off
cmake -S .. -B Build/Win64/All -A x64 -DCMAKE_INSTALL_PREFIX=../INSTALL -DEDGE_ASAN=1