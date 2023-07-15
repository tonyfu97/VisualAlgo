from skimage import io, transform, feature, img_as_ubyte
import numpy as np
import os
import glob

def normalize(image):
    return (image - np.min(image)) / (np.max(image) - np.min(image))

def compute_blob(image_path):
    image = io.imread(image_path, as_gray=True)
    resized_image = transform.resize(image, (128, 256))

    # Normalize the image
    resized_image = (resized_image - np.min(resized_image)) / (np.max(resized_image) - np.min(resized_image))

    # Apply LoG and DoG blob detection
    blobs_log = feature.blob_log(resized_image, max_sigma=10, min_sigma=1, num_sigma=3, threshold=0.01, log_scale=True)
    blobs_dog = feature.blob_dog(resized_image, max_sigma=10, min_sigma=1, sigma_ratio=1.6, threshold=0.01)

    # Create blank images for output
    blob_log_img = np.zeros_like(resized_image)
    blob_dog_img = np.zeros_like(resized_image)

    # Mark blob locations
    for blob in blobs_log:
        y, x, r = blob
        blob_log_img[int(y), int(x)] = r
    for blob in blobs_dog:
        y, x, r = blob
        blob_dog_img[int(y), int(x)] = r
        
    # Normalize the images
    blob_log_img = normalize(blob_log_img)
    blob_dog_img = normalize(blob_dog_img)

    # Scale up to full range
    blob_log_img = blob_log_img.astype(np.uint8) * 255
    blob_dog_img = blob_dog_img.astype(np.uint8) * 255

    # Convert grayscale images to RGB
    blob_log_img = np.dstack((blob_log_img, blob_log_img, blob_log_img))
    blob_dog_img = np.dstack((blob_dog_img, blob_dog_img, blob_dog_img))

    # Save the results
    base_name = os.path.basename(image_path).split('.')[0]
    io.imsave(base_name + '_expected_blob_log.ppm', img_as_ubyte(blob_log_img), check_contrast=False)
    io.imsave(base_name + '_expected_blob_dog.ppm', img_as_ubyte(blob_dog_img), check_contrast=False)


if __name__ == '__main__':
    # Get all .png files in the current directory
    png_files = glob.glob('./*.png')

    for png_file in png_files:
        compute_blob(png_file)
