import os
import glob

def main():

    # dir = '/publicfs/cms/data/TopQuark/nanoAOD/2017/BtagCSV/BTagCSV/'
    # inDir = '/publicfs/cms/data/TopQuark/nanoAOD/2017/data/BTagCSV_2017b/'
    inDir = '/publicfs/cms/data/TopQuark/nanoAOD/2017/data/BTagCSV_2017f/'

    # outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2017/data/'
    changeFileName(inDir)


def changeFileName(directory):
    # Find all files matching the pattern 'tree_*.root'
    files = glob.glob(os.path.join(directory, 'tree_*.root'))

    # Loop through each file and rename it
    for file_path in files:
        # Extract the base name of the file (e.g., 'tree_1.root')
        base_name = os.path.basename(file_path)
        
        # Replace 'tree_' with 'outTree_'
        new_base_name = base_name.replace('tree_', 'outTree_')
        
        # Construct the new file path
        new_file_path = os.path.join(directory, new_base_name)
        
        # Rename the file
        os.rename(file_path, new_file_path)
        
        # Print the old and new file names for confirmation
        print(f'Renamed: {base_name} -> {new_base_name}')


if __name__=='__main__':
    main()