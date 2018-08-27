<h1><strong>Image Colorization using Generative Adversarial Networks</strong></h1>

This project consists of 1 python and 3 matlab files.
1) <strong>preprocess.m</strong> preprocesses a color input image, including image resizing (to 2048x4096) and grayscale conversion.
2) <strong>makePatches.m</strong> takes a very large-scale image (greater than 2048x4096) and produces image patches of size 2048x4096. The number of patches is inversely proportional to the stride. Smaller the stride, higher the stitched image quality will be. 
3) <strong>stitchPatches.m</strong> combines all image patches together to obtain a high-resolution stitched image. For the parts that the patches overlap, the intensity of those overlapping pixels will be averaged.
4) <strong>pix2pix_2048x4096.py</strong> is the modification of the original pix2pix.py by Isola et al. We have modified the GAN structure including the generator and the discriminator to fit our image size of 2048 by 4096. The program takes in a groundtruth input (output of preprocess.m or makePatches.m depending on the application), which is a concatenation of grayscale and color version of the original image, and produces a predictive colorized version of the grayscale input image.
