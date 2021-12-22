from PIL import Image

alphabet = "abcdefghijklmnopqrstuvwxyz"
alphabetList = list(alphabet)

for alpha in alphabetList:
    raw_path = f"C:\\Users\\mooja\\Google Drive\\alphabet\\{alpha}.png"
    save_path = f"C:\\Users\\mooja\\Google Drive\\data\\{alpha}\\"

    img = Image.open(raw_path)
    count = 0
    for j in range(6):
        for i in range(9):
            box = (i*196, j*196, (i+1)*196, (j+1)*196)
            region = img.crop(box)
            # region.show()
            region = region.resize((28, 28), Image.BICUBIC).convert('L').save(save_path + f"{alpha}({count}).png")
            count+=1

