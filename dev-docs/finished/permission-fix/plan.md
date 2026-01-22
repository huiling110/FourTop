# Plan: Fix Command Permission Prompting Issue

**Created**: 2025-12-11
**Status**: 🔄 RE-OPENED - Testing new approach

---

## Problem Statement

Claude Code prompts for permission on basic commands despite having `Bash` in project allow list.

---

## Root Causes Found

1. **settings.local.json override**: When `settings.local.json` has `permissions.allow`, it REPLACES `settings.json`'s allow list entirely
2. **Invalid deny rule syntax**: Rules like `Bash(sudo *)` don't work - must use `Bash(sudo :*)` for prefix matching
3. **NEW (2025-12-16)**: Global settings (`~/.claude/settings.json`) may not merge properly with project settings for Bash permission

---

## Solution History

### Attempt 1 (2025-12-15): Local Settings Only
- Added `Bash` to `.claude/settings.local.json`
- Fixed deny rule syntax (`:*` for prefix matching)
- **Result**: Did NOT work - still prompting

### Attempt 2 (2025-12-16): Global Settings with Deny Rules
- Added `Bash` to global `~/.claude/settings.json`
- Added critical deny rules to global settings as safety backup
- **Result**: PENDING - needs restart to test

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

### Three Layers of Protection
1. **Global deny rules** - in `~/.claude/settings.json`
2. **Project deny rules** - in `.claude/settings.json` and `.claude/settings.local.json`
3. **PreToolUse hook** - substring matching for compound commands

---

## Success Criteria

- [ ] Basic commands run without prompts
- [ ] Loop constructs run without prompts
- [x] Deny rules use correct `:*` syntax
- [x] Multiple safety layers in place

---

**Last Updated**: 2025-12-16
