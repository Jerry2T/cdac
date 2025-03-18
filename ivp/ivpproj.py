import streamlit as st
import cv2
import numpy as np
from PIL import Image
import io

def rgb_to_grey(rgb_image):
    return cv2.cvtColor(rgb_image, cv2.COLOR_BGR2GRAY)

def grey_to_binary(grey_image, threshold):
    _, binary_image = cv2.threshold(grey_image, threshold, 255, cv2.THRESH_BINARY)
    return binary_image

def negation(image):
    return cv2.bitwise_not(image)

def darken(grey_image, factor):
    return np.clip(grey_image - factor, 0, 255).astype(np.uint8)

def brighten(grey_image, factor):
    return np.clip(grey_image + factor, 0, 255).astype(np.uint8)

def adjust_contrast(image, alpha):
    return np.clip(alpha * image, 0, 255).astype(np.uint8)

def apply_filter(image, filter_type, kernel_size):
    if filter_type == "Average Filter":
        return cv2.blur(image, (kernel_size, kernel_size))
    elif filter_type == "Median Filter":
        return cv2.medianBlur(image, kernel_size)
    elif filter_type == "Gaussian Filter":
        return cv2.GaussianBlur(image, (kernel_size, kernel_size), 0)
    elif filter_type == "Bilateral Filter":
        return cv2.bilateralFilter(image, kernel_size, 75, 75)
    elif filter_type == "Laplacian Edge Detection":
        laplacian = cv2.Laplacian(image, cv2.CV_64F)
        return np.clip(np.abs(laplacian), 0, 255).astype(np.uint8)
    return image

def segment_image(image, method):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    if method == "Otsu's Thresholding":
        _, segmented = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    elif method == "Adaptive Thresholding":
        segmented = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 2)
    elif method == "Canny Edge Detection":
        segmented = cv2.Canny(gray, 100, 200)
    return segmented

def detect_objects(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    edges = cv2.Canny(gray, 50, 150)
    contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    result = image.copy()
    cv2.drawContours(result, contours, -1, (0, 255, 0), 2)
    return result

st.title("Image Processing Web App")
uploaded_file = st.file_uploader("Upload an image", type=["png", "jpg", "jpeg"])

if uploaded_file is not None:
    image = Image.open(uploaded_file)
    image = np.array(image)
    st.image(image, caption='Uploaded Image', use_container_width=True)
    
    option = st.selectbox("Select an operation", 
                         ["RGB to Grayscale", "Grayscale to Binary", "Negation", "Darken", "Brighten", "Adjust Contrast", "Apply Filter", "Image Segmentation", "Object Detection"])
    processed_image = None
    
    if option == "RGB to Grayscale":
        processed_image = rgb_to_grey(image)
    elif option == "Grayscale to Binary":
        threshold = st.slider("Select threshold", 0, 255, 127)
        processed_image = grey_to_binary(rgb_to_grey(image), threshold)
    elif option == "Negation":
        processed_image = negation(image)
    elif option == "Darken":
        factor = st.slider("Select darkening factor", 0, 100, 50)
        processed_image = darken(rgb_to_grey(image), factor)
    elif option == "Brighten":
        factor = st.slider("Select brightening factor", 0, 100, 50)
        processed_image = brighten(rgb_to_grey(image), factor)
    elif option == "Adjust Contrast":
        alpha = st.slider("Select contrast factor", 0.5, 3.0, 1.0)
        processed_image = adjust_contrast(image, alpha)
    elif option == "Apply Filter":
        filter_type = st.selectbox("Choose a filter", ["Average Filter", "Median Filter", "Gaussian Filter", "Bilateral Filter", "Laplacian Edge Detection"])
        kernel_size = st.slider("Select kernel size", 3, 15, 5, step=2)
        processed_image = apply_filter(image, filter_type, kernel_size)
    elif option == "Image Segmentation":
        segmentation_method = st.selectbox("Choose a segmentation method", ["Otsu's Thresholding", "Adaptive Thresholding", "Canny Edge Detection"])
        processed_image = segment_image(image, segmentation_method)
    elif option == "Object Detection":
        processed_image = detect_objects(image)
    
    if processed_image is not None:
        st.image(processed_image.astype(np.uint8), caption=f'{option} Applied', use_container_width=True)
        
        # Convert processed image for download
        _, buffer = cv2.imencode(".png", processed_image)
        st.download_button(label="Download Processed Image", 
                           data=buffer.tobytes(), 
                           file_name="processed_image.png", 
                           mime="image/png")
