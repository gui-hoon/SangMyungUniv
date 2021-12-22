function [y] = logisti(x);
  % �Է� x�� ���� Logistic ������ ����
  % ����� ��ȯ
  % �� f(x) = 1/(1+exp(bx)), b�� ���⸦ �����ϴ� �Ű�����
  
  y = 1 ./ (1+exp(-x));
endfunction
