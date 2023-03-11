import matplotlib.pyplot as plt
import FTBS
import FTCS
import LaxW 

def Draw_Same(way1, way2, way3):
    plt.figure("FTBS(blue), FTCS(red), LaxW(greens), t(0.05), dt(0.01)")
    plt.plot(way1.x0, way1.fx0)
    plt.plot(way2.x0, way2.fx0)
    plt.plot(way3.x0, way3.fx0)
    plt.show()

    plt.figure("FTBS(blue), FTCS(red), LaxW(greens), t(0.05), dt(0.04)")
    plt.plot(way1.x1, way1.fx1)
    plt.plot(way2.x1, way2.fx1)
    plt.plot(way3.x1, way3.fx1)
    plt.show()

    plt.figure("FTCS(blue), LaxW(red), t(0.20), dt(0.01)")
    # plt.plot(way1.x2, way1.fx2)
    plt.plot(way2.x2, way2.fx2)
    plt.plot(way3.x2, way3.fx2)
    plt.show()

    plt.figure("FTCS(blue), LaxW(red),, t(0.20), dt(0.04)")
    # plt.plot(way1.x3, way1.fx3)
    plt.plot(way2.x3, way2.fx3)
    plt.plot(way3.x3, way3.fx3)
    plt.show()

    plt.figure("FTCS(blue), LaxW(red),, t(0.80), dt(0.01)")
    # plt.plot(way1.x4, way1.fx4)
    plt.plot(way2.x4, way2.fx4)
    plt.plot(way3.x4, way3.fx4)
    plt.show()

    plt.figure("FTCS(blue), LaxW(red), t(0.80), dt(0.04)")
    # plt.plot(way1.x5, way1.fx5)
    # plt.plot(way2.x5, way2.fx5)
    plt.plot(way3.x5, way3.fx5)
    plt.show()
    
    plt.figure("FTCS(blue), LaxW(red),, t(3.20), dt(0.01)")
    # plt.plot(way1.x6, way1.fx6)
    # plt.plot(way2.x6, way2.fx6)
    plt.plot(way3.x6, way3.fx6)
    plt.show()
    
    plt.figure("FTCS(blue), LaxW(red),, t(3.20), dt(0.04)")
    # plt.plot(way1.x7, way1.fx7)
    # plt.plot(way2.x7, way2.fx7)
    plt.plot(way3.x7, way3.fx7)
    plt.show()
    pass

def Draw(file, name):
    plt.figure(name+"t=0.05,dt: 0.01(blue) vs 0.04(red)")
    plt.plot(file.x0, file.fx0)
    plt.plot(file.x1, file.fx1)
    plt.show()

    plt.figure(name+"t=0.20,dt: 0.01(blue) vs 0.04(red)")
    plt.plot(file.x2, file.fx2)
    plt.plot(file.x3, file.fx3)
    plt.show()

    plt.figure(name+"t=0.80,dt: 0.01(blue) vs 0.04(red)")
    plt.plot(file.x4, file.fx4)
    plt.plot(file.x5, file.fx5)
    plt.show()

    plt.figure(name+"t=3.20,dt: 0.01(blue) vs 0.04(red)")
    plt.plot(file.x6, file.fx6)
    plt.plot(file.x7, file.fx7)
    plt.show()

if __name__ == "__main__":
    Draw_Same(FTBS, FTCS, LaxW)
    # Draw(FTBS, "FTBS, ")
    # Draw(FTCS, "FTCS, ")
    # Draw(LaxW, "LaxW, ")
