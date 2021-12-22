% 이미지 회전, rotation 함수 rot 입니다.
% 회전시킬이미지(in)과 회전시킬 각도(theta)를 입력받아 회전한 이미지(out)을 출력합니다.
function [out] = rot(in, theta)
  [M, N] = size(in); % 입력받은 이미지의 행,렬의 크기값을 M과N에 저장
  out = zeros(M,N); % M행N렬의 out을 0으로 초기화
  % 입력받은 이미지의 중심 좌표 (Xc,Yc)
  Xc = M/2;
  Yc = N/2;
  % 새로운 회전 이미지 좌표를 구하고 그것에 대한 원본 이미지 좌표값을 계산
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
     