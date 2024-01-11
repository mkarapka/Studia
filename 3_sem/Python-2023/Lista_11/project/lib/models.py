from django.db import models
from django.utils import timezone
from django.core.exceptions import ValidationError

# Create your models here.
class Book(models.Model):
    author = models.CharField(max_length=100)
    title = models.CharField(max_length=100)
    year = models.IntegerField()

    def __str__(self) -> str:
        return self.title


class Friend(models.Model):
    name = models.CharField(max_length=100)
    email = models.EmailField(unique=True)

    def __str__(self) -> str:
        return self.name


class Borrow(models.Model):
    book = models.ForeignKey(Book, on_delete=models.CASCADE)
    friend = models.ForeignKey(Friend, on_delete=models.CASCADE)
    borrow_date = models.DateField(default=timezone.now)
    return_date = models.DateField(null=True)

    def clean(self):
        # Checking if book is borrowed
        if (
            self._state.adding
            and Borrow.objects.filter(book=self.book, return_date__isnull=True).exists()
        ):
            raise ValidationError(f"Książka '{self.book.title}' jest już wypożyczona.")

    def save(self, *args, **kwargs):
        if self._state.adding:
            self.clean()
        super().save(*args, **kwargs)

    def __str__(self):
        return f"{self.book.title} wypożyczona przez {self.friend.name}"
