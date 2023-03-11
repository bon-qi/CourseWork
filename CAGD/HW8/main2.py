import matplotlib.pyplot as plt
import numpy as np

## 将投影到平面
def homo2card(x):
    n_pts, dim = x.shape
    return x[:,:-1]/np.repeat(x[:,-1],dim-1).reshape([-1,dim-1])

## 画二维曲线
def plot2d(pts):
    plt.plot(pts[:,0], pts[:,1])

## 画三维曲线
def plot3d(pts):
    plt.plot(pts[:,0], pts[:,1], pts[:,2])

## 对椭圆的画图
def prob_elip(a=2, b=1):
    pts_pos = np.array([[0,b,1],[2*a,0,0],[0,-b,1]], dtype=np.float32)
    pts_neg = np.array([[0,b,1],[-2*a,0,0],[0,-b,1]], dtype=np.float32)
    
    curve_pos = np.zeros([100, 3])
    curve_neg = np.zeros([100, 3])

    for i in range(100):
        t = i/99.
        curve_pos[i,:] = pts_pos[0,:]*(1-t)**2 + pts_pos[1,:]*t*(1-t) + pts_pos[2,:]*t**2
        curve_neg[i,:] = pts_neg[0,:]*(1-t)**2 + pts_neg[1,:]*t*(1-t) + pts_neg[2,:]*t**2

    fig = plt.figure()
    ax = fig.add_subplot(projection="3d")
    plot3d(curve_pos)
    plot3d(curve_neg)
    plt.show()

    plt.figure()
    plot2d(homo2card(curve_pos))    
    plot2d(homo2card(curve_neg))
    plt.show()

## 对双曲线的画图
def prob_hyperb(a=2, b=1):
    ## 需要的参数点
    pts_pos = np.array([[a,0,1],[0,2*b,0],[a,0,-1]], dtype=np.float32)
    pts_neg = np.array([[a,0,1],[0,-2*b,0],[a,0,-1]], dtype=np.float32)
    ## 结果的接受区
    curve_pos = np.zeros([100, 3])
    curve_neg = np.zeros([100, 3])

    for i in range(100):
        t = i/99.
        curve_pos[i,:] = pts_pos[0,:]*(1-t)**2 + pts_pos[1,:]*t*(1-t) + pts_pos[2,:]*t**2
        curve_neg[i,:] = pts_neg[0,:]*(1-t)**2 + pts_neg[1,:]*t*(1-t) + pts_neg[2,:]*t**2

    fig = plt.figure()
    ax = fig.add_subplot(projection="3d")
    plot3d(curve_pos)
    plot3d(curve_neg)
    plt.show()


    plt.figure()
    plot2d(homo2card(curve_pos))    
    plot2d(homo2card(curve_neg))
    plt.show()


if __name__ == "__main__":
    a = input("Input a: ")
    b = input("Input b: ")
    prob_elip(a,b)
    prob_hyperb(a,b)