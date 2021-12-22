function [w,b] = trainpt1(x,t,w,b)
  % ���� �ۼ�Ʈ�� ��Ʈ��ũ�� ���� �ѹ��� �Ʒ��� �ǽ���;
  % ���⼭ x�� �Է� ������, t�� ��ǥ ���, w�� ����ġ �຤��,
  % b�� �Ӱ谪�� ��Ÿ����.
  
  y = thresh([w b]*[x ;1]); 
  if y==t % ����ġ ��ȭ ����(w=w; b=b)
    w = w;
    b = b;
  elseif y==0 % ��ǥ = 1
    w = w+x'; b = b+1; 
  else % y=1, ��ǥ=0.
    w = w-x'; b = b-1;
  end
  
endfunction