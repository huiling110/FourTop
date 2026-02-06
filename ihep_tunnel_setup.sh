  #!/bin/bash
  # SSH Tunnel Setup for Claude on IHEP

  echo "=== Step 1: Configure proxy to use tunnel ==="
  export http_proxy="http://hua:123456@127.0.0.1:8889"
  export https_proxy="http://hua:123456@127.0.0.1:8889"
  export HTTP_PROXY="http://hua:123456@127.0.0.1:8889"
  export HTTPS_PROXY="http://hua:123456@127.0.0.1:8889"
  echo "✓ Proxy configured"

  echo ""
  echo "=== Step 2: Remove IHEP API endpoint ==="
  unset ANTHROPIC_BASE_URL
  unset ANTHROPIC_API_KEY
  echo "✓ IHEP endpoint removed"

  echo ""
  echo "=== Step 3: Test if tunnel works ==="
  curl -x http://hua:123456@127.0.0.1:8889 https://claude.ai -I --max-time 10

#   echo ""
#   echo "=== Step 4: Check Claude auth status ==="
#   claude auth status

  echo ""
  echo "=== Ready! You can now use: ==="
  echo "claude"