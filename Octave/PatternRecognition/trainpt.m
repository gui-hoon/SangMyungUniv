function [w,b]=trainpt(x,t,w,b)
  % �ϰ� ó�� ������ �ۼ�Ʈ�� �Ʒ�;
  % ���⼭ x�� �Է� [x1 x2 ... xn]�� ���� ���, t�� ��ǥ ��� [t1 t2 ... tn],
  % w�� ����ġ �຤��, b�� �Ӱ谪�� ��Ÿ����.

  [inputs,patterns]=size(x);
  y = percpt(x,w,b); % percpt �Լ� ���
  
  for i=1:patterns
    if y(i)==t(i) % ��ȭ�� ����(w=w; b=b)
      w=w;
      b=b;
    elseif y(i)==0 % ��ǥ = 1
      w = w+x(:,i)'; 
      b = b+1;
    else % y=1, ��ǥ=0.
      w = w-x(:,i)'; 
      b = b-1;
    end
  end
end