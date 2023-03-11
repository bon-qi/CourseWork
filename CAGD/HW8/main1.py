import matplotlib.pyplot as plt
import numpy as np

## 对向量做归一化
def normalize(v):
    return v / (np.dot(v,v)**0.5)

## 视角投影，对两个点构成的线段
def proj_line(p1,p2, camera):

    ## 得到相对方向
    v1 = p1 - camera["position"]
    v2 = p2 - camera["position"]

    fx = camera["fx"]
    fy = camera["fy"]

    ## 获得相机坐标的方向
    orientation = normalize(camera["lookat"] - camera["position"])
    direction1 =  normalize(camera["headup"])
    direction2 = np.cross(orientation, direction1)

    ## 获得相机坐标
    p1x = np.dot(v1, direction1)
    p1y = np.dot(v1, direction2)
    p1z = np.dot(v1, orientation)

    p2x = np.dot(v2, direction1)
    p2y = np.dot(v2, direction2)
    p2z = np.dot(v2, orientation)

    ## render!
    plt.plot([p1x/p1z/fx, p2x/p2z/fx],[p1y/p1z/fy, p2y/p2z/fy])

## 垂直投影，对两个点构成的线段
def orth_line(p1,p2, camera):
    ## 获得物体在相机下的坐标
    v1 = p1 - camera["position"]
    v2 = p2 - camera["position"]

    fx = camera["fx"]
    fy = camera["fy"]

    ## 获得相机坐标的单位方向
    orientation = normalize(camera["lookat"] - camera["position"])
    direction1 = normalize(camera["headup"])
    direction2 = np.cross(orientation, direction1)

    ## 得到物体的坐标
    p1x = np.dot(v1, direction1)
    p1y = np.dot(v1, direction2)
    p1z = np.dot(v1, orientation)

    p2x = np.dot(v2, direction1)
    p2y = np.dot(v2, direction2)
    p2z = np.dot(v2, orientation)

    ## render！
    plt.plot([p1x/fx, p2x/fx],[p1y/fy, p2y/fy])

def orth(v, l, camera):
    plt.figure()
    ## 将每一条线render出来
    for l_ in l:
        orth_line(v[l_[0],:], v[l_[1],:], camera)
    plt.show()

def proj(v, l, camera):
    plt.figure()
    ## 将每一条线render出来
    for l_ in l:
        proj_line(v[l_[0],:], v[l_[1],:], camera)
    plt.show()



def main(d, center, camera):
    ## 设置单位正方形
    ## 顶点位置
    v = np.array([
        [0,0,0], [1,0,0], [1,1,0], [0,1,0],
        [0,0,1], [1,0,1], [1,1,1], [0,1,1],
    ],dtype=np.float32)
    ## 边的关系
    l = [[0,1],[2,1],[2,3],[3,0],
         [4,5],[5,6],[6,7],[7,4],
         [0,4],[1,5],[2,6],[3,7]]
    ## 中心坐标
    x_0 = np.array([1./2., 1./2., 1./2.], dtype=np.float32)
    ## 根据用户指定变化
    v = center + (v - x_0)*d/0.5
    ## render！
    proj(v, l, camera)
    pass

if __name__ == "__main__":
    ## 设置相机内外参数
    camera = {
        "position" :    np.array([-10,0,0],dtype=np.float32),
        "lookat" :      np.array([0,0,0], dtype=np.float32),
        "headup":       np.array([0,1,0], dtype=np.float32),
        "fx": 1,
        "fy": 1    }

    print("Camera parameters (you can edit it in source code): ")
    print( camera ) 

    try:    ## 用户交互提示
        KeyError("aaa")
        d = input("size(1): ")
        x = input("center.x(0): ")
        y = input("center.y(0): ")
        z = input("center.z(0): ")
        d = np.array([d], dtype=np.float32)
        center = np.array([x,y,z], dtype=np.float32)
    except: ## 如果用户交互的结果有问题，就用一个默认的。。。
        d = np.array([0.5], dtype=np.float32)
        center = np.array([0,0,0], dtype=np.float32)
        print("Type error! Using d = 0.5, center = (0,0,0)")

    main(d, center, camera)
















