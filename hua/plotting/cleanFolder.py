
import os
import time
import shutil

def delete_folders(directory, threshold_time):
    deleteList = []
    for entry in os.listdir(directory):
        entry_path = os.path.join(directory, entry)
        # print(entry_path)
        time = os.path.getmtime(entry_path)
        # print(time)
        if time < threshold_time:
            print(f"Deleting folder: {entry}")
            remove_directory(entry_path)
             
            deleteList.append(entry)
    print('delete: ', deleteList)
       
def remove_directory(directory):
    confirm = input(f"Are you sure you want to delete '{directory}'? (y/n): ")
    if confirm.lower() == "y":
        shutil.rmtree(directory)
        print(f"Directory '{directory}' has been deleted.")
    else:
        print("Deletion canceled.")
  
   
        

# Specify the directory and threshold time in seconds
# directory_path = "/path/to/directory"
directory_path = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP'
threshold_time = time.time() - (200 * 24 * 60 * 60)  # Delete folders older than 7 days

delete_folders(directory_path, threshold_time)
