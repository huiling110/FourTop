
import os
import time
import shutil
from datetime import datetime, timedelta

def main():
    # Specify the directory and threshold time in seconds
    # directory_path = "/path/to/directory"
    # directory_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/'
    directory_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/'
    # directory_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/'
    # directory_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/'
    # directory_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/'
    # directory_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/'
    # removeOlderDays = 60
    # removeOlderDays = 40
    removeOlderDays = 20
    ifDryRun = True
    # ifDryRun = False #!!!careful setting this!!!
    
    # subDirsToClean = ['v0baselineHardro_v80addTauJetVar']
    versionsToClean = ['v75', 'v76', 'v77', 'v78', 'v79', 'v80']
    subDirsToClean = getSubDirsToClean(versionsToClean, directory_path) 
    for idir in subDirsToClean:
        print('cleaning: ', idir)
        directory_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/' + idir
        # print('cleaning: ', directory_path)
        deleteFiles( directory_path, ifDryRun)
    
    
    # delete_folders(directory_path, threshold_time, ifDryRun)
    # delete_folders(directory_path, removeOlderDays, ifDryRun)
    
def getSubDirsToClean(versionsToClean, baseDir):
    subDirsToClean = []
    for idir in os.listdir(baseDir):
        for iversion in versionsToClean:
            if iversion in idir: 
                subDirsToClean.append(idir) 
    return subDirsToClean

def deleteFiles(directory, ifDryRun = True):
     for root, dirs, files in os.walk(directory, topdown=False):
        for file_name in files:
            # # Construct full path
            file_path = os.path.join(root, file_name)
            # print('file_path: ', file_path)
            if 'results'  in file_path: continue
            if 'dataset/weight' in file_path: continue
            print('going to remove: ', file_path)
            if not ifDryRun:
                os.remove(file_path)
                print(' really removed!!!')  

    


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
     
   
        

