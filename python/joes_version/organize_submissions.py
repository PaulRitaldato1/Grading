from pathlib import Path
import shutil
import re
import utils

config = None
submission_regex = "^(?P<name>[^_]+)_(?:late_)?(?P<canvas_id>[\d]+)_(?P<ufid>[\d]{8})?_?(?P<filename>.+?(?=-\d+|\.|\n|\Z))(?:-\d+)?\.?(?P<extension>[\w\d]+)?$"

def extract_submissions():
    shutil.unpack_archive(config['submissions_archive'], config['submissions_folder'])

def organize_submissions():
    submission_folder = Path(config['submissions_folder'])
    regex = re.compile(submission_regex)
    # iterate over each submitted file
    for filepath in submission_folder.iterdir():
        # ignore any directories, in case they exist
        if(filepath.is_dir()):
            continue

        result = regex.match(filepath.name)
        name = result.group('name')
        filename = result.group('filename')
        extension = result.group('extension')

        # make the student's directory if it doesn't exist
        destination = submission_folder.joinpath(name)
        destination.mkdir(exist_ok=True)
        # if the file is a zip for some reason, unzip ip into their folder
        # and delete the zip
        if(extension.lower() == 'zip'):
            shutil.unpack_archive(filepath, destination, 'zip')
            filepath.unlink()
        #otherwise, move the file to the student's folder
        else:
            shutil.move(filepath, destination.joinpath(filename + "." + extension))

if __name__ == "__main__":
    config = utils.read_config_file("config.json")
    extract_submissions()
    organize_submissions()