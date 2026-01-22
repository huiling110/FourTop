# Context: Permission Fix

**Created**: 2025-12-11
**Updated**: 2025-12-16
**Status**: RE-OPENED - Testing

---

## Background

Claude Code uses THREE settings files for permissions:
- `~/.claude/settings.json` - **Global** user settings (lowest precedence)
- `.claude/settings.json` - Project-level settings (version controlled)
- `.claude/settings.local.json` - Local overrides (highest precedence, not version controlled)

### Settings Precedence (from Claude Code docs)

1. **Local project** (`.claude/settings.local.json`) - highest
2. **Shared project** (`.claude/settings.json`)
3. **User/Global** (`~/.claude/settings.json`) - lowest

### Merge Behavior (CRITICAL)

- **Deny always wins** - deny rules block regardless of allow rules at any level
- **Arrays REPLACE, not merge** - within a category, higher precedence file wins completely
- Settings changes require Claude session restart

---

## Configuration History

### What Didn't Work (2025-12-15)
- `Bash` in `.claude/settings.local.json` only
- Issue: Still prompted for permission

### Current Attempt (2025-12-16)
- Added `Bash` to **global** `~/.claude/settings.json`
- Added deny rules to global as safety backup
- Rationale: Global worked before; project-level wasn't respected

---

## Current Configuration

### Global (`~/.claude/settings.json`)
```json
{
  "permissions": {
    "allow": ["Bash", "WebSearch"],
    "deny": [
      "Bash(rm -rf /)", "Bash(rm -rf ~)", "Bash(rm -rf .)",
      "Bash(sudo :*)", "Bash(mkfs:*)", "Bash(dd if=:*)", "Bash(dd of=:*)",
      "Bash(shutdown:*)", "Bash(reboot:*)",
      "Bash(git push --force:*)", "Bash(git push -f:*)", "Bash(git reset --hard HEAD~:*)"
    ]
  }
}
```

### Project (`.claude/settings.json`)
- Contains full deny list with more patterns
- Does NOT include `Bash` in allow (users opt-in)

### Local (`.claude/settings.local.json`)
- Contains `Bash` in allow
- Duplicates deny rules and hooks

---

## Three Layers of Protection

1. **Global deny rules** - in `~/.claude/settings.json`
2. **Project deny rules** - in `.claude/settings.json` and `.claude/settings.local.json`
3. **PreToolUse hook** - substring matching for compound commands (catches `&&`, loops, etc.)

---

## Dangerous Commands Blocked

### Via Settings (Prefix Match)
| Pattern | Risk |
|---------|------|
| `rm -rf /`, `rm -rf .` | Delete root/cwd |
| `sudo :*` | Privilege escalation |
| `mkfs:*`, `dd if=:*`, `dd of=:*` | Disk operations |
| `shutdown:*`, `reboot:*`, `halt:*` | System shutdown |
| `chmod -R 000:*`, `chmod -R 777:*` | Dangerous permissions |
| `git push --force:*`, `git reset --hard HEAD~:*` | Git destructive ops |

### Via Hook (Substring Match)
The `pre-tool-use.sh` hook blocks patterns with substring matching:
- `echo test && sudo rm -rf /` (compound commands)
- `for i in 1 2 3; do sudo $cmd; done` (loops)

---

## Key Learnings

1. **Deny rule syntax**: Use `:*` for prefix matching, not `*`
2. **Settings replacement**: Higher precedence files REPLACE, not merge
3. **Deny always wins**: Across all files, deny rules take precedence
4. **Hook input**: Hooks receive JSON via stdin, parse with `jq`
5. **Session restart**: Settings changes require Claude session restart
6. **Wildcard limitations**:
   - Only prefix matching supported (`:*` at the end)
   - Wildcards in the middle of commands NOT supported
7. **Global vs Local**: Global settings may be required for Bash permission to work

---

## Key Files

| File | Purpose |
|------|---------|
| `~/.claude/settings.json` | Global user settings |
| `.claude/settings.json` | Project settings (git tracked) |
| `.claude/settings.local.json` | Local overrides (not tracked) |
| `.claude/hooks/pre-tool-use.sh` | Safety hook for compound commands |

---

**Last Updated**: 2025-12-16
