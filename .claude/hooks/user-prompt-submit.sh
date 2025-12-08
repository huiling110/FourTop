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
    if [[ "$prompt_lower" =~ (stage|run|submit|job|histogram|hist|datacard|template|combine|validation|plot|pl\.py) ]]; then
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
    if [[ "$prompt_lower" =~ (createfaketau|addjes|addtemplate|writedatacard) ]]; then
        return 0
    fi

    # Python editing keywords (trigger workflow_utils reminder)
    if [[ "$prompt_lower" =~ (edit|update|modify|fix|refactor).*(pl\.py|plotting|workflow_utils|addtemplate|writedatacard|createfake) ]]; then
        return 0
    fi

    # workflow_utils pattern reminder
    if [[ "$prompt_lower" =~ (load_config|get_options|build_hist_path|workflow_utils) ]]; then
        return 0
    fi

    return 1
}

# Check if workflow skill should be activated
if check_workflow_patterns; then
    echo ""
    echo "═══════════════════════════════════════════════════════════════════════"
    echo "🎯 SKILL ACTIVATION CHECK: workflow skill may be relevant"
    echo "═══════════════════════════════════════════════════════════════════════"
    echo ""
    echo "Detected workflow-related keywords in your prompt."
    echo ""
    echo "Consider using the workflow skill (.claude/skills/workflow.md) for:"
    echo "  - Correct environment setup (source setEnv_newNew.sh vs cmsenv)"
    echo "  - Required flags (--config and --era)"
    echo "  - Stage-specific commands and order"
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

exit 0
