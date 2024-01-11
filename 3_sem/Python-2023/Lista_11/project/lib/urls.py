from django.urls import path
from . import views

urlpatterns = [
    path("", views.home, name="home"),
    path("books/", views.show_books, name="show_books"),
    path("friends/", views.show_friends, name="show_friends"),
    path("borrows/", views.show_borrows, name="show_borrows"),
]
