#!/bin/bash
# UserPromptSubmit Hook for FourTop Analysis
# Runs BEFORE Claude sees the user's message
# Purpose: Inject skill activation reminders based on prompt keywords AND current directory
#
# This implements auto-activation of skills as suggested by best practices

USER_PROMPT="$USER_PROMPT"

# Detect current directory and suggest skill
detect_directory_skill() {
    local cwd="${PWD:-$(pwd)}"

    # Map directories to skills
    if [[ "$cwd" == *"/plotting"* ]] || [[ "$cwd" == *"/plotting/"* ]]; then
        echo "workflow-stage4-combine"
    elif [[ "$cwd" == *"/writeHistGood"* ]]; then
        echo "workflow-stage3-wh"
    elif [[ "$cwd" == *"/makeVariables_goodCode"* ]]; then
        echo "workflow-stage2-mv"
    elif [[ "$cwd" == *"/objectSelectionOptimized"* ]]; then
        echo "workflow-stage1-os"
    elif [[ "$cwd" == *"/hua/combine"* ]]; then
        echo "workflow-stage4-combine"
    else
        echo ""
    fi
}

# Get directory-based skill
DIR_SKILL=$(detect_directory_skill)

# Inject directory-based skill hint if detected
if [[ -n "$DIR_SKILL" ]]; then
    echo ""
    echo "<directory_skill_hint>"
    echo "Current directory suggests: $DIR_SKILL"
    echo ">>> Use: /workflow or invoke Skill(\"$DIR_SKILL\") for stage-specific commands <<<"
    echo "</directory_skill_hint>"
    echo ""
fi

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
    if [[ "$prompt_lower" =~ (createfaketau|createfakelepton|addjes|addtemplate|writedatacard|makejob_os|makejob_mv|makejob.*hist) ]]; then
        return 0
    fi

    # Stage 1 (OS) keywords
    if [[ "$prompt_lower" =~ (skimmed|nanoaod|nano.?aod|stage.?1|objectselection|object.?selection) ]]; then
        return 0
    fi

    # Stage 2 (MV) keywords
    if [[ "$prompt_lower" =~ (makevariables|make.?variables|stage.?2|fr_weight|fake.?rate) ]]; then
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
    PROJECT_ROOT="${PROJECT_ROOT:-/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop}"

    # V3 state file (compact format) - check first
    STATE_FILE_V3="$PROJECT_ROOT/.workflow/state.json"
    # V2 state file (legacy format) - fallback
    STATE_FILE_V2="$PROJECT_ROOT/.workflow_state.json"

    V3_INJECTED=false

    # Try V3 state file first (compact format with paths)
    if [[ -f "$STATE_FILE_V3" ]]; then
        # Read V3 state using Python (more reliable than jq for this format)
        V3_OUTPUT=$(python3 -c "
import json
import sys
try:
    state_file = sys.argv[1]
    with open(state_file) as f:
        state = json.load(f)

    channel = state.get('channel', 'unknown')
    config = state.get('config', '')
    next_action = state.get('next_action', 'check status')
    eras = state.get('eras', {})
    versions = state.get('versions', {})

    # Build era summary
    era_parts = []
    for era in sorted(eras.keys()):
        info = eras[era]
        stage = info.get('stage', '?')
        status = info.get('status', '?')
        jobs = info.get('jobs', 0)

        if stage == 'complete':
            era_parts.append(f'{era}: complete')
        elif jobs > 0 and status == 'running':
            era_parts.append(f'{era}: S{stage} {status} ({jobs} jobs)')
        else:
            era_parts.append(f'{era}: S{stage} {status}')

    # Get next command suggestion
    next_cmd = '# check workflow state'
    active_era = None
    for era in sorted(eras.keys()):
        info = eras[era]
        status = info.get('status', 'unknown')
        stage = info.get('stage', '0')

        if status == 'running':
            next_cmd = f'hep_q -u \$USER  # Check {era} S{stage} jobs'
            active_era = era
            break
        elif status in ['pending', 'done', 'submitted']:
            stage_cmds = {
                '3': f'python3 writeHistGood/jobs/makeJob_WH.py --config {config} --era {era} --systematic nominal',
                '3.1': f'python3 writeHistGood/jobs/makeJob_WH.py --config {config} --era {era} --systematic all',
                '4.1': f'python3 plotting/addJESTemplatesToHistFile.py --config {config} --era {era} --execute --quiet',
                '4.2': f'python3 plotting/addTemplateNew.py --config {config} --era {era} --quiet',
                '4.3': f'python3 plotting/writeDatacard.py --config {config} --era {era}',
                '4.4': f'python3 plotting/pl.py --config {config} --era {era}',
                '4.5': f'cd hua/combine/ && bash run_combine_fits.sh ../../{config} {era} {channel}',
                '4.6': f'python3 plotting/pl_postFit.py --config {config} --era {era}',
            }
            next_cmd = stage_cmds.get(stage, '# check workflow state')
            active_era = era
            break

    # Get paths for active era (V3.1 enhancement)
    paths_info = ''
    if active_era:
        era_info = eras.get(active_era, {})
        paths = era_info.get('paths', {})
        if paths and 'hist_dir' in paths:
            hist_dir = paths['hist_dir']
            paths_info = f'''
<paths era=\"{active_era}\">
hist_dir: {hist_dir}
verify: ls {hist_dir}/*.root 2>/dev/null | wc -l  # expect 71 (nominal) or 559+ (with sys)
errors: ls {hist_dir}/log/*.err 2>/dev/null | xargs grep -l Error | head -3
</paths>'''

    # Output
    print(f'CHANNEL={channel}')
    print(f'ERAS={\" | \".join(era_parts)}')
    print(f'NEXT={next_action}')
    print(f'CMD={next_cmd}')
    print(f'HIST_VERSION={versions.get(\"hist\", \"\")}')
    print(f'PATHS_INFO={paths_info}')
    print('SUCCESS=true')
except Exception as e:
    print(f'SUCCESS=false')
    print(f'ERROR={e}')
" "$STATE_FILE_V3" 2>/dev/null)

        # Parse output
        if echo "$V3_OUTPUT" | grep -q "SUCCESS=true"; then
            V3_CHANNEL=$(echo "$V3_OUTPUT" | grep "^CHANNEL=" | cut -d= -f2-)
            V3_ERAS=$(echo "$V3_OUTPUT" | grep "^ERAS=" | cut -d= -f2-)
            V3_NEXT=$(echo "$V3_OUTPUT" | grep "^NEXT=" | cut -d= -f2-)
            V3_CMD=$(echo "$V3_OUTPUT" | grep "^CMD=" | cut -d= -f2-)
            V3_HIST_VERSION=$(echo "$V3_OUTPUT" | grep "^HIST_VERSION=" | cut -d= -f2-)
            V3_PATHS_INFO=$(echo "$V3_OUTPUT" | grep "^PATHS_INFO=" | cut -d= -f2-)

            # Inject V3 workflow state with paths (V3.1 format)
            echo ""
            echo "<workflow_state>"
            echo "Channel: $V3_CHANNEL | $V3_ERAS"
            if [[ -n "$V3_HIST_VERSION" ]]; then
                echo "Hist version: $V3_HIST_VERSION"
            fi
            echo "Next: $V3_NEXT"
            echo "Cmd: $V3_CMD"
            # Inject paths block if available
            if [[ -n "$V3_PATHS_INFO" ]]; then
                echo "$V3_PATHS_INFO"
            fi
            echo ""
            echo ">>> IMPORTANT: Read .workflow/state.json for all era paths <<<"
            echo "</workflow_state>"

            # Detect stage-specific keywords and suggest registered skill
            prompt_lower=$(echo "$USER_PROMPT" | tr '[:upper:]' '[:lower:]')
            STAGE_SKILL=""
            # Stage 1: OS, object selection, NanoAOD processing
            if [[ "$prompt_lower" =~ (stage.?1|objectselection|object.?selection|skimmed|nanoaod) ]] || [[ "$prompt_lower" =~ (^|[[:space:]])os([[:space:]]|$|[,\.]) ]]; then
                STAGE_SKILL="workflow-stage1-os"
            # Stage 2: MV, make variables, BDT, fake backgrounds
            elif [[ "$prompt_lower" =~ (stage.?2|makevariables|make.?variables|fr_weight|fake.?rate|fake.?tau|fake.?lepton) ]] || [[ "$prompt_lower" =~ (^|[[:space:]])mv([[:space:]]|$|[,\.]) ]]; then
                STAGE_SKILL="workflow-stage2-mv"
            # Stage 3: WH, write histograms
            elif [[ "$prompt_lower" =~ (stage.?3|writehist|write.?hist) ]] || [[ "$prompt_lower" =~ (^|[[:space:]])wh([[:space:]]|$|[,\.]) ]]; then
                STAGE_SKILL="workflow-stage3-wh"
            # Stage 4: combine, datacard, template, plotting
            elif [[ "$prompt_lower" =~ (stage.?4|combine|datacard|template|pl\.py|addjes|addtemplate) ]] || [[ "$prompt_lower" =~ (^|[[:space:]])pl([[:space:]]|$|[,\.]) ]]; then
                STAGE_SKILL="workflow-stage4-combine"
            fi

            if [[ -n "$STAGE_SKILL" ]]; then
                SKILL_FILE="$PROJECT_ROOT/.claude/skills/$STAGE_SKILL/SKILL.md"
                if [[ -f "$SKILL_FILE" ]]; then
                    echo ""
                    echo "<skill name=\"$STAGE_SKILL\">"
                    cat "$SKILL_FILE"
                    echo "</skill>"
                    # Create marker file for pre-tool-use hook to check
                    echo "$(date +%s)" > "/tmp/.claude_skill_${STAGE_SKILL}_$USER"
                fi
            fi
            echo ""
            V3_INJECTED=true
        fi
    fi

    # Fall back to V2 state file if V3 not available
    if [[ "$V3_INJECTED" != "true" ]] && [[ -f "$STATE_FILE_V2" ]]; then
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
            CHANNEL=$(python3 -c "import json; print(list(json.load(open('$STATE_FILE_V2')).get('channels', {}).keys())[0] if json.load(open('$STATE_FILE_V2')).get('channels') else '')" 2>/dev/null)
        fi

        if [[ -n "$CHANNEL" ]]; then
            # Python extraction for V2 format
            CURRENT_STAGE=$(python3 -c "import json; d=json.load(open('$STATE_FILE_V2')); print(d.get('channels',{}).get('$CHANNEL',{}).get('current',{}).get('stage','unknown'))" 2>/dev/null)
            CURRENT_ERA=$(python3 -c "import json; d=json.load(open('$STATE_FILE_V2')); print(d.get('channels',{}).get('$CHANNEL',{}).get('current',{}).get('era','unknown'))" 2>/dev/null)
            CURRENT_STATUS=$(python3 -c "import json; d=json.load(open('$STATE_FILE_V2')); print(d.get('channels',{}).get('$CHANNEL',{}).get('current',{}).get('status','unknown'))" 2>/dev/null)
            CURRENT_OP=$(python3 -c "import json; d=json.load(open('$STATE_FILE_V2')); print(d.get('channels',{}).get('$CHANNEL',{}).get('current',{}).get('operation','unknown'))" 2>/dev/null)

            # Inject V2 workflow context
            if [[ "$CURRENT_STAGE" != "unknown" && "$CURRENT_STAGE" != "null" ]]; then
                echo ""
                echo "<workflow_context>"
                echo "Channel: $CHANNEL (V2 state)"
                echo "  Stage: $CURRENT_STAGE | Era: $CURRENT_ERA | Status: $CURRENT_STATUS"
                echo "  Operation: $CURRENT_OP"
                echo "Skill: .claude/skills/workflow/stage${CURRENT_STAGE%%.*}.md"
                echo "</workflow_context>"
                echo ""
                V3_INJECTED=true
            fi
        fi
    fi

    # Show fallback banner only if no state injected
    if [[ "$V3_INJECTED" != "true" ]]; then
        echo ""
        echo "═══════════════════════════════════════════════════════════════════════"
        echo "WORKFLOW SKILL: Detected workflow keywords in prompt"
        echo "═══════════════════════════════════════════════════════════════════════"
        echo ""
        echo "No workflow state found. Initialize with:"
        echo "  python3 plotting/workflow_state_v3.py --init --channel 1tau1l \\"
        echo "    --config config/analysis_config_1tau1l_TTBBtest.yaml --eras 2017"
        echo ""
        echo "Or use workflow skill: .claude/skills/workflow/"
        echo "═══════════════════════════════════════════════════════════════════════"
        echo ""
    fi
fi

exit 0
