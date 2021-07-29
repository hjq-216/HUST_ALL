import mglearn
import  matplotlib.pyplot as plt
import  numpy as np
#有这样的训练集，比如通过体重和身高来判断一个人的性别是男还是女
#X输入 ：身高、体重    Y输出：男（0） 女（1）
X=np.array([[1.5,40],[1.6,51],[1.5,49],[1.7,60],[1.8,70],[1.8,75],[1.55,55],[1.77,63]])
Y=np.array([1,1,1,0,0,0,1,0])
#对数据集进行作图
mglearn.discrete_scatter(X[:, 0], X[:, 1], Y)
plt.legend(["Man","Women"],loc=1)
plt.xlabel("Height")
plt.ylabel("Weight")
plt.show()