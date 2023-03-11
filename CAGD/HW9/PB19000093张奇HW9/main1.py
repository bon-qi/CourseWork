import polyscope as ps
import numpy as np

def sphere(n_phi, n_theta):
    v = [] 
    for i in range(n_phi+1):
        for j in range(n_theta+1):
            theta = j * 1./n_theta * np.pi - np.pi/2
            phi = i * 1./n_phi * np.pi * 2
            v.append([np.cos(theta) * np.cos(phi), np.cos(theta) * np.sin(phi), np.sin(theta)])
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

def bezier2(t, i):
    if   i == 0 : return (1-t)**2
    elif i == 1 : return 2*(1-t)*t
    elif i == 2 : return t**2

def basis_func_11(t,s):

    x = [[ 1,-1, 0, 1],     ## s
         [ 0, 0, 1, 0], 
         [ 1, 1, 0, 1]]

    y = [[ 1, 1, 1, 0],     ## t
         [ 1, 1, 1, 1], 
         [ 2, 0, 0, 2]]

    def add(a,b):
        return [a[0]+b[0],a[1]+b[1],a[2]+b[2],a[3]+b[3]] 
    
    def tensor_pt(a,b):
        return [a[0]*b[0],a[1]*b[1],a[2]*b[2],a[3]*b[3]] 
    
    def prod(b,a):
        return [a[0]*b, a[1]*b, a[2]*b, a[3]*b]

    ret = [0, 0, 0, 0]
    for i in range(3):
        for j in range(3):
            ret = add(ret, prod( bezier2(t,i)*bezier2(s,j),  tensor_pt(x[i], y[j]) ))

    return [ret[1]/ret[0], ret[2]/ret[0], ret[3]/ret[0]]


def basis_func_21(t,s):

    x = [[ 1,-1, 0, 1],     ## s
         [ 0, 0,-1, 0], 
         [ 1, 1, 0, 1]]

    y = [[ 1, 1, 1, 0],     ## t
         [ 1, 1, 1, 1], 
         [ 2, 0, 0, 2]]

    def add(a,b):
        return [a[0]+b[0],a[1]+b[1],a[2]+b[2],a[3]+b[3]] 
    
    def tensor_pt(a,b):
        return [a[0]*b[0],a[1]*b[1],a[2]*b[2],a[3]*b[3]] 
    
    def prod(b,a):
        return [a[0]*b, a[1]*b, a[2]*b, a[3]*b]

    ret = [0, 0, 0, 0]
    for i in range(3):
        for j in range(3):
            ret = add(ret, prod( bezier2(t,i)*bezier2(s,j),  tensor_pt(x[i], y[j]) ))

    return [ret[1]/ret[0], ret[2]/ret[0], ret[3]/ret[0]]

def basis_func_12(t,s):

    x = [[ 1,-1, 0, 1],     ## s
         [ 0, 0, 1, 0], 
         [ 1, 1, 0, 1]]

    y = [[ 1, 1, 1, 0],     ## t
         [ 1, 1, 1,-1], 
         [ 2, 0, 0,-2]]

    def add(a,b):
        return [a[0]+b[0],a[1]+b[1],a[2]+b[2],a[3]+b[3]] 
    
    def tensor_pt(a,b):
        return [a[0]*b[0],a[1]*b[1],a[2]*b[2],a[3]*b[3]] 
    
    def prod(b,a):
        return [a[0]*b, a[1]*b, a[2]*b, a[3]*b]

    ret = [0, 0, 0, 0]
    for i in range(3):
        for j in range(3):
            ret = add(ret, prod( bezier2(t,i)*bezier2(s,j),  tensor_pt(x[i], y[j]) ))

    return [ret[1]/ret[0], ret[2]/ret[0], ret[3]/ret[0]]

def basis_func_22(t,s):

    x = [[ 1,-1, 0, 1],     ## s
         [ 0, 0,-1, 0], 
         [ 1, 1, 0, 1]]

    y = [[ 1, 1, 1, 0],     ## t
         [ 1, 1, 1,-1], 
         [ 2, 0, 0,-2]]

    def add(a,b):
        return [a[0]+b[0],a[1]+b[1],a[2]+b[2],a[3]+b[3]] 
    
    def tensor_pt(a,b):
        return [a[0]*b[0],a[1]*b[1],a[2]*b[2],a[3]*b[3]] 
    
    def prod(b,a):
        return [a[0]*b, a[1]*b, a[2]*b, a[3]*b]

    ret = [0, 0, 0, 0]
    for i in range(3):
        for j in range(3):
            ret = add(ret, prod( bezier2(t,i)*bezier2(s,j),  tensor_pt(x[i], y[j]) ))

    return [ret[1]/ret[0], ret[2]/ret[0], ret[3]/ret[0]]

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