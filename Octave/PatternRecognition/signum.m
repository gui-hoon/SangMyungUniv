function [y] = sigmun(x)
  % Signum ������; �Է� x�� ���� signum ������ ����
  % ����� ��ȯ
  % �� x>0�̸� y=1�̰�, x<=0�̸� y=-1�� ��ȯ
  
  y = sign(x-eps);
endfunction

