import matplotlib.pyplot as plt
import nifs as spline


def mult_minus_one(lst):
    return [-1 * number for number in lst]


def return_spline_points(x_points, y_points, t, u):
    y_points = mult_minus_one(y_points)
    sx = spline.NIFS3(t, x_points).result()
    sy = spline.NIFS3(t, y_points).result()

    return [sx(uk) for uk in u], [sy(uk) for uk in u]


def parse_list(lst):
    result = []
    for number in lst:
        number = number.strip()
        if number[-1] == "]":
            number = number[:-1]
        result.append(float(number))
    return result


def parse_data(file_path):
    def append_to_dict(key, sub_key, value):
        parsed_data[key][sub_key] = value

    with open(file_path, "r") as file:
        data = file.readlines()

    parsed_data = {}
    current_key = None
    note = ["x", "y", "t", "u"]
    index = 0
    for line in data:
        if line.startswith("#"):
            current_key = line.strip()[1:]
            parsed_data[current_key] = {"x": [], "y": [], "t": [], "u": []}
        else:
            values_str = line.strip("]\n").split("[")
            vals_cut = values_str[1:]
            if len(vals_cut) > 0 and vals_cut[0] != "#":
                res = vals_cut[0].split(", ")
                parsed = parse_list(res)
                append_to_dict(current_key, note[index], parsed)
                index += 1
                index %= 4

    return parsed_data


file_path = "splines.txt"
parsed_data = parse_data(file_path)

fig, ax = plt.subplots(figsize=(24, 2))
for key in parsed_data:
    x = parsed_data[key]["x"]
    y = parsed_data[key]["y"]
    t = parsed_data[key]["t"]
    u = parsed_data[key]["u"]
    sx, sy = return_spline_points(x, y, t, u)
    ax.plot(sx, sy, "r-", linewidth=3)
plt.show()
