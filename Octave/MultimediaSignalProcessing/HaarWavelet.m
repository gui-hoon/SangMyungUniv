clear all

% Haar Wavelet
in = imread('lena512.jpg');
in = double(in);

[M,N] = size(in);
row = zeros(M,N);
col = zeros(M,N);
  
for i = 1:M % row Approximation
  for j = 1:N/2
    row(i,j) = (in(i,2*j-1) + in(i,2*j))/2;     
  endfor
endfor
  
for i = 1:M % row Details
  for j = 1:N/2
    row(i,j+N/2) = (in(i,2*j-1) - in(i,2*j))/2;
  endfor
endfor
  
for i = 1:N % col Approximation
  for j = 1:M/2
    col(j,i) = (row(2*j-1,i) + row(2*j,i))/2;
  endfor
endfor
  
for i = 1:N % col Details
  for j = 1:M/2
    col(j+M/2,i) = (row(2*j-1,i) - row(2*j,i))/2;
  endfor
endfor 
col = uint8(col); 
 
figure(1);
imshow(uint8(in));  % original image
figure(2);
imshow(col);  % haar wavelet image

% inverse Haar Wavelet
col = double(col);
inv_row = zeros(M,N);
inv_col = zeros(M,N);

for i = 1:N % col inverse 
  for j = 1:M/2
    inv_col(2*j-1,i) = col(j,i) + col(j+M/2,i);
    inv_col(2*j,i) = col(j,i) - col(j+M/2,i);
  endfor
endfor

for i = 1:M % row inverse
  for j = 1: N/2
    inv_row(i,2*j-1) = inv_col(i,j) + inv_col(i,j+N/2);
    inv_row(i,2*j) = inv_col(i,j) - inv_col(i,j+N/2);    
  endfor
endfor
inv_row = uint8(inv_row);

figure(3);
imshow(inv_row);  % inverse haar wavelet image