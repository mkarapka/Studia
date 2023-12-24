# Wizualizacja cen ropy Brent w latach 2021-2023
# Strona: https://www.investing.com/commodities/brent-oil-historical-data
import csv
import matplotlib.pyplot as plt

def add_to_ys(line, ind):
    ys[ind].append(float(line[1]))
    return line[0][:5]

def predict_prices(year, year_before):
    return [sum(x) / 2 for x in zip(year, year_before)]

def print_diffs(ls1, ls2):
    month = 1
    print("Prediction error:")
    for a, b in zip(ls1, ls2):
        print(f"month:{month} -",round(abs(a - b), 2))
        month += 1

def rev_sublists(ls):
    return [x[::-1] for x in ls]

years = 3
ys = [[] for _ in range(years)]
xs = [[] for _ in range(years)]

with open("Brent_Oil_Data.csv", "r") as fs:
    csv_reader = csv.reader(fs)
    next(csv_reader)

    for i in range(years):
        xs[i] = [add_to_ys(next(csv_reader), i) for _ in range(0, 12)]

    xs = rev_sublists(xs)
    ys = rev_sublists(ys)

    fig, ax = plt.subplots()
    plt.title("The price of Brent oil per 42 gallons in the years 2021-22")
    ax.set_ylabel("USD")
    ax.set_xlabel("Following months")

    plt.plot(xs[1], ys[1], label="2022")
    plt.plot(xs[2], ys[2], label="2021")

    result = predict_prices(ys[1], ys[2])
    plt.plot(result, label="2023-prediction")
    plt.plot(xs[0], ys[0], label="2023-real")

    plt.legend()
    plt.show()
    print_diffs(result, ys[0])
