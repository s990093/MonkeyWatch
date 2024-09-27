from django.contrib import admin
from .models import CompletionStatus, Task, DailyTask, WeeklyTask

@admin.register(CompletionStatus)
class CompletionStatusAdmin(admin.ModelAdmin):
    list_display = ('time', 'desc')
    search_fields = ('desc',)
    ordering = ('-time',)

@admin.register(Task)
class TaskAdmin(admin.ModelAdmin):
    list_display = ('name', 'time')
    search_fields = ('name',)
    ordering = ('-time',)

@admin.register(DailyTask)
class DailyTaskAdmin(admin.ModelAdmin):
    list_display = ('name', 'task_type', 'completion_status')
    search_fields = ('name',)
    list_filter = ('task_type',)
    ordering = ('-time',)

@admin.register(WeeklyTask)
class WeeklyTaskAdmin(admin.ModelAdmin):
    list_display = ('task', 'day_of_week')
    search_fields = ('task__name',)
    list_filter = ('day_of_week',)
    ordering = ('task', 'day_of_week')

