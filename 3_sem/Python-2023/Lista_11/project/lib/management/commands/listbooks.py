from django.core.management.base import BaseCommand
from lib.models import Book


class Command(BaseCommand):
    help = "Wyświetla listę wszystkich książek wraz z ich ID"
        
    def handle(self, *args, **kwargs):
        for book in Book.objects.all():
            self.stdout.write(
                f"ID: {book.id}, Tytuł: {book.title}, Autor: {book.author}, Rok: {book.year}"
            )
