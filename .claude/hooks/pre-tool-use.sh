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

    # Special check: find with -delete (regex needed)
    if [[ "$cmd" =~ find[[:space:]].*-delete ]]; then
        echo ""
        echo "═══════════════════════════════════════════════════════════════════════"
        echo "🚫 BLOCKED: Dangerous command detected!"
        echo "═══════════════════════════════════════════════════════════════════════"
        echo ""
        echo "Pattern: find ... -delete"
        echo "Command: $cmd"
        echo ""
        echo "This command has been blocked for safety."
        echo "═══════════════════════════════════════════════════════════════════════"
        echo ""
        return 1
    fi

    return 0
}

# Check for dangerous commands
if ! check_dangerous "$command_str"; then
    exit 2  # Exit code 2 = blocked by hook
fi

# ============================================================================
# ENVIRONMENT CHECKS
# ============================================================================

# Note: Removed the setEnv path check - Claude Code runs from project root so
# "source setEnv_newNew.sh" works fine. The environment check below catches real issues.

# Skip ONLY if command is purely environment setup (no other commands chained)
# This allows "source setEnv && python3 pl.py" to proceed to skill checking
if [[ "$command_str" =~ ^(source.*setEnv|cmsenv)$ ]]; then
    exit 0
fi

# ============================================================================
# STAGE PATH BLOCKING (MANDATORY SKILL INVOCATION) - MUST BE BEFORE SKIP CHECK
# ============================================================================
# Block ls/find/check commands on stage-specific paths unless skill was invoked
# This enforces the "Forced Eval" pattern - Claude MUST invoke skill first

check_stage_path_blocking() {
    local cmd="$1"

    # Only check ls, find, stat, wc commands (path inspection)
    if [[ ! "$cmd" =~ ^(ls|find|stat|wc|du) ]] && [[ ! "$cmd" =~ "| wc" ]] && [[ ! "$cmd" =~ "ls " ]]; then
        return 0
    fi

    local stage_skill=""
    local stage_name=""
    local path_hint=""

    # Stage 1 (OS): NanoAOD output paths
    if [[ "$cmd" =~ /tauOfTTTT_NanoAOD/UL ]] && [[ ! "$cmd" =~ /forMVA/ ]]; then
        stage_skill="workflow-stage1-os"
        stage_name="Stage 1 (Object Selection)"
        path_hint="/tauOfTTTT_NanoAOD/UL*"
    fi

    # Stage 2 (MV): forMVA paths or baselineHadro pattern
    if [[ "$cmd" =~ /forMVA/ ]] || [[ "$cmd" =~ baselineHadro ]] || [[ "$cmd" =~ v[0-9]+baseline ]]; then
        stage_skill="workflow-stage2-mv"
        stage_name="Stage 2 (Make Variables)"
        path_hint="/forMVA/ or *baselineHadro*"
    fi

    # Stage 3 (WH): variableHists paths
    if [[ "$cmd" =~ variableHists_ ]] || [[ "$cmd" =~ /variableHists/ ]]; then
        stage_skill="workflow-stage3-wh"
        stage_name="Stage 3 (Write Histograms)"
        path_hint="variableHists_*"
    fi

    # Stage 4 (Combine): datacard/template/combine paths
    if [[ "$cmd" =~ /datacard ]] || [[ "$cmd" =~ /combine/ ]] || [[ "$cmd" =~ templatesNew ]]; then
        stage_skill="workflow-stage4-combine"
        stage_name="Stage 4 (Combine)"
        path_hint="datacard/ or combine/"
    fi

    if [[ -n "$stage_skill" ]]; then
        # Check if skill was recently invoked (marker file within 30 mins)
        local marker_file="/tmp/.claude_skill_${stage_skill}_$USER"
        local current_time=$(date +%s)

        if [[ -f "$marker_file" ]]; then
            local marker_time=$(cat "$marker_file" 2>/dev/null || echo 0)
            local age=$((current_time - marker_time))
            if [[ $age -lt 1800 ]]; then
                # Skill was invoked within 30 mins, allow
                return 0
            fi
        fi

        echo ""
        echo "═══════════════════════════════════════════════════════════════════════"
        echo "WARNING: Stage path check - ensure skill was invoked!"
        echo "═══════════════════════════════════════════════════════════════════════"
        echo ""
        echo "Detected: $stage_name path pattern ($path_hint)"
        echo ""
        echo "If you haven't already, invoke the skill first:"
        echo "  Skill(\"$stage_skill\")"
        echo ""
        echo "This ensures correct paths and verification commands."
        echo "═══════════════════════════════════════════════════════════════════════"
        echo ""
        # Non-blocking (warn only) - return 0 to allow command
        return 0
    fi

    return 0
}

# Check for stage path blocking EARLY (BLOCKING - exit 2)
if ! check_stage_path_blocking "$command_str"; then
    exit 2
fi

# Skip simple commands that don't need environment (AFTER stage path check)
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

# ============================================================================
# WORKFLOW SKILL ENFORCEMENT (BLOCKING)
# ============================================================================
# Block stage-specific commands unless the skill was invoked first
# This ensures Claude always has the skill context before running commands

check_workflow_skill_blocking() {
    local cmd="$1"
    local skill_name=""
    local stage_name=""

    # Stage 1: Object Selection
    if [[ "$cmd" =~ makeJob_OS || "$cmd" =~ submit_all_systematics\.sh ]]; then
        skill_name="workflow-stage1-os"
        stage_name="Stage 1 (Object Selection)"
    # Stage 2: Make Variables
    elif [[ "$cmd" =~ makeJob_MV || "$cmd" =~ makeJob_makeVaribles || "$cmd" =~ createFaketau || "$cmd" =~ createFakeLepton ]]; then
        skill_name="workflow-stage2-mv"
        stage_name="Stage 2 (Make Variables)"
    # Stage 3: Write Histograms
    elif [[ "$cmd" =~ makeJob_WH\.py || "$cmd" =~ run_treeAnalyzer\.out ]]; then
        skill_name="workflow-stage3-wh"
        stage_name="Stage 3 (Write Histograms)"
    # Stage 4: Plotting/Datacard/Combine
    elif [[ "$cmd" =~ addJES.*\.py || "$cmd" =~ addTemplate.*\.py || "$cmd" =~ smooth_systematics.*\.py || "$cmd" =~ writeDatacard\.py || "$cmd" =~ pl\.py || "$cmd" =~ writeCombination.*\.py || "$cmd" =~ run_combine || "$cmd" =~ runCombine || "$cmd" =~ plotVariables ]]; then
        skill_name="workflow-stage4-combine"
        stage_name="Stage 4 (Plotting/Combine)"
    fi

    # If no stage detected, allow command
    if [[ -z "$skill_name" ]]; then
        return 0
    fi

    # Check if skill was recently invoked (marker file within 30 mins)
    local marker_file="/tmp/.claude_skill_${skill_name}_$USER"
    local current_time=$(date +%s)

    if [[ -f "$marker_file" ]]; then
        local marker_time=$(cat "$marker_file" 2>/dev/null || echo 0)
        local age=$((current_time - marker_time))
        if [[ $age -lt 1800 ]]; then
            # Skill was invoked within 30 mins, allow command
            return 0
        fi
    fi

    # BLOCK: Skill not invoked or expired
    echo ""
    echo "═══════════════════════════════════════════════════════════════════════"
    echo "🚫 BLOCKED: $stage_name skill not invoked!"
    echo "═══════════════════════════════════════════════════════════════════════"
    echo ""
    echo "Command: $cmd"
    echo ""
    echo "You MUST invoke the skill first:"
    echo "  Skill(\"$skill_name\")"
    echo ""
    echo "This ensures you have the correct paths, prerequisites, and commands."
    echo "═══════════════════════════════════════════════════════════════════════"
    echo ""
    return 1
}

# Check workflow skill (BLOCKING - exit 2 if skill not invoked)
if ! check_workflow_skill_blocking "$command_str"; then
    exit 2
fi

exit 0
