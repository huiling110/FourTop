#!/bin/bash
export PATH=/cvmfs/container.ihep.ac.cn/bin:$PATH
# alias hep7='hep_container shell CentOS7'
# hep_container shell CentOS7 

# hep_container shell CentOS7 && /bin/bash -c "
#   source /cvmfs/cms.cern.ch/cmsset_default.sh
#   cmsenv
# "

# hep_container shell CentOS7 bash << 'EOF'
# source /cvmfs/cms.cern.ch/cmsset_default.sh
# cmsenv
# echo "Sourcing CMS default setup script."
# EOF


# Create a temporary script
cat << 'EOL' > temp_script.sh
#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsenv
# Other necessary commands
EOL

# Launch new shell and execute the script within it
hep_container shell CentOS7 /bin/bash temp_script.sh

# Clean up
rm temp_script.sh





