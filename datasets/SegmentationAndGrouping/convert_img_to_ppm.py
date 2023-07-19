import os
from PIL import Image

def convert_img_to_ppm(image_name):
    img = Image.open(image_name)
    img = img.resize((256, 128))
    if img.mode != 'L':
        img = img.convert('L')
    # Expand grayscale to RGB (actually, it will still be a grayscale image, but in RGB format)
    img = img.convert('RGB')
    img.save(image_name[:-4] + '.ppm')

if __name__ == '__main__':
    # list png files, and convert them into ppm files
    # image_names = os.listdir('./')
    # for image_name in image_names:
    #     if image_name[-4:] == '.png':
    #         convert_img_to_ppm(image_name)
    convert_img_to_ppm("coins.png")