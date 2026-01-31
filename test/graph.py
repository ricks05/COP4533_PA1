import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("..\\data\\matching_data.csv")

plt.figure(figsize=(8, 5))
plt.plot(df["n"], df["T(n)"])
plt.xlabel("n")
plt.ylabel("T (ns)")
plt.title("Matching: Execution Time (T) vs Input Size (n)")

plt.show()


df = pd.read_csv("..\\data\\verifying_data.csv")

plt.figure(figsize=(8, 5))
plt.plot(df["n"], df["T(n)"])
plt.xlabel("n")
plt.ylabel("T (microns)")
plt.title("Verifying: Execution Time (T) vs Input Size (n)")

plt.show()
