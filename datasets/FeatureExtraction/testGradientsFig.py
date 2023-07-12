from skimage import io, filters, transform
import numpy as np
import os
import glob

def normalize(image):
    return (image - np.min(image)) / (np.max(image) - np.min(image))

def compute_sobel(image_path):
    image = io.imread(image_path, as_gray=True)
    resized_image = transform.resize(image, (128, 256))
    
    # Normalize the image
    resized_image = normalize(resized_image)

    # Apply Sobel filters to compute x and y gradients
    sobel_x = filters.sobel_v(resized_image)
    sobel_y = filters.sobel_h(resized_image)
    
    # Normalize the outputs
    sobel_x = normalize(sobel_x)
    sobel_y = normalize(sobel_y)

    # Convert to uint8
    resized_image = (resized_image * 255).astype(np.uint8)
    sobel_x = (sobel_x * 255).astype(np.uint8)
    sobel_y = (sobel_y * 255).astype(np.uint8)

    # Convert grayscale images to RGB by duplicating the grayscale channel three times
    sobel_x = np.stack((sobel_x, sobel_x, sobel_x), axis=-1)
    sobel_y = np.stack((sobel_y, sobel_y, sobel_y), axis=-1)
    resized_image = np.stack((resized_image, resized_image, resized_image), axis=-1)

    # Save the results, be careful with gamma correction
    base_name = os.path.basename(image_path).split('.')[0]
    io.imsave(base_name + '_resized.ppm', resized_image, check_contrast=False)
    io.imsave(base_name + '_expected_sobel_x.ppm', sobel_x, check_contrast=False)
    io.imsave(base_name + '_expected_sobel_y.ppm', sobel_y, check_contrast=False)


if __name__ == '__main__':
    # Get all .png files in the current directory
    png_files = glob.glob('./*.png')
    
    for png_file in png_files:
        compute_sobel(png_file)
