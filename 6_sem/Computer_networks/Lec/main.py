from random_q_and_a import Memo
import random
import time

m_2013 = Memo(2013, "user_answers_2013")
m_2019 = Memo(2019, "user_anwers_2019")
memos = (m_2013, m_2019)

select_year = input("Wybierz rok: 1 - 2013, 2 - 2019")

if '1' in select_year:
    m_2013.main()
elif '2' in select_year:
    m_2019.main()
else:
    print("Chuj masz losowe")
    m_rand = random.choice(memos)
    time.sleep(0.5)
    print("tiriri")
    time.sleep(0.5)
    print("tralala")
    time.sleep(0.5)
    print(m_rand.year, "i chuj")
    time.sleep(0.5)
    m_rand.main()
