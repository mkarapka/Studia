from django.contrib import admin
from .models import Book, Friend, Borrow

# Register your models here.
admin.site.register(Book)
admin.site.register(Friend)
admin.site.register(Borrow)
