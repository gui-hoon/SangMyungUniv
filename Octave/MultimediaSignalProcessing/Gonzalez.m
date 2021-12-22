img = imread('lena512.jpg'); % 512x512 크기의 lena이미지를 img변수에 저장(pixel값이 512x512 행렬로 저장)
img = double(img); % img 값들을 double형으로 변환
img_max = max(max(img)); % img_max 변수에 레나 이미지의 pixel값중 가장 큰수를 저장
img_min = min(min(img)); % img_min 변수에 레나 이미지의 pixel값중 가장 작은수를 저장
T1 = (img_max+img_min)/2; % 초기 경계값 T1을  밝기의 최소값과 최대값 의 중간점으로 저장

while e > 0.1, % 경계값의 변화가 0.1보다 작을때까지 반복문 수행
  g1 = img(img >= T1); % 밝기값이 경계값보다 큰 영역
  g2 = img(img < T1); % 밝기값이 경계값보다 작은 영역
  m1 = mean(g1(g1)); % 영역 g1의 밝기의 평균값
  m2 = mean(g2(g2)); % 영역 g2의 밝기의 평균값
  T2 = (m1+m2)/2; % 새로운 경계값 T2
  e = abs(T1 - T2); % 경계값의 변화
  T1 = T2;
end
% 영상 이진화(영상에서 경계값보다 낮은 밝기는 0으로, 높은 밝기는 255로 바꿈)
img(img < T1) = 0;
img(img >= T1) = 255;                                     

imshow(img)