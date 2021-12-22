clear all

pkg load signal
pkg load image

lena = imread('lena512.jpg');
lena = double(lena);
Qf = rand;  % 0~1
[M,N] = size(lena);

% Quantization table
Qt = [16,11,10,16,24,40,51,61;
      12,12,14,19,26,58,60,55;
      14,13,16,24,40,57,69,56;
      14,17,22,29,51,87,80,62;
      18,22,37,56,68,109,103,77;
      24,35,55,64,81,104,113,92;
      49,64,78,87,103,121,120,101;
      72,92,95,98,112,100,103,99];
      
% Qf = Q-factor      
Suv = (Qt*(200 - Qf*2)+50)/100;

% level shift
ls_lena = lena - 128;

% 8x8 DCT
dct = @dct2;
DCT_lena = blockproc(ls_lena,[8,8],dct);

% Quantization
qut = @(block_struct)round(block_struct./Suv);
Qut_lena = blockproc(DCT_lena,[8,8],qut);

% inverse Quantization
iqut = @(block_struct)block_struct.*Suv;
IQut_lena = blockproc(Qut_lena,[8,8],iqut);

% 8x8 IDCT
idct = @idct2;
IDCT_lena = blockproc(IQut_lena,[8,8],idct);

% level shift
R_lena = IDCT_lena + 128;

% error
Err = R_lena - lena;

% PSNR
MSE = sum(sum(Err.*Err))/(M*N);
Psnr = 10*log10(((2^8-1)^2)/MSE)

subplot(1,2,1);
imshow(uint8(lena))
title('Original')
subplot(1,2,2);
imshow(uint8(R_lena));
title('restoration')