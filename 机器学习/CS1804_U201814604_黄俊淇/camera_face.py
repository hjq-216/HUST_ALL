# -*- coding: utf-8 -*-
import face_recognition
import cv2
import scipy.misc
import os
# 读取摄像头，并识别摄像头中的人脸，进行匹配。
video_capture = cv2.VideoCapture(0)

def endwith(s,*endstring):
   resultArray = map(s.endswith,endstring)
   if True in resultArray:
       return True
   else:
       return False

def read_file(path):
    label_list = []
    dir_counter = 0

    #二维数组存储每个子文件夹下每张图片的face_encoding.
    img_encoding = [[] for i in range(6)]
    for child_dir in os.listdir(path):
         child_path = os.path.join(path, child_dir)

         for dir_image in  os.listdir(child_path):

             if endwith(dir_image,'JPG'):
                img = scipy.misc.imread(os.path.join(child_path, dir_image))

                img_encoding[dir_counter].append(face_recognition.face_encodings(img)[0])
                label_list.append(dir_counter)
         dir_counter += 1


    return img_encoding,label_list,dir_counter

#读取训练数据集的文件夹，把他们的名字返回给一个list
def read_name_list(path):
    name_list = []
    for child_dir in os.listdir(path):
        name_list.append(child_dir)
    return name_list

#main
all_encoding, lable_list, counter = read_file("train")
name_list = read_name_list("train")
face_locations = []
face_encodings = []
face_names = []
process_this_frame = True

while True:
    ret, frame = video_capture.read()
    small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)
    rgb_small_frame = small_frame[:, :, ::-1]
    if process_this_frame:
        face_locations = face_recognition.face_locations(small_frame)
        face_encodings = face_recognition.face_encodings(small_frame, face_locations)
        face_names = []
        # 匹配，并赋值
        for face_encoding in face_encodings:
            i = 0
            j = 0
            for t in all_encoding:
                for k in t:
                    match = face_recognition.compare_faces([k], face_encoding,tolerance=0.3)
                    if True in match:
                        name = name_list[i]
                        j = 1
                i = i + 1
            if j == 0:
                name = "unknown"

            face_names.append(name)

    process_this_frame = not process_this_frame

    for (top, right, bottom, left), name in zip(face_locations, face_names):
        top *= 4
        right *= 4
        bottom *= 4
        left *= 4

        cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)

        cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), 2)
        font = cv2.FONT_HERSHEY_DUPLEX
        cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)

    cv2.imshow('Video', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

video_capture.release()
cv2.destroyAllWindows()