import numpy as np

def check_collision(bot1, bot2):
    a1, b1, c1 = bot1
    a2, b2, c2 = bot2
    mass1 = np.array([[a1, b1],[a2, b2]])
    mass2 = np.array([-c1, -c2])
    if np.linalg.matrix_rank(mass1) == 2:
        res1, res2 = np.linalg.solve(mass1, mass2)
        return np.round(res1, 2), np.round(res2,2)
    return None

def check_surface(point1, point2, point3):
    x1, y1, z1 = point1
    x2, y2, z2 = point2
    x3, y3, z3 = point3
    mass1 = np.array([[x1, y1, 1], [x2, y2, 1], [x3, y3, 1]])
    mass2 = np.array([z1, z2, z3])
    if np.linalg.matrix_rank(mass1) == len(mass1):
        res = np.linalg.solve(mass1, mass2)
        return np.round(res, 2)
    return None

def check_rotation(vec, rad):
    matrat = np.array([[np.cos(rad), -np.sin(rad), 0], [np.sin(rad), np.cos(rad), 0], [0, 0, 1]])
    res = np.dot(matrat, vec)
    return np.round(res, 2)
