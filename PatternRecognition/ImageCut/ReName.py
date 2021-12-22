import os

raw_path = './frame_data/'  # 원본 이미지 경로
token_list = os.listdir(raw_path)  # 원본 이미지 경로 내 폴더들 list
data_path = './300size_data/'  # 저장할 이미지 경로

# resize 시작 --------------------
for token in token_list:
#원본 이미지 경로와 저장할 경로 이미지 지정
    image_path = raw_path + token + '/'
    save_path = data_path + token + '/'
    # 저장할 경로 없으면 생성
    if not os.path.exists(save_path):
       os.mkdir(save_path)

#원본 이미지 경로의 모든 이미지 list 지정
data_list = os.listdir(image_path)
print(len(data_list))

# 모든 이미지 resize 후 저장하기
for name in data_list:

    # 이미지 열기
    im = Image.open(image_path + name)

    # 이미지 resize
    im = im.resize((300, 300))

    # 이미지 JPG로 저장
    im = im.convert('RGB')
    im.save(save_path + name)
print('end ::: ' + token)