from skimage import io, filters, transform
import numpy as np
import os
import glob

SIGMA = 3.0

def normalize(image):
    return (image - np.min(image)) / (np.max(image) - np.min(image))

def apply_gaussian_filter(image_path, sigma):
    image = io.imread(image_path, as_gray=True)
    resized_image = transform.resize(image, (128, 256))

    # Normalize the image
    resized_image = normalize(resized_image)

    # Apply Gaussian filter
    gaussian_image = filters.gaussian(resized_image, sigma=sigma)

    # Normalize the output
    gaussian_image = normalize(gaussian_image)

    # Convert to uint8
    gaussian_image = (gaussian_image * 255).astype(np.uint8)

    # Convert grayscale image to RGB by duplicating the grayscale channel three times
    gaussian_image = np.stack((gaussian_image, gaussian_image, gaussian_image), axis=-1)

    # Save the result
    base_name = os.path.basename(image_path).split('.')[0]
    io.imsave(base_name + '_expected_gaussian.ppm', gaussian_image, check_contrast=False)


if __name__ == '__main__':
    # Get all .png files in the current directory
    png_files = glob.glob('./*.png')

    for png_file in png_files:
        apply_gaussian_filter(png_file, sigma=SIGMA)
