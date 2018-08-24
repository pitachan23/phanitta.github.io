<strong>Image Colorization using Generative Adversarial Networks</strong>

This project consists of 1 python and 3 matlab files.
1) preprocess.m: Preprocesses a color input image, including image resizing (to 2048x4096) and grayscale conversion.
2) makePatches.m: Takes a very large-scale image (greater than 2048x4096) and produces image patches of size 2048x4096. The number of patches is inversely proportional to the stride. Smaller the stride, higher the stitched image quality will be. 
3) stitchPatches.m: Combine all image patches together to obtain a stitched image. For the parts that the patches overlap, the intensity of those overlapping pixels will be averaged.
