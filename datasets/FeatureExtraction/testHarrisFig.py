from skimage import io, feature, transform
from skimage.color import gray2rgb
import numpy as np
import os
import glob

def compute_harris(image_path, sigma, k, threshold):
    # Read the image
    image = io.imread(image_path, as_gray=True)
    resized_image = transform.resize(image, (128, 256))

    # Normalize the image
    resized_image = (resized_image - np.min(resized_image)) / (np.max(resized_image) - np.min(resized_image))

    # Apply Harris corner detector
    harris = feature.corner_harris(resized_image, method='k', k=k, sigma=sigma)

    # Threshold the Harris response
    harris = harris > threshold

    # Convert boolean array to int array (ones and zeros)
    harris = harris.astype(np.uint8) * 255

    # Convert grayscale image to RGB by duplicating the grayscale channel three times
    harris = np.stack((harris, harris, harris), axis=-1)

    # Save the results, be careful with gamma correction
    base_name = os.path.basename(image_path).split('.')[0]
    io.imsave(base_name + '_expected_harris.ppm', harris, check_contrast=False)

if __name__ == '__main__':
    # Get all .png files in the current directory
    png_files = glob.glob('./*.png')

    for png_file in png_files:
        compute_harris(png_file, sigma=1.0, k=0.04, threshold=0.01)
