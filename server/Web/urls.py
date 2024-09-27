from django.urls import path
from . import views

app_name = "Web"

from django.urls import path
from . import views

urlpatterns = [
    path('weekly-tasks/', views.WeeklyTaskView.as_view(), name='weekly-task-list'),
    path('tasks/<int:pk>/complete/', views.TaskCompletionUpdateView.as_view(), name='task-complete-update'),
]