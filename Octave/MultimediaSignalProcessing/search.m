% 2D Logarithmic Search
clear all
pkg load image

test_im1 = imread('im01.jpg');
test_im2 = imread('im03.jpg');

test_grayim1 = 0.2989 * test_im1(:,:,1) + 0.5870 * test_im1(:,:,2) + 0.1140 * test_im1(:,:,3);
test_grayim2 = 0.2989 * test_im2(:,:,1) + 0.5870 * test_im2(:,:,2) + 0.1140 * test_im2(:,:,3);
[H, W] = size(test_grayim1);

blocksize = 8;
im_block_h = H/blocksize;
im_block_w = fix(W/blocksize);

previous_im = double(imresize(test_grayim1, [blocksize*im_block_h, blocksize*im_block_w]));
current_im = double(imresize(test_grayim2, [blocksize*im_block_h, blocksize*im_block_w]));
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
MAD = [255,255,255,255,255,255,255,255,255];
block_index = zeros(9,2);
motion_vector = zeros(im_block_h,im_block_w);

for h = 1:im_block_h
  for w = 1:im_block_w
    c_blockindex_h = h;
    c_blockindex_w = w;
    i=h;,j=w;
    step_size = 4;
    current_block = current_im(8*(h-1)+1:i*blocksize,8*(w-1)+1:j*blocksize);
    % 3step
    while(step_size >= 1)  
      if(i-step_size > 0 && j-step_size > 0)
       i1 = i-step_size;
       j1 = j-step_size;
       previous_block1 = previous_im(8*(i1-1)+1:i1*blocksize,8*(j1-1)+1:j1*blocksize);
       MAD(1,1) = sum(sum(abs(current_block .- previous_block1)))/blocksize^2;
       block_index(1,1:2) = [i1,j1];
      endif
      if(i-step_size > 0 && j > 0)
       i2 = i-step_size;
       j2 = j;
       previous_block2 = previous_im(8*(i2-1)+1:i2*blocksize,8*(j2-1)+1:j2*blocksize);
       MAD(1,2) = sum(sum(abs(current_block .- previous_block2)))/blocksize^2;
       block_index(2,1:2) = [i2,j2];
      endif
      if(i-step_size > 0 && j+step_size < im_block_w +1)
       i3 = i-step_size;
       j3 = j+step_size;
       previous_block3 = previous_im(8*(i3-1)+1:i3*blocksize,8*(j3-1)+1:j3*blocksize);
       MAD(1,3) = sum(sum(abs(current_block .- previous_block3)))/blocksize^2;
       block_index(3,1:2) = [i3,j3];
      endif
      if(i > 0 && j-step_size > 0)
       i4 = i;
       j4 = j-step_size;
       previous_block4 = previous_im(8*(i4-1)+1:i4*blocksize,8*(j4-1)+1:j4*blocksize);
       MAD(1,4) = sum(sum(abs(current_block .- previous_block4)))/blocksize^2;
       block_index(4,1:2) = [i4,j4];
      endif
      if(i > 0 && j > 0)
       i5 = i;
       j5 = j;
       previous_block5 = previous_im(8*(i5-1)+1:i5*blocksize,8*(j5-1)+1:j5*blocksize);
       MAD(1,5) = sum(sum(abs(current_block .- previous_block5)))/blocksize^2;
       block_index(5,1:2) = [i5,j5];  
      endif
      if(i > 0 && j+step_size < im_block_w +1) 
       i6 = i;
       j6 = j+step_size;
       previous_block6 = previous_im(8*(i6-1)+1:i6*blocksize,8*(j6-1)+1:j6*blocksize);
       MAD(1,6) = sum(sum(abs(current_block .- previous_block6)))/blocksize^2;
       block_index(6,1:2) = [i6,j6];
      endif
      if(i+step_size < im_block_h +1 && j-step_size > 0)
       i7 = i+step_size;
       j7 = j-step_size;
       previous_block7 = previous_im(8*(i7-1)+1:i7*blocksize,8*(j7-1)+1:j7*blocksize);
        MAD(1,7) = sum(sum(abs(current_block .- previous_block7)))/blocksize^2;
        block_index(7,1:2) = [i7,j7];
      endif
      if(i+step_size < im_block_h +1 && j > 0)      
       i8 = i+step_size;
       j8 = j;
       previous_block8 = previous_im(8*(i8-1)+1:i8*blocksize,8*(j8-1)+1:j8*blocksize);
       MAD(1,8) = sum(sum(abs(current_block .- previous_block8)))/blocksize^2;
        block_index(8,1:2) = [i8,j8];
      endif
      if(i+step_size < im_block_h +1 && j+step_size < im_block_w +1)
        i9 = i+step_size;
        j9 = j+step_size;
        previous_block9 = previous_im(8*(i9-1)+1:i9*blocksize,8*(j9-1)+1:j9*blocksize);
        MAD(1,9) = sum(sum(abs(current_block .- previous_block9)))/blocksize^2;
        block_index(9,1:2) = [i9,j9];
      endif
      % Blocks that minimize MAD index b_i, b_j   
      [min_mad, best_index] = min(min(MAD,[],1));
      b_i = block_index(best_index,1);
      b_j = block_index(best_index,2);  
      i = b_i;
      j = b_j;
      step_size = step_size/2;
    endwhile
    % motion vector x
    motion_vector(i,j,1) = c_blockindex_h - b_i;
    % motion vector y
    motion_vector(i,j,2) = c_blockindex_w - b_j;   
  endfor 
endfor            
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
restoration = previous_im;

for rh = 1:im_block_h
  for rw = 1:im_block_w
    p_blockindex_h = rh;
    p_blockindex_w = rw;
    previous_block = previous_im(8*(rh-1)+1:rh*blocksize,8*(rw-1)+1:rw*blocksize);
    re_index_h = rh + motion_vector(rh,rw,1);
    re_index_w = rw + motion_vector(rh,rw,2);
    restoration(8*(re_index_h-1)+1:re_index_h*blocksize,8*(re_index_w-1)+1:re_index_w*blocksize) = previous_block;
  endfor
endfor
Err = current_im - restoration;

subplot(2,2,1);
imshow(uint8(previous_im));title('previous image');
subplot(2,2,2);
imshow(uint8(current_im));title('Current image');
subplot(2,2,3);
imshow(uint8(restoration));title('Restoration image');
subplot(2,2,4);
imshow(uint8(Err));title('Error');

