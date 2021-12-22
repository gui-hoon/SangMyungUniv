function [w,b] = trainpt1(x,t,w,b)
  % 단층 퍼셉트론 네트워크에 관해 한번의 훈련을 실시함;
  % 여기서 x는 입력 열벡터, t는 목표 출력, w는 가중치 행벡터,
  % b는 임계값을 나타낸다.
  
  y = thresh([w b]*[x ;1]); 
  if y==t % 가중치 변화 없음(w=w; b=b)
    w = w;
    b = b;
  elseif y==0 % 목표 = 1
    w = w+x'; b = b+1; 
  else % y=1, 목표=0.
    w = w-x'; b = b-1;
  end
  
endfunction