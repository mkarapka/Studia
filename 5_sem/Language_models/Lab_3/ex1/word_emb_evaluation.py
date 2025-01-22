# -*- encoding: utf8 -*-

from collections import defaultdict as dd
import numpy as np
import random
import sys


def benchmark(CLUSTERED_TEXT, CALCULATED_EMBEDINGS):

    # CLUSTERED_TEXT = "clustered_text.txt"

    with open(CLUSTERED_TEXT, "r", encoding="utf-8") as file:
        clusters_txt = file.read()

    # słownik [słowo]: np.array(znormalizowane floaty)
    vectors = {}

    def best(w, K):
        v = vectors[w]

        L = sorted([(v.dot(vectors[w]), w) for w in vectors])
        L.reverse()

        return L[:K]

    # name = 'word_embedings_file.txt'

    for x in open(CALCULATED_EMBEDINGS):
        L = x.split()
        if len(L) < 2:
            continue
        w = L[0]
        values = [float(x) for x in L[1:]]
        v = np.array(values)
        length = v.dot(v) ** 0.5
        vectors[w] = v / length

    C = {}

    def choose_another(A, a):
        while True:
            b = random.choice(A)
            if a != b:
                return b

    # zbiór wszystkich słów
    words = set()

    for x in clusters_txt.split("\n"):
        L = x.split()
        if len(L) < 2:
            continue
        C[L[0]] = L[1:]
        words.update(L[1:])

    # kategorie słów
    groups = list(C.keys())

    score = 0.0
    N = 30000
    N = 500000

    bad = all_words = 0.0
    # bad to kategorie, których nie ma w wektorach osadzeń, które badamy
    for w in words:
        if not w in vectors:
            # print (w, end=' ')
            bad += 1
        all_words += 1

    print("PROBLEMS:", bad / all_words)

    print("Start ABX tests")
    for i in range(N):
        # wybierz kategorię słowa
        g1 = random.choice(groups)
        # wybierz wyrazy z tej kategorii
        A = C[g1]
        # wybierz słowa z innej kategorii niż A należą
        B = C[choose_another(groups, g1)]

        # wybierz dwa różne słowa ze słów należących do kategorii A
        a1 = random.choice(A)
        a2 = choose_another(A, a1)
        # wybierz dowolne słowo z tej drugiej kategorii
        b = random.choice(B)

        # print (a1,a2,b)
        # jak nie policzyliśmy embedingu dla któregoś z tych słów, dostajemy 0.5 pkt
        if not a1 in vectors or not a2 in vectors or not b in vectors:
            score += 0.5
            # print (a1,a2,b)
            continue

        va1 = vectors[a1]
        va2 = vectors[a2]
        vb = vectors[b]

        # test ABX
        if va1.dot(va2) > va1.dot(vb):
            score += 1.0
        else:
            pass
            # print (a1,a2,'--',b)

    print("TOTAL SCORE:", score / N)
