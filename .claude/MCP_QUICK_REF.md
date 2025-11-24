# MCP Quick Reference Card

## 🚀 Setup Complete!

**Status**: ✅ Filesystem & Memory servers configured
**Config**: `.claude/mcp.json`
**Guide**: See `MCP_SETUP_GUIDE.md` for full documentation

---

## 🔄 To Activate

**IMPORTANT**: Restart Claude Code to load the MCP servers

---

## 💬 How to Use (Just Ask Naturally!)

### Filesystem Operations

| What You Want | Example Request |
|---------------|-----------------|
| Find files | *"Find all tttt ROOT files modified today"* |
| Read multiple files | *"Read all datacards in combinationV18/"* |
| Check file info | *"When was the last analysis output created?"* |
| List directories | *"Show me what's in /publicfs/cms/data/"* |

### Memory Operations

| What You Want | Example Request |
|---------------|-----------------|
| Store info | *"Remember that V18 uses 30 BDT bins"* |
| Retrieve info | *"What parameters did I use for V18?"* |
| Track results | *"Store that VLL m700 gives r < 0.89"* |
| Remember locations | *"Save the path to validated reference output"* |

---

## 📁 Configured Directories

- `/workfs2/cms/huahuil` - Your working area
- `/publicfs/cms` - Public CMS data
- `/hpcfs/cms/cmsgpu/huahuil` - GPU cluster files

---

## ✅ Test After Restart

Ask me:
1. *"What MCP servers are loaded?"*
2. *"Find combine log files from today"*
3. *"Remember that I'm working on the addVLL branch"*

---

## 🔧 Troubleshooting

If MCP doesn't load:
```bash
# Test manually
npx -y @modelcontextprotocol/server-filesystem /workfs2
npx -y @modelcontextprotocol/server-memory
```

---

**Full Documentation**: [MCP_SETUP_GUIDE.md](MCP_SETUP_GUIDE.md)
