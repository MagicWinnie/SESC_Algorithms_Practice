def checker(path_to_input, path_to_output):
    true_output = {}
    user_output = {}

    with open(path_to_input, 'r') as f:
        true_len = int(f.readline())
        true_inp_pts = [list(map(float, f.readline().split()))
                        for _ in range(true_len)]
    
        true_output['list'] = true_pts

    with open(path_to_output, 'r') as f:
        output_len = int(f.readline())
        output_pts = [list(map(float, f.readline().split())) for _ in range(output_len)]

        user_output['list'] = output_pts


    return user_output, true_output, False # check_arrs(output_pts, true_pts)
