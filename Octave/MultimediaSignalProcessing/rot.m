% �̹��� ȸ��, rotation �Լ� rot �Դϴ�.
% ȸ����ų�̹���(in)�� ȸ����ų ����(theta)�� �Է¹޾� ȸ���� �̹���(out)�� ����մϴ�.
function [out] = rot(in, theta)
  [M, N] = size(in); % �Է¹��� �̹����� ��,���� ũ�Ⱚ�� M��N�� ����
  out = zeros(M,N); % M��N���� out�� 0���� �ʱ�ȭ
  % �Է¹��� �̹����� �߽� ��ǥ (Xc,Yc)
  Xc = M/2;
  Yc = N/2;
  % ���ο� ȸ�� �̹��� ��ǥ�� ���ϰ� �װͿ� ���� ���� �̹��� ��ǥ���� ���
  for i = 1: N
    for j = 1: M
      fy=round((j-Xc)*cos(theta) - (i-Yc)*sin(theta)) +Xc;
      fx=round((j-Xc)*sin(theta) + (i-Yc)*cos(theta)) +Yc;
      if (fy>=1 && fy<=N && fx>=1 && fx<=M)
        out(j,i) = in(fy,fx);
      end            
    end
  end
  imshow(uint8(out));
end
     