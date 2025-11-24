import os
import requests

def download_folder(repo_url, folder_path, local_dir):
    # Construct the GitHub API URL
    repo_api_url = repo_url.replace("github.com", "api.github.com/repos")
    folder_api_url = f"{repo_api_url}/contents/{folder_path}?ref=3056a92be7fc4159efc7cf49568d8594676ae9ca"

    # Get the folder contents from the GitHub API
    response = requests.get(folder_api_url)
    response.raise_for_status()
    folder_contents = response.json()

    # Create the local directory if it doesn't exist
    os.makedirs(local_dir, exist_ok=True)

    # Download each file in the folder
    for item in folder_contents:
        if item['type'] == 'file':
            file_url = item['download_url']
            file_path = os.path.join(local_dir, item['name'])
            print(f"Downloading {file_url} to {file_path}")
            file_response = requests.get(file_url)
            file_response.raise_for_status()
            with open(file_path, 'wb') as file:
                file.write(file_response.content)

# Example usage
repo_url = "https://github.com/NielsVdBossche/ewkino"
folder_path = "_FourTopAnalysis/DatadrivenInput/nonprompt"
# local_dir = "nonprompt"
local_dir = "/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/inputFiles/FR_fromSS"
download_folder(repo_url, folder_path, local_dir)
