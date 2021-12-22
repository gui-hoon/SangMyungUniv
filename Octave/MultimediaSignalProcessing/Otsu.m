% 512x512 ũ���� lena�̹����� img������ ����(pixel���� 512x512 ��ķ� ����)
img = imread('lena512.jpg');
[M,N] = size(img); % img�� ����ũ�� = M, ����ũ�� = N
%���� �ʱ�ȭ
hist = zeros(256,1); 
w1 = zeros(256, 1);
m1 = zeros(256, 1);
m2 = zeros(256, 1);
intensity = [0:1:255];
mt = zeros(256, 1);
%���� for������ �����̹����� ���� ������׷� ����
for i = 1:M,
  for j = 1:N,
    k = img(i,j);
    hist(k+1) = hist(k+1)+1;
  end    
end

nor_hist = hist/(M*N); 
% w1,w2 �� �� Ŭ������ Ȯ��
for k = 1:256
    w1(k) = sum(nor_hist(1:k));    
end
w2 = 1 - w1;
% m1,m2 �� �� Ŭ������ ��� ��Ⱚ
for k = 1:256,
    m1(k) = sum(intensity(1:k)*nor_hist(1:k));
    for i = (k+1):256,
       m2(k) = sum(intensity(k+1:256)*nor_hist(k+1:256));
    end   
end
% mt �� ��ü ������ ��� ��Ⱚ
mt = m1(256);
% k���� ���� �л� ���� ����
for k = 1:256,
  variance(k) = w1(k)*((m1(k) - mt).^2) + w2(k)*((m2(k) - mt).^2);
end
% �л��� �ִ밪�� �� ���� k�� 
[max_var, k] = max(variance);
% �л��� �ִ�ȭ��Ű�� ������ ��谪 k�� �������� ���� ����ȭ
img(img < k) = 0;
img(img >= k) = 255;

imshow(img);