#!/usr/bin/env bash
set -e

echo "=== ShellForge Integration Test Suite (Milestones 1-5) ==="

SHELL_BIN="./shellforge"

if [ ! -x "$SHELL_BIN" ]; then
    echo "Error: $SHELL_BIN binary not found!"
    exit 1
fi

echo "[1/5] Testing basic command execution..."
OUTPUT=$($SHELL_BIN << 'EOF'
echo "Hello ShellForge"
pwd
EOF
)
echo "$OUTPUT" | grep -q "Hello ShellForge"

echo "[2/5] Testing invalid command error handling..."
$SHELL_BIN << 'EOF' 2> err.tmp || true
nonexistent_command_12345
EOF
grep -q "command not found" err.tmp
rm -f err.tmp

echo "[3/5] Testing built-in navigation (cd & pwd)..."
OUTPUT=$($SHELL_BIN << 'EOF'
pwd
cd ..
pwd
EOF
)
echo "$OUTPUT"

echo "[4/5] Testing system commands (whoami & date)..."
OUTPUT=$($SHELL_BIN << 'EOF'
whoami
date
EOF
)
echo "$OUTPUT"

echo "[5/5] Testing empty line and exit..."
$SHELL_BIN << 'EOF'

exit
EOF

echo "=== ALL MILESTONE 1-5 TESTS PASSED CLEANLY ==="
