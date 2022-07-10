import os


def checkMakeDir( folder ):
    if not os.path.exists( folder ):
        os.mkdir( folder )