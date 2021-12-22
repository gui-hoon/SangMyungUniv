% 512x512 크기의 lena이미지를 img변수에 저장(pixel값이 512x512 행렬로 저장)
img = imread('lena512.jpg');
[M,N] = size(img); % img의 행의크기 = M, 열의크기 = N
%변수 초기화
hist = zeros(256,1); 
w1 = zeros(256, 1);
m1 = zeros(256, 1);
m2 = zeros(256, 1);
intensity = [0:1:255];
mt = zeros(256, 1);
%이중 for문으로 레나이미지에 대한 히스토그램 생성
for i = 1:M,
  for j = 1:N,
    k = img(i,j);
    hist(k+1) = hist(k+1)+1;
  end    
end

nor_hist = hist/(M*N); 
% w1,w2 는 각 클래스의 확률
for k = 1:256
    w1(k) = sum(nor_hist(1:k));    
end
w2 = 1 - w1;
% m1,m2 는 각 클래스의 평균 밝기값
for k = 1:256,
    m1(k) = sum(intensity(1:k)*nor_hist(1:k));
    for i = (k+1):256,
       m2(k) = sum(intensity(k+1:256)*nor_hist(k+1:256));
    end   
end
% mt 는 전체 영상의 평균 밝기값
mt = m1(256);
% k값의 따른 분산 값을 저장
for k = 1:256,
  variance(k) = w1(k)*((m1(k) - mt).^2) + w2(k)*((m2(k) - mt).^2);
end
% 분산의 최대값과 그 때의 k값 
[max_var, k] = max(variance);
% 분산을 최대화시키는 최적의 경계값 k를 기준으로 영상 이진화
img(img < k) = 0;
img(img >= k) = 255;

imshow(img);