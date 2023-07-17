from skimage import io, transform
from scipy import ndimage
import numpy as np
import os
import glob

def normalize(image):
    return (image - np.min(image)) / (np.max(image) - np.min(image))

def make_rgb(normalized_image):
    one_channel = (normalized_image * 255).astype(np.uint8)
    return np.stack((one_channel, one_channel, one_channel), axis=-1)

def save_interpolated_images(image_path, scale_factor):
    image = io.imread(image_path, as_gray=True)
    image = transform.resize(image, (128, 256))
    
    # Normalize the image
    image = normalize(image)

    # Nearest neighbor interpolation
    resized_nearest = ndimage.zoom(image, scale_factor, order=0, prefilter=False, mode='nearest')
    resized_nearest = normalize(resized_nearest)
    resized_nearest = make_rgb(resized_nearest)
    base_name = os.path.basename(image_path).split('.')[0]
    io.imsave(f"{base_name}_expected_nearest_{scale_factor:.1f}.ppm", resized_nearest, check_contrast=False)
    
    # Bilinear interpolation
    resized_bilinear = ndimage.zoom(image, scale_factor, order=1, prefilter=False, mode='nearest')
    resized_bilinear = normalize(resized_bilinear)
    resized_bilinear = make_rgb(resized_bilinear)
    base_name = os.path.basename(image_path).split('.')[0]
    io.imsave(f"{base_name}_expected_bilinear_{scale_factor:.1f}.ppm", resized_bilinear, check_contrast=False)
    
    # Bicubic interpolation
    resized_bicubic = ndimage.zoom(image, scale_factor, order=3, prefilter=False, mode='nearest')
    resized_bicubic = normalize(resized_bicubic)
    resized_bicubic = make_rgb(resized_bicubic)
    base_name = os.path.basename(image_path).split('.')[0]
    io.imsave(f"{base_name}_expected_bicubic_{scale_factor:.1f}.ppm", resized_bicubic, check_contrast=False)

if __name__ == '__main__':
    # Get all .png files in the current directory
    png_files = glob.glob('./*.png')
    print(png_files)

    scale_factor = 0.5  # try 0.5 and 2.0
    for png_file in png_files:
        save_interpolated_images(png_file, scale_factor)
