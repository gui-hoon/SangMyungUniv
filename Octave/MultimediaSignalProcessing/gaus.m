% gaussian smoothing filter 함수입니다.
% 함수 사용전에 imread()와 imnoise() 함수를 사용하여 gaussian noise가 섞인 이미지를 저장합니다. 
% gaus(in, sigma) -> in에는 미리 준비한 noise가 있는 이미지를 넣습니다.
% -> sigma에는 원하는 sigma 크기 를 입력합니다.

function [out] = gaus(in, sigma)
  [x, y] = size(in); % 입력받은 이미지의 행의 크기와 열의 크기가 x y에 저장됩니다.
  mask_size = double(6.0 * sigma) + 1; % 마스크 크기를 결정하는 식입니다.

  % 2차원 가우시안 함수를 적당한 크기로 만들어 줍니다.
  rad = floor(mask_size / 2); 
  [a, b] = meshgrid(-rad:rad, -rad:rad);

  % 가우시안 함수 식입니다. 
  gaussian = (1/(2*pi*(sigma.^2)))*exp(-1 * (a.^2 + b.^2)./ (2*sigma.^2) );
  gaussian = gaussian / sum(gaussian(:));
  
  in = double(in);
  % 가우시안 마스크와 입력한 noise가 섞인 이미지를 컨볼루션 처리 합니다.
  out = conv2(in, gaussian, 'same');
  out = uint8(out);
  % noise를 제거한 이미지를 출력합니다.
  imshow(out);
end

% gaussian smoothing filter는 가우시안 분포를 영상처리에 적용한 것으로 가우시안 잡음을 포함한 영상의 잡음을 제거하고 영상을 흐리게하는 기법입니다.
% sigma값이 커질수록 영상이 흐려지는 것을 볼 수 있습니다.