function [w,b]=trainpt(x,t,w,b)
  % 일괄 처리 형태의 퍼셉트론 훈련;
  % 여기서 x는 입력 [x1 x2 ... xn]에 관한 행렬, t는 목표 출력 [t1 t2 ... tn],
  % w는 가중치 행벡터, b는 임계값을 나타낸다.

  [inputs,patterns]=size(x);
  y = percpt(x,w,b); % percpt 함수 사용
  
  for i=1:patterns
    if y(i)==t(i) % 변화가 없음(w=w; b=b)
      w=w;
      b=b;
    elseif y(i)==0 % 목표 = 1
      w = w+x(:,i)'; 
      b = b+1;
    else % y=1, 목표=0.
      w = w-x(:,i)'; 
      b = b-1;
    end
  end
end