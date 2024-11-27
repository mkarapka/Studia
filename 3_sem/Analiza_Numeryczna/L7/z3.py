from math import ceil
import matplotlib.pyplot as mpt
import numpy


# Polynomial function
polynomial = lambda arg, x_list: numpy.prod([(arg - x) for x in x_list])

# Node generating functions
node_generators = {
    "chebyshev": lambda n: numpy.cos(
        (2 * numpy.arange(1, n + 2) - 1) * numpy.pi / (2 * (n + 1))
    ),
    "equidistant": lambda n: numpy.linspace(-1, 1, n + 1),
}


def draw(start, end, in_row):
    figure, axis = mpt.subplots(ceil((end - start) / in_row), in_row)

    for n in range(start, end + 1):
        x_values = numpy.linspace(-1, 1, 1000)

        for name, generator in node_generators.items():
            y_values = [polynomial(arg, generator(n)) for arg in x_values]
            axis[(n - start) // in_row, (n - start) % in_row].plot(
                x_values,
                y_values,
                label=" ",
                linestyle="--" if name == "chebyshev" else "-",
            )

        axis[(n - start) // in_row, (n - start) % in_row].set_xlabel("x")
        axis[(n - start) // in_row, (n - start) % in_row].set_ylabel("p(x)")
        axis[(n - start) // in_row, (n - start) % in_row].set_title(
            f"Comparison for n = {n}"
        )
        figure.subplots_adjust(hspace=0.5, wspace=0.5)

    mpt.show()


draw(5, 20, 4)
