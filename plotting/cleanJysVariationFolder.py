import os
import shutil
import zipfile

def zip_and_remove_directory(directory_path):
    """
    Compress a directory and then remove it.
    """
    # Ensure the path is a directory
    if not os.path.isdir(directory_path):
        print(f"{directory_path} is not a valid directory.")
        return

    # Create the zip file path by appending '.zip' to the directory path
    zip_file_path = f"{directory_path}.zip"

    # Create a zip archive of the directory
    with zipfile.ZipFile(zip_file_path, 'w', zipfile.ZIP_DEFLATED) as zipf:
        for root, _, files in os.walk(directory_path):
            for file in files:
                file_path = os.path.join(root, file)
                # Add file to the zip file, maintaining directory structure
                arcname = os.path.relpath(file_path, start=directory_path)
                zipf.write(file_path, arcname)
    
    # Remove the original directory
    shutil.rmtree(directory_path)
    print(f"Zipped and removed directory: {directory_path}")

def find_and_process_directories(base_path):
    """
    Find and process all 'log' and 'jobSH' directories.
    """
    for root, dirs, _ in os.walk(base_path):
        for dir_name in dirs:
            if dir_name in ['log', 'jobSH']:
                dir_path = os.path.join(root, dir_name)
                zip_and_remove_directory(dir_path)

if __name__ == '__main__':
    # Define the base directory to search in
    base_dir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/'
    # idir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_JESup_RelativePtHF_AK4PFchs_v94LepPreJetVetoHemOnly_JESPt22' 

    keywords = ['v1baselineHadroBtagWeightAdded_JESup', 'v1baselineHadroBtagWeightAdded_JESdown']
    matched_dirs = []
    for item in os.listdir(base_dir):
        item_path = os.path.join(base_dir, item)
        # Check if the item is a directory and contains any of the keywords
        if os.path.isdir(item_path) and any(keyword in item for keyword in keywords):
            matched_dirs.append(item_path)

    
    # Process the directories
    for idir in matched_dirs:
        print(f"Processing directory: {idir}")
        # Call the function to find and process 'log' and 'jobSH' directories
        find_and_process_directories(idir)