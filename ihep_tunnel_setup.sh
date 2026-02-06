  #!/bin/bash
  # SSH Tunnel Setup for Claude on IHEP

  echo "=== Step 1: Configure proxy to use tunnel ==="
  if [ -z "$PROXY_USER" ] || [ -z "$PROXY_PASS" ]; then
      echo "Error: PROXY_USER and PROXY_PASS environment variables must be set"
      echo "Usage: export PROXY_USER=your_user PROXY_PASS=your_pass && source ihep_tunnel_setup.sh"
      return 1 2>/dev/null || exit 1
  fi
  export http_proxy="http://${PROXY_USER}:${PROXY_PASS}@127.0.0.1:8889"
  export https_proxy="http://${PROXY_USER}:${PROXY_PASS}@127.0.0.1:8889"
  export HTTP_PROXY="http://${PROXY_USER}:${PROXY_PASS}@127.0.0.1:8889"
  export HTTPS_PROXY="http://${PROXY_USER}:${PROXY_PASS}@127.0.0.1:8889"
  echo "✓ Proxy configured for user: $PROXY_USER"

  echo ""
  echo "=== Step 2: Remove IHEP API endpoint ==="
  unset ANTHROPIC_BASE_URL
  unset ANTHROPIC_API_KEY
  echo "✓ IHEP endpoint removed"

  echo ""
  echo "=== Step 3: Test if tunnel works ==="
  curl -x "http://${PROXY_USER}:${PROXY_PASS}@127.0.0.1:8889" https://claude.ai -I --max-time 10

#   echo ""
#   echo "=== Step 4: Check Claude auth status ==="
#   claude auth status

  echo ""
  echo "=== Ready! You can now use: ==="
  echo "claude"