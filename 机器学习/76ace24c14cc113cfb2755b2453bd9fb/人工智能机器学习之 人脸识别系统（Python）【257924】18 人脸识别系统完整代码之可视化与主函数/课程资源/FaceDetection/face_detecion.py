#人脸标识代码

from  skimage import  io
import  dlib

#1 获取图片，转换成数组
file_name="li_00.jpg"
image=io.imread(file_name)

#2 建立一个人脸探测器

detector=dlib.get_frontal_face_detector()

#3 运行在图片上
detector_faces=detector(image,1)
print("发现{}张人脸，在{}图片中".format(len(detector_faces),file_name))

#4 提取人脸“68点”特征
model="shape_predictor_68_face_landmarks.dat"
# 提取特征
predictor=dlib.shape_predictor(model)

#5 建立窗口
win=dlib.image_window()
win.set_image(image)

#6 遍历识别的每一张脸，去操作
for i,box  in enumerate(detector_faces):
    win.add_overlay(box)
    print("第{}张人脸的左边位置:{}，右边位置：{}".format(i,box.left(),box.right()))
    landmarks=predictor(image,box)
    win.add_overlay(landmarks)
    dlib.hit_enter_to_continue()

