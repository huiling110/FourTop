# Bash Commands Explained - Learning Guide

This document explains common bash commands used in this session so you can learn and reuse them.

---

## Process Management Commands

### Check Running Processes
```bash
# ps: "process status" - shows running processes
# aux: a=all users, u=user-oriented format, x=include processes without terminal
# grep: search for pattern in output
# | (pipe): sends output of one command as input to next command
ps aux | grep "run_treeAnalyzer.out" | grep -v grep | head -1

# Breakdown:
# 1. ps aux              → List all running processes with details
# 2. | grep "pattern"    → Filter only lines containing "pattern"
# 3. | grep -v grep      → Remove the grep command itself from results (-v = invert match)
# 4. | head -1           → Show only first line of output
```

**What it shows:**
- Username, PID (Process ID), CPU%, Memory%, etc.
- Command that's running
- How long it's been running

### Kill a Process
```bash
# Kill running jobs (be careful with this!)
ps aux | grep -E "python.*runCombineAll.py" | grep -v grep | awk '{print $2}' | xargs kill -9 2>/dev/null

# Breakdown:
# 1. ps aux | grep -E "pattern"  → Find processes matching extended regex pattern
# 2. awk '{print $2}'            → Extract 2nd column (PID)
# 3. xargs kill -9               → Pass PIDs to kill command with signal 9 (force kill)
# 4. 2>/dev/null                 → Suppress error messages (2=stderr, /dev/null=discard)
```

⚠️ **Warning**: `kill -9` forces termination. Use regular `kill` first if possible.

---

## File Operations

### Check File Contents
```bash
# head: Show first N lines of file
head -50 filename.log

# tail: Show last N lines of file
tail -30 filename.log

# tail -f: Follow file as it grows (like "live view")
tail -f filename.log

# cat: Concatenate and display entire file
cat filename.txt

# less: View file with scrolling (q to quit, / to search)
less filename.log
```

### Check File Existence and Permissions
```bash
# ls: List files
# -l: Long format (shows permissions, size, date)
# -h: Human-readable sizes (KB, MB, GB instead of bytes)
# -a: Show hidden files (starting with .)
ls -lh filename.txt

# file: Determine file type
file filename.out

# Check if file is executable
ls -l filename.out | grep "^-rwx"
# First column shows permissions: r=read, w=write, x=execute
```

---

## Git Commands

### Check Status
```bash
# git status: Show which files are modified/staged/untracked
git status

# git status --short: Condensed view
# M  = modified and staged
#  M = modified but not staged
# ?? = untracked file
git status --short
```

### Add and Commit Files
```bash
# Stage files for commit
git add file1.txt file2.txt

# Commit with inline message
git commit -m "Brief description"

# Commit with multi-line message using heredoc
git commit -m "$(cat <<'EOF'
Title: Brief summary

Detailed explanation:
- Point 1
- Point 2
- Point 3
EOF
)"

# Breakdown of heredoc:
# $(...)     → Command substitution - runs command and inserts output
# cat        → Output what follows
# <<'EOF'    → Here document - multi-line string until EOF marker
#              Quotes around EOF prevent variable expansion
# EOF        → End marker (can be any word, EOF is conventional)
```

### View Changes
```bash
# Show differences in staged files
git diff --staged

# Show differences in working directory
git diff

# Show specific file changes
git diff filename.txt

# Show last N commits
git log -3

# Show commit graph
git log --oneline --graph
```

---

## Directory Navigation

### Change and Create Directories
```bash
# cd: Change directory
cd /path/to/directory

# cd with relative paths
cd ..                    # Go up one level
cd ../../                # Go up two levels
cd ~/                    # Go to home directory
cd -                     # Go to previous directory

# mkdir: Create directory
mkdir dirname

# mkdir -p: Create parent directories if needed (no error if exists)
mkdir -p path/to/deep/directory

# pwd: Print working directory (shows where you are)
pwd
```

---

## Environment and Build Commands

### Source Environment Scripts
```bash
# source: Execute script in current shell (keeps variables)
source script.sh

# Alternative syntax (same thing)
. script.sh

# Why use source instead of running script directly?
# ./script.sh         → Runs in new shell, variables lost after exit
# source ./script.sh  → Runs in current shell, variables persist
```

### Build with Make
```bash
# make: Build project using Makefile
make

# make clean: Remove built files
make clean

# make with output filtering
make 2>&1 | tail -30

# Breakdown:
# 2>&1       → Redirect stderr (2) to stdout (1) so both go through pipe
# | tail -30 → Show only last 30 lines of output
```

---

## Background Jobs and Monitoring

### Run Commands in Background
```bash
# & at end: Run in background
command &

# nohup: Keep running after terminal closes
nohup command > output.log 2>&1 &

# Breakdown:
# nohup                → "no hang up" - immune to hangup signal
# > output.log         → Redirect stdout to file
# 2>&1                 → Redirect stderr to same place as stdout
# &                    → Run in background

# Store PID for later reference
command &
echo "Started with PID: $!"
# $! is special variable containing PID of last background job
```

### Monitor Background Jobs
```bash
# jobs: List background jobs in current shell
jobs

# jobs -l: List with PIDs
jobs -l

# fg: Bring background job to foreground
fg %1                    # Bring job 1 to foreground

# bg: Resume suspended job in background
bg %1
```

---

## Text Processing

### Grep (Search Text)
```bash
# grep: Search for pattern in text
grep "pattern" filename.txt

# Common options:
grep -i "pattern" file   # -i: Case insensitive
grep -n "pattern" file   # -n: Show line numbers
grep -v "pattern" file   # -v: Invert match (exclude lines)
grep -E "pat1|pat2" file # -E: Extended regex (OR pattern)
grep -A 5 "pattern" file # -A: Show 5 lines After match
grep -B 3 "pattern" file # -B: Show 3 lines Before match
grep -C 2 "pattern" file # -C: Show 2 lines of Context (before & after)
```

### Awk (Column Processing)
```bash
# awk: Pattern scanning and processing language
# Common use: Extract columns

# Print 2nd column
echo "col1 col2 col3" | awk '{print $2}'
# Output: col2

# Print columns 1 and 3
ps aux | awk '{print $1, $3}'  # Username and CPU%

# With custom separator
awk -F',' '{print $1}' file.csv  # CSV file (comma-separated)
```

### Find Files
```bash
# find: Search for files by name/type/etc
find /path -name "*.txt"           # Find all .txt files
find . -type f -name "test*"       # Find files starting with "test"
find . -type d                     # Find all directories
find . -name "*.log" -mtime -7     # Files modified in last 7 days

# Limit output
find . -name "*.sh" | head -5      # Show only first 5 results
```

---

## Combining Commands

### Conditional Execution
```bash
# && : Run second command only if first succeeds
command1 && command2

# || : Run second command only if first fails
command1 || command2

# Example:
mkdir testdir && cd testdir
# Only cd if mkdir succeeded

ls file.txt 2>/dev/null || echo "File not found"
# Print message only if file doesn't exist
```

### Command Chaining
```bash
# ; : Run commands sequentially (ignore success/fail)
command1 ; command2 ; command3

# Example:
cd /tmp ; ls ; pwd
# Changes to /tmp, lists files, shows current directory
```

---

## Special Variables and Redirection

### Special Variables
```bash
$?     # Exit status of last command (0=success, non-zero=error)
$!     # PID of last background job
$$     # PID of current shell
$0     # Name of script
$1-$9  # Script arguments (positional parameters)
$@     # All arguments as separate words
$#     # Number of arguments
```

### Redirection
```bash
>      # Redirect stdout to file (overwrite)
>>     # Redirect stdout to file (append)
2>     # Redirect stderr to file
2>&1   # Redirect stderr to stdout
&>     # Redirect both stdout and stderr (bash shortcut)

# Examples:
command > output.txt              # Save output
command 2> errors.txt             # Save only errors
command > output.txt 2>&1         # Save both output and errors
command &> combined.txt           # Same as above (shorter)
command > /dev/null 2>&1          # Discard all output
```

---

## Practical Examples

### Example 1: Build and Run
```bash
# Clean, source environment, build, and run
source ../setEnv_newNew.sh &&  # Source environment (keep vars)
make clean &&                   # Remove old build files
make &&                         # Build project
./apps/executable.out args      # Run if build succeeded
```

### Example 2: Monitor Log File
```bash
# Run in background and monitor
nohup ./program > program.log 2>&1 &  # Start in background
echo "Started with PID: $!"            # Show PID
tail -f program.log                    # Follow log file (Ctrl+C to stop)
```

### Example 3: Check and Commit
```bash
# Check status, add files, commit
git status --short &&                  # See what changed
git add file1.txt file2.txt &&        # Stage files
git commit -m "Description" &&        # Commit
git log -1                            # Show last commit
```

### Example 4: Search and Process
```bash
# Find files, search content, process results
find . -name "*.log" |                    # Find all log files
  xargs grep -l "ERROR" |                 # Find logs containing "ERROR"
  while read file; do                     # Loop through each file
    echo "Processing: $file"
    # Do something with $file
  done
```

---

## Tips and Best Practices

### 1. Always Quote Variables
```bash
# Bad (can break with spaces):
cd $DIR

# Good:
cd "$DIR"
# or
cd "${DIR}"
```

### 2. Check Command Success
```bash
# Check if command succeeded
if make; then
    echo "Build successful"
else
    echo "Build failed"
    exit 1
fi

# Or shorter:
make || { echo "Build failed"; exit 1; }
```

### 3. Use set Options for Safety
```bash
#!/bin/bash
set -e  # Exit on error
set -u  # Exit on undefined variable
set -x  # Print commands as they execute (debugging)
```

### 4. Test Before Destructive Operations
```bash
# Check if file exists before deleting
[ -f "file.txt" ] && rm "file.txt"

# Check if directory is empty before removing
[ "$(ls -A directory)" ] || rmdir directory
```

---

## Quick Reference

| Command | Purpose | Example |
|---------|---------|---------|
| `pwd` | Print working directory | `pwd` |
| `ls` | List files | `ls -lh` |
| `cd` | Change directory | `cd /path` |
| `mkdir` | Create directory | `mkdir -p path/to/dir` |
| `cp` | Copy | `cp src dest` |
| `mv` | Move/rename | `mv old new` |
| `rm` | Remove | `rm file.txt` |
| `cat` | Show file | `cat file.txt` |
| `grep` | Search text | `grep "pattern" file` |
| `find` | Find files | `find . -name "*.txt"` |
| `ps` | Show processes | `ps aux` |
| `kill` | Terminate process | `kill PID` |
| `make` | Build project | `make` |
| `git status` | Check git status | `git status` |
| `source` | Run script in shell | `source script.sh` |

---

*Remember*:
- Use `man command` to see full manual (e.g., `man grep`)
- Use `command --help` for quick help
- Use `which command` to find where a command is located
- Use Tab key for auto-completion!

---

*Last Updated: 2025-11-04*
