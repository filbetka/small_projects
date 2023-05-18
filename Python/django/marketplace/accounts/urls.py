from django.urls import path

from . import views

app_name = 'accounts'

urlpatterns = [
    path('sign-up', views.sign_up, name='sign-up'),
    path('sign-in', views.sign_in, name='sign-in'),
]
