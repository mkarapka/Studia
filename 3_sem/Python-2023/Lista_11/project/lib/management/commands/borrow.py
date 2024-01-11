from django.core.management.base import BaseCommand, CommandError
from lib.models import Book, Friend, Borrow
from django.core.exceptions import ValidationError


class Command(BaseCommand):
    help = "Wypożycza książkę znajomemu"

    def add_arguments(self, parser):
        # Adding arguments ID of book and ID of friend
        parser.add_argument("book_id", type=int, help="ID książki do wypożyczenia")
        parser.add_argument(
            "friend_id", type=int, help="ID znajomego, który wypożycza książkę"
        )

    def handle(self, *args, **kwargs):
        book_id = kwargs["book_id"]
        friend_id = kwargs["friend_id"]

        # Checking if book and friend exist
        try:
            book = Book.objects.get(id=book_id)
        except Book.DoesNotExist:
            raise CommandError(f"Książka o ID {book_id} nie istnieje.")

        try:
            friend = Friend.objects.get(id=friend_id)
        except Friend.DoesNotExist:
            raise CommandError(f"Znajomy o ID {friend_id} nie istnieje.")

        # Creating new borrow
        try:
            borrow = Borrow(book=book, friend=friend)
            # Validation (e.g. if book is not already borrowed)
            borrow.clean()  
            borrow.save()
            self.stdout.write(
                self.style.SUCCESS(
                    f'Książka "{book.title}" została wypożyczona znajomemu {friend.name}.'
                )
            )
        except ValidationError as e:
            raise CommandError(e)
