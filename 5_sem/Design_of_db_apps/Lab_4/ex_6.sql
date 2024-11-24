/*
READ UNCOMMITTED:
Pozwala na odczytanie danych, które mogą być zmieniane przez inne transakcje, 
nawet jeśli nie zostały jeszcze zatwierdzone. Może prowadzić do brudnych odczytów.

READ COMMITTED (domyślny):
Pozwala na odczytanie tylko zatwierdzonych (commitowanych) danych. 
Zapobiega brudnym odczytom, ale nie eliminuje innych problemów, takich jak non-repeatable reads.

REPEATABLE READ:
Zapewnia, że dane, które zostały odczytane, nie będą zmieniane przez inne transakcje w trakcie trwania bieżącej transakcji.
Zapobiega non-repeatable reads, ale może pozwolić na phantom reads (wstawienie nowych wierszy przez inne transakcje).

SERIALIZABLE:
Najwyższy poziom izolacji. Zapewnia pełną izolację, 
uniemożliwiając jakiekolwiek zmiany w odczytywanych danych
lub wstawianie nowych danych w obszarze odczytu przez inne transakcje. 
Zapobiega wszystkim problemom związanym z równoczesnymi transakcjami.
*/
--SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
--SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
--SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;

BEGIN TRANSACTION;

-- Odczytujemy transakcje bez żadnych blokad, dzięki temu transakcje nie będą blokowane przez inne transakcje
SELECT *
FROM TableName WITH (NOLOCK);

COMMIT TRANSACTION;