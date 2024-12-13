# WT Scheduler:

Scheduling Web Application built in C++ with WT.

#### Requirements:

Wt Installation guide located here:
Linux: https://www.webtoolkit.eu/wt/doc/reference/html/InstallationUnix.html

Windows: https://www.webtoolkit.eu/wt/doc/reference/html/InstallationWindows.html

Compiler: g++ with support for C++20

#### From Shell Script

If you have a `posix` compliant shell, then it's simple:
Simply run `run.sh` in project directory.

Program will be compiled and ran automatically.

**Read shell script to see other options for script.**

#### Windows:

Run commands in parent directory:

Compile:
```
make
```
Afterwards the binary for the project should be in root of project directory
named: `main`.

Execute the binary:
```
./main --docroot / --deploy-path / --http-address 0.0.0.0  --http-port 9090
```

