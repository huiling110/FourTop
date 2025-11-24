# MCP Servers Setup & Usage Guide

## 🎯 Installed Servers

You now have two MCP servers configured:

### 1. **Filesystem Server**
- Access to your key directories: `/workfs2`, `/publicfs`, `/hpcfs`
- Safe, read-only operations on your analysis files

### 2. **Memory Server**
- Knowledge graph storage across sessions
- Remember analysis parameters, findings, and configurations

---

## 📁 Filesystem Server Usage

### What It Can Do

The filesystem server provides these tools:
- `mcp__read_file` - Read file contents
- `mcp__read_multiple_files` - Read several files at once
- `mcp__list_directory` - List directory contents
- `mcp__search_files` - Search for files by name/pattern
- `mcp__get_file_info` - Get file metadata (size, modified time, permissions)

### Example Use Cases for Your Analysis

#### 1. Search for ROOT Files Across Multiple Directories
```
"Find all tttt ROOT files in /publicfs/cms/data/ modified in the last week"
```
I would use `mcp__search_files` to quickly locate files without manual navigation.

#### 2. Batch File Reading
```
"Read the first 50 lines of all datacard .txt files in hua/combine/combinationV18/"
```
I would use `mcp__read_multiple_files` to efficiently read multiple datacards at once.

#### 3. Check File Timestamps
```
"Which analysis output files were modified today?"
```
I would use `mcp__get_file_info` or `mcp__search_files` with timestamp filters.

#### 4. Directory Structure Exploration
```
"Show me all subdirectories under /publicfs/cms/data/Run2/"
```
I would use `mcp__list_directory` recursively.

---

## 🧠 Memory Server Usage

### What It Can Do

The memory server provides these tools:
- `mcp__create_entities` - Store facts/information as entities
- `mcp__create_relations` - Link entities with relationships
- `mcp__search_nodes` - Search the knowledge graph
- `mcp__open_nodes` - Retrieve specific stored information
- `mcp__delete_entities` - Remove outdated information
- `mcp__add_observations` - Add notes to existing entities

### Example Use Cases for Your Analysis

#### 1. Remember Analysis Parameters
```
You: "Remember that for V18 analysis, we use 30 BDT bins and enable fake tau data-driven method"

Me: I would store this using mcp__create_entities:
- Entity: "V18_analysis_config"
- Observations: ["30_BDT_bins", "fake_tau_data_driven_enabled"]
```

#### 2. Track What Works
```
You: "The 1tau1l channel with VLL mass 700 GeV gives expected limit r < 0.89"

Me: I would create entities and relations:
- Entity: "VLL_m700_1tau1l"
- Relation: "has_expected_limit" → "0.89"
```

#### 3. Remember File Locations
```
You: "Store that the validated reference output is at /publicfs/.../v94HadroPreJetVetoHemOnly/"

Me: I would create:
- Entity: "reference_output_validated"
- Relation: "located_at" → file path
```

#### 4. Track Bugs and Fixes
```
You: "We fixed the VLL permission bug by creating temp_* directories"

Me: I would store:
- Entity: "VLL_permission_bug"
- Relation: "fixed_by" → "temp_directory_creation"
- Observation: "runCombineAll.py line 61-101"
```

---

## 🚀 How to Activate

**You need to restart Claude Code for MCP servers to load:**

1. Exit this session
2. Restart Claude Code
3. The servers will be loaded automatically
4. You'll see new `mcp__*` tools available

---

## 💡 Practical Workflow Examples

### Scenario 1: Starting a New Analysis Version

**You**: "I'm starting V19 analysis. Find all V18 datacards and remember the parameters I used."

**Claude with MCP**:
1. Uses `mcp__search_files` to find all V18 datacards
2. Uses `mcp__read_multiple_files` to read their parameters
3. Uses `mcp__create_entities` to store V18 config for reference
4. Suggests what to change for V19

### Scenario 2: Debugging Failed Jobs

**You**: "Check all job log files modified in the last hour for errors"

**Claude with MCP**:
1. Uses `mcp__search_files` with timestamp filter
2. Uses `mcp__read_multiple_files` to batch-read logs
3. Uses `mcp__create_entities` to remember which jobs failed
4. Provides summary of error patterns

### Scenario 3: Cross-Session Memory

**Session 1**:
You: "Remember that 2016preVFP uses luminosity 19.5 fb^-1"

**Session 2** (days later):
You: "What luminosity did I use for 2016preVFP?"
Claude: *Retrieves from memory server* "19.5 fb^-1"

---

## 🔧 Configuration Details

### Location
`.claude/mcp.json`

### Configured Directories (Filesystem Server)
- `/workfs2/cms/huahuil` - Your working area
- `/publicfs/cms` - Public CMS data
- `/hpcfs/cms/cmsgpu/huahuil` - GPU cluster files

### Auto-Approved Operations
Both servers have their read operations auto-approved, so I won't ask permission for:
- Reading files
- Searching directories
- Storing/retrieving memories

### Safety
- **Filesystem**: Read-only access, scoped to specific directories
- **Memory**: Isolated knowledge graph, no external access

---

## 📊 Performance Benefits

### Without MCP:
```bash
# To search for files, I'd run:
find /publicfs/cms -name "*.root" -mtime -7
# To read multiple files:
cat file1.txt file2.txt file3.txt
```
**Issues**: Limited by bash output size, can't efficiently filter results

### With MCP:
- **Parallel operations**: Read multiple files simultaneously
- **Smart filtering**: Search with complex patterns
- **Persistent context**: Remember findings across sessions
- **Structured queries**: More precise than regex/grep

---

## 🎓 Learning to Use MCP

Just ask naturally! Examples:

❌ **Don't say**: "Use mcp__search_files to find ROOT files"

✅ **Do say**:
- "Find all tttt samples in the input directory"
- "What datacards exist for the 1tau1l channel?"
- "Remember that this BDT training gave 95% accuracy"
- "What parameters did I use last time for VLL analysis?"

I'll automatically choose the right MCP tools based on your request.

---

## 🐛 Troubleshooting

### MCP Servers Not Loading

**Check**:
```bash
# Test filesystem server manually:
npx -y @modelcontextprotocol/server-filesystem /workfs2/cms/huahuil

# Test memory server manually:
npx -y @modelcontextprotocol/server-memory
```

### Permission Issues

If you see permission errors:
```bash
# Check npm cache:
npm config get cache

# Should be: /hpcfs/cms/cmsgpu/huahuil/.npm-cache
```

### See What's Available

After restarting, ask me:
```
"What MCP tools do you have access to?"
```

---

## 📝 Next Steps

1. **Restart Claude Code** to load the MCP servers
2. **Try a test query**: "Search for all combine log files from today"
3. **Use memory**: "Remember that I prefer 1tau1l channel for testing"
4. **Check it works**: Ask me "What MCP servers are loaded?"

---

## 🔗 Resources

- [MCP Documentation](https://modelcontextprotocol.io)
- [Filesystem Server](https://github.com/modelcontextprotocol/servers/tree/main/src/filesystem)
- [Memory Server](https://github.com/modelcontextprotocol/servers/tree/main/src/memory)

---

*Configuration file: `.claude/mcp.json`*
*Created: 2025-11-13*
