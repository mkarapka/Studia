from django.core.management.base import BaseCommand
from lib.models import Borrow
from django.utils import timezone
import datetime


class Command(BaseCommand):
    help = "Oznacza książkę jako zwróconą"

    def add_arguments(self, parser):
        parser.add_argument("borrow_id", type=int, help="ID wypożyczenia książki")
        parser.add_argument(
            "--return_date",
            type=str,
            help="Data zwrotu (format YYYY-MM-DD)",
            default=timezone.now().strftime("%Y-%m-%d"),
        )

    def handle(self, *args, **kwargs):
        borrow_id = kwargs["borrow_id"]
        return_date = kwargs["return_date"]
        try:
            borrow = Borrow.objects.get(id=borrow_id)
            borrow.return_date = datetime.datetime.strptime(
                return_date, "%Y-%m-%d"
            ).date()
            borrow.save()
            self.stdout.write(
                self.style.SUCCESS(
                    f'Książka "{borrow.book.title}" zwrócona dnia {borrow.return_date}'
                )
            )
        except Borrow.DoesNotExist:
            self.stdout.write(
                self.style.ERROR(f"Wypożyczenie o ID {borrow_id} nie istnieje.")
            )
