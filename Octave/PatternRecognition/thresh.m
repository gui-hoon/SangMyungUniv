function [y] = thresh(x)
  % 입력 x에 대해 threshold 연산자 적용;=.
  % 즉 y=1(x >= 0이면), y=0(x<0이면)
  
  y = (x>=0);
endfunction
