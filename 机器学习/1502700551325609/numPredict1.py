#coding:utf8

from PIL import Image
from sklearn.externals import joblib
from sklearn.cross_validation import train_test_split
from sklearn.metrics import confusion_matrix, classification_report
from sklearn.preprocessing import LabelBinarizer
import numpy as np
from getImageData import ImageData
from BpNN import NeuralNetwork
import matplotlib.pyplot as plt
import os



###############提取图片中的特征向量####################
X = []
Y = []

for i in range(0, 10):
    #遍历文件夹，读取数字图片
    for f in os.listdir("numImage/%s" % i):
        #打开一张文件并灰度化
        im = Image.open("numImage/%s/%s" % (i, f)).convert("L")
        #使用ImageData类
        z = ImageData(im)
        #获取图片网格特征向量，2代表每上下2格和左右两格为一组
        data = z.getData(2)
        X.append(data*0.1)
        Y.append(i)

X = np.array(X)
Y = np.array(Y)


#切分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, Y, test_size=0.2, random_state=1)
#对标记进行二值化
labels_train = LabelBinarizer().fit_transform(y_train)

###########构造神经网络模型################
#构建神经网络结构
nn = NeuralNetwork([14*14, 100, 10], 'logistic')
#训练模型
nn.fit(X_train, labels_train, learning_rate=0.2, epochs=60)
#保存模型
# joblib.dump(nn, 'model/nnModel.m')
#加载模型
# nn = joblib.load('model/nnModel.m')

###############数字识别####################
#存储预测结果
predictions = []
#对测试集进行预测
for i in range(y_test.shape[0]):
    out = nn.predict(X_test[i])
    predictions.append(np.argmax(out))

###############模型评测#####################
#打印预测报告
print confusion_matrix(y_test, predictions)
#打印预测结果混淆矩阵
print classification_report(y_test, predictions)

