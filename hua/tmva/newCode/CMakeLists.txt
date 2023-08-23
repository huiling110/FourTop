cmake_minimum_required(VERSION 3.12)  # Minimum CMake version required

project(tmvaBDT_training)  # Replace with your project name

# Locate and configure ROOT
find_package(ROOT REQUIRED)
# find_package(TMVA REQUIRED)

# Create an executable target
add_executable(YourExecutableName tmvaBDT_training.C)  # Replace with your desired executable name

# Link the ROOT libraries
target_link_libraries(YourExecutableName ROOT::Core)
target_link_libraries(YourExecutableName TMVA)

# Optional: Set C++ standard
set_target_properties(YourExecutableName PROPERTIES CXX_STANDARD 14)  # Adjust to your desired C++ standard
