#1 导入相关的库函数
from  skimage  import io,color
import dlib
from  skimage.feature import  hog
import matplotlib.pyplot as plt
#2 导入图片，简化处理
image=io.imread("eg.png")
image=color.rgb2gray(image)
#3 计算HOG   pixels 像素   cells 方格   block 区间
array,hog_image=hog(image,visualise=True)
#4 可视化，作图
fig,(ax1,ax2)=plt.subplots(1,2,figsize=(8,4))
ax1.imshow(image,cmap=plt.cm.gray)
ax2.imshow(hog_image,cmap=plt.cm.gray)
plt.show()