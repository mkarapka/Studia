import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.datasets import make_classification
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

# Step 1: Generate Synthetic Dataset
X, y = make_classification(
    n_samples=500,
    n_features=4,
    n_informative=2,
    n_redundant=0,
    n_classes=2,
    random_state=42,
)

# Pairplot to visualize relationships
sns.pairplot(
    data=sns.load_dataset("iris"),
    vars=["sepal_length", "sepal_width", "petal_length", "petal_width"],
    hue="species",
)
plt.show()

# Step 2: Train-Test Split
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.3, random_state=42
)

# Apply Logistic Regression (no regularization)
model = LogisticRegression(penalty="none", solver="lbfgs", max_iter=1000)
model.fit(X_train, y_train)
y_pred = model.predict(X_test)

# Measure accuracy
accuracy = accuracy_score(y_test, y_pred)
print(f"Accuracy without regularization: {accuracy:.2f}")

# Step 3: Add Regularization (L1 and L2)
# L1 Regularization
model_l1 = LogisticRegression(penalty="l1", solver="liblinear", max_iter=1000, C=1.0)
model_l1.fit(X_train, y_train)
l1_accuracy = accuracy_score(y_test, model_l1.predict(X_test))
print(f"Accuracy with L1 regularization: {l1_accuracy:.2f}")

# L2 Regularization
model_l2 = LogisticRegression(penalty="l2", solver="lbfgs", max_iter=1000, C=1.0)
model_l2.fit(X_train, y_train)
l2_accuracy = accuracy_score(y_test, model_l2.predict(X_test))
print(f"Accuracy with L2 regularization: {l2_accuracy:.2f}")

# Step 4: Features Selected by L1 Regularization
l1_coefficients = model_l1.coef_[0]
selected_features = np.where(l1_coefficients != 0)[0]
print(f"Features selected by L1 regularization: {selected_features}")

# Plot Decision Boundary for Selected Features
if len(selected_features) == 2:
    feature_1, feature_2 = selected_features

    plt.figure(figsize=(8, 6))
    x_min, x_max = X[:, feature_1].min() - 1, X[:, feature_1].max() + 1
    y_min, y_max = X[:, feature_2].min() - 1, X[:, feature_2].max() + 1
    xx, yy = np.meshgrid(np.arange(x_min, x_max, 0.1), np.arange(y_min, y_max, 0.1))
    Z = model_l1.predict(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)
    plt.contourf(xx, yy, Z, alpha=0.8)
    plt.scatter(X[:, feature_1], X[:, feature_2], c=y, edgecolor="k", marker="o")
    plt.xlabel(f"Feature {feature_1}")
    plt.ylabel(f"Feature {feature_2}")
    plt.title("Decision Boundary for Selected Features (L1)")
    plt.show()
else:
    print(
        "L1 regularization did not select exactly two features, decision boundary cannot be plotted."
    )
