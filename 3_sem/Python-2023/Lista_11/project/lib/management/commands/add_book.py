from django.core.management.base import BaseCommand
from lib.models import Book


class Command(BaseCommand):
    help = "Adds a book to the library"

    def add_arguments(self, parser):
        parser.add_argument("author", type=str)
        parser.add_argument("title", type=str)
        parser.add_argument("year", type=int)

    def handle(self, *args, **kwargs):
        author = kwargs["author"]
        title = kwargs["title"]
        year = kwargs["year"]
        Book.objects.create(author=author, title=title, year=year)
        self.stdout.write(self.style.SUCCESS(f"Book {title} added successfully"))
