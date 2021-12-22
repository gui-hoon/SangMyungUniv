clear all;
pkg load image; # ��Ű���� �ٿ��� �޴´�.
pkg load signal;

# im3, im4�� ���.
# size transform
im03 = imread('im03.jpg');
im04 = imread('im04.jpg');
reference_img = rgb2gray(im03);
target_img = rgb2gray(im04);
curr_img = rgb2gray(im04);

reference_img = imresize(reference_img, [240, 424]);
target_img = imresize(target_img, [240, 424]);
curr_img = imresize(curr_img, [240, 424]);
##############################################################################
# ���� ����
[M, N] = size(target_img);
MV_vector_x = zeros(M/4, N/4);
MV_vector_y = zeros(M/4, N/4);
act_block = zeros(4,4);
macro_block = zeros(4,4);
curr_x=0; curr_y=0;
min_mad_value = 999999;
temp = 9999999;
mad_x = 0; mad_y = 0;
move_p = 0; move_m = 0;
sxy = 4;
#############################################################################
# search and mad func start;
for i = 1:4:M
  for j = 1:4:N
    # curr_img �� act_block ä���
    curr_x = j;
    curr_y = i;
    for x = j:j+3
      for y = i:i+3
        act_block(y-i+1, x-j+1) = curr_img(y,x);
      endfor
    endfor
    # mad x,y���� �ʱ� ����.
    mad_x = curr_x;
    mad_y = curr_y;
    # 2-D search ����.
    while sxy >= 1
      # Ž�� ��ġ�� 4 -> 2 -> 1 ������ ���� ��Ų��.
      move_p = 4+sxy;
      move_m = -4-sxy;
      #���� ����
      # +/- ������ ���ư��鼭 ���� �ְ� for loop ����.
      
      for a = move_m:move_p:move_p
        for b = move_m:move_p:move_p
          if (mad_x+a >=1 && mad_x+a <= N-4 && ...
            mad_y+b >= 1 && mad_y+b <= M-4)
            # ������ �����ϴٸ� ����.
            for q = 1:4
              for w = 1:4
                macro_block(q,w) = reference_img(mad_y+b+(q-1),mad_x+a+(w-1));
              endfor
            endfor
            # ��ũ�� �� ����
            temp = (sum(sum(abs(act_block - macro_block))))/16;
            # ������ act_block�� macro_block�� ���� ���밪�� ���� ����� ���Ѵ�.
            if (temp < min_mad_value) 
              mad_x = mad_x+a;
              mad_y = mad_y+b;
              min_mad_value = temp;
              # �ּҰ��̶�� �ʱ�ȭ�� ���ش�.
            endif # mad�Լ�.          
          endif
        endfor
      endfor
      sxy /= 2; # ���� ���̱�
      min_mad_value = 999999; # �� �ʱ�ȭ. 
    endwhile
    MV_vector_x(i/4+0.75,j/4+0.75) = j - mad_x;
    MV_vector_y(i/4+0.75,j/4+0.75) = i - mad_y;
    sxy = 4;
    # ���������� ����� x,y vector�� ���� ���� ����. 
    # sxy�� �ʱ�ȭ ���ش�.
  endfor
endfor

# ���ø� ����غ���. 
figure(1),
imshow(uint8(curr_img));
%{
for i = 1:4:M
  for j = 1:4:N
    for y = 1:4
      for x = 1:4
        a = i+(y-1)+MV_vector_y(i/4+0.75,j/4+0.75);
        b = j+(x-1)+MV_vector_x(i/4+0.75,j/4+0.75);
        if(a >= 1 && b >= 1 && a<=M && b <=N)
          curr_img(i+(y-1), j+(x-1)) = reference_img(a,b);
        endif
      endfor
    endfor
  endfor
endfor
%}
restoration = reference_img;
for rh = 1:60
  for rw = 1:106
    p_blockindex_h = rh;
    p_blockindex_w = rw;
    previous_block = reference_img(4*(rh-1)+1:rh*4,4*(rw-1)+1:rw*4);
    re_index_h = rh + MV_vector_y(rh,rw);
    re_index_w = rw + MV_vector_x(rh,rw);
    restoration(4*(re_index_h-1)+1:re_index_h*4,4*(re_index_w-1)+1:re_index_w*4) = previous_block;
  endfor
endfor
figure(2),
imshow(uint8(curr_img-restoration));