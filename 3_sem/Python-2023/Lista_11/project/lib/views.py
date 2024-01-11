from django.shortcuts import render
from .models import Book, Borrow, Friend

# Create your views here.


def home(request):
    return render(request, "home.html")


def show_books(request):
    books = Book.objects.all()
    return render(request, "show_books.html", {"books": books})


def show_borrows(request):
    borrows = Borrow.objects.all()
    return render(request, "show_borrows.html", {"borrows": borrows})


def show_friends(request):
    friends = Friend.objects.all()
    return render(request, "show_friends.html", {"friends": friends})
