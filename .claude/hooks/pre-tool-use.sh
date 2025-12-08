#!/bin/bash
# PreToolUse Hook for FourTop Analysis Environment Checking
# Runs before Bash operations to verify environment is set up
#
# Purpose: Remind to source environment before running analysis scripts

# Only check for Bash tool
if [[ "$TOOL_NAME" != "Bash" ]]; then
    exit 0
fi

# Get the command being executed
command_str="$BASH_COMMAND"

# Skip environment setup commands themselves
if [[ "$command_str" =~ source.*setEnv || "$command_str" =~ cmsenv ]]; then
    exit 0
fi

# Skip simple commands that don't need environment
if [[ "$command_str" =~ ^(ls|cd|pwd|cat|head|tail|grep|find|mkdir|rm|cp|mv|git|hep_q|hep_sub|which|echo) ]]; then
    exit 0
fi

# Check if command involves Python analysis scripts
if [[ "$command_str" =~ python.*plotting/ || "$command_str" =~ python.*writeHistGood/ || "$command_str" =~ python.*makeVariables/ ]]; then
    # Check if ROOT is available (indicates environment is set up)
    if ! command -v root &> /dev/null; then
        echo ""
        echo "═══════════════════════════════════════════════════════════════════════"
        echo "⚠️  ENVIRONMENT CHECK: ROOT not found in PATH"
        echo "═══════════════════════════════════════════════════════════════════════"
        echo ""
        echo "You may need to source the environment first:"
        echo "  source setEnv_newNew.sh"
        echo ""
        echo "Exception: For hua/combine/ scripts, use 'cmsenv' instead."
        echo "═══════════════════════════════════════════════════════════════════════"
        echo ""
        # Don't block, just warn (exit 0)
    fi
fi

# Check if command involves combine scripts
if [[ "$command_str" =~ python.*hua/combine ]]; then
    # Check if we're in CMSSW environment
    if [[ -z "$CMSSW_BASE" ]]; then
        echo ""
        echo "═══════════════════════════════════════════════════════════════════════"
        echo "⚠️  ENVIRONMENT CHECK: CMSSW environment not detected"
        echo "═══════════════════════════════════════════════════════════════════════"
        echo ""
        echo "For combine scripts, you need CMSSW environment:"
        echo "  cd hua/combine/"
        echo "  cmsenv"
        echo ""
        echo "═══════════════════════════════════════════════════════════════════════"
        echo ""
    fi
fi

exit 0
