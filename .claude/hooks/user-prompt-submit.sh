#!/bin/bash
# UserPromptSubmit Hook for FourTop Analysis
# Runs BEFORE Claude sees the user's message
# Purpose: Inject skill activation reminders based on prompt keywords
#
# This implements auto-activation of skills as suggested by best practices

USER_PROMPT="$USER_PROMPT"

# Function to check if prompt matches workflow patterns
check_workflow_patterns() {
    local prompt_lower=$(echo "$USER_PROMPT" | tr '[:upper:]' '[:lower:]')

    # Stage-related keywords (case insensitive)
    if [[ "$prompt_lower" =~ (stage|run|submit|job|histogram|hist|datacard|template|combine|validation|plot|pl\.py|workflow|status|where.?we.?at|resume|progress|pipeline) ]]; then
        return 0
    fi

    # Abbreviation keywords
    if [[ "$prompt_lower" =~ (^|\s)(os|mv|wh|pl)(\s|$|[,\.]) ]]; then
        return 0
    fi

    # Full name keywords
    if [[ "$prompt_lower" =~ (object.?selection|make.?variable|write.?hist|plotting) ]]; then
        return 0
    fi

    # Era keywords (suggests processing data)
    if [[ "$prompt_lower" =~ (2018|2017|2016|all.?era|run2) ]]; then
        return 0
    fi

    # Config/YAML keywords
    if [[ "$prompt_lower" =~ (yaml|config|\.yaml|analysis_config) ]]; then
        return 0
    fi

    # Environment keywords
    if [[ "$prompt_lower" =~ (environment|setenv|cmsenv|source) ]]; then
        return 0
    fi

    # Fake background keywords
    if [[ "$prompt_lower" =~ (fake.?tau|fake.?lepton|data.?driven|background) ]]; then
        return 0
    fi

    # Specific scripts
    if [[ "$prompt_lower" =~ (createfaketau|addjes|addtemplate|writedatacard|makejob_os|makejob_mv|makejob.*hist) ]]; then
        return 0
    fi

    # Python editing keywords (trigger workflow_utils reminder)
    if [[ "$prompt_lower" =~ (edit|update|modify|fix|refactor).*(pl\.py|plotting|workflow_utils|addtemplate|writedatacard|createfake) ]]; then
        return 0
    fi

    # workflow_utils pattern reminder
    if [[ "$prompt_lower" =~ (load_config|get_options|build_hist_path|build_stage1|get_channel|workflow_utils) ]]; then
        return 0
    fi

    return 1
}

# Check if workflow skill should be activated
if check_workflow_patterns; then
    # Read workflow state if exists (Phase 8)
    PROJECT_ROOT="${PROJECT_ROOT:-/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop}"
    STATE_FILE="$PROJECT_ROOT/.workflow_state.json"

    if [[ -f "$STATE_FILE" ]]; then
        # Detect channel from prompt (1tau0l, 1tau1l, 1tau2l)
        prompt_lower=$(echo "$USER_PROMPT" | tr '[:upper:]' '[:lower:]')
        CHANNEL=""
        if [[ "$prompt_lower" =~ 1tau0l ]]; then
            CHANNEL="1tau0l"
        elif [[ "$prompt_lower" =~ 1tau1l ]]; then
            CHANNEL="1tau1l"
        elif [[ "$prompt_lower" =~ 1tau2l ]]; then
            CHANNEL="1tau2l"
        else
            # Default to first channel in state
            if command -v jq &> /dev/null; then
                CHANNEL=$(jq -r '.channels | keys[0]' "$STATE_FILE" 2>/dev/null)
            else
                # Fallback to Python if jq not available
                CHANNEL=$(python3 -c "import json; print(list(json.load(open('$STATE_FILE')).get('channels', {}).keys())[0] if json.load(open('$STATE_FILE')).get('channels') else '')" 2>/dev/null)
            fi
        fi

        if [[ -n "$CHANNEL" ]]; then
            # Try jq first, fall back to Python
            if command -v jq &> /dev/null; then
                CURRENT_STAGE=$(jq -r ".channels.\"$CHANNEL\".current.stage // \"unknown\"" "$STATE_FILE" 2>/dev/null)
                CURRENT_ERA=$(jq -r ".channels.\"$CHANNEL\".current.era // \"unknown\"" "$STATE_FILE" 2>/dev/null)
                CURRENT_STATUS=$(jq -r ".channels.\"$CHANNEL\".current.status // \"unknown\"" "$STATE_FILE" 2>/dev/null)
                CURRENT_OP=$(jq -r ".channels.\"$CHANNEL\".current.operation // \"unknown\"" "$STATE_FILE" 2>/dev/null)
            else
                # Python fallback
                CURRENT_STAGE=$(python3 -c "import json; d=json.load(open('$STATE_FILE')); print(d.get('channels',{}).get('$CHANNEL',{}).get('current',{}).get('stage','unknown'))" 2>/dev/null)
                CURRENT_ERA=$(python3 -c "import json; d=json.load(open('$STATE_FILE')); print(d.get('channels',{}).get('$CHANNEL',{}).get('current',{}).get('era','unknown'))" 2>/dev/null)
                CURRENT_STATUS=$(python3 -c "import json; d=json.load(open('$STATE_FILE')); print(d.get('channels',{}).get('$CHANNEL',{}).get('current',{}).get('status','unknown'))" 2>/dev/null)
                CURRENT_OP=$(python3 -c "import json; d=json.load(open('$STATE_FILE')); print(d.get('channels',{}).get('$CHANNEL',{}).get('current',{}).get('operation','unknown'))" 2>/dev/null)
            fi

            # Inject workflow context (auto-inject only, per user preference)
            if [[ "$CURRENT_STAGE" != "unknown" && "$CURRENT_STAGE" != "null" ]]; then
                echo ""
                echo "<workflow_context>"
                echo "Channel: $CHANNEL"
                echo "Current Pipeline State:"
                echo "  Stage: $CURRENT_STAGE"
                echo "  Era: $CURRENT_ERA"
                echo "  Operation: $CURRENT_OP"
                echo "  Status: $CURRENT_STATUS"
                echo ""
                echo "Detected workflow keywords in prompt. Relevant stage skill:"
                echo "  .claude/skills/workflow/stage${CURRENT_STAGE%%.*}.md"
                echo ""
                echo "State file: .workflow_state.json (updated automatically)"
                echo "</workflow_context>"
                echo ""
            fi
        fi
    fi

    # Original banner (shown if no state or as fallback)
    if [[ ! -f "$STATE_FILE" ]] || [[ -z "$CHANNEL" ]] || [[ "$CURRENT_STAGE" == "unknown" ]]; then
        echo ""
        echo "═══════════════════════════════════════════════════════════════════════"
        echo "🎯 SKILL ACTIVATION CHECK: workflow skill may be relevant"
        echo "═══════════════════════════════════════════════════════════════════════"
        echo ""
        echo "Detected workflow-related keywords in your prompt."
        echo ""
        echo "Consider using the workflow skill (.claude/skills/workflow.md) for:"
        echo "  - Correct environment setup (source setEnv_newNew.sh vs cmsenv)"
        echo "  - Required flags (--config and --era, --sys for systematics)"
        echo "  - Stage-specific commands: OS (Stage 1), MV (2), WH (3), PL (4)"
        echo "  - Fake tau/lepton regeneration requirements"
        echo "  - Python pattern: use workflow_utils for config handling"
        echo ""
        echo "Python scripts MUST use workflow_utils:"
        echo "  from workflow_utils import load_config, get_options, ..."
        echo ""
        echo "Usage: Skill 'workflow' or read .claude/skills/workflow.md"
        echo "═══════════════════════════════════════════════════════════════════════"
        echo ""
    fi
fi

exit 0
