import os
import shutil
import zipfile

def zip_and_remove_directory(directory_path):
    # Ensure the path is a directory
    if not os.path.isdir(directory_path):
        print(f"{directory_path} is not a valid directory.")
        return

    # Create a zip file with the same name as the directory
    zip_file_path = f"{directory_path}.zip"

    # Create a zip archive
    with zipfile.ZipFile(zip_file_path, 'w', zipfile.ZIP_DEFLATED) as zipf:
        for root, dirs, files in os.walk(directory_path):
            for file in files:
                file_path = os.path.join(root, file)
                # Add file to the zip file
                arcname = os.path.relpath(file_path, start=directory_path)  # Preserve directory structure
                zipf.write(file_path, arcname)

    # Remove the original directory
    shutil.rmtree(direcory_path)
    print(f"Zipped and removed directory: {directory_path}")

if __name__ == '__main__':
    # List your directories here
    
    base = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2016_preVFP/'
    
    directories_to_process = [
        # '/path/to/first/directory',
        # '/path/to/second/directory',
        # '/path/to/another/directory'
        # Add more paths as needed
        # f'{base}v94LepPreJetVetoHemOnly_EleScaleDown',
        # f'{base}v94LepPreJetVetoHemOnly_EleScaleUp',
        'v94HadroPreJetVetoHemOnly_TESdm0Down',
        'v94HadroPreJetVetoHemOnly_TESdm0Up',
        'v94HadroPreJetVetoHemOnly_TESdm1Down',
        'v94HadroPreJetVetoHemOnly_TESdm1Up',
        'v94HadroPreJetVetoHemOnly_TESdm10Down',
        'v94HadroPreJetVetoHemOnly_TESdm11Up',
        'v94HadroPreJetVetoHemOnly_TESdm11Down',
    ]

    for directory in directories_to_process:
        idir = os.path.join(base, directory)
        zip_and_remove_directory(idir)