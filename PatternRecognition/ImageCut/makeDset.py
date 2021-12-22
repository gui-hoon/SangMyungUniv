
from PIL import Image

import argparse
import PIL
import os


if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='SMU-pattern recognition making dataset')

    parser.add_argument("--name", required=True, help="name in English")
    parser.add_argument("--id", required=True, help="student ID (학번)")
    parser.add_argument("--ext", required=True, help="jpg or jpeg or png etc..")

    FLAGS, FIRE_FLAGS = parser.parse_known_args()

    ext = FLAGS.ext
    name = FLAGS.name
    studentID = FLAGS.id

    charset = "abcdefghijklmnopqrstuvwxyz"
    charList = list(charset)

    dsetPath = f"{name}-{studentID}"

    if not os.path.isdir(dsetPath):
        os.mkdir(dsetPath)
        for c in charList:
            if not os.path.isdir(os.path.join(dsetPath, c)):
                os.mkdir(os.path.join(dsetPath, c))

    for c in charList:
        img = Image.open(os.path.join("dset",c + "." + ext))

        # empirically set values, do not touch =================
        nGrid = 28
        marginPix = (img.size[0] / 28) / 2
        gridWidth = (img.size[0] / 28)
        fontWidth, fontHegith = 3 * gridWidth, 3 * gridWidth
        # ======================================================

        croppedImg = img.crop((marginPix, marginPix, img.size[0] - marginPix, img.size[1] - marginPix))

        iter = 0
        x, y = 0, 0
        for i in range(6):
            for j in range(9):
                croppedImg\
                    .crop((x, y, x + fontWidth, y + fontHegith))\
                    .resize((28, 28), PIL.Image.LANCZOS)\
                    .save(os.path.join(dsetPath, c, c + f"{iter}-{studentID}.png"))
                x += fontWidth
                iter += 1
            y += fontHegith
            x = 0

        print(f"{c} Done.")
