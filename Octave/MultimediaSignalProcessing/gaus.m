% gaussian smoothing filter �Լ��Դϴ�.
% �Լ� ������� imread()�� imnoise() �Լ��� ����Ͽ� gaussian noise�� ���� �̹����� �����մϴ�. 
% gaus(in, sigma) -> in���� �̸� �غ��� noise�� �ִ� �̹����� �ֽ��ϴ�.
% -> sigma���� ���ϴ� sigma ũ�� �� �Է��մϴ�.

function [out] = gaus(in, sigma)
  [x, y] = size(in); % �Է¹��� �̹����� ���� ũ��� ���� ũ�Ⱑ x y�� ����˴ϴ�.
  mask_size = double(6.0 * sigma) + 1; % ����ũ ũ�⸦ �����ϴ� ���Դϴ�.

  % 2���� ����þ� �Լ��� ������ ũ��� ����� �ݴϴ�.
  rad = floor(mask_size / 2); 
  [a, b] = meshgrid(-rad:rad, -rad:rad);

  % ����þ� �Լ� ���Դϴ�. 
  gaussian = (1/(2*pi*(sigma.^2)))*exp(-1 * (a.^2 + b.^2)./ (2*sigma.^2) );
  gaussian = gaussian / sum(gaussian(:));
  
  in = double(in);
  % ����þ� ����ũ�� �Է��� noise�� ���� �̹����� ������� ó�� �մϴ�.
  out = conv2(in, gaussian, 'same');
  out = uint8(out);
  % noise�� ������ �̹����� ����մϴ�.
  imshow(out);
end

% gaussian smoothing filter�� ����þ� ������ ����ó���� ������ ������ ����þ� ������ ������ ������ ������ �����ϰ� ������ �帮���ϴ� ����Դϴ�.
% sigma���� Ŀ������ ������ ������� ���� �� �� �ֽ��ϴ�.