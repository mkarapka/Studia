from django.core.management.base import BaseCommand
from lib.models import Friend


class Command(BaseCommand):
    help = "Wyświetla listę wszystkich książek wraz z ich ID"

    def handle(self, *args, **kwargs):
        for friend in Friend.objects.all():
            self.stdout.write(
                f"ID: {friend.id}, Imię: {friend.name}, Email: {friend.email}"
            )
