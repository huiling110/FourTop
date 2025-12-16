#!/bin/bash
# PreToolUse Hook for FourTop Analysis
# Receives JSON input via stdin
#
# Purpose:
#   1. Block dangerous commands (including in compound commands)
#   2. Remind to source environment before running analysis scripts

PROJECT_ROOT="/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop"

# Read JSON input from stdin
input=$(cat)

# Parse tool name and command using jq
tool_name=$(echo "$input" | jq -r '.tool_name // empty')
command_str=$(echo "$input" | jq -r '.tool_input.command // empty')

# Only check Bash tool
if [[ "$tool_name" != "Bash" ]]; then
    exit 0
fi

# ============================================================================
# DANGEROUS COMMAND DETECTION (handles compound commands)
# ============================================================================

check_dangerous() {
    local cmd="$1"

    # Dangerous patterns to block (substring match - works in compound commands)
    local dangerous_patterns=(
        "rm -rf"
        "rm -r "
        "sudo "
        "mkfs"
        "dd if="
        "dd of="
        "shutdown"
        "reboot"
        "halt "
        "poweroff"
        "kill -9 -1"
        "chmod -R 000"
        "chmod -R 777"
        "chown "
        "git push --force"
        "git push -f"
        "git push origin +"
        "git reset --hard HEAD~"
        "git clean -fd"
    )

    for pattern in "${dangerous_patterns[@]}"; do
        if [[ "$cmd" == *"$pattern"* ]]; then
            echo ""
            echo "═══════════════════════════════════════════════════════════════════════"
            echo "🚫 BLOCKED: Dangerous command detected!"
            echo "═══════════════════════════════════════════════════════════════════════"
            echo ""
            echo "Pattern: $pattern"
            echo "Command: $cmd"
            echo ""
            echo "This command has been blocked for safety."
            echo "═══════════════════════════════════════════════════════════════════════"
            echo ""
            return 1
        fi
    done
    return 0
}

# Check for dangerous commands
if ! check_dangerous "$command_str"; then
    exit 2  # Exit code 2 = blocked by hook
fi

# ============================================================================
# ENVIRONMENT CHECKS
# ============================================================================

# Check for common mistake - using setEnv_newNew.sh without full path
if [[ "$command_str" =~ "source setEnv_newNew.sh" ]] && [[ ! "$command_str" =~ "cd $PROJECT_ROOT" ]] && [[ ! "$command_str" =~ "cd /workfs2" ]]; then
    echo ""
    echo "═══════════════════════════════════════════════════════════════════════"
    echo "⚠️  PATH ERROR: setEnv_newNew.sh needs full path!"
    echo "═══════════════════════════════════════════════════════════════════════"
    echo ""
    echo "WRONG:  source setEnv_newNew.sh"
    echo "RIGHT:  cd $PROJECT_ROOT && source setEnv_newNew.sh"
    echo ""
    exit 1
fi

# Skip environment setup commands themselves
if [[ "$command_str" =~ source.*setEnv || "$command_str" =~ cmsenv ]]; then
    exit 0
fi

# Skip simple commands that don't need environment
if [[ "$command_str" =~ ^(ls|cd|pwd|cat|head|tail|grep|find|mkdir|rm|cp|mv|git|hep_q|hep_sub|which|echo|for|while) ]]; then
    exit 0
fi

# Check if command involves Python analysis scripts (excluding hua/combine/)
if [[ "$command_str" =~ python.*plotting/ || "$command_str" =~ python.*writeHistGood/ || "$command_str" =~ python.*makeVariables/ || "$command_str" =~ python.*objectSelectionOptimized/jobs/ ]] && [[ ! "$command_str" =~ python.*hua/combine ]]; then
    if ! command -v root &> /dev/null; then
        echo ""
        echo "═══════════════════════════════════════════════════════════════════════"
        echo "❌ ENVIRONMENT ERROR: setEnv_newNew.sh not sourced!"
        echo "═══════════════════════════════════════════════════════════════════════"
        echo ""
        echo "REQUIRED: Source environment before running Python analysis scripts:"
        echo "  source setEnv_newNew.sh && python3 ..."
        echo ""
        exit 1
    fi
fi

# Check if command involves combine scripts
if [[ "$command_str" =~ python.*hua/combine ]]; then
    if [[ -z "$CMSSW_BASE" ]]; then
        echo ""
        echo "═══════════════════════════════════════════════════════════════════════"
        echo "⚠️  ENVIRONMENT CHECK: CMSSW environment not detected"
        echo "═══════════════════════════════════════════════════════════════════════"
        echo ""
        echo "For combine scripts, you need CMSSW environment:"
        echo "  cmsenv"
        echo ""
    fi
fi

exit 0
