from PIL import Image, ImageEnhance
import numpy as np

def save_image_ppm(image, filename):
    image = image.convert('RGB')
    image.save(filename, 'ppm')

def adjust_brightness(image, factor):
    enhancer = ImageEnhance.Brightness(image)
    return enhancer.enhance(factor)

def adjust_contrast(image, factor):
    enhancer = ImageEnhance.Contrast(image)
    return enhancer.enhance(factor)

if __name__ == "__main__":
    image_name = "lighthouse"
    image = Image.open(f"{image_name}.png")
    image = image.convert("L")
    image = image.resize((256, 128))

    # Make image too dark
    dark_image = adjust_brightness(image, 0.3)
    save_image_ppm(dark_image, f"{image_name}_dark.ppm")

    # Make image too bright
    bright_image = adjust_brightness(image, 1.5)
    save_image_ppm(bright_image, f"{image_name}_bright.ppm")

    # Make contrast too strong
    strong_contrast_image = adjust_contrast(image, 4)
    save_image_ppm(strong_contrast_image, f"{image_name}_strong_contrast.ppm")

    # Make contrast too weak
    weak_contrast_image = adjust_contrast(image, 0.3)
    save_image_ppm(weak_contrast_image, f"{image_name}_weak_contrast.ppm")
