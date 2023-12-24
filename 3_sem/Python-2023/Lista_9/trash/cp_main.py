import csv
import matplotlib.pyplot as plt
import numpy as np
from sklearn.linear_model import LinearRegression

def add_to_ys(line, ind):
    ys[ind].append(float(line[1]))
    return line[0][:5]


def rev(lsx, lsy, ind):
    return lsx[ind][::-1], lsy[ind][::-1]


def predict_prices(year, year_before):
    x = np.array(year_before).reshape(-1, 1)
    y = np.array(year)

    model = LinearRegression()
    model.fit(x, y)

    next_year = np.array(year).reshape(-1, 1)

    return model.predict(next_year)


def predict_prices_1(year, year_before):
    return [sum(x) / 2 for x in zip(year, year_before)]

def print_diffs(ls1, ls2, ls3):
    print("Błędy prognozy: ")
    for a, b, c in zip(ls1, ls2, ls3):
        rs = round(abs(a - c),2)
        rs1 = round(abs(b - c),2)
        print(f"Regresja liniowa: {rs}, Prognoza średnia: {rs1}")
    
years = 3
ys = [[] for _ in range(years)]
xs = [[] for _ in range(years)]

with open("Brent_Oil_Data_2.csv", "r") as fs:
    csv_reader = csv.reader(fs)

    next(csv_reader)

    for i in range(years):
        xs[i] = [add_to_ys(next(csv_reader), i) for line in range(0, 12)]

    fig, ax = plt.subplots()
    plt.title("Cena ropy Brent za 42 galony w latach 2021-22")
    ax.set_ylabel("USD")
    ax.set_xlabel("Kolejne miesiące")

    plt.plot(*rev(xs, ys, 1), label="2022")
    plt.plot(*rev(xs, ys, 2), label="2021")

    result = predict_prices(*rev(ys, ["", ys[2]], 1))
    res2 = predict_prices_1(*rev(ys, ["", ys[2]], 1))
    plt.plot(result, label="2023-prognoza")
    plt.plot(res2, label="2023-prognoza-średnia")
    plt.plot(*rev(xs, ys, 0), label="2023-rzeczywiście")
    plt.legend()
    plt.show()
    print_diffs(result, res2, ys[0])
    
