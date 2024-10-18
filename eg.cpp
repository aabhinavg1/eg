import os
import re

def rename_files_in_folder(folder_path):
    # Check if the folder exists
    if not os.path.isdir(folder_path):
        print(f"Error: '{folder_path}' does not exist.")
        return

    # Iterate over all files in the folder
    for filename in os.listdir(folder_path):
        # Construct the full path to the file
        full_path = os.path.join(folder_path, filename)

        # Check if it's a file (not a folder)
        if os.path.isfile(full_path):
            # Use regex to match everything starting from 'Compiler'
            match = re.search(r'Compiler.*', filename)
            if match:
                new_filename = match.group(0)
                new_full_path = os.path.join(folder_path, new_filename)

                # Rename the file
                os.rename(full_path, new_full_path)
                print(f"Renamed '{filename}' to '{new_filename}'")
            else:
                print(f"No 'Compiler' found in '{filename}'")

# Example usage
folder_path = "./test_folder"  # Replace with your folder path
rename_files_in_folder(folder_path)
