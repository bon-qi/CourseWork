import matplotlib.pyplot as plt



def b_polar(t1, t2, t3):
    a3 = t1*t2*t3
    a2 = (t1*t2 + t1*t3 + t2*t3) / 3.
    a1 = (t1 + t2 + t3) / 3.
    x = -14./3. * a2 + 34./3. * a1 - 10. / 3.
    y = 4 * a3 - 23./2. * a2 + 55./6. * a1 + 7./6.
    return (x, y)

def b(t):
    x = -14./3. * t**2 + 34./3. * t - 10. / 3.
    y = 4 * t**3 - 23./2. * t**2 + 55./6. * t + 7./6.
    return (x, y)

px = [-2, -4, 6, 4]
py = [-10, 2, 5, -7]


x = []
y = []
for i in range(100):
    tx, ty = b(i/100.)
    x.append(tx)
    y.append(ty)

x_p = []
y_p = []

tx, ty = b_polar(0,0,0)
x_p.append(tx)
y_p.append(ty)


tx, ty = b_polar(0,0,1)
x_p.append(tx)
y_p.append(ty)

tx, ty = b_polar(0,1,1)
x_p.append(tx)
y_p.append(ty)

tx, ty = b_polar(1,1,1)
x_p.append(tx)
y_p.append(ty)


plt.figure()
plt.plot(px, py)
plt.plot(x, y)
plt.show()

plt.figure()
# plt.plot(px, py)
plt.plot(x_p, y_p)
plt.plot(x, y)
plt.show()