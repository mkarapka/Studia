from django.core.management.base import BaseCommand


class Command(BaseCommand):
    help = "Opis tego, co robi to polecenie."

    def handle(self, *args, **kwargs):
        self.stdout.write(
            """
add_book - Dodaje książkę do biblioteki, 
wywołanie: add_book <tytuł> <autor> <rok>

add_friend - Dodaje znajomego do biblioteki,
wywołanie: add_friend <imię> <email>

borrow - Wypożycza książkę znajomemu,
wywołanie: borrow <id książki> <id znajomego>

listbooks - Wyświetla listę wszystkich książek wraz z ich ID,
wywołanie: listbooks

listborrows - Wyświetla listę wszystkich wypożyczeń wraz z ich ID,
wywołanie: listborrows

listfriends - Wyświetla listę wszystkich znajomych wraz z ich ID,
wywołanie: listfriends

remove_book - Usuwa książkę z biblioteki,
wywołanie: remove_book <id książki>

return - Oznacza książkę jako zwróconą,
wywołanie: return <id wypożyczenia>
    """
        )
