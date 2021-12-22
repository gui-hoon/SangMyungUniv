function [y] = sigmun(x)
  % Signum 연산자; 입력 x에 대해 signum 연산자 적용
  % 결과를 반환
  % 즉 x>0이면 y=1이고, x<=0이면 y=-1을 반환
  
  y = sign(x-eps);
endfunction

