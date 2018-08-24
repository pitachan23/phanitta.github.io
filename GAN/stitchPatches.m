clear all
close all
clc

readPath = 'patches_folder\';  
writePath = 'stitchImg_folder\';
fileType = '.jpg'; 

% very high-resolution image
imgPath = 'image_folder\';
imgName = 'image_name';
im = imread(strcat(imgPath,imgName,fileType));
[m,n,~] = size(im);

kernel = [2048 4096];
stride = 256;
mPatches = (m-kernel(1))/stride + 1;
nPatches = (n-kernel(2))/stride + 1;

stitchImg = zeros(m,n,3);
count = zeros(m,n,3);

m_start = 1;
m_end = kernel(1);
n_start = 1;
n_end = kernel(2);

index = 1;
for i = 1:mPatches
    for j = 1:nPatches
        % image name will be for ex. 1-outputs, 2-outputs, ...
        % these image patches are outputs of the GAN 
        %imgName = strcat(num2str(index),'-outputs'); 
        imgName = num2str(index);
        
        if exist(strcat(readPath,imgName,fileType), 'file')
            im = double(imread(strcat(readPath,imgName,fileType)));
            
            stitchImg(m_start:m_end,n_start:n_end,:) = stitchImg(m_start:m_end,n_start:n_end,:) + im;
            count(m_start:m_end,n_start:n_end,:) = count(m_start:m_end,n_start:n_end,:) + 1;
        end
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

stitchImg = uint8(stitchImg./count);
writeImg = strcat(writePath, imgName, '_stitched',fileType);
imwrite(stitchImg,writeImg);
