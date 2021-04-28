import numpy as np
from scipy.spatial import ConvexHull


def check_arrs(pts_1, pts_2, err=10e-9):
    if len(pts_1) != len(pts_2):
        return False
    for i in range(len(pts_1)):
        if (abs(pts_1[i][0] - pts_2[i][0]) > err) or (abs(pts_1[i][1] - pts_2[i][1]) > err):
            return False
    return True


def checker(path_to_input, path_to_output):
    true_output = {}
    user_output = {}

    with open(path_to_input, 'r') as f:
        true_len = int(f.readline())
        true_inp_pts = [list(map(float, f.readline().split()))
                        for _ in range(true_len)]

    true_pts = ConvexHull(true_inp_pts).vertices
    true_pts = [true_inp_pts[x] for x in true_pts]
    true_pts += [true_pts[0]]
    if isinstance(true_pts, np.ndarray):
        true_pts = true_pts.tolist()
    
    true_pts = true_pts[:-1]

    true_pts = [true_inp_pts.index(x) + 1 for x in true_pts]

    with open(path_to_output, 'r') as f:
        t = float(f.readline())
        output_len = int(f.readline())
        # output_pts = [list(map(float, f.readline().split())) for _ in range(output_len)]
        output_pts = [int(f.readline()) for _ in range(output_len)]

        user_output['list'] = output_pts

    true_output['list'] = true_pts
    print(t)
    return user_output, true_output, output_pts == true_pts
