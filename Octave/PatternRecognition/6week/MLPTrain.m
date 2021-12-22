clc; clear;

# initialize var
x1 = 0.5; # input
w0 = [0.15; 0.2];
w1 = [0.4, 0.5; 0.45, 0.55];
y = [0.3; 0.9]; # 정답

z1 = x1*w0;
a1 = sigmoid(z1);
z2 = w1'* a1;
a2 = sigmoid(z2);

learning_rate=0.5;
epoch = 500;
min_err = 1;
min_err_i = 0;

# error visualize
figure(1);

for i=1:epoch
  # w1이 전체 에러에 미치는 영향
  dEtot_da2 = -(y-a2);
  da2_dz2 = a2.*(1-a2);
  dz2_dw1 = a1';

  dEtot_dw1 = ((dEtot_da2.*da2_dz2)*dz2_dw1)';

  # w0이 전체 에러에 미치는 영향
  dE_da2 = -(y-a2);
  dEtot_da1 = w1*(dE_da2.*da2_dz2);
  da1_dz1 = a1.*(1-a1);

  dEtot_dw0 = dEtot_da1.*da1_dz1*x1;

  # new w 
  w1 = w1 .- learning_rate*dEtot_dw1;
  w0 = w0 .- learning_rate*dEtot_dw0;
  
  # 학습후 var
  z1 = x1*w0;
  a1 = sigmoid(z1);
  z2 = w1'* a1;
  a2 = sigmoid(z2);
  
  # 학습후 error값
  error = 0.5*sum((y - a2).^2);
  fprintf("epoch = %d\terr= %d\n", i, error)
  
  plot(i, error,'b');
  hold on
  
  if min_err > error
    min_err = error;
    min_err_i = i;    
  end

  if i == epoch
    fprintf("The training is over as much as the entire epoch.\n");
    fprintf("When there's a minimum error, epoch= %d\tminimum error= %d",min_err_i, min_err);
  end
  
endfor
