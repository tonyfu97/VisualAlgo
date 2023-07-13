from skimage import io, filters, transform, feature
import numpy as np
import os
import glob

def compute_canny(image_path):
    image = io.imread(image_path, as_gray=True)
    resized_image = transform.resize(image, (128, 256))

    # Normalize the image
    resized_image = (resized_image - np.min(resized_image)) / (np.max(resized_image) - np.min(resized_image))

    # Apply Canny edge detection to compute edge non-maximum suppression image
    canny = feature.canny(resized_image)

    # Convert boolean array to int array (ones and zeros)
    canny = canny.astype(np.uint8) * 255

    # Convert grayscale image to RGB by duplicating the grayscale channel three times
    canny = np.stack((canny, canny, canny), axis=-1)

    # Save the results, be careful with gamma correction
    base_name = os.path.basename(image_path).split('.')[0]
    io.imsave(base_name + '_expected_canny.ppm', canny, check_contrast=False)

if __name__ == '__main__':
    # Get all .png files in the current directory
    png_files = glob.glob('./*.png')

    for png_file in png_files:
        compute_canny(png_file)
