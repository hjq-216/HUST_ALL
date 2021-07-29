import  os
from sklearn import  neighbors
import os.path
import  pickle
from  PIL  import  Image,ImageDraw
import face_recognition as fr
from face_recognition.face_recognition_cli import  image_files_in_folder
#定义一个训练模型的函数
def train(train_dir,model_save_path='face_recog_model.clf',n_neighbors=3,knn_algo='ball tree'):
    #生成训练集
    X=[]
    Y=[]
    #遍历训练集中的每一个人  class_dir是获取到的人名
    for class_dir in os.listdir(train_dir):
        if not os.path.isdir(os.path.join(train_dir,class_dir)):
            continue #结束当前循环，进入下一个循环

        #遍历这个人每一张图片 img_path是获取到的具体的人文件夹下的一张图片名
        for img_path in image_files_in_folder(os.path.join(train_dir,class_dir)):
           image= fr.load_image_file(img_path)
           boxes=fr.face_locations(image)
           #对于当前的图片，增加编码至训练集
           X.append(fr.face_encodings(image,known_face_locations=boxes)[0])  #返回128维度的向量
           Y.append(class_dir)

    #决定K值 (KNN)
    if n_neighbors is None:
        n_neighbors=3

    #创建并且训练分类器
    knn_clf=neighbors.KNeighborsClassifier(n_neighbors=n_neighbors)
    knn_clf.fit(X,Y)

    #保存训练好的分类器
    if model_save_path is not None:
        with open(model_save_path,'wb') as f:
            pickle.dump(knn_clf,f)

    return  knn_clf


#使用模型预测
def predict(img_path,knn_clf=None,model_path=None,distance_threshold=0.5):
    if knn_clf is None and model_path is None:
        raise  Exception("必须提供KNN分类器，可选方式为knn_clf或model_path")

    #加载训练好的KNN模型
    if knn_clf is None:
        with open(model_path,"rb") as f:
            knn_clf=pickle.load(f)

    #加载图片，发现人脸的位置
    X_img=fr.load_image_file(img_path)
    X_face_locations=fr.face_locations(X_img)

    #对测试图片中的人脸编码  返回的是128个人脸特征构成的向量
    encondings=fr.face_encodings(X_img,known_face_locations=X_face_locations)[0]

    #利用KNN model找出与测试人脸最匹配的人脸
    closest_distances=knn_clf.kneighbors(encondings,n_neighbors=1)
    are_matches=[closest_distances[0][i][0]<=distance_threshold
                for i in range(len(X_face_locations))    ]

    #预测类别
    return  [(pred,loc) if rec else("unknown",loc)
            for pred,loc ,rec in zip(knn_clf.predict(encondings),X_face_locations,are_matches)]


#人脸识别可视化函数
def show_names_on_image(img_path,predictions):
    pil_image=Image.open(img_path).convert("RGB")
    draw=ImageDraw.Draw(pil_image)

    for name,(top,right,bottom,left) in predictions:
        #用Pillow模块画出人脸边界盒子
        draw.rectangle(((left,top),(right,bottom)),outline=(255,0,255))

        #pillow里可能生成非UTF-8格式，所以做如下的转换
        name=name.encode("UTF-8")
        name=name.decode("ascii")

        #在人脸下写下名字，作为标签
        text_width,text_height=draw.textsize(name)
        draw.rectangle(((left,bottom-text_height-10),(right,bottom)),
                       fill=(255,0,255),outline=(255,0,255))
        draw.text((left+6,bottom-text_height-5),name,fill=(255,255,255))



    del draw
    pil_image.show()


#主函数
if __name__=="__main__":
    #1 训练KNN分类器，可以先保存，后面使用
    print("正在训练KNN分类器~~~~")
    train("examples/train",model_save_path="face_recog_model.clf",n_neighbors=2)
    print("训练完成")

    #2 利用训练好的分类器，对新照片进行预测
    for image_file  in os.listdir("examples/test"):
        full_file_path=os.path.join("examples/test",image_file)
        print("在{}中寻找人脸……".format(image_file))

        #利用分类器，找出所有的人脸：
        #要么传递一个classifier文件名，要么传一个classifier模型实例
        predictions=predict(full_file_path,model_path="face_recog_model.clf")

        #打印结果
        for name,(top,right,bottom,left) in predictions:
            print("发现{}，位置:({},{},{},{})".format(name,top,right,bottom,left))

        #在图片上显示预测结果
        show_names_on_image(os.path.join("examples/test",image_file),predictions)