from  sklearn.neighbors  import  KNeighborsClassifier
#X 输入     Y 输出
X=[[1.5,40],[1.6,51],[1.5,49],[1.7,60],[1.8,70],[1.8,75],[1.55,55],[1.77,63]]
Y=[1,1,1,0,0,0,1,0]
neigh=KNeighborsClassifier(n_neighbors=1)
neigh.fit(X,Y)
print(neigh.predict([[1.5,35]]))


#求距离
from sklearn.neighbors import  NearestNeighbors
s=[[0,0,0],[1,2,3],[3,4,5],[4,5,6]]
neigh_2=NearestNeighbors(n_neighbors=1)
neigh_2.fit(s)
p=[[0,0.5,0],[3,6,5]]
print(neigh_2.kneighbors(p))