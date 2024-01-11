from django.core.management.base import BaseCommand
from lib.models import Borrow


class Command(BaseCommand):
    help = "Wyświetla listę wszystkich książek wraz z ich ID"

    def handle(self, *args, **kwargs):
        for borrow in Borrow.objects.all():
            self.stdout.write(
                f"ID: {borrow.id}, Imię: {borrow.book}, Email: {borrow.friend}, borrow_date: {borrow.borrow_date}, return_date: {borrow.return_date}"
            )
