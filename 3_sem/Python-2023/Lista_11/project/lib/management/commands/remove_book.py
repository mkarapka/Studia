from django.core.management.base import BaseCommand
from lib.models import Book


class Command(BaseCommand):
    help = "Usuwa książkę z bazy danych na podstawie ID"

    def add_arguments(self, parser):
        parser.add_argument("book_id", type=int, help="ID książki do usunięcia")

    def handle(self, *args, **kwargs):
        book_id = kwargs["book_id"]
        try:
            book = Book.objects.get(id=book_id)
            book.delete()
            self.stdout.write(
                self.style.SUCCESS(f"Książka o ID {book_id} została usunięta.")
            )
        except Book.DoesNotExist:
            self.stdout.write(self.style.ERROR(f"Książka o ID {book_id} nie istnieje."))
