close all
clc

readPath = 'input_folder\';  
writePath = 'output_folder_patches\';
fileType = '.jpg'; 
imgName = 'image_name';
im = imread(strcat(readPath,imgName,fileType));

[m,n,~] = size(im);
kernel = [2048 4096];
stride = 256;
mPatches = (m-kernel(1))/stride + 1;
nPatches = (n-kernel(2))/stride + 1;

m_start = 1;
m_end = kernel(1);
n_start = 1;
n_end = kernel(2);

index = 1;
for i = 1:mPatches
    for j = 1:nPatches
        new_im = im(m_start:m_end,n_start:n_end,:);
        new_im_gray = rgb2gray(new_im);
        new_im_gray2 = new_im_gray;
        new_im_gray2(:,:,2) = new_im_gray;
        new_im_gray2(:,:,3) = new_im_gray;
        IM = horzcat(new_im,new_im_gray2);
        
        writeImg = strcat(writePath,num2str(index),fileType);
        imwrite(IM,writeImg);
        disp(index)
        
        index = index + 1;
        n_start = n_start + stride;
        n_end = n_end + stride;
    end
    m_start = m_start + stride;
    m_end = m_end + stride;
    n_start = 1;
    n_end = kernel(2);
end
