# Import libraries
import numpy as np
import pandas as pd
from sklearn.datasets import make_classification
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split


class LogisticRegression:
    def __init__(self, learning_rate, epochs):
        self.learning_rate = learning_rate
        self.epochs = epochs

    def sigmoid(self, x_i: np.array, β: np.array):
        return 1.0 / (1.0 + np.exp(-np.dot(x_i, β)))

    def log_likelihood(self, x: np.array, y: np.array, β: np.array):
        s_x = self.sigmoid(x, β)  # Liczy sigmoid dla wszystkich przykładów jednocześnie
        s_x = np.clip(s_x, 1e-15, 1 - 1e-15)  # Ograniczenie dla stabilności numerycznej
        return np.sum(y * np.log(s_x) + (1 - y) * np.log(1 - s_x))

    # def log_likelihood(x: np.array, y: np.array, β: np.array):
    #     def log_p(y_i: np.array, x_i: np.array):
    #         s_x = sigmoid(x_i, β)
    #         return (y_i) * np.log(s_x) + (1 - y_i) * np.log(1 - s_x)
    #     return sum([log_p(y_i, x_i) for x_i, y_i in zip(x, y)])

    def fit_CGA(self, y_test, x_test):
        β = np.random.random(x_test.shape[1])

        losses = []
        for epoch in range(self.epochs):
            x_i, y_i = x[epoch % x.shape[0]], y[epoch % y.shape[0]]

            for j in range(β.shape[0]):
                y_pred = self.sigmoid(x_i, β)

                β[j] = β[j] + self.learning_rate * (y_i - y_pred) * x_i[j]

            loss = -1 * self.log_likelihood(x_test, y_test, β)
            losses.append(loss)
        return β, losses


log_reg = LogisticRegression(0.01, 100)
x, y = make_classification(
    n_samples=100, n_features=2, n_informative=2, n_redundant=0, n_clusters_per_class=1
)

β, losses = log_reg.fit_CGA(y, x)
plt.plot(losses)
plt.title("Loss over time")
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.show()
