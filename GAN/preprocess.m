close all
clc

readPath = 'input_folder\';  
writePath = 'output_folder\';
fileType = '.jpg'; 

% reading files in a folder without specifying file names
oldImg = dir(strcat(readPath,'*',fileType));
old_nfiles = length(oldImg); % number of files in a directory

% new dimensions that you want the image to be resized to
rdim = 2048;
cdim = 4096;

for i = 1:old_nfiles
    % reading an image file
    imgName = oldImg(i).name;
    imgFile = strcat(readPath,imgName);
    im = imread(imgFile);
    [m,n,~] = size(im);

    % resize "horizontal" image to size 2048 x 4096
    if(m > rdim && n > cdim)
        ratio = cdim/rdim;
        curr_ratio = n/m;
        
        if (curr_ratio < 2)
            % crop excess rows
            scale = cdim/n;
            im = imresize(im, [m*scale cdim]);
            [m,~,~] = size(im);
            y = (m-rdim)/2;
            p1 = y+1;
            p2 = y+rdim;
            im = im(p1:p2,:,:);
           
        elseif (curr_ratio > 2)
            % crop excess columns
            scale = rdim/m;
            im = imresize(im, [rdim n*scale]);
            [~,n,~] = size(im);
            x = (n-cdim)/2;
            p1 = x+1;
            p2 = x+cdim;
            im = im(:,p1:p2,:);
            
        else % curr_ratio == 2
            im = imresize(im, [0.5 0.5]);
        end
        
    end
 
        % get grayscale version of the image
        im_gray = rgb2gray(im);
        im_gray2 = im_gray;
        im_gray2(:,:,2) = im_gray;
        im_gray2(:,:,3) = im_gray;

        % concatenate grayscale and color images together
        IM = horzcat(im,im_gray2);

        % write new image to folder
        writeImg = strcat(writePath,num2str(i),fileType);
        imwrite(IM,writeImg);
        message = strcat('image ',num2str(i),' done');
        disp(message)
end