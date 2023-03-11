import polyscope as ps
import numpy as np

def make_surface( base_func, n_phi=100, n_theta=100):
    v = [] 
    for i in range(n_phi+1):
        for j in range(n_theta+1):
            theta = j * 1./n_theta
            phi = i * 1./n_phi
            v.append(base_func(theta, phi))
    v = np.array(v)

    def ij2v(i,j):
        return (i*(n_theta+1) + j)%( (n_theta+1) * (n_phi+1))

    f = []
    for i in range(n_theta):
        for j in range(n_theta):
            f.append([ij2v(i,j), ij2v(i+1,j), ij2v(i,j+1)])
            f.append([ij2v(i+1,j), ij2v(i+1,j+1),  ij2v(i,j+1)])
    f = np.array(f)

    return v, f

def bezier3(t, i):
    if   i == 0 : return (1-t)**3
    elif i == 1 : return 3*(1-t)**2*t
    elif i == 2 : return 3*t**2*(1-t)
    elif i == 3 : return t**3

def basis_func_11(t,s,a=1/np.sqrt(3), b=1/np.sqrt(2), c=1):

    x = [[ 1,-a, 0, c],     ## s
         [ 0, 0, b, 0], 
         [ 1, a, 0, c]]

    y = [[ 1, 1, 1, 0],     ## t
         [ 1, 1, 1, 1], 
         [ 2, 0, 0, 2]]

    def add(a,b):
        return [a[0]+b[0],a[1]+b[1],a[2]+b[2],a[3]+b[3]] 

    def tensor_pt(a,b):
        return [a[0]*b[0],a[1]*b[1],a[2]*b[2],a[3]*b[3]] 
    
    def prod(b,a):
        return [a[0]*b, a[1]*b, a[2]*b, a[3]*b]

    def sub(a,b):
        return [a[0]-b[0],a[1]-b[1],a[2]-b[2],a[3]-b[3]] 

    x3 = []
    x3.append(x[0])
    x3.append(add(prod(2./3.,x[1]), prod(1./3., x[0])))
    x3.append(add(prod(2./3.,x[1]), prod(1./3., x[2])))
    x3.append(x[2])
    y3 = []
    y3.append(y[0])
    y3.append(add(prod(2./3.,y[1]), prod(1./3., y[0])))
    y3.append(add(prod(2./3.,y[1]), prod(1./3., y[2])))
    y3.append(y[2])

    ret = [0, 0, 0, 0]
    for i in range(4):
        for j in range(4):
            ret = add(ret, prod( bezier3(t,i)*bezier3(s,j),  tensor_pt(x3[i], y3[j]) ))

    if ret[0] == 0: return [np.sign(ret[1])*9999,np.sign(ret[2])*9999,np.sign(ret[3])*9999]
    return [ret[1]/ret[0], ret[2]/ret[0], ret[3]/ret[0]]


def basis_func_21(t,s,a=1/np.sqrt(3), b=1/np.sqrt(2), c=1):

    x = [[ 1,-a, 0, c],     ## s
         [ 0, 0,-b, 0], 
         [ 1, a, 0, c]]

    y = [[ 1, 1, 1, 0],     ## t
         [ 1, 1, 1, 1], 
         [ 2, 0, 0, 2]]

    def add(a,b):
        return [a[0]+b[0],a[1]+b[1],a[2]+b[2],a[3]+b[3]] 
    
    def tensor_pt(a,b):
        return [a[0]*b[0],a[1]*b[1],a[2]*b[2],a[3]*b[3]] 
    
    def prod(b,a):
        return [a[0]*b, a[1]*b, a[2]*b, a[3]*b]

    def sub(a,b):
        return [a[0]-b[0],a[1]-b[1],a[2]-b[2],a[3]-b[3]] 

    x3 = []
    x3.append(x[0])
    x3.append(add(prod(2./3.,x[1]), prod(1./3., x[0])))
    x3.append(add(prod(2./3.,x[1]), prod(1./3., x[2])))
    x3.append(x[2])
    y3 = []
    y3.append(y[0])
    y3.append(add(prod(2./3.,y[1]), prod(1./3., y[0])))
    y3.append(add(prod(2./3.,y[1]), prod(1./3., y[2])))
    y3.append(y[2])


    ret = [0, 0, 0, 0]
    for i in range(4):
        for j in range(4):
            ret = add(ret, prod( bezier3(t,i)*bezier3(s,j),  tensor_pt(x3[i], y3[j]) ))

    if ret[0] == 0: return [np.sign(ret[1])*9999,np.sign(ret[2])*9999,np.sign(ret[3])*9999]
    return [ret[1]/ret[0], ret[2]/ret[0], ret[3]/ret[0]]

def basis_func_12(t,s,a=1/np.sqrt(3), b=1/np.sqrt(2), c=1):

    x = [[ 1,-a, 0, c],     ## s
         [ 0, 0, b, 0], 
         [ 1, a, 0, c]]

    y = [[ 1, 1, 1, 0],     ## t
         [ 1, 1, 1,-1], 
         [ 2, 0, 0,-2]]

    def add(a,b):
        return [a[0]+b[0],a[1]+b[1],a[2]+b[2],a[3]+b[3]] 
    
    def tensor_pt(a,b):
        return [a[0]*b[0],a[1]*b[1],a[2]*b[2],a[3]*b[3]] 
    
    def prod(b,a):
        return [a[0]*b, a[1]*b, a[2]*b, a[3]*b]

    def sub(a,b):
        return [a[0]-b[0],a[1]-b[1],a[2]-b[2],a[3]-b[3]] 

    x3 = []
    x3.append(x[0])
    x3.append(add(prod(2./3.,x[1]), prod(1./3., x[0])))
    x3.append(add(prod(2./3.,x[1]), prod(1./3., x[2])))
    x3.append(x[2])
    y3 = []
    y3.append(y[0])
    y3.append(add(prod(2./3.,y[1]), prod(1./3., y[0])))
    y3.append(add(prod(2./3.,y[1]), prod(1./3., y[2])))
    y3.append(y[2])


    ret = [0, 0, 0, 0]
    for i in range(4):
        for j in range(4):
            ret = add(ret, prod( bezier3(t,i)*bezier3(s,j),  tensor_pt(x3[i], y3[j]) ))

    if ret[0] == 0: return [np.sign(ret[1])*9999,np.sign(ret[2])*9999,np.sign(ret[3])*9999]
    return [ret[1]/ret[0], ret[2]/ret[0], ret[3]/ret[0]]

def basis_func_22(t,s,a=1/np.sqrt(3), b=1/np.sqrt(2), c=1):

    x = [[ 1,-a, 0, c],     ## s
         [ 0, 0,-b, 0], 
         [ 1, a, 0, c]]

    y = [[ 1, 1, 1, 0],     ## t
         [ 1, 1, 1,-1], 
         [ 2, 0, 0,-2]]

    def add(a,b):
        return [a[0]+b[0],a[1]+b[1],a[2]+b[2],a[3]+b[3]] 
    
    def tensor_pt(a,b):
        return [a[0]*b[0],a[1]*b[1],a[2]*b[2],a[3]*b[3]] 
    
    def prod(b,a):
        return [a[0]*b, a[1]*b, a[2]*b, a[3]*b]

    def sub(a,b):
        return [a[0]-b[0],a[1]-b[1],a[2]-b[2],a[3]-b[3]] 

    x3 = []
    x3.append(x[0])
    x3.append(add(prod(2./3.,x[1]), prod(1./3., x[0])))
    x3.append(add(prod(2./3.,x[1]), prod(1./3., x[2])))
    x3.append(x[2])
    y3 = []
    y3.append(y[0])
    y3.append(add(prod(2./3.,y[1]), prod(1./3., y[0])))
    y3.append(add(prod(2./3.,y[1]), prod(1./3., y[2])))
    y3.append(y[2])

    ret = [0, 0, 0, 0]
    for i in range(4):
        for j in range(4):
            ret = add(ret, prod( bezier3(t,i)*bezier3(s,j),  tensor_pt(x3[i], y3[j]) ))
    try:
        return [ret[1]/ret[0], ret[2]/ret[0], ret[3]/ret[0]]
    except:
        print(ret)
        return [np.sign(ret[1])*9999,np.sign(ret[2])*9999,np.sign(ret[3])*9999]

def main():
    ps.init()
    # v, f = sphere(100,100)
    v_11, f_11 = make_surface(basis_func_11)
    v_21, f_21 = make_surface(basis_func_21)
    v_12, f_12 = make_surface(basis_func_12)
    v_22, f_22 = make_surface(basis_func_22)
    ps.register_surface_mesh("Piece (+,+)",v_11,f_11)
    ps.register_surface_mesh("Piece (-,+)",v_21,f_21)
    ps.register_surface_mesh("Piece (+,-)",v_12,f_12)
    ps.register_surface_mesh("Piece (-,-)",v_22,f_22)
    ps.show()
    pass

if __name__ == "__main__":
    main()
    print("Hello World!")