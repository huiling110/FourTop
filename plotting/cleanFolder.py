
import os
import time
import shutil
from datetime import datetime, timedelta

def main():
    # Specify the directory and threshold time in seconds
    # directory_path = "/path/to/directory"
    # directory_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/'
    # directory_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/'
    directory_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/'
    # directory_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/'
    # directory_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/'
    # directory_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/'
    # removeOlderDays = 60
    # removeOlderDays = 40
    removeOlderDays = 20
    # ifDryRun = True
    ifDryRun = False #!!!careful setting this!!!
    
    
    # delete_folders(directory_path, threshold_time, ifDryRun)
    delete_folders(directory_path, removeOlderDays, ifDryRun)


# def delete_folders(directory, threshold_time, ifDryRun = True):
def delete_folders(directory, oldDays, ifDryRun = True):
    deleteList = []
    for entry in os.listdir(directory):
        entry_path = os.path.join(directory, entry)
        cutoff_date = datetime.now() - timedelta(days=oldDays)
        modification_time = datetime.fromtimestamp(os.path.getmtime(entry_path))
        if modification_time < cutoff_date:
            print(f"Deleting folder: {entry}\n")
            delete_files_with_extension(entry_path, '.root', ifDryRun)
            deleteList.append(entry)
    print('delete list: ')
    for i in deleteList:
        print(i)
    print('done deleting')
    
def delete_files_with_extension(folder_path, extension, ifDryRun=True):
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            if file.endswith(extension):
                file_path = os.path.join(root, file)
                if 'results'  in file_path: continue
                if 'variableHists' in file_path : continue#variableHists
                if 'template' in file : continue
                print('going to remove: ', file_path)
                if not ifDryRun:
                    os.remove(file_path)
                    print('really removed!!!')

       
def remove_directory(directory):
    confirm = input(f"Are you sure you want to delete '{directory}'? (y/n): ")
    if confirm.lower() == "y":
        shutil.rmtree(directory)
        print(f"Directory '{directory}' has been deleted.")
    else:
        print("Deletion canceled.")
 
 
if __name__=='__main__':
    main()
     
   
        

