function [y] = logisti(x);
  % 입력 x에 대해 Logistic 연산자 적용
  % 결과를 반환
  % 즉 f(x) = 1/(1+exp(bx)), b는 기울기를 결정하는 매개변수
  
  y = 1 ./ (1+exp(-x));
endfunction
