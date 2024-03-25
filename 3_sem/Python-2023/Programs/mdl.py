result  = 0
def generate_sequences(k, sequence=""):
    global result
    if k == 0:
        result += 1
        print(sequence)
        return

    for digit in range(10):
        if len(sequence) < 2 or (sequence[-1] != str(digit) and sequence[-2] != str(digit)):
            generate_sequences(k - 1, sequence + str(digit))

k = 4
print(f"Wszystkie k-elementowe ciągi cyfr, gdzie cyfra na miejscu i >= 3 jest inna od cyfry na miejscu i-1 i i-2 dla k={k}:")
generate_sequences(k)
print(f"Liczba takich ciągów: {result}")